SUBDIRS = include src
if TESTS
  SUBDIRS += tests
endif

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = coreHezelnut.pc

EXTRA_DIST = coreHezelnut.pc.in

ACLOCAL_AMFLAGS = -I builds/m4

dist-hook: changelog

changelog: $(top_srcdir)/.git/HEAD
	git log --stat > ChangeLog

doc: doxygen.conf
	doxygen doxygen.conf
