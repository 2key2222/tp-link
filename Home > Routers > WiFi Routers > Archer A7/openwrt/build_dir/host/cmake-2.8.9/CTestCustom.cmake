SET(CTEST_CUSTOM_ERROR_MATCH
  ${CTEST_CUSTOM_ERROR_MATCH}
  "ERROR:")

SET(CTEST_CUSTOM_WARNING_EXCEPTION
  ${CTEST_CUSTOM_WARNING_EXCEPTION}
  "xtree.[0-9]+. : warning C4702: unreachable code"
  "warning LNK4221"
  "warning LNK4204" # Occurs by race condition with objects in small libs
  "variable .var_args[2]*. is used before its value is set"
  "jobserver unavailable"
  "warning: \\(Long double usage is reported only once for each file"
  "warning: To disable this warning use"
  "could not be inlined"
  "libcmcurl.*has no symbols"
  "not sorted slower link editing will result"
  "stl_deque.h:479"
  "Utilities.cmzlib."
  "Utilities.cmbzip2."
  "Source.CTest.Curl"
  "Source.CursesDialog.form"
  "Utilities.cmcurl"
  "Utilities.cmexpat."
  "Utilities.cmlibarchive"
  "/usr/include.*warning.*shadowed declaration is here"
  "/usr/bin/ld.*warning.*-..*directory.name.*bin.*does not exist"
  "Redeclaration of .send..... with a different storage class specifier"
  "is not used for resolving any symbol"
  "Clock skew detected"
  "remark\\(1209"
  "remark: .*LOOP WAS VECTORIZED"
  "warning .980: wrong number of actual arguments to intrinsic function .std::basic_"
  "LINK : warning LNK4089: all references to.*ADVAPI32.dll.*discarded by /OPT:REF"
  "LINK : warning LNK4089: all references to.*USER32.dll.*discarded by /OPT:REF"
  "Warning: library was too large for page size.*"
  "Warning: public.*_archive_.*in module.*archive_*clashes with prior module.*archive_.*"
  "Warning: public.*BZ2_bz.*in module.*bzlib.*clashes with prior module.*bzlib.*"
  "Warning: public.*_archive.*clashes with prior module.*"
  "Warning: LINN32: Last line.*is less.*"
  "warning.*directory name.*CMake-Xcode.*/bin/.*does not exist.*"
  "stl_deque.h:1051"
  "(Lexer|Parser).*warning.*conversion.*may (alter its value|change the sign)"
  "(Lexer|Parser).*warning.*statement is unreachable"
  "PGC-W-0095-Type cast required for this conversion.*ProcessUNIX.c"
  "[Qq]t([Cc]ore|[Gg]ui).*warning.*conversion.*may alter its value"
  "warning:.*is.*very unsafe.*consider using.*"
  "warning:.*is.*misused, please use.*"
  "CMakeSetupManifest.xml.*manifest authoring warning.*Unrecognized Element"
  "cc-3968 CC: WARNING File.*" # "implicit" truncation by static_cast
  "ld: warning: directory not found for option .-(F|L)"
  "warning.*This version of Mac OS X is unsupported"
  "clang.*: warning: argument unused during compilation: .-g"

  # Ignore clang's summary warning, assuming prior text has matched some
  # other warning expression:
  "[0-9,]+ warnings? generated."
  )

IF(NOT "Unix Makefiles" MATCHES "Xcode")
  SET(CTEST_CUSTOM_COVERAGE_EXCLUDE
    ${CTEST_CUSTOM_COVERAGE_EXCLUDE}
    "XCode"
    )
ENDIF (NOT "Unix Makefiles" MATCHES "Xcode")

IF(NOT "Unix Makefiles" MATCHES "KDevelop")
  SET(CTEST_CUSTOM_COVERAGE_EXCLUDE
    ${CTEST_CUSTOM_COVERAGE_EXCLUDE}
    "Kdevelop"
    )
ENDIF (NOT "Unix Makefiles" MATCHES "KDevelop")

SET(CTEST_CUSTOM_COVERAGE_EXCLUDE
  ${CTEST_CUSTOM_COVERAGE_EXCLUDE}

  # Exclude kwsys files from coverage results. They are reported
  # (with better coverage results) on kwsys dashboards...
  "/Source/(cm|kw)sys/"

  # Exclude try_compile sources from coverage results:
  "/CMakeFiles/CMakeTmp/"

  # Exclude Qt source files from coverage results:
  "[A-Za-z]./[Qq]t/qt-.+-opensource-src"
  )
