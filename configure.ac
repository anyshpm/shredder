dnl Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(shredder, 1.0)

AC_ARG_WITH([wxwidgets-prefix],
	[AS_HELP_STRING([--with-wxwidgets-prefix=PATH],
		[search for wxwidgets in PATH]
    )],
    [
        LIBS="$LIBS $($withval/bin/wx-config --libs)"
        CXXFLAGS="$CXXFLAGS $($withval/bin/wx-config --cxxflags)"
    ],
    []
)

AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE()

AC_PROG_CXX

AC_CONFIG_FILES(Makefile src/Makefile)
AC_OUTPUT
