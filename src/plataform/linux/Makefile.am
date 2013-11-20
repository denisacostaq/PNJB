if DEBUG
COCOS_LIB_PATH=$(COCOS2DX_ROOT)@PLATAFORM_LIBS_PATH@/debug
else
COCOS_LIB_PATH=$(COCOS2DX_ROOT)@PLATAFORM_LIBS_PATH@/release
endif

AUTOMAKE_OPTIONS = subdir-objects
CC_FLAGS = -MMD -Wall -fPIC
AM_CPPFLAGS = -MMD -Wall -fPIC -D @PLATAFORM@

AM_CPPFLAGS += -I $(COCOS2DX_ROOT)/cocos2dx
AM_CPPFLAGS += -I $(COCOS2DX_ROOT)/cocos2dx/include
AM_CPPFLAGS += -I $(COCOS2DX_ROOT)/cocos2dx/platform
AM_CPPFLAGS += -I $(COCOS2DX_ROOT)/cocos2dx/platform/linux
AM_CPPFLAGS += -I $(COCOS2DX_ROOT)/cocos2dx/kazmath/include
AM_CPPFLAGS += -I $(COCOS2DX_ROOT)/cocos2dx/layers_scenes_transitions_nodes
AM_CPPFLAGS += -I $(COCOS2DX_ROOT)/cocos2dx/cocoa
AM_CPPFLAGS += -I $(COCOS2DX_ROOT)/cocos2dx/sprite_nodes
AM_CPPFLAGS += -I $(COCOS2DX_ROOT)/cocos2dx/support
AM_CPPFLAGS += -I $(COCOS2DX_ROOT)/cocos2dx/menu_nodes
AM_CPPFLAGS += -I $(COCOS2DX_ROOT)/extensions
AM_CPPFLAGS += -I $(COCOS2DX_ROOT)/extensions/CocoStudio/CCArmature/display
AM_CPPFLAGS += -I $(COCOS2DX_ROOT)/cocos2dx/textures
AM_CPPFLAGS += -I $(COCOS2DX_ROOT)/cocos2dx/label_nodes
AM_CPPFLAGS += -I $(COCOS2DX_ROOT)/cocos2dx/base_nodes
AM_CPPFLAGS += -I $(COCOS2DX_ROOT)/cocos2dx/touch_dispatcher
AM_CPPFLAGS += -I $(COCOS2DX_ROOT)/cocos2dx/actions
AM_CPPFLAGS += -I $(COCOS2DX_ROOT)/cocos2dx/shaders
AM_CPPFLAGS += -I $(COCOS2DX_ROOT)/cocos2dx

AM_CPPFLAGS += -I $(COCOS2DX_ROOT)/cocos2dx/platform/third_party/linux/libtiff/include

AM_CPPFLAGS += -I $(COCOS2DX_ROOT)/external
AM_CPPFLAGS += -I $(COCOS2DX_ROOT)/external/Box2D
AM_CPPFLAGS += -I $(COCOS2DX_ROOT)/external/Box2D/Dynamics

AM_CPPFLAGS += -I $(COCOS2DX_ROOT)/CocosDenshion/include

AM_CPPFLAGS += -I $(COCOS2DX_ROOT)/extensions
AM_CPPFLAGS += -I $(COCOS2DX_ROOT)/extensions/GUI
AM_CPPFLAGS += -I $(COCOS2DX_ROOT)/extensions/GUI/CCControlExtension


bin_PROGRAMS = pnjb

pnjb_SOURCES = \
		../../portable/AppMacros.h \
        main.cpp \
        ../../portable/AppDelegate.h \
        ../../portable/AppDelegate.cpp \
        ../../portable/scene/Level1/L1Menu.h \
        ../../portable/scene/Level1/L1Menu.cpp \
        ../../portable/scene/MenuLayer.h \
        ../../portable/scene/MenuLayer.cpp \
        ../../portable/scene/ShaderNode.h \
        ../../portable/scene/ShaderNode.cpp \
        ../../portable/scene/LoadLevel.h \
        ../../portable/scene/LoadLevel.cpp \
        ../../portable/scene/Levels.h \
        ../../portable/scene/Levels.cpp \
        ../../portable/scene/Level1/L1b2Sprite.h \
        ../../portable/scene/Level1/L1b2Sprite.cpp \
        ../../portable/scene/Level1/L1Bunny.h \
        ../../portable/scene/Level1/L1Bunny.cpp \
        ../../portable/scene/Level1/L1Stone.h \
        ../../portable/scene/Level1/L1Stone.cpp \
        ../../portable/scene/Level1/L1Splash.h \
        ../../portable/scene/Level1/L1Splash.cpp \
        ../../portable/scene/Level1/L1CollisionListener.h \
        ../../portable/scene/Level1/L1CollisionListener.cpp \
        ../../portable/scene/Level1/L1GameLayer.h \
        ../../portable/scene/Level1/L1GameLayer.cpp \
        ../../portable/scene/Level1/L1GameOverScene.h \
        ../../portable/scene/Level1/L1GameOverScene.cpp \
        ../../portable/scene/Level3/L3GameLayer.h \
		../../portable/scene/Level3/L3GameLayer.cpp \
		../../portable/scene/Level3/L3Menu.h \
		../../portable/scene/Level3/L3Menu.cpp


pnjb_LDADD = \
	$(COCOS_LIB_PATH)/libcocosdenshion.so \
        $(COCOS_LIB_PATH)/libcocos2d.so \
        $(COCOS_LIB_PATH)/libbox2d.a \
        $(COCOS_LIB_PATH)/libextension.a


pnjb_LDFLAGS =  @GLS_LIBS@
