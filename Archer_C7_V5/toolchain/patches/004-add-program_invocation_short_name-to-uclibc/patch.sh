for file in `find . -maxdepth 1`;
do
	[ "$file" != "./patch.sh" -a "$file" != "." ] && {
	cp -drf $file ../../gcc-4.3.3/build_mips/staging_dir/usr/mips-linux-uclibc/lib/
	}
done
