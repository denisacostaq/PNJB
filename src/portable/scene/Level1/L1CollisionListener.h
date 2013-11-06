/*! @file L1CollisionListener.h Brebe del fichero.    
    @author Alvaro Denis Acosta Quesada denisacostaq\@gmail.com    
    @date Wed Oct 23 12:11:06 CDT 2013
  
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

#ifndef COLLISIONLISTENER_H
#define COLLISIONLISTENER_H

#include "Box2D.h"

#include "L1b2Sprite.h"

#include "../../AppMacros.h"

#include "L1Bunny.h"

#include <iostream>

namespace Level1 {
class L1CollisionListener : public b2ContactListener
{
public:
	L1CollisionListener();
    ~L1CollisionListener();
	
	/**
	 * @brief ...
	 * 
	 * @param contact ...
	 * @return void
	 */
	virtual void BeginContact(b2Contact* contact);
    
	/**
	 * @brief ...
	 * 
	 * @param contact ...
	 * @return void
	 */	
	virtual void EndContact(b2Contact* contact);
    
	
	/**
	 * @brief ...
	 * 
	 * @param contact ...
	 * @param oldManifold ...
	 * @return void
	 */
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    
	//virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* 
	//impulse);
	
private:
};

};
#endif // COLLISIONLISTENER_H
