#!/bin/sh
# Tests for pkg-config compliance.
# * Copyright (c) 2012 Michał Górny <mgorny@gentoo.org>.

done=0
failed=0

run_test() {
	local res t_ret 2>/dev/null || true
	local cmdline 2>/dev/null || true

	cmdline="${1}"

	eval res="\$(${1})" 2>/dev/null

	t_ret=0
	while [ ${#} -gt 1 ]; do
		shift

		case "${res}" in
			*"${1}"*)
				;;
			*)
				echo
				echo "***********************"
				echo "!!! Test $done failed."
				echo "!!! $ ${cmdline}"
				echo "!!! ${res}"
				echo "!!! expected '${1}' in output"
				echo "***********************"
				t_ret=1
				;;
		esac
	done

	if [ ${t_ret} -eq 0 ]; then
		echo -n "."
	else
		failed=$(( failed + 1 ))
	fi
	done=$(( done + 1 ))
}

selfdir=$(cd "$(dirname "${0}")"; pwd | sed s#/c/#c:/#)

PATH_SEP=":"
SYSROOT_DIR="${selfdir}/test"
if [ "$(uname -o)" = "Msys" ]; then
	PATH_SEP=";"
fi

# 1) overall 'is it working?' test
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1}; echo \$?" \
	'1'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --libs foo" \
	'-lfoo'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --cflags --libs foo" \
	'-lfoo' '-I/usr/include/foo' '-fPIC'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --cflags --libs 'foo > 1.2'" \
	'-lfoo' '-I/usr/include/foo' '-fPIC'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --cflags --libs 'foo > 1.2 bar >= 1.3'" \
	'-lfoo' '-I/usr/include/foo' '-fPIC'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --cflags --libs 'foo' '>' '1.2'" \
	'-lfoo' '-I/usr/include/foo' '-fPIC'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --exists nonexistant; echo \$?" \
	'1'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} nonexistant; echo \$?" \
	'1'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --exists 'foo > 1.2'; echo \$?" \
	'0'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --exists 'foo > 1.2.3'; echo \$?" \
	'1'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --exists 'foo' '>' '1.2'; echo \$?" \
	'0'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --uninstalled 'foo'; echo \$?" \
	'1'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --uninstalled 'omg'; echo \$?" \
	'0'
run_test "${1} --modversion ${selfdir}/lib1/foo.pc" \
	'1.2.3'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --exists 'foo >= '; echo \$?" \
	'1'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --exists 'tilde <= 1.0.0'; echo \$?" \
	'1'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --exists 'tilde = 1.0.0~rc1'; echo \$?" \
	'0'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --exists 'tilde >= 1.0.0'; echo \$?" \
	'0'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --exists '' 'foo'; echo \$?" \
	'0'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --libs intermediary-1 intermediary-2" \
	'-lintermediary-1 -lintermediary-2 -lfoo -lbar -lbaz'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --libs circular-1" \
	'-lcircular-1 -lcircular-2 -lcircular-3'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --libs circular-3" \
	'-lcircular-3 -lcircular-1 -lcircular-2'
run_test "${1} --libs ${selfdir}/lib1/circular-3.pc" \
	'-lcircular-1 -lcircular-2 -lcircular-3'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --libs static-archive-libs" \
	'/libfoo.a -pthread'

# 2) tests for PKG_CONFIG_PATH order
run_test "PKG_CONFIG_PATH='${selfdir}/lib1${PATH_SEP}${selfdir}/lib2' ${1} --libs foo" \
	'-lfoo'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1${PATH_SEP}${selfdir}/lib2' ${1} --libs bar" \
	'-lbar'

# 3) tests for 'Requires' and 'Requires.private'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --libs bar" \
	'-lfoo' '-lbar'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --libs --cflags baz" \
	'-lbaz' '-fPIC' '-I/usr/include/foo'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --static --libs baz" \
	'-lfoo' '-lbaz' '-lzee'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --static --libs argv-parse-2" \
	'-pthread '
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --static --cflags baz" \
	'-fPIC' '-I/usr/include/foo' '-DFOO_STATIC'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --static --libs-only-l private-libs-duplication" \
	'-lprivate -lfoo -lbaz -lzee -lbar -lfoo'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --static --libs static-libs" \
	'-lbar -lbar-private -lfoo'

# 4) tests for parser bugs
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --libs dos-lineendings" \
	'-L/usr/lib/dos-lineendings -ldos-lineendings'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --cflags no-trailing-newline" \
	'-I/usr/include/no-trailing-newline'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --libs argv-parse" \
	'-llib-2 -lpthread'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --exists -foo; echo \$?" \
	'1'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --libs argv-parse-3" \
	'-llib-1'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --libs tilde-quoting" \
	'-L~'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --cflags tilde-quoting" \
	'-I~'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --libs paren-quoting" \
	'-L$(libdir)'

# 5) tests for other regressions
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --variable=includedir foo" \
	'/usr/include'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --libs-only-L --keep-system-libs cflags-libs-only" \
	'-L/usr/local/lib'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --libs cflags-libs-only" \
	'-L/usr/local/lib -lfoo'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --libs-only-L --libs-only-l cflags-libs-only" \
	'-L/usr/local/lib -lfoo'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --cflags-only-I --cflags-only-other cflags-libs-only" \
	'-I/usr/local/include'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --libs incomplete; echo $?" \
	'0'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --cflags incomplete" \
	' '
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --libs incomplete" \
	' '

# 6) tests for builtins
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --modversion pkg-config" \
	'0.28'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --variable=prefix foo" \
	'/usr'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --define-variable=prefix=/test --variable=prefix foo" \
	'/test'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --variable=pcfiledir foo" \
	"${selfdir}/lib1"

# 7) tests for env modifiers
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' PKG_CONFIG_SYSROOT_DIR='${SYSROOT_DIR}' ${1} --cflags baz" \
	"-I${SYSROOT_DIR}/usr/include/foo"
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' PKG_CONFIG_SYSROOT_DIR='${SYSROOT_DIR}' ${1} --variable=prefix baz" \
	"${SYSROOT_DIR}/usr"
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' PKG_CONFIG_SYSROOT_DIR='${SYSROOT_DIR}' ${1} --variable=includedir baz" \
	"${SYSROOT_DIR}/usr/include"

# 8) tests for 'Conflicts'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --libs conflicts; echo \$?" \
	'0'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --ignore-conflicts --libs conflicts; echo \$?" \
	'-lconflicts' '0'

# 9) tests for --atleast-version (with and without trailing space)
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --atleast-version 1.0 foo; echo \$?" \
	'0'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --atleast-version 2.0 foo; echo \$?" \
	'1'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --exact-version 1.0 foo; echo \$?" \
	'1'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --exact-version 1.2.3 foo; echo \$?" \
	'0'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --max-version 1.0 foo; echo \$?" \
	'1'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --max-version 2.0 foo; echo \$?" \
	'0'

#    tests for issue #20
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --atleast-version 1.0 'foo '; echo \$?" \
	'0'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --atleast-version 2.0 'foo '; echo \$?" \
	'1'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --exact-version 1.0 'foo '; echo \$?" \
	'1'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --exact-version 1.2.3 'foo '; echo \$?" \
	'0'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --max-version 1.0 'foo '; echo \$?" \
	'1'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --max-version 2.0 'foo '; echo \$?" \
	'0'

# test missing requires
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --cflags missing-require; echo \$?" \
	'1'

# test the multiline description field
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --list-all | grep -q 'multiline description'; echo \$?" \
	'0'

# test quoted #35
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --cflags quotes" \
	"-DQUOTED=\\\"bla\\\""

run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --libs nolib; echo \$?" \
	'0'

run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --libs nocflag; echo \$?" \
	'0'

# test 36 - running against file in CWD with no path
# File moved to CWD to allow arbitrary path to pkgconf and keep pc file in CWD
run_test "cp ${selfdir}/lib1/foo.pc . && ${1} --libs foo.pc; rm -f foo.pc" \
	'-lfoo'

# test 47 - framework flags
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --libs framework-1" \
	"-F/usr/lib -framework framework-1"
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --libs framework-2" \
	"-F/usr/lib -framework framework-2 -framework framework-1"
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --libs framework-1 framework-2" \
	"-F/usr/lib -framework framework-1 -framework framework-2"

run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --exists --print-errors 'foo > 0.6.0 foo < 0.8.0'; echo \$?" \
	'1'

run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --exists --print-errors 'nonexisting foo <= 3'; echo \$?" \
	'1'

run_test "PKG_CONFIG_PATH='${selfdir}/lib2' ${1} ${selfdir}/lib3/bar.pc --cflags" \
	'-fPIC -I/usr/include/foo'

run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --variable=foo case-sensitivity" \
	"3"
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --variable=Foo case-sensitivity" \
	"4"

run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --libs comments-in-fields" \
	"-lfoo"

run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --libs comments" \
	"-lfoo"

run_test "PKG_CONFIG_PATH='${selfdir}/lib1' PKG_CONFIG_SYSROOT_DIR='/sysroot' ${1} --libs sysroot-dir" \
	'-L/sysroot/lib -lfoo'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' PKG_CONFIG_SYSROOT_DIR='/sysroot2' ${1} --libs sysroot-dir" \
	'-L/sysroot2/sysroot/lib -lfoo'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --libs prefix-foo1" \
	'-L/usr/bar/lib -lfoo1'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --libs prefix-foo1 prefix-foo2" \
	'-L/usr/bar/lib -lfoo1 -lfoo2'
run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --cflags prefix-foo1 prefix-foo2" \
	'-I/usr/bar/include/foo -DBAR -fPIC -DFOO'

# 10) tests for internal getopt implementation with options at the end
if [ "xno" = "xno" ]; then
	run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} foo --libs" \
		'-lfoo'
	run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} foo --cflags --libs" \
		'-lfoo' '-I/usr/include/foo' '-fPIC'
	run_test "PKG_CONFIG_PATH='${selfdir}/lib1' ${1} --cflags foo --libs" \
		'-lfoo' '-I/usr/include/foo' '-fPIC'
fi

run_test "${1} --blah; echo \$?" \
	'1'

echo

if [ ${failed} -gt 0 ]; then
	echo "${failed} of ${done} tests failed. See output for details." >&2
	exit 1
else
	echo "${done} tests done. All succeeded." >&2
	exit 0
fi
