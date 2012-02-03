#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT(coreHezelnut, 0.1, ned.rihine@gmail.com)
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/objects.c])
AM_CONFIG_HEADER([include/config.h])
AC_CONFIG_FILES([coreHezelnut.pc:coreHezelnut.pc.in])


# Checks for programs.
AC_PROG_LIBTOOL
AC_LIBTOOL_WIN32_DLL
AC_PROG_INSTALL
#AC_PROG_RANLIB
AC_PROG_CC
AC_HEADER_STDC

AC_ARG_ENABLE(gc,
    [   --enable-gc Enable OpenGL suppert [default=yes]],
    , enable_gc=yes)

# Checks for libraries.
AC_CHECK_LIB(pthread, pthread_create, [LIBS="$LIBS -pthread"])
if test x$enable_gc = xyes; then
  AC_CHECK_LIB(gc, [GC_malloc], [LIBS="$LIBS -lgc"])
fi

# Checks for header files.
AC_CHECK_HEADERS([limits.h stddef.h stdio.h stdarg.h stdlib.h string.h])
AC_CHECK_HEADERS(pthread.h,, [AC_MSG_ERROR([pthread.h required])])

if test x$enable_gc = xyes; then
  AC_CHECK_HEADERS(gc.h)
fi

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_C_CONST
AC_TYPE_SIZE_T
AC_FUNC_MALLOC

CFLAGS="$CFLAGS -W -Wall"

AC_DEFINE([CORE_HEZELNUT_BUILD], [], [build flag])

# Checks for library functions.
AC_CONFIG_FILES([Makefile
    include/Makefile
    include/coreHezelnut/Makefile
    include/coreHezelnut/classes/Makefile
    src/Makefile
    src/classes/Makefile])
AC_OUTPUT
