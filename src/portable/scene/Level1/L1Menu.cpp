/*! @file L1Menu.cpp Brebe del fichero.    
    @author Alvaro Denis Acosta Quesada denisacostaq\@gmail.com    
    @date Wed Oct 23 12:06:10 CDT 2013
  
    @brief Este fichero ...
 
    @attention <h1><center>&copy; COPYRIGHT 
    GNU GENERAL PUBLIC LICENSE Version 2, June 1991</center></h1>
    
    @copyright    

    <h3>This file is part of PNJB program, a short 2D game.</h3>
    Copyright (C) 2013  Alvaro Denis Acosta Quesada denisacostaq\@gmail.com
 
	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.
 
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
 
	You should have received a copy of the GNU General Public License along
	with this program; if not, write to the Free Software Foundation, Inc.,
	51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

 */


#include "L1Menu.h"

namespace Level1 {
L1Menu::L1Menu()
{
}


L1Menu::~L1Menu()
{
    //CC_SAFE_RELEASE(_ddsf);
}

cocos2d::CCScene* L1Menu::scene()
{
    cocos2d::CCScene *pScene = cocos2d::CCScene::create();
    L1Menu *pLayer = L1Menu::create();
    pScene->addChild(pLayer);

    return pScene;
}

void L1Menu::update (float dt)
{
    return;
}

bool L1Menu::init()
{
    if (!Levels::init()) {
        return false;
    }

    _winSize = CCDirector::sharedDirector()->getWinSize();
    initSounds();
    initgameScreen();

    return true;
}

void L1Menu::initgameScreen()
{
    CCSprite *bg = CCSprite::create ("Level1/local-of-NASA.png");
    bg->setPosition(ccp(0.5*_winSize.width, 0.5*_winSize.height));
    this->addChild(bg, kBackground);

    createMenu();
}

void L1Menu::initSounds()
{
	if (SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
	{
		SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	}



	CC_AUDIO_->preloadBackgroundMusic (CC_FILE_->
		fullPathForFilename ("Sounds/Level1/background.ogg").c_str());
	CC_AUDIO_->playBackgroundMusic (CC_FILE_->
		fullPathForFilename ("Sounds/Level1/background.ogg").c_str());
	
//
//     SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
//     SimpleAudioEngine::sharedEngine()->stopAllEffects();
//     CCDirector::sharedDirector()->replaceScene(L1GameLayer::scene());
}

void L1Menu::createMenu()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCMenuItemImage *pGoNextItem = CCMenuItemImage::create(
            "Level1/go-next.png",
            "Level1/go-next.png",
            this,
            menu_selector(L1Menu::menuGoNextCallback));
        pGoNextItem->setPosition(ccp(winSize.width/2,  winSize.height*.4));

   CCMenuItemImage *pGoPreviousItem = CCMenuItemImage::create(
        "Level1/go-previous.png",
        "Level1/go-previous.png",
        this,
        menu_selector(L1Menu::menuGoPreviousCallback));
    pGoPreviousItem->setPosition(ccp(winSize.width/2, winSize.height*.25));

    CCMenu *pMenu = CCMenu::create(pGoNextItem, pGoPreviousItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu,  1);
}


void L1Menu::menuGoNextCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f,
        L1GameLayer::scene()));
}

void L1Menu::menuGoPreviousCallback(CCObject* pSender)
{
    //CCDirector::sharedDirector()->replaceScene(MenuLayer::scene());
}
}
