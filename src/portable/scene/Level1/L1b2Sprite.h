/*! @file L1b2Sprite.h Brebe del fichero.    
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

#ifndef B2SPRITE_H
#define B2SPRITE_H

#include "CCSprite.h"
#include "Dynamics/b2Body.h"

#include "CCPlatformMacros.h"
namespace Level1 {

USING_NS_CC;
	class L1GameLayer;
		enum {
        ninguno1,
        ninguno2,
		kSpriteBunny,
		kSpriteBrick
	};

class L1b2Sprite : public CCSprite
{
public:
    L1b2Sprite(L1GameLayer *game, int type);
    ~L1b2Sprite();
    CC_SYNTHESIZE(b2Body *, _body, Body);
    CC_SYNTHESIZE(L1GameLayer *, _game, Game);
	CC_SYNTHESIZE(int, _type, Type)
	
    virtual void setL1b2SpritePosition (CCPoint position);
    virtual void update(float dt);
    virtual void hide(void);
    virtual void reset(void);
    virtual float mag();

private:
};

};
#endif // B2SPRITE_H
