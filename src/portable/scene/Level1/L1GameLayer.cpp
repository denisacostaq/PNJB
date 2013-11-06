/*! @file L1GameLayer.cpp Brebe del fichero.    
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



#include "L1GameLayer.h"

namespace Level1 {

    L1GameLayer::L1GameLayer()
    : _menu(NULL),
    _showingTutorial(false),
    _bunnyShowTutorial(NULL),
    _bunnyShowTutorialMove(NULL),
    _showTutorialState(NULL),
    _tutorialLabel(NULL),

    _playerScore(0),
    _player(NULL),
    _floor(NULL),
    startMove(false),
    _locationStartTousch(CCPointZero),
    _winSize(0, 0),
    _phFloor(NULL),
    _groundBody(NULL),
    _positionRatio(1.0),
    _gameOver(false),
    _scoreLabel(NULL),
    _collisionListener(NULL),
    _moveToLefth(NULL) {
        _splashs = new CCArray();
        _winSize = CCDirector::sharedDirector()->getWinSize();

        _dinamicTime = new cocos2d::cc_timeval();
    }

    L1GameLayer::~L1GameLayer() {
        delete _collisionListener;
        delete _dinamicTime;
        _world->DestroyBody(_groundBody);
        delete _world;
    }

    cocos2d::CCScene* L1GameLayer::scene() {
        cocos2d::CCScene *pScene = cocos2d::CCScene::create();
        cocos2d::CCLayer *pLayer = L1GameLayer::create();
        pScene->addChild(pLayer);
        return pScene;
    }

    bool L1GameLayer::init() {
        if (!CCLayer::init()) {
            return false;
        }

        _positionRatio = _winSize.height / MAX_VISIBLE_BRICKS;
        this->setKeypadEnabled(true);
        srand(time(NULL));

        CC_DIRECTOR_->getTouchDispatcher()->addStandardDelegate(this, 0);

        initMenu();
        initSounds();

        return true;
    }

    void L1GameLayer::initMenu() {
        CCMenuItemImage *newGame = CCMenuItemImage::create(
            "Level1/new_game.png",
            "Level1/new_game_pressed.png",
            this,
            menu_selector(L1GameLayer::menuPlayCallback));
        newGame->setPosition(ccp(_winSize.width / 2, _winSize.height * .5));

        CCMenuItemImage *howToPlay = CCMenuItemImage::create(
            "Level1/how_to_play.png",
            "Level1/how_to_play_pressed.png",
            this,
            menu_selector(L1GameLayer::menuHowToPlayCallback));
        howToPlay->setPosition(ccp(_winSize.width / 2, _winSize.height * .44));

        _menu = CCMenu::create(newGame, howToPlay, NULL);
        _menu->setPosition(CCPointZero);
        this->addChild(_menu, 20, _menuTag);
    }

    void L1GameLayer::initSounds() {
        if (SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()) {
            SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
        }

        CC_AUDIO_->preloadEffect(CC_FILE_->fullPathForFilename
            ("Sounds/Level1/jump.wav").c_str());
        CC_AUDIO_->preloadEffect(CC_FILE_->fullPathForFilename
            ("Sounds/Level1/uh.wav").c_str());
    }



/******************************************************************************/
/*                       ACTIONS WHEN MENU IS PRESSED                         */
/******************************************************************************/
    void L1GameLayer::menuPlayCallback() {

        if (this->getChildByTag(_menuTag)) {
            _menu->setEnabled(false);
        }

        //init game screen.
        initScoreLabel();
        initFloor();

        initActions();

        //initPhysics
        b2Vec2 gravity;
        gravity.Set(0.0f, -1.0f);
        _world = new b2World(gravity);
        _collisionListener = new L1CollisionListener();
        _world->SetContactListener(_collisionListener);
        initPhEdges();
        initPhSplash();
        initPhPlayer();

        if (this->getChildByTag(_menuTag)) {
            this->schedule(schedule_selector(L1GameLayer::explodeMenu));
        }

        this->schedule(schedule_selector(L1GameLayer::jumps), .9);

        this->schedule(schedule_selector(L1GameLayer::updatePhysics));

        this->schedule(schedule_selector(L1GameLayer::updateGame));

        this->schedule(schedule_selector(L1GameLayer::removePhFloorTask));
    }

    void L1GameLayer::explodeMenu() {
        CCArray *componets = _menu->getChildren();

        CCMenuItemImage *newGame = static_cast<CCMenuItemImage*> (
            componets->objectAtIndex(0));
        if (newGame->getOpacity() > 0) {
            newGame->setOpacity(newGame->getOpacity() - 3.5);
        }
        newGame->setPositionY(newGame->getPositionY() - 5);

        CCMenuItemImage *howToPlay = static_cast<CCMenuItemImage*> (
            componets->objectAtIndex(1));
        if (howToPlay->getOpacity() > 0) {
            howToPlay->setOpacity(howToPlay->getOpacity() - 3.5);
        }
        howToPlay->setPositionY(howToPlay->getPositionY() + 5);

        if (newGame->getPositionY() < 0 &&
            howToPlay->getPositionY() > _winSize.height) {
            this->removeChild(_menu);
            this->unschedule(schedule_selector(L1GameLayer::explodeMenu));
        }
    }

    void L1GameLayer::menuHowToPlayCallback() {
        _menu->setEnabled(false);

        this->schedule(schedule_selector(L1GameLayer::explodeMenu));

        _showingTutorial = true;

        _tutorialLabel = CCLabelTTF::create("", "Times New Roman", 40); //TODO: poner aki una fuente en talla
        _tutorialLabel->setPosition(ccp(_winSize.width * 0.5f,
            _winSize.height * 0.7f));
        this->addChild(_tutorialLabel, 20);
        _tutorialLabel->setVisible(false);


        _bunnyShowTutorial = CCSprite::create("Level1/dona_idle.png");
        _bunnyShowTutorial->setPosition(
            ccp(_winSize.width * 0.5f, _winSize.height * 0.0f));
        this->addChild(_bunnyShowTutorial, 20);

        _bunnyShowTutorialMove = CCMoveTo::create
            (1.0f, ccp(_winSize.width * 0.5f, _winSize.height * 0.5f));
        _bunnyShowTutorialMove->setTag(0);
        _bunnyShowTutorial->runAction(_bunnyShowTutorialMove);
        _showTutorialState = new int (0);
        _moveToLefth = new bool (true);
        this->schedule(schedule_selector(L1GameLayer::showTutorial), .1);
    }

    void L1GameLayer::showTutorial() {
        switch (*_showTutorialState) {
            case 0:
                if (!_bunnyShowTutorial->getActionByTag(0)) {
                    _tutorialLabel->setVisible(true);
                    _tutorialLabel->setString(
                        "Tap the screen\nover the player\nto make this move.");
                    ++(*_showTutorialState);
                }
                break;
            case 3:
                _tutorialLabel->setVisible(false);
                ++*_showTutorialState;
                break;
            case 5:
                if (!_bunnyShowTutorial->getActionByTag(0)) {
                    _tutorialLabel->setVisible(true);
                    _tutorialLabel->setString("press the touch to play");
                    ++*_showTutorialState;
                }
                break;
            case 7:
                delete _showTutorialState;
                delete _moveToLefth;
                menuPlayCallback();
                _showingTutorial = false;

                this->removeChild(_bunnyShowTutorial);
                this->removeChild(_tutorialLabel);

                this->unschedule
                    (schedule_selector(L1GameLayer::showTutorial));
                break;
            default:
                break;
        }

        //NOTE: //this is part of the state machine
        if (*_showTutorialState == 4) {
            if (*_moveToLefth) {
                _bunnyShowTutorialMove = CCMoveTo::create(1.5f,
                    ccp(_bunnyShowTutorial->getContentSize().width / 2,
                    _bunnyShowTutorial->getContentSize().height / 2));
                _initialPlayerPosition = ccp(
                    _bunnyShowTutorial->getContentSize().width / 2,
                    _bunnyShowTutorial->getContentSize().height / 2);
            } else {
                _bunnyShowTutorialMove = CCMoveTo::create(1.5f,
                    ccp(_winSize.width - _bunnyShowTutorial->getContentSize().width / 2,
                    _bunnyShowTutorial->getContentSize().height / 2));
                _initialPlayerPosition = ccp(
                    _winSize.width - _bunnyShowTutorial->getContentSize().width / 2,
                    _bunnyShowTutorial->getContentSize().height / 2);
            }
            _bunnyShowTutorialMove->setTag(0);
            _bunnyShowTutorial->runAction(_bunnyShowTutorialMove);
            ++*_showTutorialState;
        }

        if (*_showTutorialState == 5) {

        }
    }

    void L1GameLayer::showTutorialCollaboratorTouchBegand() {
        //NOTE: esto es solo para el case 1 ggg
        CCRect spriteRect = CCRectMake(
            _bunnyShowTutorial->getPosition().x - _bunnyShowTutorial->getContentSize().width / 2,
            _bunnyShowTutorial->getPosition().y - _bunnyShowTutorial->getContentSize().height / 2,
            _bunnyShowTutorial->getContentSize().width,
            _bunnyShowTutorial->getContentSize().height);
        switch (*_showTutorialState) {
            case 1:
                _tutorialLabel->setString(
                    "Tap the screen\nover the player\nto make this move.");
                if (spriteRect.containsPoint(_locationStartTousch)) {
                    _tutorialLabel->setString("Move the touch\n");
                    ++(*_showTutorialState);
                }
                break;
            case 6:
                _tutorialLabel->setVisible(false);
                ++*_showTutorialState;
                break;
            default:
                break;
        }
    }

    void L1GameLayer::showTutorialCollaboratorTouchEnd(const CCPoint* location) {
        switch (*_showTutorialState) {
            case 2:
                if (_locationStartTousch.x == location->x) {
                    _tutorialLabel->setString(
                        "Tap the screen\nover the player\nto make this move.");
                    *_showTutorialState = 1;
                } else {
                    if (_locationStartTousch.x < location->x) {
                        *_moveToLefth = false;
                    }
                    ++(*_showTutorialState);

                }
                break;
            default:
                break;
        }
    }



/******************************************************************************/
/*                                INIT                                        */
/******************************************************************************/
    void L1GameLayer::initScoreLabel() {
        CCSprite* scorePannel = CCSprite::create("Level1/score_panel.png");
        scorePannel->setPosition(ccp(_winSize.width / 2,
            _winSize.height - (scorePannel->getContentSize().height / 2)));
        scorePannel->setVisible(true);
        this->addChild(scorePannel, z_index5);

        _scoreLabel = CCLabelTTF::create("0", "Felt", 32);
        _scoreLabel->setColor(ccc3(116, 78, 57));
        _scoreLabel->setPosition(ccp(_winSize.width / 2, _winSize.height -
            (_scoreLabel->getTextureRect().size.height * 0.75)));

        _scoreLabel->setString("0");
        _scoreLabel->setVisible(true);

        this->addChild(_scoreLabel, z_index6);
    }

    void L1GameLayer::initFloor() {
        _floor = CCSprite::create("Level1/floor.jpg");
        _floor->setAnchorPoint(CCPointZero);
        _floor->setPosition(CCPointZero);

        this->addChild(_floor, z_index1);
    }

    void L1GameLayer::initActions() {
        CCArray *playerAnimationFrames = new CCArray();
        //TODO: esto seria un problema para el multi size CCRectMake(0, 0, 96, 122)
        playerAnimationFrames->addObject(
            CCSpriteFrame::create("Level1/dona_idle.png", CCRectMake(0, 0, 96, 122)));
        playerAnimationFrames->addObject(
            CCSpriteFrame::create("Level1/dona_jumping.png",
            CCRectMake(0, 0, 96, 122)));
        // Create player animation from the animation frames
        CCAnimation* playerAnimation = CCAnimation::createWithSpriteFrames(
            playerAnimationFrames);
        // Add player animation to animation cache
        CCAnimationCache::sharedAnimationCache()->addAnimation(playerAnimation,
            "PlayerAnimation");
        // Player animation frames are stored by the player animation
        CC_SAFE_RELEASE_NULL(playerAnimationFrames);
    }

    void L1GameLayer::initPhEdges() {
        // Create edges around the entire screen
        b2BodyDef groundBodyDef;
        groundBodyDef.position.Set(0, 0);

        _groundBody = _world->CreateBody(&groundBodyDef);
        b2EdgeShape groundEdge;
        b2FixtureDef boxShapeDef;
        boxShapeDef.shape = &groundEdge;

        //0000 0000 0000 0001 --> 0x0001
        boxShapeDef.filter.categoryBits = 1 << 0;

        //wall definitions
        groundEdge.Set(b2Vec2(0, 0), b2Vec2(_winSize.width / PTM_RATIO, 0));
        _phFloor = _groundBody->CreateFixture(&boxShapeDef);

        //0000 0000 0000 0010 --> 0x0002
        boxShapeDef.filter.categoryBits = 1 << 1;
        boxShapeDef.restitution = 0.4f;
        boxShapeDef.friction = 0.0f;

        groundEdge.Set(b2Vec2(0, 0), b2Vec2(0, _winSize.height / PTM_RATIO));
        _groundBody->CreateFixture(&boxShapeDef);

        groundEdge.Set(b2Vec2(0, _winSize.height / PTM_RATIO),
            b2Vec2(_winSize.width / PTM_RATIO, _winSize.height / PTM_RATIO));
        _groundBody->CreateFixture(&boxShapeDef);

        groundEdge.Set(b2Vec2(_winSize.width / PTM_RATIO,
            _winSize.height / PTM_RATIO), b2Vec2(_winSize.width / PTM_RATIO, 0));
        _groundBody->CreateFixture(&boxShapeDef);
    }

    //TODO: Esta funcion hay que arreglarla que hay tremenda cochina de cpdigo.
    //y ademas l funcion void L1Splash::initBrincks()

    void L1GameLayer::initPhSplash() {
        L1Splash* tmp1 = L1Splash::create(this, "Level1/carmelite_background.png",
            CCPointZero, 0);
        tmp1->setL1b2SpritePosition(ccp(
            ((L1Splash*) tmp1->getBody()->GetUserData())->
            getContentSize().width / 2,
            ((L1Splash*) tmp1->getBody()->GetUserData())->
            getContentSize().height / 2));
        //el centro de este esta en 210x350
        _splashs->addObject(tmp1);
        this->addChild(tmp1, 1);

        L1Splash* tmp2 = L1Splash::create(this, "Level1/carmelite_background.jpg",
            CCPointZero, 0);
        tmp2->setL1b2SpritePosition(ccp(
            ((L1Splash*) tmp2->getBody()->GetUserData())->
            getContentSize().width / 2,
            ((L1Splash*) tmp1->getBody()->GetUserData())->
            getContentSize().height / 2 +
            ((L1Splash*) tmp2->getBody()->GetUserData())->
            getContentSize().height));
        //el centro de este esta en 210x1050
        _splashs->addObject(tmp2);
        this->addChild(tmp2, 1);
    }

    void L1GameLayer::initPhPlayer() {
        //TODO: los nombres estos no tienen sentido ej: createWithSpriteFrameName
        _player = L1Bunny::createWithSpriteFrameName(this, CCPointZero, kSpriteBunny);
        //FIXME: sa void L1Bunny::initL1Bunny()
        //con algo como esto se arreglaria
        //_bunny->setDisplayFrameWithAnimationName ("PlayerAnimation", 0);

        if (_initialPlayerPosition.x == CCPointZero.x &&
            _initialPlayerPosition.y == CCPointZero.y) {
            _player->setL1b2SpritePosition(ccp(
                _winSize.width / 2,
                _player->getContentSize().height));
        } else {
            _player->setL1b2SpritePosition(_initialPlayerPosition);
        }
        this->addChild(_player, 5);
        _player->getBody()->ApplyLinearImpulse(b2Vec2(0, 5), b2Vec2(0, 0));
    }



/******************************************************************************/
/*                            SCHEDULERS                                      */
/******************************************************************************/
    void L1GameLayer::removePhFloorTask() {
        if (_playerScore > 0) {
            _groundBody->DestroyFixture(_phFloor);
            this->unschedule(schedule_selector(L1GameLayer::removePhFloorTask));
        }
    }

    void L1GameLayer::jumps() {
        if (((L1Bunny*)_player)->isCanJump())
        {
            //TODO: para que no salte en el aire hay k hacer algo...
            // 	b2Vec2 velocity = static_cast<L1Bunny*>(_bunny)->getFixture()->
            // 		GetBody()->GetLinearVelocity();
            // 		std::cout << velocity.y << std::endl;
            // 	if (velocity.y <= 0)
            // 	{

            this->schedule(schedule_selector(L1GameLayer::jumpsActions), .2);
            _player->setDisplayFrameWithAnimationName("PlayerAnimation", 1);
            _player->getBody()->ApplyLinearImpulse(b2Vec2(0, 5), b2Vec2(0, 0));
            ((L1Bunny*)_player)->setCanJump (false);
            CC_AUDIO_->playEffect("Sounds/Level1/jump.wav");
            // 	}
        }        
    }

    void L1GameLayer::jumpsActions() {
        _player->setDisplayFrameWithAnimationName("PlayerAnimation", 0);
        this->unschedule(schedule_selector(L1GameLayer::jumpsActions));
    }

    void L1GameLayer::updatePhysics() {
        _world->Step(.1, 10, 10);
        for (b2Body *b = _world->GetBodyList(); b; b = b->GetNext()) {
            if (b->GetUserData() != NULL) {
                CCSprite *ballData = dynamic_cast<CCSprite*> (
                    (CCSprite *) b->GetUserData());
                ballData->setPosition(ccp(b->GetPosition().x * PTM_RATIO,
                    b->GetPosition().y * PTM_RATIO));
                ballData->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
            }
        }
    }

    void L1GameLayer::updateGame() {
        if (_gameOver) {
            this->unschedule(schedule_selector(L1GameLayer::updateGame));
            this->unschedule(schedule_selector(L1GameLayer::updatePhysics));
            this->unschedule(schedule_selector(L1GameLayer::jumps));
            stopAllActions();
            CC_AUDIO_->stopBackgroundMusic();
            CC_AUDIO_->playEffect("Sounds/Level1/uh.wav", false); //CC_AUDIO_->stopAllEffects();
            char scoreText[128];
            memset(scoreText, 0, sizeof (scoreText));
            sprintf(scoreText, "%d", _playerScore);
            CC_DIRECTOR_->replaceScene(
                CCTransitionFade::create(1.0f, GameOverScene::scene()));
            return;
        } else {
            scrollScene();
        }
    }

    void L1GameLayer::scrollScene() {
        float pos = _player->getBody()->GetPosition().y * PTM_RATIO;
        if (pos <= 0) {
            _gameOver = true;
        }
        float scrollBase = _winSize.height * 0.5f;
        if (pos > scrollBase) {
            updateScore();
            float scrollMove = scrollBase - pos;

            _player->setL1b2SpritePosition(ccp(
                _player->getBody()->GetPosition().x * PTM_RATIO,
                _player ->getBody()->GetPosition().y * PTM_RATIO + scrollMove));

            L1Splash *tmpL1Splash1 = static_cast<L1Splash*>
                (_splashs->objectAtIndex(0));
            tmpL1Splash1->setL1b2SpritePosition(ccp(
                tmpL1Splash1->getBody()->GetPosition().x * PTM_RATIO,
                tmpL1Splash1->getBody()->GetPosition().y * PTM_RATIO + scrollMove));
            L1Splash *tmpL1Splash2 = static_cast<L1Splash*>
                (_splashs->objectAtIndex(1));
            tmpL1Splash2->setL1b2SpritePosition(ccp(
                tmpL1Splash2->getBody()->GetPosition().x * PTM_RATIO,
                tmpL1Splash2->getBody()->GetPosition().y * PTM_RATIO + scrollMove));

            if (tmpL1Splash1->getPositionY() +
                tmpL1Splash1->getContentSize().height / 2 <= 0) {
                tmpL1Splash1->setL1b2SpritePosition
                    (ccp(tmpL1Splash1->getBody()->GetPosition().x * PTM_RATIO,
                    tmpL1Splash2->getBody()->GetPosition().y * PTM_RATIO +
                    tmpL1Splash2->getContentSize().height));
                tmpL1Splash1->repositioneBeginningWithLatestBrink();
            }
            if (tmpL1Splash2->getPositionY() +
                tmpL1Splash2->getContentSize().height / 2 <= 0) {
                tmpL1Splash2->setL1b2SpritePosition(
                    ccp(tmpL1Splash2->getBody()->GetPosition().x * PTM_RATIO,
                    tmpL1Splash1->getBody()->GetPosition().y * PTM_RATIO +
                    tmpL1Splash1->getContentSize().height));
                tmpL1Splash2->repositioneBeginningWithLatestBrink();
            }
        }
    }

    void L1GameLayer::updateScore() {
        _playerScore++;
        char scoreText[32];
        memset(scoreText, 0, sizeof (scoreText));
        sprintf(scoreText, "%d", _playerScore);
        _scoreLabel->setString(scoreText);
    }



/******************************************************************************/
/*                                   TOUCH                                    */
/******************************************************************************/
    void L1GameLayer::ccTouchesBegan(CCSet* touches, CCEvent* event) {
        CCTouch* touch = (CCTouch*) (touches->anyObject());
        _locationStartTousch = touch->getLocation();

        if (_showingTutorial) {
            showTutorialCollaboratorTouchBegand();
        } else {
            b2Vec2 touchLocation = b2Vec2(_locationStartTousch.x / PTM_RATIO,
                _locationStartTousch.y / PTM_RATIO);
            if (static_cast<L1Bunny*> (_player)->
                getFixture()->TestPoint(touchLocation)) {
                startMove = true;
                CCTime::gettimeofdayCocos2d(_dinamicTime, NULL);
            }
        }
    }

    void L1GameLayer::ccTouchesEnded(CCSet* touches, CCEvent* event) {
        CCTouch* touch = (CCTouch*) (touches->anyObject());
        CCPoint location = touch->getLocation();

        if (_showingTutorial) {
            showTutorialCollaboratorTouchEnd(&location);
        } else {
            if (startMove) {
                cc_timeval t = transcurredTime(_dinamicTime);
                long microseconds = t.tv_sec * 1000000 + t.tv_usec;
                //NOTE: ponerle inteligencia a los brik en el posicionado     
                float val = (-(_locationStartTousch.x - location.x) /
                             float(microseconds / 100000));
                val = val < -500 ? -500 : val;
                val = val > 500 ? 500 : val;
                b2Vec2 force(val*.02, 0);
                _player->getBody()->ApplyLinearImpulse(force,
                    b2Vec2(_player->getPositionX(), _player->getPositionY()));
                _player->getBody()->GetLinearVelocity();
                startMove = false;
            }
        }
    }

    cc_timeval L1GameLayer::transcurredTime(cc_timeval* entry) {
        cc_timeval time_current;
        CCTime::gettimeofdayCocos2d(&time_current, NULL);

        int microseconds = (time_current.tv_sec - entry->tv_sec) * 1000000 +
            ((int) time_current.tv_usec - (int) entry->tv_usec);

        cc_timeval t = {microseconds / 1000000, microseconds % 1000000};
        return t;
    }

}
