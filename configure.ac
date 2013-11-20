#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
# Packaged by denisacostaq@gmail.com

AC_PREREQ([2.69])
AC_INIT([PNJB], [0.0.0], [denisacostaq@gmail.com], [pnjb], [https://www.com])

AM_INIT_AUTOMAKE([1.13.3])


if test "$COCOS2DX_ROOT" = ""; then
	AC_MSG_ERROR([sorry, can’t determine the coco2s2 library path, run ./configure COCOS2DX_ROOT=path to cocos])
fi
AC_SUBST(COCOS2DX_ROOT)


AC_ARG_ENABLE([debug],
	[AS_HELP_STRING([--enable-debug], [Turn on debugging])],
	[case "${enableval}" in
		yes) debug=true ;;
		no) debug=false ;;
		*) AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
	esac],
	[debug=false])
AM_CONDITIONAL([DEBUG], [test x$debug = xtrue])

AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

AC_CANONICAL_HOST
AC_CANONICAL_BUILD

case "${host_os}" in
    linux-gnu) PLATAFORM_LIBS_PATH=/lib/linux;
        PLATAFORM=LINUX;;
    linux-androideabi)
        PLATAFORM=ANDROID;;
    *) AC_MSG_ERROR([${host_os} is an unknown system]) ;;
esac
PLATAFORM_LIBS_PATH=/lib/linux
AC_SUBST(PLATAFORM_LIBS_PATH)
AC_SUBST(PLATAFORM)

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_AWK
AC_PROG_CPP
AC_PROG_MKDIR_P
#LT_INIT
AC_PROG_MAKE_SET



# Checks for libraries.
PKG_CHECK_MODULES(GLS, [gl glew])
AC_SUBST(GLS_CFLAGS)
AC_SUBST(GLS_LIBS)

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h unistd.h ])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memset])

AC_CONFIG_FILES([Makefile
                 src/plataform/linux/Makefile
                 src/plataform/android/Makefile])
AC_OUTPUT

