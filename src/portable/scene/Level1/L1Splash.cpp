/*! @file L1Splash.cpp Brebe del fichero.    
    @author Alvaro Denis Acosta Quesada denisacostaq\@gmail.com    
    @date Wed Oct 23 12:06:57 CDT 2013
  
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

#include "L1Splash.h"
#include "L1GameLayer.h"

namespace Level1 {
L1Splash::L1Splash (L1GameLayer * game, const char *pszFilename, CCPoint position, 
int type) :
L1b2Sprite (game, type)
{
	_game = game;
	_pszFilename = pszFilename;
	_startPosition = position;
	_winSize = CC_DIRECTOR_->getWinSize();
    _positionRatio = _winSize.height / MAX_VISIBLE_BRICKS;
	
	_bricks = new CCArray ();
}

L1Splash::~L1Splash()
{
	
}

L1Splash* L1Splash::create(L1GameLayer* game, const char *pszFilename, CCPoint 
position, int type)
{
	L1Splash *splash = new L1Splash (game, pszFilename, position, type);
	if (splash)
	{
		splash->initL1Splash();
		splash->initBrincks();
		splash->autorelease();
		return splash;
	}
	CC_SAFE_DELETE (splash);
	return NULL;
}

void L1Splash::initL1Splash()
{

	this->initWithFile (_pszFilename);
	this->setPosition (ccp (_startPosition.x, _startPosition.y));
	
	//create box2d body
    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody;
	bodyDef.userData = this;
	bodyDef.position.Set (_startPosition.x/PTM_RATIO, 
		_startPosition.y/PTM_RATIO);

	_body = _game->getWorld()->CreateBody(&bodyDef);

    //create rectangle shape
    b2PolygonShape  rectangle;
	
    rectangle.SetAsBox ((this->getContentSize().width*.5)/PTM_RATIO, 
		(this->getContentSize().height*.5)/PTM_RATIO);

	//define fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &rectangle;
    fixtureDef.density = 1.0f;
    fixtureDef.restitution = 0.0;
	//0000 0000 0000 0100 -> 0x0004
	fixtureDef.filter.categoryBits = 1<<2;
	fixtureDef.friction = 0.2f;
	_body->CreateFixture(&fixtureDef);

    setL1b2SpritePosition(_startPosition);
}

L1Splash *L1Splash::_recentSplash = NULL;

	//TODO: ver void L1GameLayer::initPhSplash()
void L1Splash::initBrincks()
{/*
	float t = getRandom (62, 420-62)-_winSize.width/2;
	float y = 0;
	if (_recentSplash)
	{
		t = 0;
		y = 0;
	}
	else
	{
		_recentSplash = this;
		t = 0;
		y = 0;
	}
	
	L1Stone *brick = NULL;
	brick = L1Stone::create (_game, "carmelite_brink.png", 
		ccp(t, y), kSpriteBrick);
	fusioneWithThis (brick);
	_game->addChild (brick, 23);*/
	
	
	
	//TODO: el anchor point cambia de aki a new game sa
	//repositioneBeginningWithLatestBrink
// 		L1Stone *brick = NULL;
// 	//int startY = 0;
// 	for (int i = 0; i < 1; i++)
//  	{
// 		brick = L1Stone::create (_game, "carmelite_brink.png", 
// 			CCPointZero, kSpriteBrick);
// 		brick->setL1b2SpritePosition (CCPointZero);
// 		std::cout << brick->getPositionX() << std::endl;
// 		fusioneWithThis (brick);
// 		_game->addChild (brick, 3);
// 		_bricks->addObject (brick);
//  	}
// 	repositioneBeginningWithLatestBrink();
	
	
	
	L1Stone *brick = NULL;
	int startY = -this->getContentSize().height/2;
	for (int i = 0; i < MAX_BRICKS; i++)
 	{
		brick = L1Stone::create (_game, "Level1/carmelite_brink.png", 
			CCPointZero, kSpriteBrick);
		std::cout << brick->getContentSize().width << " "
		<< brick->getContentSize().height << std::endl;
		brick->setL1b2SpritePosition (ccp (getRandomX(brick) - _winSize.width/2,
										   startY + (i + 1) * _positionRatio));
		fusioneWithThis (brick);
		_game->addChild (brick, 3);
		_bricks->addObject (brick);
 	}
}

void L1Splash::fusioneWithThis(L1b2Sprite *brick)
{
	b2PrismaticJointDef joinDef;

	joinDef.Initialize (this->getBody(), brick->getBody(), 
	b2Vec2 (210/PTM_RATIO, 350/PTM_RATIO), b2Vec2 (1.0f, 0.0f));
	
	static_cast<b2PrismaticJoint*>
	(_game->getWorld()->CreateJoint (&joinDef));

 	joinDef.localAxisA = b2Vec2 (0.0f, 1.0f);
 	static_cast<b2PrismaticJoint*> 
 		(_game->getWorld()->CreateJoint (&joinDef));
}

int L1Splash::getRandomX(L1Stone* sprite)
{
    return getRandom (sprite->getContentSize().width/2,
					  _winSize.width - sprite->getContentSize().width/2);
}

int L1Splash::getRandom(int min, int max)
{
    return (rand() % (max - min)) + min;
}

void L1Splash::repositioneBeginningWithLatestBrink()
{
	//TODO: sa initBrincks
// 		CCObject* iterator = NULL;
//     CCARRAY_FOREACH(_bricks, iterator) {
// 		L1Stone* brick = dynamic_cast<L1Stone*> (iterator);
// 		brick->setL1b2SpritePosition (CCPointZero);
// 	}
	
	
	CCObject* iterator = NULL;
    CCARRAY_FOREACH(_bricks, iterator) {
		L1Stone* brick = dynamic_cast<L1Stone*> (iterator);
		brick->setL1b2SpritePosition (ccp (
			getRandomX(brick) - _winSize.width/2, brick->getPositionY()));
	}
}

L1Stone* L1Splash::getLatestBrink()
{
	return this->_latestBrink;
}


}