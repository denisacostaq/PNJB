#all: apk-run
all:

Android.mk: Makefile.am
	androgenizer -:PROJECT pnjb \
	\
	-:REL_TOP $(top_srcdir) -:ABS_TOP $(abs_top_srcdir) \
	-:SHARED pnjb_shared \
	-:EXECUTABLE pnjb \
	-:SOURCES $(libtestlib_la_SOURCES) \
	-:LDFLAGS $(libtestlib_la_LDFLAGS) \
	-:REL_TOP $(top_srcdir)/src/portable/scene \
	\
	-:STATIC external/Box2D \
	-:REL_TOP $(top_srcdir) -:ABS_TOP $(abs_top_srcdir) \
	-:EXECUTABLE testapp \
	-:LDFLAGS -ltestlib \
	-:SOURCES $(testapp_SOURCES) \
> $@


apk-create-project:
	./autogen.sh create_or_replace_project

apk-run: apk-uninstall apk-install
	./autogen.sh run_apk

apk-install:
	./autogen.sh install_apk

apk-uninstall:
	./autogen.sh uninstall_apk

apk-clean:
	./autogen.sh clean_project

apk-logcat:
	./autogen.sh log_cat_apk

apk-build:
	./autogen.sh build_debug_project

apk-purge_project:
	./autogen.sh purge_project
