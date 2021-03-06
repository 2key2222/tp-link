/* config.h.  Generated from config.in by configure.  */
/* config.in.  Generated from configure.ac by autoheader.  */

/* Define if the compiler is building for multiple architectures of Apple
   platforms at once. */
/* #undef AA_APPLE_UNIVERSAL_BUILD */

/* Define if building universal (internal helper macro) */
/* #undef AC_APPLE_UNIVERSAL_BUILD */

/* Define to the number of bits in type 'ptrdiff_t'. */
/* #undef BITSIZEOF_PTRDIFF_T */

/* Define to the number of bits in type 'sig_atomic_t'. */
/* #undef BITSIZEOF_SIG_ATOMIC_T */

/* Define to the number of bits in type 'size_t'. */
/* #undef BITSIZEOF_SIZE_T */

/* Define to the number of bits in type 'wchar_t'. */
/* #undef BITSIZEOF_WCHAR_T */

/* Define to the number of bits in type 'wint_t'. */
/* #undef BITSIZEOF_WINT_T */

/* Define to 1 if the compiler supports long long. */
#define CC_HAS_LONG_LONG 1

/* Define to one of `_getb67', `GETB67', `getb67' for Cray-2 and Cray-YMP
   systems. This function is required for `alloca.c' support on those systems.
   */
/* #undef CRAY_STACKSEG_END */

/* Define to 1 if using `alloca.c'. */
/* #undef C_ALLOCA */

/* look for global separate debug info in this path [LIBDIR/debug] */
#define DEBUGDIR "/home/ubuntu/Archer_C7_V5/openwrt/staging_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/lib/debug"

/* Define if the separate-debug-dir directory should be relocated when GDB is
   moved. */
#define DEBUGDIR_RELOCATABLE 1

/* Define to BFD's default architecture. */
#define DEFAULT_BFD_ARCH bfd_mips_arch

/* Define to BFD's default target vector. */
#define DEFAULT_BFD_VEC bfd_elf32_tradbigmips_vec

/* Define to 1 if translation of program messages to the user's native
   language is requested. */
/* #undef ENABLE_NLS */

/* look for global separate data files in this path [DATADIR/gdb] */
#define GDB_DATADIR "/home/ubuntu/Archer_C7_V5/openwrt/staging_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/share/gdb"

/* Define if the gdb-datadir directory should be relocated when GDB is moved.
   */
#define GDB_DATADIR_RELOCATABLE 1

/* Define to be a string naming the default host character set. */
#define GDB_DEFAULT_HOST_CHARSET "UTF-8"

/* Host double floatformat */
#define GDB_HOST_DOUBLE_FORMAT &floatformat_ieee_double_little

/* Host float floatformat */
#define GDB_HOST_FLOAT_FORMAT &floatformat_ieee_single_little

/* Host long double floatformat */
#define GDB_HOST_LONG_DOUBLE_FORMAT &floatformat_i387_ext

/* nativefile */
/* #undef GDB_NM_FILE */

/* Define to the default OS ABI for this configuration. */
#define GDB_OSABI_DEFAULT GDB_OSABI_LINUX

/* Define to 1 when the gnulib module memchr should be tested. */
#define GNULIB_TEST_MEMCHR 1

/* Define to 1 when the gnulib module memmem should be tested. */
#define GNULIB_TEST_MEMMEM 1

/* Define to 1 if you have `alloca', as a function or macro. */
#define HAVE_ALLOCA 1

/* Define to 1 if you have <alloca.h> and it should be used (not on Ultrix).
   */
#define HAVE_ALLOCA_H 1

/* Define to 1 if you have the <bp-sym.h> header file. */
/* #undef HAVE_BP_SYM_H */

/* Define to 1 if you have the `btowc' function. */
#define HAVE_BTOWC 1

/* Define to 1 if you have the `canonicalize_file_name' function. */
#define HAVE_CANONICALIZE_FILE_NAME 1

/* Define to 1 if you have the <ctype.h> header file. */
#define HAVE_CTYPE_H 1

/* Define to 1 if you have the <cursesX.h> header file. */
/* #undef HAVE_CURSESX_H */

/* Define to 1 if you have the <curses.h> header file. */
#define HAVE_CURSES_H 1

/* Define to 1 if you have the declaration of `ADDR_NO_RANDOMIZE', and to 0 if
   you don't. */
#define HAVE_DECL_ADDR_NO_RANDOMIZE 1

/* Define to 1 if you have the declaration of `free', and to 0 if you don't.
   */
#define HAVE_DECL_FREE 1

/* Define to 1 if you have the declaration of `getopt', and to 0 if you don't.
   */
#define HAVE_DECL_GETOPT 1

/* Define to 1 if you have the declaration of `malloc', and to 0 if you don't.
   */
#define HAVE_DECL_MALLOC 1

/* Define to 1 if you have the declaration of `memmem', and to 0 if you don't.
   */
#define HAVE_DECL_MEMMEM 1

/* Define to 1 if you have the declaration of `ptrace', and to 0 if you don't.
   */
#define HAVE_DECL_PTRACE 1

/* Define to 1 if you have the declaration of `realloc', and to 0 if you
   don't. */
#define HAVE_DECL_REALLOC 1

/* Define to 1 if you have the declaration of `snprintf', and to 0 if you
   don't. */
#define HAVE_DECL_SNPRINTF 1

/* Define to 1 if you have the declaration of `strerror', and to 0 if you
   don't. */
#define HAVE_DECL_STRERROR 1

/* Define to 1 if you have the declaration of `strstr', and to 0 if you don't.
   */
#define HAVE_DECL_STRSTR 1

/* Define to 1 if you have the declaration of `vsnprintf', and to 0 if you
   don't. */
#define HAVE_DECL_VSNPRINTF 1

/* Define to 1 if you have the <dirent.h> header file, and it defines `DIR'.
   */
#define HAVE_DIRENT_H 1

/* Define if ELF support should be included. */
#define HAVE_ELF 1

/* Define to 1 if you have the <elf_hp.h> header file. */
/* #undef HAVE_ELF_HP_H */

/* Define to 1 if your system has the etext variable. */
#define HAVE_ETEXT 1

/* Define to 1 if you have the `fork' function. */
#define HAVE_FORK 1

/* Define if <sys/procfs.h> has fpregset_t. */
/* #undef HAVE_FPREGSET_T */

/* Define to 1 if you have the `getgid' function. */
#define HAVE_GETGID 1

/* Define to 1 if you have the `getpagesize' function. */
#define HAVE_GETPAGESIZE 1

/* Define to 1 if you have the `getrlimit' function. */
#define HAVE_GETRLIMIT 1

/* Define to 1 if you have the `getrusage' function. */
#define HAVE_GETRUSAGE 1

/* Define to 1 if you have the `getuid' function. */
#define HAVE_GETUID 1

/* Define to 1 if you have the <gnu/libc-version.h> header file. */
#define HAVE_GNU_LIBC_VERSION_H 1

/* Define if <sys/procfs.h> has gregset_t. */
/* #undef HAVE_GREGSET_T */

/* Define if you have HPUX threads */
/* #undef HAVE_HPUX_THREAD_SUPPORT */

/* Define if you have the iconv() function. */
#define HAVE_ICONV 1

/* Define to 1 if you have the `iconvlist' function. */
/* #undef HAVE_ICONVLIST */

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define if you have <langinfo.h> and nl_langinfo(CODESET). */
#define HAVE_LANGINFO_CODESET 1

/* Define if your <locale.h> file defines LC_MESSAGES. */
#define HAVE_LC_MESSAGES 1

/* Define to 1 if you have the `dl' library (-ldl). */
/* #undef HAVE_LIBDL */

/* Define if you have the expat library. */
/* #undef HAVE_LIBEXPAT */

/* Define to 1 if you have the `libiconvlist' function. */
/* #undef HAVE_LIBICONVLIST */

/* Define to 1 if you have the `m' library (-lm). */
#define HAVE_LIBM 1

/* Define if Python 2.4 is being used. */
/* #undef HAVE_LIBPYTHON2_4 */

/* Define if Python 2.5 is being used. */
/* #undef HAVE_LIBPYTHON2_5 */

/* Define if Python 2.6 is being used. */
/* #undef HAVE_LIBPYTHON2_6 */

/* Define if Python 2.7 is being used. */
/* #undef HAVE_LIBPYTHON2_7 */

/* Define if libunwind library is being used. */
/* #undef HAVE_LIBUNWIND */

/* Define to 1 if you have the <libunwind.h> header file. */
/* #undef HAVE_LIBUNWIND_H */

/* Define to 1 if you have the <libunwind-ia64.h> header file. */
/* #undef HAVE_LIBUNWIND_IA64_H */

/* Define to 1 if you have the `w' library (-lw). */
/* #undef HAVE_LIBW */

/* Define to 1 if you have the <link.h> header file. */
#define HAVE_LINK_H 1

/* Define to 1 if you have the <locale.h> header file. */
#define HAVE_LOCALE_H 1

/* Define to 1 if the compiler supports long double. */
#define HAVE_LONG_DOUBLE 1

/* Define to 1 if the system has the type `long long int'. */
#define HAVE_LONG_LONG_INT 1

/* Define if <sys/procfs.h> has lwpid_t. */
#define HAVE_LWPID_T 1

/* Define to 1 if you have the <machine/reg.h> header file. */
/* #undef HAVE_MACHINE_REG_H */

/* Define to 1 if mmap()'s MAP_ANONYMOUS flag is available after including
   config.h and <sys/mman.h>. */
#define HAVE_MAP_ANONYMOUS 1

/* Define to 1 if you have the `memchr' function. */
#define HAVE_MEMCHR 1

/* Define to 1 if you have the `memmem' function. */
#define HAVE_MEMMEM 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have a working `mmap' system call. */
#define HAVE_MMAP 1

/* Define to 1 if you have the `monstartup' function. */
#define HAVE_MONSTARTUP 1

/* Define to 1 if you have the `mprotect' function. */
#define HAVE_MPROTECT 1

/* Define to 1 if you have the <ncurses.h> header file. */
#define HAVE_NCURSES_H 1

/* Define to 1 if you have the <ncurses/ncurses.h> header file. */
/* #undef HAVE_NCURSES_NCURSES_H */

/* Define to 1 if you have the <ncurses/term.h> header file. */
/* #undef HAVE_NCURSES_TERM_H */

/* Define to 1 if you have the <ndir.h> header file, and it defines `DIR'. */
/* #undef HAVE_NDIR_H */

/* Define to 1 if you have the <nlist.h> header file. */
/* #undef HAVE_NLIST_H */

/* Define if you support the personality syscall. */
#define HAVE_PERSONALITY 1

/* Define to 1 if you have the `pipe' function. */
#define HAVE_PIPE 1

/* Define to 1 if you have the `poll' function. */
#define HAVE_POLL 1

/* Define to 1 if you have the <poll.h> header file. */
#define HAVE_POLL_H 1

/* Define to 1 if you have the `posix_madvise' function. */
#define HAVE_POSIX_MADVISE 1

/* Define to 1 if you have the `pread64' function. */
#define HAVE_PREAD64 1

/* Define if <sys/procfs.h> has prfpregset32_t. */
/* #undef HAVE_PRFPREGSET32_T */

/* Define if <sys/procfs.h> has prfpregset_t. */
#define HAVE_PRFPREGSET_T 1

/* Define if <sys/procfs.h> has prgregset32_t. */
/* #undef HAVE_PRGREGSET32_T */

/* Define if <sys/procfs.h> has prgregset_t. */
#define HAVE_PRGREGSET_T 1

/* Define if ioctl argument PIOCSET is available. */
/* #undef HAVE_PROCFS_PIOCSET */

/* Define to 1 if you have the <proc_service.h> header file. */
/* #undef HAVE_PROC_SERVICE_H */

/* Define if <sys/procfs.h> has prrun_t. */
/* #undef HAVE_PRRUN_T */

/* Define if <sys/procfs.h> has prsysent_t. */
/* #undef HAVE_PRSYSENT_T */

/* Define if <sys/procfs.h> has pr_sigaction64_t. */
/* #undef HAVE_PR_SIGACTION64_T */

/* Define if <sys/procfs.h> has pr_siginfo64_t. */
/* #undef HAVE_PR_SIGINFO64_T */

/* Define if <sys/procfs.h> has pr_sigset_t. */
/* #undef HAVE_PR_SIGSET_T */

/* Define if <sys/procfs.h> has psaddr_t. */
#define HAVE_PSADDR_T 1

/* Define if <sys/procfs.h> has pstatus_t. */
/* #undef HAVE_PSTATUS_T */

/* Define if sys/ptrace.h defines the PTRACE_GETFPXREGS request. */
#define HAVE_PTRACE_GETFPXREGS 1

/* Define if sys/ptrace.h defines the PTRACE_GETREGS request. */
#define HAVE_PTRACE_GETREGS 1

/* Define to 1 if you have the <ptrace.h> header file. */
/* #undef HAVE_PTRACE_H */

/* Define if sys/ptrace.h defines the PT_GETDBREGS request. */
/* #undef HAVE_PT_GETDBREGS */

/* Define if sys/ptrace.h defines the PT_GETXMMREGS request. */
/* #undef HAVE_PT_GETXMMREGS */

/* Define if Python interpreter is being linked in. */
/* #undef HAVE_PYTHON */

/* Define to 1 if btowc is declared even after undefining macros. */
#define HAVE_RAW_DECL_BTOWC 1

/* Define to 1 if mbrlen is declared even after undefining macros. */
#define HAVE_RAW_DECL_MBRLEN 1

/* Define to 1 if mbrtowc is declared even after undefining macros. */
#define HAVE_RAW_DECL_MBRTOWC 1

/* Define to 1 if mbsinit is declared even after undefining macros. */
#define HAVE_RAW_DECL_MBSINIT 1

/* Define to 1 if mbsnrtowcs is declared even after undefining macros. */
#define HAVE_RAW_DECL_MBSNRTOWCS 1

/* Define to 1 if mbsrtowcs is declared even after undefining macros. */
#define HAVE_RAW_DECL_MBSRTOWCS 1

/* Define to 1 if memmem is declared even after undefining macros. */
#define HAVE_RAW_DECL_MEMMEM 1

/* Define to 1 if mempcpy is declared even after undefining macros. */
#define HAVE_RAW_DECL_MEMPCPY 1

/* Define to 1 if memrchr is declared even after undefining macros. */
#define HAVE_RAW_DECL_MEMRCHR 1

/* Define to 1 if rawmemchr is declared even after undefining macros. */
#define HAVE_RAW_DECL_RAWMEMCHR 1

/* Define to 1 if stpcpy is declared even after undefining macros. */
#define HAVE_RAW_DECL_STPCPY 1

/* Define to 1 if stpncpy is declared even after undefining macros. */
#define HAVE_RAW_DECL_STPNCPY 1

/* Define to 1 if strcasestr is declared even after undefining macros. */
#define HAVE_RAW_DECL_STRCASESTR 1

/* Define to 1 if strchrnul is declared even after undefining macros. */
#define HAVE_RAW_DECL_STRCHRNUL 1

/* Define to 1 if strdup is declared even after undefining macros. */
#define HAVE_RAW_DECL_STRDUP 1

/* Define to 1 if strncat is declared even after undefining macros. */
#define HAVE_RAW_DECL_STRNCAT 1

/* Define to 1 if strndup is declared even after undefining macros. */
#define HAVE_RAW_DECL_STRNDUP 1

/* Define to 1 if strnlen is declared even after undefining macros. */
#define HAVE_RAW_DECL_STRNLEN 1

/* Define to 1 if strpbrk is declared even after undefining macros. */
#define HAVE_RAW_DECL_STRPBRK 1

/* Define to 1 if strsep is declared even after undefining macros. */
#define HAVE_RAW_DECL_STRSEP 1

/* Define to 1 if strsignal is declared even after undefining macros. */
#define HAVE_RAW_DECL_STRSIGNAL 1

/* Define to 1 if strtok_r is declared even after undefining macros. */
#define HAVE_RAW_DECL_STRTOK_R 1

/* Define to 1 if strverscmp is declared even after undefining macros. */
#define HAVE_RAW_DECL_STRVERSCMP 1

/* Define to 1 if wcrtomb is declared even after undefining macros. */
#define HAVE_RAW_DECL_WCRTOMB 1

/* Define to 1 if wcsnrtombs is declared even after undefining macros. */
#define HAVE_RAW_DECL_WCSNRTOMBS 1

/* Define to 1 if wcsrtombs is declared even after undefining macros. */
#define HAVE_RAW_DECL_WCSRTOMBS 1

/* Define to 1 if wctob is declared even after undefining macros. */
#define HAVE_RAW_DECL_WCTOB 1

/* Define to 1 if wcwidth is declared even after undefining macros. */
#define HAVE_RAW_DECL_WCWIDTH 1

/* Define to 1 if you have the `realpath' function. */
#define HAVE_REALPATH 1

/* Define to 1 if you have the `sbrk' function. */
#define HAVE_SBRK 1

/* Define to 1 if you have the `setlocale' function. */
#define HAVE_SETLOCALE 1

/* Define to 1 if you have the `setpgid' function. */
#define HAVE_SETPGID 1

/* Define to 1 if you have the `setpgrp' function. */
#define HAVE_SETPGRP 1

/* Define to 1 if you have the `setrlimit' function. */
#define HAVE_SETRLIMIT 1

/* Define to 1 if you have the `setsid' function. */
#define HAVE_SETSID 1

/* Define to 1 if you have the <sgtty.h> header file. */
#define HAVE_SGTTY_H 1

/* Define to 1 if you have the `sigaction' function. */
#define HAVE_SIGACTION 1

/* Define to 1 if you have the <signal.h> header file. */
#define HAVE_SIGNAL_H 1

/* Define to 1 if 'sig_atomic_t' is a signed integer type. */
/* #undef HAVE_SIGNED_SIG_ATOMIC_T */

/* Define to 1 if 'wchar_t' is a signed integer type. */
/* #undef HAVE_SIGNED_WCHAR_T */

/* Define to 1 if 'wint_t' is a signed integer type. */
/* #undef HAVE_SIGNED_WINT_T */

/* Define to 1 if you have the `sigprocmask' function. */
#define HAVE_SIGPROCMASK 1

/* Define if sigsetjmp is available. */
#define HAVE_SIGSETJMP 1

/* Define to 1 if you have the `sigsetmask' function. */
#define HAVE_SIGSETMASK 1

/* Define to 1 if you have the `socketpair' function. */
#define HAVE_SOCKETPAIR 1

/* Define to 1 if the system has the type `socklen_t'. */
#define HAVE_SOCKLEN_T 1

/* Define to 1 if you have the <stddef.h> header file. */
#define HAVE_STDDEF_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define if <sys/link.h> has struct link_map32 */
/* #undef HAVE_STRUCT_LINK_MAP32 */

/* Define if <link.h> exists and defines struct link_map which has members
   with an ``lm_'' prefix. (For SunOS.) */
/* #undef HAVE_STRUCT_LINK_MAP_WITH_LM_MEMBERS */

/* Define if <link.h> exists and defines struct link_map which has members
   with an ``l_'' prefix. (For Solaris, SVR4, and SVR4-like systems.) */
/* #undef HAVE_STRUCT_LINK_MAP_WITH_L_MEMBERS */

/* Define to 1 if your system has struct lwp. */
/* #undef HAVE_STRUCT_LWP */

/* Define to 1 if your system has struct reg in <machine/reg.h>. */
/* #undef HAVE_STRUCT_REG */

/* Define to 1 if `struct reg' is a member of `r_fs'. */
/* #undef HAVE_STRUCT_REG_R_FS */

/* Define to 1 if `struct reg' is a member of `r_gs'. */
/* #undef HAVE_STRUCT_REG_R_GS */

/* Define if <link.h> exists and defines a struct so_map which has members
   with an ``som_'' prefix. (Found on older *BSD systems.) */
/* #undef HAVE_STRUCT_SO_MAP_WITH_SOM_MEMBERS */

/* Define to 1 if `struct stat' is a member of `st_blksize'. */
#define HAVE_STRUCT_STAT_ST_BLKSIZE 1

/* Define to 1 if `struct stat' is a member of `st_blocks'. */
#define HAVE_STRUCT_STAT_ST_BLOCKS 1

/* Define to 1 if `struct thread' is a member of `td_pcb'. */
/* #undef HAVE_STRUCT_THREAD_TD_PCB */

/* Define to 1 if you have the `syscall' function. */
#define HAVE_SYSCALL 1

/* Define to 1 if you have the <sys/bitypes.h> header file. */
/* #undef HAVE_SYS_BITYPES_H */

/* Define to 1 if you have the <sys/debugreg.h> header file. */
#define HAVE_SYS_DEBUGREG_H 1

/* Define to 1 if you have the <sys/dir.h> header file, and it defines `DIR'.
   */
/* #undef HAVE_SYS_DIR_H */

/* Define to 1 if you have the <sys/fault.h> header file. */
/* #undef HAVE_SYS_FAULT_H */

/* Define to 1 if you have the <sys/file.h> header file. */
#define HAVE_SYS_FILE_H 1

/* Define to 1 if you have the <sys/filio.h> header file. */
/* #undef HAVE_SYS_FILIO_H */

/* Define to 1 if you have the <sys/inttypes.h> header file. */
/* #undef HAVE_SYS_INTTYPES_H */

/* Define to 1 if you have the <sys/ioctl.h> header file. */
#define HAVE_SYS_IOCTL_H 1

/* Define to 1 if you have the <sys/mman.h> header file. */
#define HAVE_SYS_MMAN_H 1

/* Define to 1 if you have the <sys/ndir.h> header file, and it defines `DIR'.
   */
/* #undef HAVE_SYS_NDIR_H */

/* Define to 1 if you have the <sys/param.h> header file. */
#define HAVE_SYS_PARAM_H 1

/* Define to 1 if you have the <sys/poll.h> header file. */
#define HAVE_SYS_POLL_H 1

/* Define to 1 if you have the <sys/procfs.h> header file. */
#define HAVE_SYS_PROCFS_H 1

/* Define to 1 if you have the <sys/proc.h> header file. */
/* #undef HAVE_SYS_PROC_H */

/* Define to 1 if you have the <sys/ptrace.h> header file. */
#define HAVE_SYS_PTRACE_H 1

/* Define to 1 if you have the <sys/reg.h> header file. */
#define HAVE_SYS_REG_H 1

/* Define to 1 if you have the <sys/resource.h> header file. */
#define HAVE_SYS_RESOURCE_H 1

/* Define to 1 if you have the <sys/select.h> header file. */
#define HAVE_SYS_SELECT_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/syscall.h> header file. */
#define HAVE_SYS_SYSCALL_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <sys/user.h> header file. */
#define HAVE_SYS_USER_H 1

/* Define to 1 if you have the <sys/wait.h> header file. */
#define HAVE_SYS_WAIT_H 1

/* Define to 1 if you have the <termios.h> header file. */
#define HAVE_TERMIOS_H 1

/* Define to 1 if you have the <termio.h> header file. */
#define HAVE_TERMIO_H 1

/* Define to 1 if you have the <term.h> header file. */
#define HAVE_TERM_H 1

/* Define to 1 if you have the <thread_db.h> header file. */
#define HAVE_THREAD_DB_H 1

/* Define if using Solaris thread debugging. */
/* #undef HAVE_THREAD_DB_LIB */

/* Define to 1 if you have the <time.h> header file. */
#define HAVE_TIME_H 1

/* Define if you support the tkill syscall. */
#define HAVE_TKILL_SYSCALL 1

/* Define to 1 if you have the `ttrace' function. */
/* #undef HAVE_TTRACE */

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if the system has the type `unsigned long long int'. */
#define HAVE_UNSIGNED_LONG_LONG_INT 1

/* Define to 1 if you have the `vfork' function. */
#define HAVE_VFORK 1

/* Define to 1 if you have the <vfork.h> header file. */
/* #undef HAVE_VFORK_H */

/* Define to 1 if you have the <wait.h> header file. */
#define HAVE_WAIT_H 1

/* Define to 1 if you have the `wborder' function. */
/* #undef HAVE_WBORDER */

/* Define to 1 if you have the <wchar.h> header file. */
#define HAVE_WCHAR_H 1

/* Define if you have the 'wchar_t' type. */
#define HAVE_WCHAR_T 1

/* Define if you have the 'wint_t' type. */
#define HAVE_WINT_T 1

/* Define to 1 if `fork' works. */
#define HAVE_WORKING_FORK 1

/* Define to 1 if `vfork' works. */
#define HAVE_WORKING_VFORK 1

/* Define to 1 if you have the `XML_StopParser' function. */
/* #undef HAVE_XML_STOPPARSER */

/* Define to 1 if you have the <zlib.h> header file. */
#define HAVE_ZLIB_H 1

/* Define to 1 if your system has the _etext variable. */
#define HAVE__ETEXT 1

/* Define to 1 if you have the `_mcleanup' function. */
#define HAVE__MCLEANUP 1

/* Define as const if the declaration of iconv() needs const. */
#define ICONV_CONST 

/* Define to a substitute value for mmap()'s MAP_ANONYMOUS flag. */
/* #undef MAP_ANONYMOUS */

/* Define if you want to use new multi-fd /proc interface (replaces
   HAVE_MULTIPLE_PROC_FDS as well as other macros). */
/* #undef NEW_PROC_API */

/* Name of this package. */
#define PACKAGE "gdb"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT ""

/* Define to the full name of this package. */
#define PACKAGE_NAME ""

/* Define to the full name and version of this package. */
#define PACKAGE_STRING ""

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME ""

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION ""

/* Additional package description */
#define PKGVERSION "(Linaro GDB) "

/* Define if the prfpregset_t type is broken. */
/* #undef PRFPREGSET_T_BROKEN */

/* Define to 1 if the "%H, %D and %DD" formats work to print decfloats. */
/* #undef PRINTF_HAS_DECFLOAT */

/* Define to 1 if the "%Lg" format works to print long doubles. */
#define PRINTF_HAS_LONG_DOUBLE 1

/* Define to 1 if the "%ll" format works to print long longs. */
#define PRINTF_HAS_LONG_LONG 1

/* Define if <proc_service.h> on solaris uses int instead of size_t, and
   assorted other type changes. */
/* #undef PROC_SERVICE_IS_OLD */

/* Define to the type of arg 3 for ptrace. */
#define PTRACE_TYPE_ARG3 long

/* Define to the type of arg 5 for ptrace. */
/* #undef PTRACE_TYPE_ARG5 */

/* Define as the return type of ptrace. */
#define PTRACE_TYPE_RET long

/* Define to l, ll, u, ul, ull, etc., as suitable for constants of type
   'ptrdiff_t'. */
/* #undef PTRDIFF_T_SUFFIX */

/* Define if the python directory should be relocated when GDB is moved. */
/* #undef PYTHON_PATH_RELOCATABLE */

/* Relocated directory for source files. */
/* #undef RELOC_SRCDIR */

/* Bug reporting address */
#define REPORT_BUGS_TO "<http://bugs.launchpad.net/gdb-linaro/>"

/* Define as the return type of signal handlers (`int' or `void'). */
#define RETSIGTYPE void

/* Define to 1 if the "%Lg" format works to scan long doubles. */
#define SCANF_HAS_LONG_DOUBLE 1

/* Define to 1 if the `setpgrp' function takes no argument. */
#define SETPGRP_VOID 1

/* Define to l, ll, u, ul, ull, etc., as suitable for constants of type
   'sig_atomic_t'. */
/* #undef SIG_ATOMIC_T_SUFFIX */

/* The size of `long', as computed by sizeof. */
/* #undef SIZEOF_LONG */

/* Define to l, ll, u, ul, ull, etc., as suitable for constants of type
   'size_t'. */
/* #undef SIZE_T_SUFFIX */

/* If using the C implementation of alloca, define if you know the
   direction of stack growth for your system; otherwise it will be
   automatically deduced at runtime.
	STACK_DIRECTION > 0 => grows toward higher addresses
	STACK_DIRECTION < 0 => grows toward lower addresses
	STACK_DIRECTION = 0 => direction of growth unknown */
/* #undef STACK_DIRECTION */

/* Define to 1 if the `S_IS*' macros in <sys/stat.h> do not work properly. */
/* #undef STAT_MACROS_BROKEN */

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* automatically load a system-wide gdbinit file */
#define SYSTEM_GDBINIT ""

/* Define if the system-gdbinit directory should be relocated when GDB is
   moved. */
#define SYSTEM_GDBINIT_RELOCATABLE 0

/* Define if <thread_db.h> has the TD_NOTALLOC error code. */
#define THREAD_DB_HAS_TD_NOTALLOC 1

/* Define if <thread_db.h> has the TD_NOTLS error code. */
#define THREAD_DB_HAS_TD_NOTLS 1

/* Define if <thread_db.h> has the TD_VERSION error code. */
#define THREAD_DB_HAS_TD_VERSION 1

/* Define to 1 if the regex included in libiberty should be used. */
/* #undef USE_INCLUDED_REGEX */

/* Define if we should use the Windows API, instead of the POSIX API. On
   Windows, we use the Windows API when building for MinGW, but the POSIX API
   when building for Cygwin. */
/* #undef USE_WIN32API */

/* Define to l, ll, u, ul, ull, etc., as suitable for constants of type
   'wchar_t'. */
/* #undef WCHAR_T_SUFFIX */

/* Define to l, ll, u, ul, ull, etc., as suitable for constants of type
   'wint_t'. */
/* #undef WINT_T_SUFFIX */

/* Define if --with-python provides a path, either directly or via
   python-config.py --exec-prefix. */
/* #undef WITH_PYTHON_PATH */

/* Define if the simulator is being linked in. */
#define WITH_SIM 1

/* Define WORDS_BIGENDIAN to 1 if your processor stores words with the most
   significant byte first (like Motorola and SPARC, unlike Intel). */
#if defined AC_APPLE_UNIVERSAL_BUILD
# if defined __BIG_ENDIAN__
#  define WORDS_BIGENDIAN 1
# endif
#else
# ifndef WORDS_BIGENDIAN
/* #  undef WORDS_BIGENDIAN */
# endif
#endif

/* Number of bits in a file offset, on hosts where this is settable. */
#define _FILE_OFFSET_BITS 64

/* Define to 1 so <sys/proc.h> gets a definition of anon_hdl. Works around a
   <sys/proc.h> problem on IRIX 5. */
/* #undef _KMEMUSER */

/* Define for large files, on AIX-style hosts. */
/* #undef _LARGE_FILES */

/* Define to 1 if on MINIX. */
/* #undef _MINIX */

/* Define to 1 to avoid a clash between <widec.h> and <wchar.h> on Solaris
   2.[789] when using GCC. */
/* #undef _MSE_INT_H */

/* Define to 2 if the system does not provide POSIX.1 features except with
   this defined. */
/* #undef _POSIX_1_SOURCE */

/* Define to 1 if you need to in order for `stat' and other things to work. */
/* #undef _POSIX_SOURCE */

/* Define if <sys/link.h> has link_map32 (solaris sparc-64 target) */
/* #undef _SYSCALL32 */

/* Define to 500 only on HP-UX. */
/* #undef _XOPEN_SOURCE */

/* Enable extensions on AIX 3, Interix.  */
#ifndef _ALL_SOURCE
# define _ALL_SOURCE 1
#endif
/* Enable GNU extensions on systems that have them.  */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif
/* Enable threading extensions on Solaris.  */
#ifndef _POSIX_PTHREAD_SEMANTICS
# define _POSIX_PTHREAD_SEMANTICS 1
#endif
/* Enable extensions on HP NonStop.  */
#ifndef _TANDEM_SOURCE
# define _TANDEM_SOURCE 1
#endif
/* Enable general extensions on Solaris.  */
#ifndef __EXTENSIONS__
# define __EXTENSIONS__ 1
#endif


/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
/* #undef inline */
#endif

/* Work around a bug in Apple GCC 4.0.1 build 5465: In C99 mode, it supports
   the ISO C 99 semantics of 'extern inline' (unlike the GNU C semantics of
   earlier versions), but does not display it by setting __GNUC_STDC_INLINE__.
   __APPLE__ && __MACH__ test for MacOS X.
   __APPLE_CC__ tests for the Apple compiler and its version.
   __STDC_VERSION__ tests for the C99 mode.  */
#if defined __APPLE__ && defined __MACH__ && __APPLE_CC__ >= 5465 && !defined __cplusplus && __STDC_VERSION__ >= 199901L && !defined __GNUC_STDC_INLINE__
# define __GNUC_STDC_INLINE__ 1
#endif

/* Define to `int' if <sys/types.h> does not define. */
/* #undef pid_t */

/* readline-6.0 started to use different name. */
/* #undef readline_echoing_p */

/* Define to the equivalent of the C99 'restrict' keyword, or to
   nothing if this is not supported.  Do not define if restrict is
   supported directly.  */
#define restrict __restrict
/* Work around a bug in Sun C++: it does not support _Restrict or
   __restrict__, even though the corresponding Sun C compiler ends up with
   "#define restrict _Restrict" or "#define restrict __restrict__" in the
   previous line.  Perhaps some future version of Sun C++ will work with
   restrict; if so, hopefully it defines __RESTRICT like Sun C does.  */
#if defined __SUNPRO_CC && !defined __RESTRICT
# define _Restrict
# define __restrict__
#endif

/* Define as a marker that can be attached to declarations that might not
    be used.  This helps to reduce warnings, such as from
    GCC -Wunused-parameter.  */
#if __GNUC__ >= 3 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 7)
# define _GL_UNUSED __attribute__ ((__unused__))
#else
# define _GL_UNUSED
#endif
/* The name _UNUSED_PARAMETER_ is an earlier spelling, although the name
   is a misnomer outside of parameter lists.  */
#define _UNUSED_PARAMETER_ _GL_UNUSED


/* Define as `fork' if `vfork' does not work. */
/* #undef vfork */
