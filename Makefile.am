SUBDIRS=src/plataform/linux
#SUBDIRS=src/plataform/android
#ifeq ($(TARGET_CPU),x86)
# TARGET_CPU_IS_X86 := 1
#else ifeq ($(TARGET_CPU),x86_64)
#  TARGET_CPU_IS_X86 := 1
#else
#  TARGET_CPU_IS_X86 := 0

EXTRA_DIST = README THANKS TODO HACKING MAINTAINERS Resources doc autogen.sh src/plataform/android
#EXTRA_DIST += pnjb.config               pnjb.files        pnjb.includes               pnjb.creator
CLEANFILES = *~

ACLOCAL_AMFLAGS = -I m4

details:
	@echo "Building from:"
	@echo "build_cpu = $(build_cpu), build_os = $(build_os), build_vendor = $(build_vendor)"
	@echo "To:"
	@echo "host_cpu = $(host_cpu), host_os = $(host_os), host_vendor = $(host_vendor)"

license:
	if test -f /usr/share/common-licenses/GPL-2 ; then \
		echo Updating license from /usr/share/common-licenses/GPL-2 ; \
		cat /usr/share/common-licenses/GPL-2 > COPYING ; \
	else \
		echo "You need run apt-get install base-files" ; \
	fi

html-doc:
	cd doc ; \
	doxygen Doxfile ; \
	cd ../

android-apk:
	@echo Android currently not supported

apk:
	@echo build apk current not supported
#imagesdir = $(pkgdatadir)/images
#soundsdir = $(pkgdatadir)/sounds
#dist_images_DATA = images/vortex.pgm
#dist_sounds_DATA = sounds/whirl.ogg
#see Section 14.2 [Fine-grained Distribution Control], page 98


apk-create-project:
	make -C src/plataform/android apk-create-project

apk-run:
	make -C src/plataform/android apk-run
apk-install:
	make -C src/plataform/android apk-install

apk-uninstall:
	make -C src/plataform/android apk-uninstall

apk-clean:
	make -C src/plataform/android apk-clean

apk-logcat:
	make -C src/plataform/android apk-logcat

apk-build:
	make -C src/plataform/android apk-build

apk-purge_project:
	make -C src/plataform/android apk-purge_project
