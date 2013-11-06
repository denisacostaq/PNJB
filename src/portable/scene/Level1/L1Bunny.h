/*! @file L1Bunny.h Brebe del fichero.    
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

#ifndef BUNNY_H
#define BUNNY_H

#define BALL_RADIUS 26.0f

#include "L1b2Sprite.h"

namespace Level1 {

	class L1GameLayer;
class L1Bunny :  public L1b2Sprite
{
public:
    L1Bunny (L1GameLayer * game, CCPoint position, int type);
    ~L1Bunny ();
	static L1Bunny* createWithSpriteFrame (L1GameLayer * game, CCPoint 
		position, int type);
	static L1Bunny* createWithSpriteFrameName (L1GameLayer * game, 
		CCPoint position, int type);
	
	/*! @brief un errorcillo por aki
     * @brief esto \"_body->GetLinearVelocity().y <= 1\" se pone por el temblor
     * @brief que hace a veces cuando esta en una piedra, cuando solucione  esto
     * @brief podre poner _body->GetLinearVelocity().y == 0
     */
    bool isCanJump ();
    void setCanJump (bool state);
	CC_SYNTHESIZE (b2Fixture*, _fixture, Fixture)
private:
	
    bool _canJump;
    
	void initL1Bunny();

	CCPoint _startPosition;

};

};
#endif // BUNNY_H
