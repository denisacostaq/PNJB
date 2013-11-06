/*! @file L1Bunny.cpp Brebe del fichero.    
    @author Alvaro Denis Acosta Quesada denisacostaq\@gmail.com    
    @date Wed Oct 23 12:10:09 CDT 2013
  
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

#include "L1Bunny.h"
#include "L1GameLayer.h"

namespace Level1 {
L1Bunny::L1Bunny(L1GameLayer * game, CCPoint position, int type)
: L1b2Sprite(game, type),
    _canJump (true)
{
	_startPosition = position;
}

L1Bunny::~L1Bunny()
{

}

L1Bunny* L1Bunny::createWithSpriteFrame (L1GameLayer * game, CCPoint 
position, int type)
{

	L1Bunny *bunny = new L1Bunny (game, position, type);
	if (bunny)
	{
		bunny->initL1Bunny();
		bunny->autorelease();
		return bunny;
	}

	CC_SAFE_DELETE (bunny);
	return NULL;
}

L1Bunny* L1Bunny::createWithSpriteFrameName (L1GameLayer * game, CCPoint 
	position, int type)
{

	L1Bunny *bunny = new L1Bunny (game, position, type);
	if (bunny)
	{
		bunny->initL1Bunny();
		bunny->autorelease();
		return bunny;
	}    

	CC_SAFE_DELETE (bunny);
	return NULL;
}

void L1Bunny::initL1Bunny()
{
	//FIXME: esto (initWithFile("dona_idle.png");) no va aqui, lo pongo para que 
	//el Sprite tenga tamanno y la biblioteca fisica pueda calcular la masa 
	//del cuerpo al llamar a 
	//_body->CreateFixture(&fixtureDef);, 
	//sa _body = _game->getWorld()->CreateBody(&bodyDef); 
	//sa 	bodyDef.userData = this;
	initWithFile("Level1/dona_idle.png");


	this->setPosition (ccp (_startPosition.x, _startPosition.y));

	//create box2d body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
	bodyDef.userData = this;
	bodyDef.fixedRotation = true;
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
	fixtureDef.friction = 0.2f;
	//0000 0000 0000 1000
	fixtureDef.filter.categoryBits = 1<<3;
	fixtureDef.filter.maskBits = 0xFFFF & ~0x0004;
	_fixture = _body->CreateFixture(&fixtureDef);
		
    setL1b2SpritePosition(_startPosition);
}

void L1Bunny::setCanJump (bool state)
{
    _canJump = state;
}

bool L1Bunny::isCanJump()
{
    return _canJump && _body->GetLinearVelocity().y >= -.2;
}

}