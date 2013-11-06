#include "L3GameLayer.h"

namespace Level3 {

L3GameLayer::L3GameLayer()
{

}

L3GameLayer::~L3GameLayer()
{

}

bool L3GameLayer::init()
{
    if (!CCLayer::init())
    {
        return false;
    }

   // _positionRatio = _winSize.height / MAX_VISIBLE_BRICKS;
    this->setKeypadEnabled(true);
 //   srand(time(NULL));

    initgameScreen();
    initSounds();

    CC_DIRECTOR_->getTouchDispatcher()->addStandardDelegate(this, 0);

    _winSize = CC_DIRECTOR_->getWinSize();
    this->schedule(schedule_selector(L3GameLayer::updateGame));

    return true;
}            
            
void L3GameLayer::updateGame()
{
 
}

void L3GameLayer::initSounds()
{
    if (CC_AUDIO_->isBackgroundMusicPlaying())
    {
        CC_AUDIO_->stopBackgroundMusic();
    }    
	CC_AUDIO_->preloadBackgroundMusic("Level3/bgMusic.mp3");
    CC_AUDIO_->playBackgroundMusic ("Level3/bgMusic.mp3", true);

}

void L3GameLayer::initgameScreen()
{   
    CC_SPRITE_FRM_CACHE_->
		addSpriteFramesWithFile ("Level3/textureTransparentPack.plist");
    _gameBatchNode = CCSpriteBatchNode::create("Level3/textureTransparentPack.png");
    this->addChild(_gameBatchNode, z_index1);

    

    
    CCSprite *pSprite = CCSprite::create("bg01.png");
    pSprite->setAnchorPoint(CCPointZero);
    pSprite->setPosition(CCPointZero);
    this->addChild(pSprite, z_index0);
    
    CCSprite *nave = CCSprite::createWithSpriteFrameName ("ship01.png");
    nave->setAnchorPoint(CCPointZero);
    nave->setPosition(CCPointZero);
    _gameBatchNode->addChild(nave, z_index2);
    
    CCSprite *nave1 = CCSprite::createWithSpriteFrameName ("ship02.png");
    nave1->setAnchorPoint(CCPointZero);
    nave1->setPosition(ccp(20, 50));
    _gameBatchNode->addChild(nave1, z_index2);
    
    CCSprite *nave2 = CCSprite::createWithSpriteFrameName ("ship03.png");
    nave2->setAnchorPoint(CCPointZero);
    nave2->setPosition(ccp(40, 100));
    _gameBatchNode->addChild(nave2, z_index2);
    
    
        CCSprite *cosa = CCSprite::createWithSpriteFrameName ("E5.png");
    cosa->setAnchorPoint(CCPointZero);
    cosa->setPosition(ccp(60, 150));
    _gameBatchNode->addChild(cosa, z_index2);
}

CCScene* L3GameLayer::scene()
{
    cocos2d::CCScene *pScene = cocos2d::CCScene::create();
    cocos2d::CCLayer *pLayer = L3GameLayer::create();
    pScene->addChild(pLayer);
    return pScene;
}

}