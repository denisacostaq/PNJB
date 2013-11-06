/*! @file MenuLayer.cpp Brebe del fichero.    
    @author Alvaro Denis Acosta Quesada denisacostaq\@gmail.com    
    @date Thu Oct 24 23:34:00 CDT 2013
  
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

#include "MenuLayer.h"

MenuLayer::MenuLayer()
    : m_pMenuMuteEffect(NULL),
      m_pMenuMuteBackgroundMusic (NULL),
      m_pEfectVolumeLabel (NULL),
      m_pBgMusicVolumeLabel (NULL),
      m_gameBatchNode (NULL),
      m_dancer (NULL),
      m_dancingCount (0)
{	
}



MenuLayer::~MenuLayer()
{
    //FIXME: esto hay que hacerlo...
}



CCScene* MenuLayer::scene()
{
    CCScene *scene = CCScene::create();
    CCLayer *layer = MenuLayer::create();
	layer->retain();
	layer->autorelease();
    scene->addChild(layer);
    return scene;
}



bool MenuLayer::init()
{
    if (!CCLayer::create())
    {
        return false;
    }

    _winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
	
    setTouchEnabled(true);
    scheduleUpdate();

    this->setKeypadEnabled(true);
	
    createScreen ();

    initSounds ();	

	this->schedule(schedule_selector(MenuLayer::startDance), 7.7);
    
    this->schedule(schedule_selector(MenuLayer::runSpeaker3_4), 27.5);
    
    this->schedule(schedule_selector(MenuLayer::runSpeaker5), 48);
    
    return true;
}




void MenuLayer::createScreen()
{
    //Backgroundd
    CCSprite *bg = CCSprite::create("MenuLayer/splash_screen.png");
    bg->setPosition(ccp(_winSize.width/2,  _winSize.height/2));
    this->addChild(bg, _0backGroundIndex);
	
    CCSprite *sprite = CCSprite::create ("MenuLayer/Sun.png");
    sprite->setPosition (ccp(_winSize.width*.93, _winSize.height*.96));
    this->addChild (sprite, _1sunIndex);

    sprite = CCSprite::create ("MenuLayer/Brick.png");
    sprite->setPosition (ccp(_winSize.width*.85, _winSize.height*.85));
    sprite->setOpacity (150);
    this->addChild (sprite, _2brickIndex);

    createMenu ();

    createShaders ();

    putGameName ();

    initActions ();
}



void MenuLayer::createMenu ()
{
    /**************************************************************************/
    /*                                 Buttons                                */
    /**************************************************************************/
    CCArray *pMenuItems = CCArray::create();

    CCMenuItemImage *pPlayItem = CCMenuItemImage::create(
        "MenuLayer/play_button.png",
        "MenuLayer/play_button_pressed.png",
        this,
        menu_selector(MenuLayer::menuPlayCallback));
    pPlayItem->setPosition (ccp(_winSize.width/2,  _winSize.height*.48));
    pMenuItems->addObject (pPlayItem);

   CCMenuItemImage *pCreditsItem = CCMenuItemImage::create(
        "MenuLayer/credits_button.png",
        "MenuLayer/credits_button_pressed.png",
        this,
        menu_selector(MenuLayer::menuCreditsCallback));
    pCreditsItem->setPosition(ccp(_winSize.width/2, _winSize.height*.33));
    pMenuItems->addObject (pCreditsItem);

    CCMenuItemImage *pExitItem = CCMenuItemImage::create(
        "MenuLayer/exit.png",
        "MenuLayer/exit_pressed.png",
        this,
        menu_selector(MenuLayer::menuExitCallback));
    pExitItem->setPosition(ccp(_winSize.width*.93,  _winSize.height*.04));
    pMenuItems->addObject (pExitItem);
    
    /**************************************************************************/
    /*                                 Toggles                                */
    /**************************************************************************/
    CCArray *pStatesOfToggles = CCArray::create();

    CCMenuItemImage *pAudioState = CCMenuItemImage::create (
        "MenuLayer/audio-volume-muted.png",
        "MenuLayer/audio-volume-muted.png");
    pStatesOfToggles->addObject (pAudioState);
    
    pAudioState = CCMenuItemImage::create (
        "MenuLayer/audio-volume-low.png",
        "MenuLayer/audio-volume-low.png");
    pStatesOfToggles->addObject (pAudioState);
    
    pAudioState = CCMenuItemImage::create (
        "MenuLayer/audio-volume-medium.png",
        "MenuLayer/audio-volume-medium.png");
    pStatesOfToggles->addObject (pAudioState);
    
    pAudioState = CCMenuItemImage::create (
        "MenuLayer/audio-volume-high.png",
        "MenuLayer/audio-volume-high.png");
    pStatesOfToggles->addObject (pAudioState);
    
    m_pMenuMuteBackgroundMusic = CCMenuItemToggle::createWithTarget (this,
        menu_selector(MenuLayer::menuBackgroundVolumeCallback),
        pStatesOfToggles);    
    m_pMenuMuteBackgroundMusic->setPosition(ccp(_winSize.width*.1,
        _winSize.height*.1));
    pMenuItems->addObject (m_pMenuMuteBackgroundMusic);

    pStatesOfToggles->removeAllObjects();

    pAudioState = CCMenuItemImage::create (
        "MenuLayer/audio-volume-muted.png",
        "MenuLayer/audio-volume-muted.png");
    pStatesOfToggles->addObject (pAudioState);

    pAudioState = CCMenuItemImage::create (
        "MenuLayer/audio-volume-low.png",
        "MenuLayer/audio-volume-low.png");
    pStatesOfToggles->addObject (pAudioState);

    pAudioState = CCMenuItemImage::create (
        "MenuLayer/audio-volume-medium.png",
        "MenuLayer/audio-volume-medium.png");
    pStatesOfToggles->addObject (pAudioState);

    pAudioState = CCMenuItemImage::create (
        "MenuLayer/audio-volume-high.png",
        "MenuLayer/audio-volume-high.png");
    pStatesOfToggles->addObject (pAudioState);

    m_pMenuMuteEffect = CCMenuItemToggle::createWithTarget (this,
        menu_selector(MenuLayer::menuEfectVolumeCallback),
        pStatesOfToggles);
    m_pMenuMuteEffect->setPosition(ccp(_winSize.width*.1,  _winSize.height*.2));
    pMenuItems->addObject (m_pMenuMuteEffect);

    CCMenu *pMenu = CCMenu::createWithArray (pMenuItems);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /**************************************************************************/
    /*                               CCLabelTTF                               */
    /*         Add a label in which the slider value will be displayed        */
    /**************************************************************************/
    m_pBgMusicVolumeLabel = CCLabelTTF::create("NULL" ,"Marker Felt", 32);
    m_pBgMusicVolumeLabel->retain();
    m_pBgMusicVolumeLabel->setPosition(ccp(_winSize.width *.85f,
                                           _winSize.height *.1f));
    this->addChild (m_pBgMusicVolumeLabel);

    m_pEfectVolumeLabel = CCLabelTTF::create("NULL" ,"Marker Felt", 32);
    m_pEfectVolumeLabel->retain();
    m_pEfectVolumeLabel->setPosition(ccp(_winSize.width *.85f,
                                     _winSize.height *.2f));
    this->addChild (m_pEfectVolumeLabel);

    /**************************************************************************/
    /*                             CCControlSlider                            */
    /**************************************************************************/
    CCControlSlider *slider = CCControlSlider::create(
                "MenuLayer/sliderTrack.png",
                "MenuLayer/sliderProgress.png",
                "MenuLayer/sliderThumb.png");
    slider->setMinimumValue(0.0f); // Sets the min value of range
    slider->setMaximumValue(1.0f); // Sets the max value of range
    slider->setPosition(ccp(_winSize.width *.44f, _winSize.height *.20f));
    slider->setTag(efectMusicControlTag);
    // When the value of the slider will change, the given selector will be call
    slider->addTargetWithActionForControlEvents(this,
        cccontrol_selector(MenuLayer::valueChanged),
        CCControlEventValueChanged);
    this->addChild (slider);

    slider = CCControlSlider::create(
                "MenuLayer/sliderTrack.png",
                "MenuLayer/sliderProgress.png",
                "MenuLayer/sliderThumb.png");
    slider->setMinimumValue(0.0f); // Sets the min value of range
    slider->setMaximumValue(1.0f); // Sets the max value of range
    slider->setPosition(ccp(_winSize.width *.44f, _winSize.height *.1f));
    slider->setTag(bgMusicControlTag);
    // When the value of the slider will change, the given selector will be call
    slider->addTargetWithActionForControlEvents(
                this,
                cccontrol_selector(MenuLayer::valueChanged),
                CCControlEventValueChanged);
    this->addChild (slider);
}



void MenuLayer::createShaders()
{
    ShaderNode *sn = ShaderNode::shaderNodeWithVertex(
        "Shaders/MenuLayer/Common.vsh",
        "Shaders/MenuLayer/Sun.fsh");
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    sn->setPosition(ccp(s.width/2, s.height/2));
    this->addChild(sn, _1sunIndex);
}



void MenuLayer::initActions()
{
    CC_SPRITE_FRM_CACHE_->addSpriteFramesWithFile ("MenuLayer/Striper.plist");
    m_gameBatchNode = CCSpriteBatchNode::create("MenuLayer/Striper.png");
    this->addChild(m_gameBatchNode, z_index1);

    CCArray *_playerAnimationFrames = new CCArray();
    char sprite[200];
    for (int i = 0; i <= 196; i++)
    {
        memset (sprite, 0, sizeof (sprite));
        if (i < 10)
        {
            sprintf(sprite, "Striper-00%d.png", i);
        } else if (i < 100)
        {
            sprintf(sprite, "Striper-0%d.png", i);
        } else if (i >= 100)
        {
            sprintf(sprite, "Striper-%d.png", i);
        }
        _playerAnimationFrames->addObject (CCSpriteFrameCache::
            sharedSpriteFrameCache()->spriteFrameByName(sprite));
    }

    CCAnimation* playerAnimation = CCAnimation::createWithSpriteFrames(
            _playerAnimationFrames);
    CCAnimationCache::sharedAnimationCache()->addAnimation(
        playerAnimation, "PlayerAnimation");

    m_dancer = CCSprite::create();
    m_dancer->setDisplayFrameWithAnimationName ("PlayerAnimation",
        m_dancingCount++);
    m_dancer->setPosition (ccp(_winSize.width*.85, _winSize.height*.9));
    m_dancer->setOpacity (100);
    this->addChild (m_dancer, _3dancerIndex);
}



void MenuLayer::putGameName ()
{
    // Upper Label
    CCLabelBMFont *label =
            CCLabelBMFont::create("PNJB", "Fonts/MenuLayer/helvetica-32.fnt");
    label->setScale (2);
    label->setTag (gameNameLabelTag);
    this->addChild (label);

    label->setPosition( ccp(_winSize.width*.35, _winSize.height*.763) );
    label->setAnchorPoint( ccp(0.5f, 0.5f) );


    CCSprite* BChar = (CCSprite*) label->getChildByTag(0);
    CCSprite* FChar = (CCSprite*) label->getChildByTag(1);
    CCSprite* AChar = (CCSprite*) label->getChildByTag(2);


    CCActionInterval* rotate = CCRotateBy::create(2, 360);
    CCAction* rot_4ever = CCRepeatForever::create(rotate);

    CCActionInterval* scale = CCScaleBy::create(2, .5f);
    CCActionInterval* scale_back = scale->reverse();
    CCSequence* scale_seq = CCSequence::create(scale, scale_back,NULL);
    CCAction* scale_4ever = CCRepeatForever::create(scale_seq);

    CCActionInterval* jump = CCJumpBy::create(0.5f, CCPointZero, 60, 1);
    CCAction* jump_4ever = CCRepeatForever::create(jump);

    CCActionInterval* fade_out = CCFadeOut::create(1);
    CCActionInterval* fade_in = CCFadeIn::create(1);
    CCSequence* seq = CCSequence::create(fade_out, fade_in, NULL);
    CCAction* fade_4ever = CCRepeatForever::create(seq);

    BChar->runAction(rot_4ever);
    BChar->runAction(scale_4ever);
    FChar->runAction(jump_4ever);
    AChar->runAction(fade_4ever);
}



//FIXME: si vlc tiene pulse se parte el control de volumen
void MenuLayer::initSounds()
{
    float efectVolume = 0.0;
    float bgMusicVolume = 0.0;

    if (CCUserDefault::sharedUserDefault()->isXMLFileExist())
    {
        efectVolume = CCUserDefault::sharedUserDefault()->
                getFloatForKey ("m_fEfectVolume", .6);
        bgMusicVolume = CCUserDefault::sharedUserDefault()->
                getFloatForKey ("m_fBgMusicVolume", .4);
    }
    else
    {
        std::cerr << "User default configuration file not found" <<
            std::endl;
    }

    CC_AUDIO_->preloadBackgroundMusic
            ("Sounds/MenuLayer/background.mp3");
    CC_AUDIO_->playBackgroundMusic ("Sounds/MenuLayer/background.mp3");

    CC_AUDIO_->setBackgroundMusicVolume (.0f);
    CC_AUDIO_->setEffectsVolume (.0f);

    CCControlSlider* bgVolumeControl = static_cast <CCControlSlider*>(
        this->getChildByTag (bgMusicControlTag));
    CCControlSlider* efectVolumeControl = static_cast <CCControlSlider*>(
        this->getChildByTag (efectMusicControlTag));

    efectVolumeControl->setValue (efectVolume);
    bgVolumeControl->setValue (bgMusicVolume);

    char val[200];
    memset (val, 0, sizeof (val));
    sprintf( val, "%.0f%%\n", bgMusicVolume*100);
    m_pBgMusicVolumeLabel->setString (val);
    memset (val, 0, sizeof (val));
    sprintf( val, "%.0f%%\n", efectVolume*100);
    m_pEfectVolumeLabel->setString (val);

    updateVolumeValue (bgVolumeControl, bgMusicVolume);
    updateVolumeValue (efectVolumeControl, efectVolume);
}



void MenuLayer::startDance()
{
	this->schedule (schedule_selector(MenuLayer::dance), .1);
    runSpeaker1_2 ();
	this->unschedule (schedule_selector(MenuLayer::startDance));
}



void MenuLayer::dance()
{
    m_dancer->setDisplayFrameWithAnimationName ("PlayerAnimation",
        m_dancingCount++%197);
    if (!CC_AUDIO_->isBackgroundMusicPlaying())
    {
        removeAllAnimations();
        if (this->getChildByTag(shaderGreenRaysTag))
        {
            this->removeChildByTag (shaderGreenRaysTag, true);
        }
        
        m_dancer->setDisplayFrameWithAnimationName ("PlayerAnimation", 0);

        this->unschedule (schedule_selector (MenuLayer::dance));
    }
}



void MenuLayer::runSpeaker1_2()
{
    ShaderNode *sn = ShaderNode::shaderNodeWithVertex(
        "Shaders/MenuLayer/Common.vsh",
        "Shaders/MenuLayer/VerticalGREEN.fsh");
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    sn->setPosition(ccp(s.width/2, s.height/2));
    this->addChild(sn, 2, shaderGreenRaysTag);

    CCSprite *speaker1  = CCSprite::create("MenuLayer/speaker1.png");
    this->addChild (speaker1, 0, brickSpeaker1Tag);
    speaker1->setPosition (ccp(_winSize.width*.075, _winSize.height*.98));

    CCSprite *speaker2  = CCSprite::create("MenuLayer/speaker1.png");
    this->addChild (speaker2, 0, brickSpeaker2Tag);
    speaker2->setPosition (ccp(_winSize.width*.231, _winSize.height*.924));

    CCRipple3D *speaker1Action = CCRipple3D::create(
        3,
        CCSizeMake (speaker1->getContentSize().width,
                    speaker1->getContentSize().height*.5),
        ccp (speaker1->getPositionX(),
             speaker1->getPositionY() + speaker1->getContentSize().height*.4),
        speaker1->getContentSize().width,
        5,
        speaker1->getContentSize().height*.1);
    speaker1->runAction ( CCRepeatForever::create(speaker1Action));

    CCRipple3D *speaker2Action = CCRipple3D::create(
        3,
        CCSizeMake (speaker2->getContentSize().width ,
                    speaker2->getContentSize().height*.5),
        ccp (speaker2->getPositionX(),
             speaker2->getPositionY() + speaker2->getContentSize().height*.4),
        speaker2->getContentSize().width,
        5,
        speaker2->getContentSize().height*.1);
    speaker2->runAction ( CCRepeatForever::create(speaker2Action));
    this->unschedule (schedule_selector(MenuLayer::runSpeaker1_2));
}



void MenuLayer::runSpeaker3_4()
{
    CCSprite *speaker3  = CCSprite::create("MenuLayer/speaker3.png");
    this->addChild (speaker3, 0, brickSpeaker3Tag);
    speaker3->setPosition (ccp(_winSize.width*.14, _winSize.height*.615));

    CCSprite *speaker4  = CCSprite::create("MenuLayer/speaker3.png");
    this->addChild (speaker4, 0, brickSpeaker4Tag);
    speaker4->setPosition (ccp(_winSize.width*.501, _winSize.height*.602));

    CCRipple3D *speaker3Action = CCRipple3D::create(
        3,
        CCSizeMake(speaker3->getContentSize().width ,
                   speaker3->getContentSize().height*.5),
        ccp(speaker3->getPositionX(),
            speaker3->getPositionY() + speaker3->getContentSize().height*.4),
        speaker3->getContentSize().width,
        5,
        speaker3->getContentSize().height*.1);
    speaker3->runAction ( CCRepeatForever::create(speaker3Action));

    CCRipple3D *speaker4Action = CCRipple3D::create(
        3,
        CCSizeMake(speaker4->getContentSize().width ,
                   speaker4->getContentSize().height*.5),
        ccp(speaker4->getPositionX(),
            speaker4->getPositionY() + speaker4->getContentSize().height*.4),
        speaker4->getContentSize().width,
        5,
        speaker4->getContentSize().height*.1);
    speaker4->runAction ( CCRepeatForever::create(speaker4Action));

    this->unschedule (schedule_selector(MenuLayer::runSpeaker3_4));
}



void MenuLayer::runSpeaker5()
{
    CCSprite *speaker5  = CCSprite::create("MenuLayer/speaker5.png");
    this->addChild (speaker5, 0, brickSpeaker5Tag);
    speaker5->setPosition (ccp(_winSize.width*.76, _winSize.height*.604));

    CCRipple3D *speaker5Action = CCRipple3D::create(
        4,
        CCSizeMake(speaker5->getContentSize().width ,
                   speaker5->getContentSize().height*.5),
        ccp(speaker5->getPositionX(),
            speaker5->getPositionY() + speaker5->getContentSize().height*.4),
        speaker5->getContentSize().width,
        8,
        speaker5->getContentSize().height*.1);
    speaker5->runAction ( CCRepeatForever::create(speaker5Action));

    this->unschedule(schedule_selector(MenuLayer::runSpeaker5));
}



void MenuLayer::removeAllAnimations()
{
    CCNode *s = NULL;
    if ((s = getChildByTag (brickSpeaker1Tag)))
    {
        s->stopAllActions ();
        this->removeChild (s, true);
    }
    if ((s = getChildByTag (brickSpeaker2Tag)))
    {
        s->stopAllActions ();
        this->removeChild (s, true);
    }
    if ((s = getChildByTag (brickSpeaker3Tag)))
    {
                s->stopAllActions ();
        this->removeChild (s, true);
    }
    if ((s = getChildByTag (brickSpeaker4Tag)))
    {
                s->stopAllActions ();
        this->removeChild (s, true);
    }
    if ((s = getChildByTag (brickSpeaker5Tag)))
    {
        s->stopAllActions ();
        this->removeChild (s, true);
    }

    if ((s = this->getChildByTag (gameNameLabelTag)))
    {
        s->getChildByTag (0)->stopAllActions();
        s->getChildByTag (1)->stopAllActions();
        s->getChildByTag (2)->stopAllActions();
    }
}



void MenuLayer::menuPlayCallback(CCObject *pSender)
{
    removeAllAnimations();

    saveConext ();

    LoadLevel factory;
	CC_DIRECTOR_->replaceScene(
		CCTransitionJumpZoom::create(2.5f, factory.buildLevel()));
}



void MenuLayer::menuCreditsCallback(CCObject *pSneder)
{
    std::cout << "denisacostaq@gmail.com" << std::endl;
}



void MenuLayer::menuEfectVolumeCallback(CCObject *pSneder)
{
    CCControlSlider* efectVolume = static_cast <CCControlSlider*>(
        this->getChildByTag (efectMusicControlTag));
    float value = 0.0;
    switch (((CCMenuItemToggle*)pSneder)->getSelectedIndex()) {
    case 0:
        value = .00f;
        break;
    case 1:
        value = .30f;
        break;
    case 2:
        value = .60f;
        break;
    case 3:
        value = .90f;
        break;
    default:
        break;
    }
    efectVolume->setValue(value);
    updateVolumeValue (efectVolume, value);
}


void MenuLayer::menuBackgroundVolumeCallback(CCObject *pSneder)
{
    CCControlSlider* bgVolume = static_cast <CCControlSlider*>(
        this->getChildByTag (bgMusicControlTag));
    float value = 0.0;
    switch (((CCMenuItemToggle*)pSneder)->getSelectedIndex()) {
    case 0:
        value = .00f;
        break;
    case 1:
        value = .30f;
        break;
    case 2:
        value = .60f;
        break;
    case 3:
        value = .90f;
        break;
    default:
        break;
    }
    bgVolume->setValue(value);
    updateVolumeValue (bgVolume, value);
}


void MenuLayer::valueChanged(CCObject *sender, CCControlEvent controlEvent)
{
    CCControlSlider* pSlider = (CCControlSlider*)sender;
    updateVolumeValue (pSlider, pSlider->getValue());
}



void MenuLayer::updateVolumeValue (CCControlSlider* pSlider, float value)
{
    if(pSlider->getTag() == bgMusicControlTag)
    {
        if (CC_AUDIO_->getBackgroundMusicVolume () == value)
        {
            return;
        }

        char val[200];
        memset (val, 0, sizeof (val));
        sprintf( val, "%.0f%%\n", value*100);
        m_pBgMusicVolumeLabel->setString (val);

        if (value <= 0.01 )
        {
            m_pMenuMuteBackgroundMusic->setSelectedIndex (0);
        }
        else if (value > 0.01 && value <= 0.311)
        {
            m_pMenuMuteBackgroundMusic->setSelectedIndex (1);
        }
        else if (value > 0.311 && value <= 0.611)
        {
            m_pMenuMuteBackgroundMusic->setSelectedIndex (2);
        }
        else if (value > 0.6)
        {
            m_pMenuMuteBackgroundMusic->setSelectedIndex (3);
        }
        CC_AUDIO_->setBackgroundMusicVolume (value);
    }
    else if(pSlider->getTag() == efectMusicControlTag)
    {
        if (CC_AUDIO_->getEffectsVolume() == value)
        {
            return;
        }

        char val[200];
        memset (val, 0, sizeof (val));
        sprintf( val, "%.0f%%\n", value*100);
        m_pEfectVolumeLabel->setString (val);

        if (value <= 0.01 )
        {
            m_pMenuMuteEffect->setSelectedIndex (0);
        }
        else if (value > 0.01 && value <= 0.311)
        {
            m_pMenuMuteEffect->setSelectedIndex (1);
        }
        else if (value > 0.311 && value <= 0.611)
        {
            m_pMenuMuteEffect->setSelectedIndex (2);
        }
        else if (value > 0.6)
        {
            m_pMenuMuteEffect->setSelectedIndex (3);
        }
        CC_AUDIO_->setEffectsVolume (value);
    }
}



void MenuLayer::saveConext()
{
    if (CCUserDefault::sharedUserDefault()->isXMLFileExist())
    {
        CCUserDefault::sharedUserDefault()->
                setFloatForKey ("m_fEfectVolume",
                                CC_AUDIO_->getEffectsVolume());
        CCUserDefault::sharedUserDefault()->
                setFloatForKey ("m_fBgMusicVolume",
                                CC_AUDIO_->getBackgroundMusicVolume());
    }
    else
    {
        std::cerr << "User default configuration file not found" <<
            std::endl;
        exit (-1);
    }
}



void MenuLayer::menuExitCallback(CCObject *pSender)
{
    saveConext();
    CC_AUDIO_->end();
    CC_DIRECTOR_END();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
