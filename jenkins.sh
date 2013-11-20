#!/bin/bash

NDK_ROOT=/storage/adacosta/WORK/Android/android-ndk-r9
COCOS2DX_ROOT=/storage/adacosta/WORK/COCO/cocos2d-x-2.2.0
mkdir -p m4
aclocal -I m4
autoheader
autoconf
automake -a
export PATH=$NDK_ROOT/toolchains/arm-linux-androideabi-4.8/prebuilt/linux-x86/bin:$PATH
export SYSROOT=$NDK_ROOT/platforms/android-18/arch-arm
./configure --host=arm-linux-androideabi CPPFLAGS="-I$NDK_ROOT/platforms/android-18/arch-arm/usr/include" CFLAGS="-nostdlib" LDFLAGS="-Wl,-rpath-link=$NDK_ROOT/platforms/android-18/arch-arm/usr/lib/ -L$NDK_ROOT/platforms/android-18/arch-arm/usr/lib" LIBS="-lc" COCOS2DX_ROOT=$COCOS2DX_ROOT --enable-debug=yes
./configure --host=arm-linux-androideabi COCOS2DX_ROOT=$COCOS2DX_ROOT --enable-debug=yes
pushd src/plataform/android
./autogen.sh create_or_replace_project < file.in
./autogen.sh build_debug_project
popd
