#!/bin/bash
defalut_text_color="\e[1;39m"
haigt_text_color="\e[1;36m"
information_text_color="\e[1;33m"
error_text_color="\e[1;31m"

#if the variable no exist asign the default values,
#in other case ingnore an preserve the old values
PROJECT_PATH=${PROJECT_PATH=project}
ACTIVITY_NAME=${ACTIVITY_NAME=MainActivity}
PROJECT_PACKAGE=${PROJECT_PACKAGE=com.blogspot.pnjb}
TARGET=${TARGET=1}
PROJECT_NAME=${PROJECT_NAME=PNJB}

BACKUP_DIRECTORY=${BACKUP_DIRECTORY="backup"}
COCOS2DX_ROOT=${COCOS2DX_ROOT=""}
NDK_ROOT=${NDK_ROOT=""}
SDK_ROOT=${SDK_ROOT=""}

#FIXME: esto iria con el config creo, hay que ponerlo por los nodos no por los valores
#o dentro del for tambien puede que sirva
function update_default_config
{
	echo -e "$haigt_text_color""Updatin default config from $1 to $2";
	echo -e "$defalut_text_color"
	FILE=$(cat default-config.cfg | sed "s/$1/$2/g")
	echo "" > default-config.cfg
	for f in $FILE
	do
		echo $f >> default-config.cfg
	done
}

#NOTE: conver ej: ./project to \.\/project
function from_plain_to_scaped ()
{
	echo $(echo $(echo $1 | sed 's/\./\\\./g') | sed 's/\//\\\//g')
}

#NOTE: conver ej: \.\/project to ./project
function from_scaped_to_plain ()
{
	echo $(echo $(echo $1 | sed 's/\\\./\./g') | sed 's/\\\//\//g')
}

function get_node_of_default_config ()
{
	echo $(echo $(cat default-config.cfg | grep $1) | sed "s/$1=//")

#	LL=$(echo $(cat default-config.cfg | grep $1 | sed "s/$1=//"))
#	echo $(echo $(echo $LL | sed 's/\./\\\./g') | sed 's/\//\\\//g')
}



function loading_environment ()
{
	echo -e "$haigt_text_color""loading the environment"
	echo -e "$defalut_text_color"
	if [ -f default-config.cfg ]
	then
		PROJECT_PATH=$(get_node_of_default_config PROJECT_PATH)
		ACTIVITY_NAME=$(get_node_of_default_config ACTIVITY_NAME)
		PROJECT_PACKAGE=$(get_node_of_default_config PROJECT_PACKAGE)
		TARGET=$(get_node_of_default_config TARGET)
		PROJECT_NAME=$(get_node_of_default_config PROJECT_NAME)
	fi

	if [ -d $BACKUP_DIRECTORY ]
	then
		pushd "$BACKUP_DIRECTORY"
		BACKUP_DIRECTORY=$(pwd)
		popd
	else
		echo -e "$error_text_color""$BACKUP_DIRECTORY no exixt"
		echo -e "$defalut_text_color"
		exit -1
	fi

	#FIXME: arreglarlo, quitarlo
	COCOS2DX_ROOT=$(get_node_of_default_config COCOS2DX_ROOT)
	until [ -d $COCOS2DX_ROOT ] && [ "$COCOS2DX_ROOT" != "" ]
	do
		echo -e "$error_text_color""The default COCOS2DX_ROOT $COCOS2DX_ROOT no exixt"
		echo -e "$haigt_text_color"
		read -p "directory" COCOS2DX_ROOT
		echo -e "$defalut_text_color"
	done
	update_default_config $(from_plain_to_scaped $(get_node_of_default_config COCOS2DX_ROOT)) $(from_plain_to_scaped $COCOS2DX_ROOT)

	#FIXME: arreglarlo, quitarlo
	NDK_ROOT=$(get_node_of_default_config NDK_ROOT)
	until [ -d $NDK_ROOT ] && [ "$NDK_ROOT" != "" ]
	do
		echo -e "$error_text_color""The default NDK_ROOT $NDK_ROOT no exixt"
		echo -e "$haigt_text_color"
		read -p "directory" NDK_ROOT
		echo -e "$defalut_text_color"
	done
	update_default_config $(from_plain_to_scaped $(get_node_of_default_config NDK_ROOT)) $(from_plain_to_scaped $NDK_ROOT)

	#FIXME: arreglarlo, quitarlo
	SDK_ROOT=$(get_node_of_default_config SDK_ROOT)
	until [ -d $SDK_ROOT ] && [ "$SDK_ROOT" != "" ]
	do
		echo -e "$error_text_color""The default SDK_ROOT $SDK_ROOT no exixt"
		echo -e "$haigt_text_color"
		read -p "directory" SDK_ROOT
		echo -e "$defalut_text_color"
	done
	update_default_config $(from_plain_to_scaped $(get_node_of_default_config SDK_ROOT)) $(from_plain_to_scaped $SDK_ROOT)
}

function show_environment ()
{
	echo -e "$haigt_text_color""showin the environment"

	echo -e "$information_text_color"
	echo "PROJECT_PATH: $PROJECT_PATH"
	echo "ACTIVITY_NAME: $ACTIVITY_NAME"
	echo "PROJECT_PACKAGE: $PROJECT_PACKAGE"
	echo "TARGET: $TARGET"
	echo "PROJECT_NAME: $PROJECT_NAME"

	echo "BACKUP_DIRECTORY: $BACKUP_DIRECTORY"
	echo "COCOS2DX_ROOT: $COCOS2DX_ROOT"
	echo "NDK_ROOT: $NDK_ROOT"
	echo "SDK_ROOT: $SDK_ROOT"

	echo -e "$defalut_text_color"
}

echo -e "$defalut_text_color"

function make_to_project_be_fully_populated
{
	echo -e "$defalut_text_color"
	echo -e "$haigt_text_color""Make to $PROJECT_PATH be fully populated";
	echo -e "$defalut_text_color"

	echo -e "$defalut_text_color"
	echo -e "$haigt_text_color""Linkin the project java source with the backup java source"
	echo -e "$defalut_text_color"
	pushd "$PROJECT_PATH/src/`echo "$PROJECT_PACKAGE" | sed "s/\./\//g"`"
	relative=$(perl -MFile::Spec -e 'print File::Spec->abs2rel("'"$BACKUP_DIRECTORY"'","'"$(pwd)"'")')
	rm "$ACTIVITY_NAME.java"
	ln -s "$relative/$ACTIVITY_NAME.java"
	popd

	if [ "$(cat $PROJECT_PATH/project.properties | grep android.library.reference.1)" == "" ] ; then
		echo -e "$defalut_text_color"
		echo -e "$haigt_text_color""Puttin android.library.reference.1=$(perl -MFile::Spec -e 'print File::Spec->abs2rel("'"$COCOS2DX_ROOT/cocos2dx/platform/android/java"'","'"$(pwd)/$( dirname "${BASH_SOURCE[0]}" )/$PROJECT_PATH"'")') in $PROJECT_PATH/project.properties"
		echo -e "$defalut_text_color"
		echo "android.library.reference.1=$(perl -MFile::Spec -e 'print File::Spec->abs2rel("'"$COCOS2DX_ROOT/cocos2dx/platform/android/java"'","'"$(pwd)/$( dirname "${BASH_SOURCE[0]}" )/$PROJECT_PATH"'")')" >> "$PROJECT_PATH/project.properties"
	fi

	if ! [ -d $PROJECT_PATH/assets ]
	then
		echo -e "$defalut_text_color"
		echo -e "$haigt_text_color""Linkin assets with project Resources"
		echo -e "$defalut_text_color"
		mkdir -p project/assets
		pushd project/assets
		ln -s ../../../../../Resources/Fonts Fonts
		ln -s ../../../../../Resources/IMG IMG
		ln -s ../../../../../Resources/Shaders Shaders
		ln -s ../../../../../Resources/Sounds Sounds
		popd
	fi

	if ! [ -d $PROJECT_PATH/jni ]
	then
		echo -e "$defalut_text_color"
		echo -e "$haigt_text_color""Linkin the project jni source with the backup jni source"
		echo -e "$defalut_text_color"
		pushd "$PROJECT_PATH"
		ln -s ../backup/jni
		popd
	fi
}


function purge_project
{
	if [ -d $PROJECT_PATH ]
	then
		echo -e "$haigt_text_color""Purgin old project";
		echo -e "$defalut_text_color"
		rm -rf $PROJECT_PATH
	fi
}


function create_or_replace_project
{
	echo -e "$haigt_text_color""Creating the project";
	echo -e "$defalut_text_color"
	old_TARGET=$TARGET
	old_PROJECT_NAME=$PROJECT_NAME
	old_PROJECT_PATH=$PROJECT_PATH
	old_ACTIVITY_NAME=$ACTIVITY_NAME
	old_PROJECT_PACKAGE=$PROJECT_PACKAGE
	options="Default Custom"
	finished=false
	until [ $finished == true ]; do
		select opt in $options ; do
			if [ "$opt" = "Default" ] ; then
				cp "$BACKUP_DIRECTORY/default-config.cfg" ./
				update_default_config $(from_plain_to_scaped $(get_node_of_default_config COCOS2DX_ROOT)) $(from_plain_to_scaped $COCOS2DX_ROOT)
				update_default_config $(from_plain_to_scaped $(get_node_of_default_config NDK_ROOT)) $(from_plain_to_scaped $NDK_ROOT)
				update_default_config $(from_plain_to_scaped $(get_node_of_default_config SDK_ROOT)) $(from_plain_to_scaped $SDK_ROOT)
				finished=true
				break
			elif [ "$opt" = "Custom" ]; then
				$SDK_ROOT/tools/android list target
				read -p "Target selection:" TARGET
				read -p "Project name:" PROJECT_NAME
				read -p "Project path:" PROJECT_PATH
				read -p "Activity name:" ACTIVITY_NAME
				read -p "Project package:" PROJECT_PACKAGE
				finished=true
				break
			else
				clear
				echo "Invalid option"
				break
			fi
		done
	done

	purge_project
	$SDK_ROOT/tools/android create project --target $TARGET --name $PROJECT_NAME --path $PROJECT_PATH --activity $ACTIVITY_NAME --package $PROJECT_PACKAGE

	if [ -d $PROJECT_PATH ]
	then
		update_default_config $old_TARGET $TARGET
		update_default_config $old_PROJECT_NAME $PROJECT_NAME
		update_default_config $(from_plain_to_scaped $old_PROJECT_PATH) $(from_plain_to_scaped $PROJECT_PATH)
		update_default_config $old_ACTIVITY_NAME $ACTIVITY_NAME
		update_default_config $old_PROJECT_PACKAGE $PROJECT_PACKAGE
		make_to_project_be_fully_populated
	else
		echo -e "$error_text_color""Project creation fail"
		echo -e "$haigt_text_color"
	fi
}

#function build_release_native_code ()
#{
#	$NDK_ROOT/ndk-build NDK_MODULE_PATH=$COCOS2DX_ROOT:$COCOS2DX_ROOT/cocos2dx/platform/third_party/android/prebuilt
#}

#function build_release_project
#{
#	pushd project
#	build_release_native_code
#	ant release
#	popd
#}

#FIXME: el debug??
function build_debug_native_code ()
{
	echo -e "$haigt_text_color""Buildin the native code indebug"
	echo -e "$defalut_text_color"
	$NDK_ROOT/ndk-build NDK_MODULE_PATH=$COCOS2DX_ROOT:$COCOS2DX_ROOT/cocos2dx/platform/third_party/android/prebuilt
}
 
function build_debug_project
{
	echo -e "$haigt_text_color""Buildin the project in debug"
	echo -e "$defalut_text_color"
	pushd project
	build_debug_native_code
	ant debug -Dsdk.dir=$SDK_ROOT
	popd
}


#FIXME: el nativo
function clean_project
{
	echo -e "$haigt_text_color""Cleaning the project: $PROJECT_NAME"
	echo -e "$defalut_text_color"
	pushd project
	ant clean
	popd
}

#FIXME:
function run_emulator ()
{
	$SDK_ROOT/tools/emulator -avd AA -gpu on
}

#FIXME:
#function create_avd
#{
#	options="GUI CLI"
#	finished=false
#	until [ $finished == true ]; do
#		select opt in $options ; do
#			if [ "$opt" = "GUI" ] ; then
#				$SDK_ROOT/tools/android avd
#				finished=true
#				break
#			elif [ "$opt" = "CLI" ]; then
#				finished=true
#				break
#			else
#				clear
#				echo "Invalid option"
#				break
#			fi
#		done
#	done
#}

function run_apk ()
{
	echo -e "$haigt_text_color""Running the package $PROJECT_PACKAGE"
	echo -e "$defalut_text_color"
	$SDK_ROOT/platform-tools/adb shell am start -a android.intent.action.MAIN -n $PROJECT_PACKAGE/$PROJECT_PACKAGE.$ACTIVITY_NAME
}

function log_cat_apk ()
{
	echo -e "$haigt_text_color""Show the logcat output"
	echo -e "$defalut_text_color"
	$SDK_ROOT/platform-tools/adb logcat
}

#get_emulator_state ()


function install_apk ()
{
	echo -e "$haigt_text_color""Instaling the apk: $PROJECT_NAME.apk"
	echo -e "$defalut_text_color"
	if ! [ -f $PROJECT_PATH/bin/$PROJECT_NAME-debug.apk ]
	then
		build_debug_project
	fi
	$SDK_ROOT/platform-tools/adb install $PROJECT_PATH/bin/$PROJECT_NAME-debug.apk
}

function uninstall_apk ()
{
	echo -e "$haigt_text_color""Uninstalin the apk: $PROJECT_NAME.apk"
	echo -e "$defalut_text_color"
	$SDK_ROOT/platform-tools/adb uninstall $PROJECT_PACKAGE
}

#function build-project
#{
#	echo -e "$haigt_text_color""Buildin the project"
#	echo -e "$defalut_text_color"
#	pushd $PROJECT_PATH
#
#	echo -e "$defalut_text_color"
#	echo -e "$haigt_text_color""Buildin native code"
#	echo -e "$defalut_text_color"
#	$NDK_ROOT/ndk-build NDK_MODULE_PATH=$COCOS2DX_ROOT:$COCOS2DX_ROOT/cocos2dx/platform/third_party/android/prebuilt
#
#	echo -e "$defalut_text_color"
#	echo -e "$haigt_text_color""Creating package"
#	echo -e "$defalut_text_color"
#	ant debug -Dsdk.dir=$SDK_ROOT
#	popd

	#/storage/adacosta/WORK/Android/sdk/platform-tools/adb install bin/PNJB-debug.apk
	#/storage/adacosta/WORK/Android/sdk/platform-tools/adb shell am start -a android.intent.action.MAIN -n com.blogspot.pnjb/com.blogspot.pnjb.MainActivity
#}



if (($# == 1))
then
	loading_environment
	show_environment
	$1
fi
