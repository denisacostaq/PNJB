/*! @file L1b2Sprite.cpp Brebe del fichero.    
    @author Alvaro Denis Acosta Quesada denisacostaq\@gmail.com    
    @date Wed Oct 23 12:09:34 CDT 2013
  
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

#include "L1b2Sprite.h"
#include "L1GameLayer.h"
 

namespace Level1 {
L1b2Sprite::L1b2Sprite(L1GameLayer * game, int type)
{	
	_game = game;
	_type = type;
}

L1b2Sprite::~L1b2Sprite()
{

}

void L1b2Sprite::setL1b2SpritePosition(cocos2d::CCPoint position)
{
	_body->SetAwake (true);
	setPosition(position);

	//update box2d body if any
    if (_body)
	{
        _body->SetTransform( b2Vec2( position.x / PTM_RATIO,
									 position.y/ PTM_RATIO),
									 _body->GetAngle());
    }
}

void L1b2Sprite::update(float dt)
{

}

void L1b2Sprite::hide(void )
{

}

void L1b2Sprite::reset(void )
{

}

float L1b2Sprite::mag()
{
	return .0f;
}

}