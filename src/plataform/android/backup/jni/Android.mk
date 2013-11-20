LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := pnjb_shared

LOCAL_MODULE_FILENAME := libpnjb


LOCAL_SRC_FILES := main.cpp \
		../../../../portable/AppMacros.h \
        ../../../../portable/AppDelegate.h \
        ../../../../portable/AppDelegate.cpp \
        ../../../../portable/scene/Level1/L1Menu.h \
        ../../../../portable/scene/Level1/L1Menu.cpp \
        ../../../../portable/scene/MenuLayer.h \
        ../../../../portable/scene/MenuLayer.cpp \
        ../../../../portable/scene/ShaderNode.h \
        ../../../../portable/scene/ShaderNode.cpp \
        ../../../../portable/scene/LoadLevel.h \
        ../../../../portable/scene/LoadLevel.cpp \
        ../../../../portable/scene/Levels.h \
        ../../../../portable/scene/Levels.cpp \
        ../../../../portable/scene/Level1/L1b2Sprite.h \
        ../../../../portable/scene/Level1/L1b2Sprite.cpp \
        ../../../../portable/scene/Level1/L1Bunny.h \
        ../../../../portable/scene/Level1/L1Bunny.cpp \
        ../../../../portable/scene/Level1/L1Stone.h \
        ../../../../portable/scene/Level1/L1Stone.cpp \
        ../../../../portable/scene/Level1/L1Splash.h \
        ../../../../portable/scene/Level1/L1Splash.cpp \
        ../../../../portable/scene/Level1/L1CollisionListener.h \
        ../../../../portable/scene/Level1/L1CollisionListener.cpp \
        ../../../../portable/scene/Level1/L1GameLayer.h \
        ../../../../portable/scene/Level1/L1GameLayer.cpp \
        ../../../../portable/scene/Level1/L1GameOverScene.h \
        ../../../../portable/scene/Level1/L1GameOverScene.cpp \
        ../../../../portable/scene/Level3/L3GameLayer.h \
		../../../../portable/scene/Level3/L3GameLayer.cpp \
		../../../../portable/scene/Level3/L3Menu.h \
		../../../../portable/scene/Level3/L3Menu.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes $(LOCAL_PATH)/../../../../portable \
		$(LOCAL_PATH)/../../../../portable/scene \
		$(LOCAL_PATH)/../../../../portable/scene/Level1 \
		$(LOCAL_PATH)/../../../../portable/scene/Level2 \
		$(LOCAL_PATH)/../../../../portable/scene/Level3 \
		/storage/adacosta/WORK/COCO/cocos2d-x-2.2.0/CocosDenshion/include \
		/storage/adacosta/WORK/COCO/cocos2d-x-2.2.0/extensions \
		/storage/adacosta/WORK/COCO/cocos2d-x-2.2.0/cocos2dx/support \
		/storage/adacosta/WORK/COCO/cocos2d-x-2.2.0/cocos2dx/platform \
		/storage/adacosta/WORK/COCO/cocos2d-x-2.2.0/cocos2dx/base_nodes \
		/storage/adacosta/WORK/COCO/cocos2d-x-2.2.0/external \
		/storage/adacosta/WORK/COCO/cocos2d-x-2.2.0/external/Box2D \
		/storage/adacosta/WORK/COCO/cocos2d-x-2.2.0/cocos2dx/sprite_nodes \
		/storage/adacosta/WORK/COCO/cocos2d-x-2.2.0/cocos2dx/layers_scenes_transitions_nodes \
		/storage/adacosta/WORK/COCO/cocos2d-x-2.2.0/cocos2dx/touch_dispatcher \
		/storage/adacosta/WORK/COCO/cocos2d-x-2.2.0/cocos2dx/menu_nodes \
		/storage/adacosta/WORK/COCO/cocos2d-x-2.2.0/cocos2dx/shaders



LOCAL_WHOLE_STATIC_LIBRARIES = box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,external/Box2D)
$(call import-module,cocos2dx)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
