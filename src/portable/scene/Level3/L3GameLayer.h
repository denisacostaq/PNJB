#ifndef LEVEL3GAMELAYER_H
#define LEVEL3GAMELAYER_H

#include "CCLayer.h"
#include "CCDirector.h"
#include "CCTouchDispatcher.h"
#include "CCScene.h"
#include "CCSprite.h"
#include "CCSpriteBatchNode.h"
#include "CCMenuItem.h"


#include "GL/gl.h"

#include "CCSpriteFrameCache.h"




#include "../../AppMacros.h"
#include "../Level1/L1GameLayer.h"


#include <iostream>

namespace Level3 {
USING_NS_CC;



#define menu_selector(_SELECTOR) (SEL_MenuHandler)(&_SELECTOR)

class L3GameLayer : public CCLayer{
	public:
		L3GameLayer();
		~L3GameLayer();
		CREATE_FUNC(L3GameLayer)
        static cocos2d::CCScene* scene();
private:
	virtual bool init();
	
	CCSize _winSize;
    void initgameScreen();	
    void initSounds();
	
	void updateGame();
	CCSpriteBatchNode *_gameBatchNode;
};


};

#endif // LEVEL3GAMELAYER_H