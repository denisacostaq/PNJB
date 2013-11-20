/*! @file L1GameLayer.h Brebe del fichero.    
    @author Alvaro Denis Acosta Quesada denisacostaq\@gmail.com    
    @date Wed Oct 23 11:36:29 CDT 2013
  
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


#ifndef L1GAMELAYER_H
#define L1GAMELAYER_H

#include <string>
#include <iostream>

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Box2D/Box2D.h"

#include "../../AppMacros.h"
#include "L1CollisionListener.h"
#include "L1GameOverScene.h"

#include "L1b2Sprite.h"
#include "L1Stone.h"
#include "L1Splash.h"
#include "L1Bunny.h"

/**
 * @brief ...
 * 
 */
namespace Level1 {

    USING_NS_CC;
    using namespace CocosDenshion;

    //FIXME: supongo que deberia usar ccToucheBegan no ccTouchesBegan ya k no
    //necesito multitouch.

    /**
     * @brief ...
     * 
     */
    class L1GameLayer : public CCLayer {
        //TODO: Aplicar un shader a las paredes pa k se vean mas tallosiks
    private:

        enum {
            _menuTag
        };

        /*! @brief WOW
         * @brief ...
         */
        L1GameLayer();

        /*! @brief SSSSS
         * @brief ASDS
         */
        virtual bool init();

        /*! @brief
         * @brief ...
         * 
         * @return void
         */



        /*! @brief Inicializa el menu
         * @brief _initialPlayerPosition es inicializado a 0, esto se comprueba 
         * @brief en initPhPlayer, si es cero es porque no se ejecuto showTutorial
         * @brief por lo k se posiciona en otro lugar (no cero) si es diferente de
         * @brief 0 entonces el player se inicializa en esta posicion.
         * @return void
         */
        void initMenu();

        /**
         * @brief La musica de background para el L1GameLayer se deja la misma que
         * @brief tenia el L1Menu
         * @return ...
         * 
         */
        void initSounds();        

        /*! Start the game changing the screen but not the scene.
         * @brief Before change the screen this call at explodeMenu()
         * @sa explodeMenu(), menuHowToPlayCallback()
         */
        void menuPlayCallback();        
        
        /*! Explode the menu, this is a effect.
         * @brief Elimina a _menu(CCMenu *) de la lista de hijos por 
         * @brief lo que se debe tener cuidad, si se ejecuta
         * @brief menuHowToPlayCallback() despues explodeMenu ()[eliminando a _
         * menu de la lista], despues se ejecuta menuPlayCallback() pero este no
         * @brief deberia usar a _menu ni llamar a explodeMenu()
         * @sa _menu, menuPlayCallback(), menuHowToPlayCallback()
         */
        void explodeMenu();        
        
        /*! 
         * @brief
         */
        void menuHowToPlayCallback();
        
        /*! @brief state machine.
         * @brief Esta maquina de estado es para hacer que el usuario ejecute
         * @brief los pasos necesarios para mover el conejo.
         * 
         * @return ...
         * 
         */
        void showTutorial();
        
        /*! Touch began helper
         * @brief This is a helper of showTutorial state machine
         * @sa showTutorial(), showTutorialCollaboratorTouchEnd
         * 
         */
        void showTutorialCollaboratorTouchBegand ();
        
        /*! Touch end helper
         * @brief This is a helper of showTutorial state machine
         * @param location This is the location where the touch end.
         * @sa showTutorial(), showTutorialCollaboratorTouchBegand()
         */
        void showTutorialCollaboratorTouchEnd (const CCPoint* location);
        
        void initScoreLabel();
        void initFloor();
        void initActions();
        void initPhEdges();
        void initPhSplash();
        void initPhPlayer();
        void removePhFloorTask();
        void jumps();
        void jumpsActions();
        void updatePhysics();
        void updateGame();
        void scrollScene();
        void updateScore();






        /*! @brief Inicio de un evento touch
         * @brief Se necesita establecer _locationStartTousch antes de la llamada
         * @brief a showTutorialCollaboratorTouches posque esta variable miembro
         * @brief se utiliza dentro de showTutorialCollaboratorTouches().
         * @param touches ...
         * @param event ...
         * @sa ccTouchesEnded (), showTutorialCollaboratorTouches(), 
         * @return void
         */
        virtual void ccTouchesBegan(CCSet* touches, CCEvent* event);

        /**
         * @brief ...
         * 
         * @param touches ...
         * @param event ...
         * @return void
         */
        virtual void ccTouchesEnded(CCSet* touches, CCEvent* event);


        /**
         * @brief ...
         * 
         * @param entry ...
         * @return cocos2d::cc_timeval
         */
        cc_timeval transcurredTime(cocos2d::cc_timeval* entry);



        CCMenu *_menu;
        bool _showingTutorial;
        CCSprite *_bunnyShowTutorial;
        CCAction *_bunnyShowTutorialMove;
        int *_showTutorialState;
        CCLabelTTF * _tutorialLabel;

        int _playerScore;
        L1b2Sprite *_player;
        cocos2d::CCArray *_splashs;
        cocos2d::CCSprite* _floor;
        bool startMove;
        CCPoint _locationStartTousch;
        cc_timeval* _dinamicTime;
        CCSize _winSize;
        /**
         * @brief para eliminar el piso una ves que halla saltado
         * 
         */
        b2Fixture* _phFloor;
        b2Body *_groundBody;

        float _positionRatio;

        bool _gameOver;
        cocos2d::CCLabelTTF* _scoreLabel;
        b2ContactListener *_collisionListener;

        bool *_moveToLefth;
        CCPoint _initialPlayerPosition;

    public:
        //!Destructor de la clase.
        /*!
          @brief Verifica si aún existe una conexión activa, de ser así la elimina.
          @sa L1GameLayer()
         */
        ~L1GameLayer();

        /**
         * @brief ...
         * 
         * @return cocos2d::CCScene*
         */
        static cocos2d::CCScene* scene();

        /**
         * @brief ...
         * 
         * @param pRet ...
         * @return Level1::L1GameLayer*
         */
        CREATE_FUNC(L1GameLayer)
        /**
         * @brief ...
         * 
         */
        CC_SYNTHESIZE(b2World *, _world, World)

    };

};
#endif // L1GAMELAYER_H
