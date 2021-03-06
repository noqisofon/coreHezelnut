#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT(coreHezelnut, 0.1, ned.rihine@gmail.com)
COREHEZELNUT_DESCRIPTION='Smalltalk like OOP library'
AC_SUBST(COREHEZELNUT_DESCRIPTION)
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/allocation.c])
AC_CONFIG_HEADERS([include/config.h])
AC_CONFIG_MACRO_DIR([builds/m4])
AC_CONFIG_FILES([coreHezelnut.pc:coreHezelnut.pc.in])

# 
# --enable-gc
# 
AC_ARG_ENABLE(gc,
    AC_HELP_STRING([--enable-gc],
        [Enable GC suppert [default=yes]]),
    ,enable_gc=yes)

# 
# --enable-tests
# 
AC_ARG_ENABLE(tests,
    AC_HELP_STRING([--enable-tests],
    [enable test suites [default=no]]),
    ,enable_tests=no)

# 
# --enable-debug
# 
AC_ARG_ENABLE(debug,
    AC_HELP_STRING([--enable-debug],
        [use 'DEBUG' configuration [default=no]]),
        , enable_debug=no)


# Checks for programs.
AC_PROG_LIBTOOL
AC_LIBTOOL_WIN32_DLL
AC_PROG_INSTALL
AC_PROG_CC
AC_HEADER_STDC

# 
# CFLAGS 
# 
if test x$enable_debug = xyes; then
  CFLAGS="$CFLAGS -g -W -Wall"
else
  CFLAGS="$CFLAGS -O2 -W -Wall"
fi

## Makefile.am variables
AM_CONDITIONAL(TESTS, test x$enable_tests = xyes)

# Checks for libraries.
## pthread
AC_CHECK_LIB(pthread, pthread_create, [LIBS="$LIBS -pthread"])
## gc
if test x$enable_gc = xyes; then
  AC_CHECK_LIB(gc, [GC_malloc], [LIBS="$LIBS -lgc"])
fi

# Checks for header files.
AC_CHECK_HEADERS([limits.h stddef.h stdio.h stdarg.h stdlib.h string.h])
## pthread
AC_CHECK_HEADERS(pthread.h,, [AC_MSG_ERROR([pthread.h required])])
## gc
if test x$enable_gc = xyes; then
  AC_CHECK_HEADERS(gc.h)
fi

# Checks for typedefs, structures, and compiler characteristics.
## Keywords
AC_C_INLINE
AC_C_VOLATILE
AC_C_STRINGIZE
AC_C_CONST
AC_C_RESTRICT
## Types
AC_CHECK_SIZEOF(void *)
AC_TYPE_SIZE_T
## Functions
AC_FUNC_MALLOC

## Preprocessor symbol
AC_DEFINE([CORE_HEZELNUT_BUILD], [], [build flag])

# Checks for library functions.
AC_CONFIG_FILES([Makefile
    include/Makefile
    include/coreHezelnut/Makefile
    include/coreHezelnut/classes/Makefile
    src/Makefile
    src/classes/Makefile
    tests/Makefile
    tests/hello/Makefile])
AC_OUTPUT
