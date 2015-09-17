SUBDIRS = init htmlgen html utilities fetch willhabentracker

# global preprocessor flags
AM_CPPFLAGS = \
    -I$(top_srcdir)/include \
    -I$(top_srcdir) \
    $(BOOST_CPPFLAGS) \
    @LIBCURL_CPPFLAGS@


# global linker flags
AM_LDFLAGS = \
	$(BOOST_DATE_TIME_LDFLAGS) \
	$(BOOST_PROGRAM_OPTIONS_LDFLAGS) \
	$(BOOST_SYSTEM_LDFLAGS) \
	$(BOOST_FILESYSTEM_LDFLAGS) \
	$(BOOST_THREAD_LDFLAGS) \
	$(BOOST_SERIALIZATION_LDFLAGS) \
	$(BOOST_ASIO_LDFLAGS) \
	$(BOOST_GRAPH_LDFLAGS) 

# global libs
LIBS = \
	$(BOOST_DATE_TIME_LIBS) \
	$(BOOST_PROGRAM_OPTIONS_LIBS) \
	$(BOOST_SYSTEM_LIBS) \
	$(BOOST_FILESYSTEM_LIBS) \
	$(BOOST_THREAD_LIBS) \
	$(BOOST_SERIALIZATION_LIBS) \
	$(BOOST_ASIO_LIBS) \
	$(BOOST_GRAPH_LIBS) \
	$(LOG4CXX_LIBS)

# install binaries into $prefix/bin
bin_PROGRAMS = \
	fetchscholarships \
	findscholarships \
	willhaben

# the fetch binary #####################################
fetchscholarships_SOURCES = \
	fetch.cpp

fetchscholarships_LDADD = \
	$(top_builddir)/src/html/libhtml.la \
	$(top_builddir)/src/fetch/libfetch.la \
	$(top_builddir)/src/init/libinit.la \
	$(top_builddir)/src/utilities/libutilities.la \
	@LIBCURL@

# the findscholarship binary ###########################
findscholarships_SOURCES = \
	findscholarships.cpp

findscholarships_LDADD = \
	$(top_builddir)/src/html/libhtml.la \
	$(top_builddir)/src/fetch/libfetch.la \
	$(top_builddir)/src/init/libinit.la \
	$(top_builddir)/src/utilities/libutilities.la \
	$(top_builddir)/src/htmlgen/libhtmlgen.la \
	@LIBCURL@

# the willhabentracker binary ##########################
willhaben_SOURCES = \
	willhabentracker.cpp

willhaben_LDADD = \
	$(top_builddir)/src/html/libhtml.la \
	$(top_builddir)/src/init/libinit.la \
	$(top_builddir)/src/utilities/libutilities.la \
	$(top_builddir)/src/willhabentracker/libwillhabentracker.la \
	@LIBCURL@

EXTRA_DIST = COPYING

