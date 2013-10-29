AC_INIT([cre-downloader], [0.0.1], [thlorenz@gmx.de])

AM_INIT_AUTOMAKE([-Wall -Werror -Wno-portability foreign])

AM_PROG_AR

AC_PROG_CC
AC_PROG_LIBTOOL

AC_CONFIG_HEADERS([config.h])

AC_CONFIG_FILES([
  Makefile
  deps/tap/Makefile
  src/Makefile
])

LT_INIT([shared])
AC_CONFIG_MACRO_DIR([m4])

AC_OUTPUT
