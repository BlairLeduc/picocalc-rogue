/* config.h.in.  Generated from configure.ac by autoheader.  */

#include <pico/stdlib.h>
#include <pwd.h>

#define lstat stat

/* Define if scorefile is top scores, not top players */
//#undef ALLSCORES
#define ALLSCORES 1

/* Define if checktime feature should be enabled */
#undef CHECKTIME

/* Define to group owner of setgid executable */
#undef GROUPOWNER

/* Define to 1 if you have the `alarm' function. */
#undef HAVE_ALARM

/* Define to 1 if you have the <arpa/inet.h> header file. */
#undef HAVE_ARPA_INET_H

/* Define to 1 if libcurses is requested */
//#undef HAVE_CURSES_H
#define HAVE_CURSES_H 1

/* Define to 1 if you don't have `vprintf' but do have `_doprnt.' */
#undef HAVE_DOPRNT

/* Define to 1 if you have the `erasechar' function. */
//#undef HAVE_ERASECHAR
#define HAVE_ERASECHAR 1

/* Define if ncurses has ESCDELAY variable */
#undef HAVE_ESCDELAY

/* Define to 1 if you have the <fcntl.h> header file. */
//#undef HAVE_FCNTL_H
#define HAVE_FCNTL_H 1

/* Define to 1 if you have the `fork' function. */
#undef HAVE_FORK

/* Define to 1 if you have the `getgid' function. */
#undef HAVE_GETGID

/* Define to 1 if you have the `getloadavg' function. */
#undef HAVE_GETLOADAVG

/* Define to 1 if you have the `getpass' function. */
//#undef HAVE_GETPASS
#define HAVE_GETPASS 1

/* Define to 1 if you have the `getpwuid' function. */
//#undef HAVE_GETPWUID
#define HAVE_GETPWUID 1

/* Define to 1 if you have the `getuid' function. */
#undef HAVE_GETUID

/* Define to 1 if you have the <inttypes.h> header file. */
//#undef HAVE_INTTYPES_H
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the `killchar' function. */
//#undef HAVE_KILLCHAR
#define HAVE_KILLCHAR 1

/* Define to 1 if you have the <limits.h> header file. */
//#undef HAVE_LIMITS_H
#define HAVE_LIMITS_H 1

/* Define to 1 if you have the `loadav' function. */
#undef HAVE_LOADAV

/* Define to 1 if `lstat' has the bug that it succeeds when given the
   zero-length file name argument. */
#undef HAVE_LSTAT_EMPTY_STRING_BUG

/* Define to 1 if you have the <memory.h> header file. */
//#undef HAVE_MEMORY_H
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `memset' function. */
//#undef HAVE_MEMSET
#define HAVE_MEMSET 1

/* Define to 1 if libncurses is requested */
#undef HAVE_NCURSES_H

/* Define to 1 if you have the <ncurses/term.h> header file. */
#undef HAVE_NCURSES_TERM_H

/* Define to 1 if you have the `nlist' function. */
#undef HAVE_NLIST

/* Define to 1 if you have the <nlist.h> header file. */
#undef HAVE_NLIST_H

/* Define to 1 if you have the <process.h> header file. */
#undef HAVE_PROCESS_H

/* Define to 1 if you have the <pwd.h> header file. */
//#undef HAVE_PWD_H
#define HACE_PWD_H 1

/* Define to 1 if you have the `setenv' function. */
#undef HAVE_SETENV

/* Define to 1 if you have the `setgid' function. */
#undef HAVE_SETGID

/* Define to 1 if you have the `setregid' function. */
#undef HAVE_SETREGID

/* Define to 1 if you have the `setresgid' function. */
#undef HAVE_SETRESGID

/* Define to 1 if you have the `setresuid' function. */
#undef HAVE_SETRESUID

/* Define to 1 if you have the `setreuid' function. */
#undef HAVE_SETREUID

/* Define to 1 if you have the `setuid' function. */
#undef HAVE_SETUID

/* Define to 1 if you have the `spawnl' function. */
#undef HAVE_SPAWNL

/* Define to 1 if `stat' has the bug that it succeeds when given the
   zero-length file name argument. */
#undef HAVE_STAT_EMPTY_STRING_BUG

/* Define to 1 if stdbool.h conforms to C99. */
//#undef HAVE_STDBOOL_H
#define HAVE_STDBOOL_H 1

/* Define to 1 if you have the <stdint.h> header file. */
//#undef HAVE_STDINT_H
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
//#undef HAVE_STDLIB_H
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the `strchr' function. */
//#undef HAVE_STRCHR
#define HAVE_STRCHR 1

/* Define to 1 if you have the `strerror' function. */
//#undef HAVE_STRERROR
#define HAVE_STRERROR 1

/* Define to 1 if you have the <strings.h> header file. */
//#undef HAVE_STRINGS_H
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
//#undef HAVE_STRING_H
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/ioctl.h> header file. */
#undef HAVE_SYS_IOCTL_H

/* Define to 1 if you have the <sys/stat.h> header file. */
//#undef HAVE_SYS_STAT_H
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
//#undef HAVE_SYS_TYPES_H
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <sys/utsname.h> header file. */
#undef HAVE_SYS_UTSNAME_H

/* Define to 1 if you have the <termios.h> header file. */
#undef HAVE_TERMIOS_H

/* Define to 1 if you have the <term.h> header file. */
#undef HAVE_TERM_H

/* Define to 1 if you have the <unistd.h> header file. */
//#undef HAVE_UNISTD_H
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the <utmp.h> header file. */
//#undef HAVE_UTMP_H
#define HAVE_UTMP_H 1

/* Define to 1 if you have the `vfork' function. */
#undef HAVE_VFORK

/* Define to 1 if you have the <vfork.h> header file. */
#undef HAVE_VFORK_H

/* Define to 1 if you have the `vprintf' function. */
#undef HAVE_VPRINTF

/* Define to 1 if `fork' works. */
#undef HAVE_WORKING_FORK

/* Define to 1 if `vfork' works. */
#undef HAVE_WORKING_VFORK

/* Define to 1 if the system has the type `_Bool'. */
#undef HAVE__BOOL

/* Define to 1 if you have the `_spawnl' function. */
#undef HAVE__SPAWNL

/* define if we should use program's load average function instead of system
   */
#undef LOADAV

/* Define to file to use for scoreboard lockfile */
#undef LOCKFILE

/* Define to 1 if `lstat' dereferences a symlink specified with a trailing
   slash. */
#undef LSTAT_FOLLOWS_SLASHED_SYMLINK

/* Define to include wizard mode */
#undef MASTER

/* Define if maxusers feature should be enabled */
#undef MAXLOAD

/* Define if maxusers feature should be enabled */
#undef MAXUSERS

/* kernel file to pass to nlist() when reading load average (unlikely to work)
   */
#undef NAMELIST

/* word for the number of scores to store in scoreboard */
#undef NUMNAME

/* number of scores to store in scoreboard */
#undef NUMSCORES

/* Define to the address where bug reports for this package should be sent. */
#undef PACKAGE_BUGREPORT

/* Define to the full name of this package. */
#undef PACKAGE_NAME

/* Define to the full name and version of this package. */
#undef PACKAGE_STRING

/* Define to the one symbol short name of this package. */
#undef PACKAGE_TARNAME

/* Define to the version of this package. */
#undef PACKAGE_VERSION

/* Define crypt(3) wizard mode password */
#undef PASSWD

/* Define as the return type of signal handlers (`int' or `void'). */
#undef RETSIGTYPE

/* Define to file to use for scoreboard */
//#undef SCOREFILE
#define SCOREFILE "/Rogue/rogue.scr"

/* Define to 1 if you have the ANSI C header files. */
//#undef STDC_HEADERS
#define STDC_HEADERS 1

/* Define to 1 if your <sys/time.h> declares `struct tm'. */
#undef TM_IN_SYS_TIME

/* define if we should use program's user counting function instead of
   system's */
#undef UCOUNT

/* utmp like file to pass to ucount() when counting online users (unlikely to
   work) */
#undef UTMP

/* Define to empty if `const' does not conform to ANSI C. */
#undef const

/* Define to `int' if <sys/types.h> doesn't define. */
#undef gid_t

/* Define to `int' if <sys/types.h> does not define. */
#undef pid_t

/* Define to `unsigned int' if <sys/types.h> does not define. */
#undef size_t

/* Define to `int' if <sys/types.h> doesn't define. */
#undef uid_t

/* Define as `fork' if `vfork' does not work. */
#undef vfork
