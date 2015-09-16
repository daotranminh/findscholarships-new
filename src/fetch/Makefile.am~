# global preprocessor flags
AM_CPPFLAGS = \
    -I$(top_srcdir)/include \
    -I$(top_srcdir) \
    $(BOOST_CPPFLAGS)

# global linker flags
AM_LDFLAGS = \
	$(BOOST_DATE_TIME_LDFLAGS) \
	$(BOOST_PROGRAM_OPTIONS_LDFLAGS) \
	$(BOOST_SYSTEM_LDFLAGS) \
	$(BOOST_THREAD_LDFLAGS) \
	$(BOOST_SERIALIZATION_LDFLAGS) \
	$(BOOST_GRAPH_LDFLAGS) 

# global libs
LIBS = \
	$(BOOST_DATE_TIME_LIBS) \
	$(BOOST_PROGRAM_OPTIONS_LIBS) \
	$(BOOST_SYSTEM_LIBS) \
	$(BOOST_THREAD_LIBS) \
	$(BOOST_SERIALIZATION_LIBS) 
	$(BOOST_GRAPH_LIBS)

lib_LTLIBRARIES = libfetch.la

libfetch_la_SOURCES = \
	FetchedInfo.cpp \
	FetcherBase.cpp \
	FetcherDbworld.cpp \
	FetcherManual.cpp \
	FetcherScholarshipLinks.cpp \
	FetcherScholarshipPositions.cpp \
	Fetcher.cpp

bin_PROGRAMS = fetch

# the fetch binary
fetch_SOURCES = \
	fetch.cpp

fetch_LDADD = \
	$(top_builddir)/src/html/libhtmlcxx.la \
	$(top_builddir)/src/fetch/libfetch.la \
	$(top_builddir)/src/utilities/libutilities.la \
	@LIBCURL@

