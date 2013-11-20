defalut_text_color="\e[1;32m"
haigt_text_color="\e[1;36m"

BACKUP_DIRECTORY="backup"
if [ -d $BACKUP_DIRECTORY ]
then
	pushd "$BACKUP_DIRECTORY"
	BACKUP_DIRECTORY=$(pwd)
	popd
else
	echo "$BACKUP_DIRECTORY no exixt"
	exit 0
fi


#FIXME: arreglarlo, quitarlo
COCOS2DX_ROOT=/storage/adacosta/WORK/COCO/cocos2d-x-2.2.0
#COCOS2DX_ROOT=$1


#FIXME: arreglarlo, quitarlo
NDK_ROOT="/storage/adacosta/WORK/Android/android-ndk-r9"
if [ -z "${NDK_ROOT+aaa}" ];then
	read -p "NDK_ROOT not defined. Please inter the path of NDK_ROOT:" NDK_ROOT
fi

#FIXME: arreglarlo, quitarlo
SDK_ROOT="/storage/adacosta/WORK/Android/sdk"
if [ -z "${SDK_ROOT+aaa}" ];then
	read -p "SDK_ROOT not defined. Please inter the path of SDK_ROOT:" SDK_ROOT
fi



PROJECT_PATH="./project"
ACTIVITY_NAME="MainActivity"
PROJECT_PACKAGE="com.blogspot.pnjb"

function purge_project
{
	rm -rf $PROJECT_PATH
}

function create_or_replace_project
{
	echo -e "$defalut_text_color"
	echo -e "$haigt_text_color""Creating the project";
	echo -e "$defalut_text_color"
	TARGET=1
	PROJECT_NAME="PNJB"
	options="Default Custom"
	finished=false
	until [ $finished == false ]; do
		select opt in $options ; do
			if [ "$opt" = "Default" ] ; then
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
}

function clean_project
{
	pushd project
	ant clean
	popd
}

function build_release_project
{
	pushd project
	ant release
	popd	
}

function build_debug_project
{
	pushd project
	ant debug
	popd	
}

function run_project
{
	echo run
}

function create_avd
{
	options="GUI CLI"
	finished=false
	until [ $finished == false ]; do
		select opt in $options ; do
			if [ "$opt" = "GUI" ] ; then
				$SDK_ROOT/tools/android avd
				finished=true
				break
			elif [ "$opt" = "CLI" ]; then
				finished=true
				echo cliiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
				break
			else
				clear
				echo "Invalid option"
				break
			fi
		done
	done
}

create_or_replace_project
if ! [ -d $PROJECT_PATH ]
then
	echo "Project creation fail"
	exit 0
fi

#create_avd
#clean_project
#build_debug_project

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

echo -e "$defalut_text_color"
echo -e "$haigt_text_color""Buildin the project"
echo -e "$defalut_text_color"
pushd $PROJECT_PATH
echo -e "$defalut_text_color"
echo -e "$haigt_text_color""Buildin native code"
echo -e "$defalut_text_color"
$NDK_ROOT/ndk-build NDK_MODULE_PATH=$COCOS2DX_ROOT:$COCOS2DX_ROOT/cocos2dx/platform/third_party/android/prebuilt
echo -e "$defalut_text_color"
echo -e "$haigt_text_color""Creating package"
echo -e "$haigt_text_color" "ant debug -Dsdk.dir=$SDK_ROOT"
echo -e "$defalut_text_color"

#ant debug -Dsdk.dir=$SDK_ROOT
popd
#popd  el de el root directory


#ret=$($SDK_ROOT/tools/android create project --target $TARGET --name $PROJECT_NAME --path $PROJECT_PATH --activity $ACTIVITY_NAME --package $PROJECT_PACKAGE)

#if [ "$ret" = "l0" ]
#then
#	echo ERRORRRRRRRRRRRRRRRR
#	clear
#	exit -1
#fi


#popd



#/storage/adacosta/WORK/Android/sdk/platform-tools/adb shell am start -a android.intent.action.MAIN -n com.blogspot.pnjb/com.blogspot.pnjb.MainActivity


#ant debug -Dsdk.dir=/storage/adacosta/WORK/Android/sdk/
