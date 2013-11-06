#include "L3Menu.h"

namespace Level3 {

L3Menu::L3Menu()
{

}

L3Menu::~L3Menu()
{

}

CCScene* L3Menu::scene()
{
//  cocos2d::CCScene *pScene = cocos2d::CCScene::create();
//      cocos2d::CCLayer *pLayer = L3Menu::create();
//      pScene->addChild(pLayer);
//  return pScene;
        static cocos2d::CCScene *pScene = NULL;
    if (pScene == NULL)
    pScene = cocos2d::CCScene::create();
    cocos2d::CCLayer *pLayer = L3Menu::create();
    pScene->addChild(pLayer);
    return pScene;
}


bool L3Menu::init()
{
    if (!Levels::init())
    {
        return false;
    }
    this->setKeypadEnabled(true);
    
    initScreen();
    initSounds();
    
    CC_DIRECTOR_->getTouchDispatcher()->addStandardDelegate(this, 0);
    _winSize = CC_DIRECTOR_->getWinSize();
    return true;
}

void L3Menu::creteMenu()
{
    char m[] = "menu.png";
    
    CCSprite *newGameNormal = CCSprite::create(m, 
                                               CCRect(0, 0, 126, 33));
    CCSprite *newGameSelected = CCSprite::create(m,
                                                 CCRect(0, 33, 126, 33));
    CCSprite *newGameDisabled = CCSprite::create(m,
                                                CCRect(0, 33 * 2, 126, 33));
    CCMenuItemSprite *newGame = CCMenuItemSprite::create(
        newGameNormal,
        newGameSelected,
        newGameDisabled,
        menu_selector(L3Menu::playEfectCallback));

    CCSprite *gameSettingsNormal = CCSprite::create(m, 
                                                CCRect(126, 0, 126, 33));
    CCSprite *gameSettingsSelected = CCSprite::create(m, 
                                                CCRect(126, 33, 126, 33));
    CCSprite *gameSettingsDisabled = CCSprite::create(m,
                                                CCRect(126, 33 * 2, 126, 33));
    CCMenuItemSprite *gameSettings = CCMenuItemSprite::create(
        gameSettingsNormal, 
        gameSettingsSelected,
        gameSettingsDisabled,
        menu_selector(L3Menu::setingsCallback));

    CCSprite *aboutNormal = CCSprite::create(m,
                                            CCRect(252, 0, 126, 33));
    CCSprite *aboutSelected = CCSprite::create(m, 
                                            CCRect(252, 33, 126, 33));
    CCSprite *aboutDisabled = CCSprite::create(m, 
                                              CCRect(252, 33 * 2, 126, 33));    
    CCMenuItemSprite *about = CCMenuItemSprite::create(
        aboutNormal, 
        aboutSelected,
        aboutDisabled,
        menu_selector(L3Menu::aboutCallback));

    CCMenu *menu = CCMenu::create(newGame, gameSettings,about, NULL);
    menu->alignItemsVerticallyWithPadding(10);
    this->addChild(menu, 1, 2);
}


void L3Menu::flareEffect(CCObject *parent,
                                  CCObject *pSelectorTarget,
                                  SEL_CallFunc selector)
{   
    CCSprite *flare = CCSprite::create("flare.jpg");
    ccBlendFunc v = {GL_SRC_ALPHA, GL_ONE};
    flare->setBlendFunc(v);
    dynamic_cast<CCNode*>(parent)->addChild(flare, 10);
    flare->setOpacity(0);
    flare->setPosition(ccp(-100, 70));
    flare->setRotation(-120);
    flare->setScale(0.2);

    CCFadeTo *opacityAnim = CCFadeTo::create(0.5, 255);
    CCFadeTo *opacDim = CCFadeTo::create(1, 0);
    CCScaleBy *biggeAnim = CCScaleBy::create(0.7, 1.7, 1.7);
    CCEaseSineOut *biggerEase = CCEaseSineOut::create(biggeAnim);
    CCMoveBy *moveAnim = CCMoveBy::create(0.5, ccp(328, 0));
    CCEaseSineOut *easeMove = CCEaseSineOut::create(moveAnim);
    CCRotateBy *rotateAnim = CCRotateBy::create(2.5, 90);
    CCEaseExponentialOut *rotateEase = 
        CCEaseExponentialOut::create(rotateAnim);
    CCScaleTo *bigger = CCScaleTo::create(0.5, 1);
    CCCallFunc *onComplete = CCCallFunc::create(pSelectorTarget, selector); 
    CCCallFunc *killflare = CCCallFunc::create(flare, 
        callfunc_selector(L3Menu::killflareCallback));
     flare->runAction(CCSequence::create(opacityAnim, biggerEase, opacDim, 
        killflare, onComplete, NULL));
    flare->runAction(easeMove);
    flare->runAction(rotateEase);
    flare->runAction(bigger);
}


void L3Menu::initScreen()
{
    CCSprite *tmp_bg = CCSprite::create("Level3/logo.png");
    tmp_bg->setAnchorPoint(CCPointZero);
    tmp_bg->setPosition(CCPointZero);
    this->addChild(tmp_bg, z_index3);

    tmp_bg = CCSprite::create("Level3/loading.png");
    tmp_bg->setAnchorPoint(CCPointZero);
    tmp_bg->setPosition(CCPointZero);
    this->addChild(tmp_bg, z_index1);
    creteMenu();
}


void L3Menu::playEfectCallback(CCObject* pSender)
{

    flareEffect(dynamic_cast<CCObject*>(pSender), pSender, 
        callfunc_selector(L3Menu::newGameCallback));
}

void L3Menu::initSounds()
{
    CC_AUDIO_->preloadBackgroundMusic(
        CCFileUtils::sharedFileUtils()->
        fullPathForFilename ("mainMainMusic.mp3").c_str());
    CC_AUDIO_->setBackgroundMusicVolume(0.4f);
    CC_AUDIO_->setEffectsVolume(0.6f);
    CC_AUDIO_->setBackgroundMusicVolume(0.4f);
    CC_AUDIO_->playBackgroundMusic ("mainMainMusic.mp3", true);
}

void L3Menu::newGameCallback(CCObject* pSender)
{
    if (CC_AUDIO_->isBackgroundMusicPlaying())
    {
        CC_AUDIO_->stopBackgroundMusic();
    }
    CC_DIRECTOR_->replaceScene(L3GameLayer::scene());
}

void L3Menu::aboutCallback(CCObject* pSender)
{

}

void L3Menu::setingsCallback(CCObject* pSender)
{

}

void L3Menu::killflareCallback(CCObject* pSender)
{

}

}