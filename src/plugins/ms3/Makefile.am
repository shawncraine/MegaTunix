plugindir = $(datadir)/MegaTunix/plugins

INCLUDES = \
        -I$(top_srcdir)/include \
        @GTK_CFLAGS@ \
        @DEPRECATED_CFLAGS@ \
        @LIBXML2_CFLAGS@ \
        @LIBGLADE_CFLAGS@ \
        @MEGATUNIX_DEFINES@


plugin_LTLIBRARIES = libnull.la 

libnull_la_SOURCES = \
	Makefile \
	ms3_plugin.c \
	ms3_plugin.h \
	ms3_gui_handlers.c \
	ms3_gui_handlers.h \
	ms3_menu_handlers.c \
	ms3_menu_handlers.h 

libnull_la_LDFLAGS = -shared $(no_undefined) -module
libnull_la_LIBADD = @EXTRA_LIBS@ @GTK_LIBS@ @LIBXML2_LIBS@ @LIBGLADE_LIBS@

COMMON_FLAGS = @PROF_FLAGS@ @DEBUG_FLAGS@ 

if CROSS_COMPILING
no_undefined = -no-undefined
endif

AM_CFLAGS += $(COMMON_FLAGS)

CLEANFILES = *~ core gmon.out nohup.out 

EXTRA_DIST = README


