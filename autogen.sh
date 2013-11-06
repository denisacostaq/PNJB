#!/bin/bash

PLATAFORM="unknown"
options="GNU/Linux Android"
finished=false
until [ $finished == true ]; do
	select opt in $options ; do
		if [ "$opt" = "GNU/Linux" ] ; then
			PLATAFORM="Linux"
			finished=true
			break
		elif [ "$opt" = "Android" ]; then
			PLATAFORM="Android"
			finished=true
			break
		else
			clear
			echo "Invalid option"
			break
		fi
	done
done


if [ "$PLATAFORM" = "unknown" ]; then
	echo "Do you need specific the plataform"
	exit 1
elif [ "$PLATAFORM" = "Android" ]; then
	echo "Android currently not supported"
	exit 1
fi

	
if [ -z "${COCOS2DX_ROOT+aaa}" ];then
	read -p "COCOS2DX_ROOT not defined. Please inter the path of COCOS2DX_ROOT:" COCOS2DX_ROOT
fi

COCOS2DX_ROOT=/storage/adacosta/WORK/cocos2d-x-2.2.0

mkdir -p m4
aclocal -I m4
autoheader
autoconf
automake -a
#export $COCOS2DX_ROOT
./configure COCOS2DX_ROOT=$COCOS2DX_ROOT
make clean
rm -rf doc/html
make html-doc
make
make dist
make details



#if [ -z "${NDK_ROOT+aaa}" ];then
#	read -p "NDK_ROOT not defined. Please inter the path of NDK_ROOT:" NDK_ROOT
#fi