dnl Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(shredder, 1.0)

AC_ARG_WITH([wxwidgets-prefix],
	[AS_HELP_STRING([--with-wxwidgets-prefix=PATH],
		[search for wxwidgets in PATH]
    )],
    [
        # This will always add value to CXXFLAGS in Makefile
        WX_CONFIG_CXXFLAGS="$($withval/bin/wx-config --cxxflags) -g"
        AC_SUBST(WX_CONFIG_CXXFLAGS)
        # This will always add value to LIBS in Makefile
        WX_CONFIG_LIBSS="$($withval/bin/wx-config --libs)"
        AC_SUBST(WX_CONFIG_LIBS)
    ],
    []
)

AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE()

AC_PROG_CXX

AC_CONFIG_FILES(Makefile src/Makefile src/tbtest/Makefile)
AC_OUTPUT
