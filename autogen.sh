#!/bin/bash
COCOS2DX_ROOT=${COCOS2DX_ROOT=/storage/adacosta/WORK/COCO/cocos2d-x-2.2.0}
NDK_ROOT=${NDK_ROOT=/storage/adacosta/WORK/Android/android-ndk-r9}

function project_common ()
{
	mkdir -p m4
	aclocal -I m4
	autoheader
	autoconf
	automake -a

	if ! [ -d $COCOS2DX_ROOT ]
	then
		echo -e "\e[1;36m"
		read -p "please define COCOS2DX_ROOT:" COCOS2DX_ROOT
		echo -e "\e[1;39m"
	fi
}

function project_linux ()
{
	./configure COCOS2DX_ROOT=$COCOS2DX_ROOT --enable-debug=yes
	make clean
	make
}

function project_android ()
{
	pushd src/plataform/android
	#TODO: source autogen.sh si uso esta llamada primero NDK_ROOT toma el valor de default config
	if ! [ -d $NDK_ROOT ]
	then
		echo -e "\e[1;36m"
		read -p "please define NDK_ROOT:" NDK_ROOT
		echo -e "\e[1;39m"
	fi
	source autogen.sh
	update_default_config $(from_plain_to_scaped $(get_node_of_default_config COCOS2DX_ROOT)) $(from_plain_to_scaped $COCOS2DX_ROOT)
	update_default_config $(from_plain_to_scaped $(get_node_of_default_config NDK_ROOT)) $(from_plain_to_scaped $NDK_ROOT)
	popd
	export PATH=$NDK_ROOT/toolchains/arm-linux-androideabi-4.8/prebuilt/linux-x86/bin:$PATH
	export SYSROOT=$NDK_ROOT/platforms/android-18/arch-arm
	./configure --host=arm-linux-androideabi CPPFLAGS="-I$NDK_ROOT/platforms/android-18/arch-arm/usr/include" CFLAGS="-nostdlib" LDFLAGS="-Wl,-rpath-link=$NDK_ROOT/platforms/android-18/arch-arm/usr/lib/ -L$NDK_ROOT/platforms/android-18/arch-arm/usr/lib" LIBS="-lc" COCOS2DX_ROOT=$COCOS2DX_ROOT --enable-debug=yes
	make apk-create-project
	make apk-build
	make apk-run
}

project_common

PLATAFORM="unknown"
options="GNU/Linux Android"
finished=false
until [ $finished == true ]; do
	select opt in $options ; do
		if [ "$opt" = "GNU/Linux" ] ; then
			PLATAFORM="Linux"
			finished=true
			project_linux
			break
		elif [ "$opt" = "Android" ]; then
			PLATAFORM="Android"
			finished=true
			project_android
			break
		else
			clear
			echo "Invalid option"
			break
		fi
	done
done



rm -rf doc/html
make html-doc
make dist
make details
