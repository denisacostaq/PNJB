/*! @file L1Stone.cpp Brebe del fichero.    
    @author Alvaro Denis Acosta Quesada denisacostaq\@gmail.com    
    @date Wed Oct 23 12:08:07 CDT 2013
  
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

#include "L1Stone.h"
#include "L1GameLayer.h"

namespace Level1 {
L1Stone::L1Stone(L1GameLayer * game, const char *pszFilename, CCPoint 
position, int type) 
:
L1b2Sprite(game, type)
{
	_pszFilename = pszFilename;
	_startPosition = position;
	_inPlay = true;}

L1Stone::~L1Stone()
{
	
}

L1Stone* L1Stone::create(L1GameLayer* game, const char *pszFilename,
					 CCPoint position, int type)
{
	L1Stone *brink = new L1Stone (game, pszFilename, position, type);
	if (brink)
	{
		brink->initL1Stone();
		brink->autorelease();
		return brink;
	}
	
	CC_SAFE_DELETE (brink);
	return NULL;
}

void L1Stone::initL1Stone()
{
	this->initWithFile (_pszFilename);
	this->setPosition (ccp (_startPosition.x, _startPosition.y));
	
	//create box2d body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
	bodyDef.userData = this;
	bodyDef.fixedRotation = true;
	bodyDef.position.Set (_startPosition.x/PTM_RATIO, 
		_startPosition.y/PTM_RATIO);
	_body = _game->getWorld()->CreateBody (&bodyDef);
	
	//create rectangle shape
    b2PolygonShape  rectangle;
    rectangle.SetAsBox (this->getContentSize().width*.5/PTM_RATIO,
		this->getContentSize().height*.5/PTM_RATIO);

	//define fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &rectangle;
	fixtureDef.friction = 0.2f;
	fixtureDef.density = 3.0f;
	fixtureDef.restitution = 0.0f;

	//0000 0000 0001 0000
	fixtureDef.filter.categoryBits = 1<<4;
	fixtureDef.filter.maskBits = 0xFFFF & ~0x0004 & ~0x0001 & ~0x0002;
	_body->CreateFixture(&fixtureDef);

    //setL1b2SpritePosition(_startPosition);
}

}
