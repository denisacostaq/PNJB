/*! @file MenuLayer.h Brebe del fichero.
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


#ifndef MENULAYER_H
#define MENULAYER_H

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"

#include "../AppMacros.h"
#include "ShaderNode.h"
#include "LoadLevel.h"


USING_NS_CC;
using namespace CocosDenshion;
using namespace cocos2d::extension;


//FIXME: Tengo que revisar nuevamente todo el tema de manejo de memoria de coco.
class MenuLayer : public cocos2d::CCLayer
{
public:
    ~MenuLayer ();
    static cocos2d::CCScene* scene ();

    CREATE_FUNC (MenuLayer)

    virtual bool init ();
    

private:
    MenuLayer();


    /*! @brief Create all the screen components.
     */
    void createScreen();


    /*! This create all the menu: Buttons, Toggles, CCLabelTTF, CCControlSlider
     * @brief ...
     *

     * @TODO: this->addChild (m_pBgMusicVolumeLabel);, this->addChild (slider);,
     * pMenuItems->addObject (m_pMenuMuteEffect); ponerlo como hijo de
     */
    void createMenu ();


    /**
     * @brief This create the sun, the vertical green shader is created in other
     * @brief function
     * @sa runSpeaker1_2 ()
     * @return void
     */
    void createShaders();


    /*! @brief This is the striper
     * @brief Create an initializacio for the dancer from Striper.png
     */
    void initActions ();


    /*!
    * @brief This put the name of the game PNJB (PNJB is not jummping bunny).
    */
    void putGameName ();


    /*! @brief This initialice the sound
     * @brief This load the previous value saved, if not found set two default
     * @brief values.
     *
     * @return void
     */
    void initSounds ();


    /**
     * @brief ... holaaaaaaaaaaaa
     *
     * @return void
     */
    void startDance ();


    /*! @brief Aqui es donde se usa el <a href="pepe.pach"><b>parche</b></a>
     * @brief CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()
     * @brief retorna true cunado la musica esta en pause, como la
     * @brief variable pBGMChannel de
     * @brief class CocosDenshion::FmodAudioPlayer es privada no pude
     * @brief heredar de la funcio para reimplementar una clase que use
     * @brief herede de CocosDenshion::FmodAudioPlayer y reimplemente
     * @brief CocosDenshion::FmodAudioPlayer::isBackgroundMusicPlaying()
     * @brief entonces yo usar una clase que herede de
     * @brief CocosDenshion::SimpleAudioEngineFMOD que seria la que
     * @brief tendria mi isBackgroundMusicPlaying() para la platafroma
     * @brief linux
     */
   void dance ();

    
    /*! @brief This start the animation of speackers one and two,
     * @brief This too start the shader
     * @sa runSpeaker3_4(), runSpeaker5(), removeAllAnimations()
     */
    void runSpeaker1_2 ();


    /*! @brief This start the animation of speackers 3 and 4.
     * @sa runSpeaker1_2(), runSpeaker5(), removeAllAnimations()
     */
    void runSpeaker3_4 ();


    /*! @brief This start the animation of speackers five.
     * @sa runSpeaker1_2(), runSpeaker3_4(), removeAllAnimations()
     */
    void runSpeaker5 ();


    /*! @brief Remove the speakers.
  	 * @brief hay que hacerlo porque si no cuando se haga el replace scene se
     * @brief quedan fijasf o sea no participan en el CCTransitionJumpZoom,
     * @brief ademas por eso es util tener las imajenes fijas en el background
     * @sa menuPlayCallback(), dance(),
     */
    void removeAllAnimations ();

    
	/**
	 * @brief Es necesari oprimer o eliminar las speackers 
     * @copydoc MenuLayer::removeAllSpeakers()
	 * @param pSender ...
	 * @return void
     * @sa removeAllSpeakers()
	 */
	void menuPlayCallback(CCObject *pSender);
	    

	/**
	 * @brief ...
	 * 
	 * @param pSneder ...
	 * @return void
	 */	
    void menuCreditsCallback(CCObject *pSneder);


    /**
     * @brief ...
     *
     * @param pSender ...
     * @return void
     */
    void menuExitCallback (CCObject *pSender);


    /*! Change the efect music volume from toggle.
     * @sa menuEfectVolumeCallback(), valueChanged(), updateVolumeValue()
     */
    void menuEfectVolumeCallback (CCObject *pSneder);


    /*! Change the background music volume from toggle.
     * @sa menuEfectVolumeCallback(), valueChanged(), updateVolumeValue()
    */
    void menuBackgroundVolumeCallback (CCObject *pSneder);


    /*! @brief Change backgroun and efect music from slider
     * @sa menuEfectVolumeCallback(), menuBackgroundVolumeCallback(), updateVolumeValue()
     *
     */
    void valueChanged (CCObject *sender, CCControlEvent controlEvent);


    /*!
     * @sa menuEfectVolumeCallback (), menuBackgroundVolumeCallback (), valueChanged
     */
    void updateVolumeValue (CCControlSlider* pSlider, float value);


    /*! @brief Save the values of audio
     *
     */
    void saveConext ();



	/**
	 * @brief The X and Y components of the resolution
	 * 
	 */
	CCSize _winSize;
	
    /*! @brief This is a Button (ToogleButton) for change the value of Efect Music
     * @brief Volume
     * @sa m_pMenuMuteBackgroundMusic
    */
    CCMenuItemToggle *m_pMenuMuteEffect;

    /*! @brief This is a Button (ToogleButton) for change the value of Bacground
     * @brief Music Volume.
     * @sa m_pMenuMuteEffect
    */
    CCMenuItemToggle *m_pMenuMuteBackgroundMusic;

    /*! @brief This is the label for the value of Efect Music Volume
     * @sa m_pBgMusicVolumeLabel
    */
    CCLabelTTF* m_pEfectVolumeLabel;

    /*! @brief This is the label for the value of bacground Music Volume
     * @sa m_pEfectVolumeLabel
    */
    CCLabelTTF* m_pBgMusicVolumeLabel;

    /*! This is the stripper m_gameBatchNode
     * @brief CCSpriteBatchNode is like a batch node: if it contains children,
     * @brief it will draw them in 1 single OpenGL call
	 */	
    CCSpriteBatchNode *m_gameBatchNode;
	
    /*! @brief this is the dancer, he start to dance when the music is play.
     * @brief bla, bla, bla
	 */
    CCSprite *m_dancer;
	
    /*! This is the conter for the transiotions of the dance (@sa m_dancer)
	 * @brief ...
	 * 
	 */
    int m_dancingCount;
    
    /**
     * @brief This enum is fot put tags on the elemnts.
     */
    enum {
        brickSpeaker1Tag,
        brickSpeaker2Tag,
        brickSpeaker3Tag,
        brickSpeaker4Tag,
        brickSpeaker5Tag,
        shaderGreenRaysTag,
        bgMusicControlTag,
        efectMusicControlTag,
        gameNameLabelTag
    }chieldrensTags;

    /**
     * @brief This enum is fot put tags on the elemnts.
     */
    enum {
        _0backGroundIndex,
        _1sunIndex,
        _2brickIndex,
        _3dancerIndex,
        _4,
        _5,
        _6
    }zIndexOfSprites;
};

#endif // MENULAYER_H
