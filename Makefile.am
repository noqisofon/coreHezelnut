SUBDIRS = include src

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = coreHezelnut.pc

EXTRA_DIST = coreHezelnut.pc.in

dist-hook: changelog

changelog: $(top_srcdir)/.git/HEAD
	git log --stat > ChangeLog

doc: doxygen.conf
	doxygen doxygen.conf
