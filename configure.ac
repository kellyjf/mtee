#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([mtee], [1.0], [jkelly@gogoair.com])
AC_CONFIG_SRCDIR([mtee.c])

AM_INIT_AUTOMAKE(foreign -Wall)

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([strrchr])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
