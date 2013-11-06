/*! @file L1CollisionListener.cpp Brebe del fichero.    
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

#include "L1CollisionListener.h"

namespace Level1 {
L1CollisionListener::~L1CollisionListener()
{

}

L1CollisionListener::L1CollisionListener()
{

}

void L1CollisionListener::PreSolve(b2Contact* contact,
								   const b2Manifold* oldManifold)
{
	b2Body *bodyBunny = contact->GetFixtureA()->GetBody();
	b2Body *bodyBrinck = contact->GetFixtureB()->GetBody();
	
	L1b2Sprite *bunny = dynamic_cast <L1b2Sprite*> 
		((L1b2Sprite*)bodyBunny->GetUserData());
	L1b2Sprite *brinck = dynamic_cast <L1b2Sprite*> 
		((L1b2Sprite*)bodyBrinck->GetUserData());

	if (bunny && brinck) {
		if ((bunny->getType() == kSpriteBunny &&
			brinck->getType() == kSpriteBrick) ||
			(bunny->getType() == kSpriteBrick &&
			brinck->getType() == kSpriteBunny) )
		{
			if (bunny->getType() != kSpriteBunny)
			{
				swap <L1b2Sprite*>(bunny, brinck);
				swap <b2Body*>(bodyBunny, bodyBrinck);
			}

			float bunnyBottom = bunny->getPositionY() - 
				(bunny->getContentSize().height)/2;

			float brinckTop = brinck->getPositionY() + 
				(brinck->getContentSize().height)/2;

			if (!(bunnyBottom < brinckTop &&
				bunnyBottom + 20 > brinckTop &&
				bodyBunny->GetLinearVelocity().y <= 0))
			{
				contact->SetEnabled (false);
			}
		}
	}
}
    
    void L1CollisionListener::BeginContact(b2Contact* contact)
	{
	b2Body *bodyBunny = contact->GetFixtureA()->GetBody();
	b2Body *bodyOther = contact->GetFixtureB()->GetBody();
	
	L1b2Sprite *bunny = dynamic_cast <L1b2Sprite*> 
		((L1b2Sprite*)bodyBunny->GetUserData());
	L1b2Sprite *other = dynamic_cast <L1b2Sprite*> 
		((L1b2Sprite*)bodyOther->GetUserData());
    if (bunny || other)
    {
        if (!bunny)
        {            
            swap <L1b2Sprite*>(bunny, other);
        }
        else if (bunny->getType() != kSpriteBunny)
        {
            swap <L1b2Sprite*>(bunny, other);
        }
        if (bunny->getType() == kSpriteBunny)
        {
            dynamic_cast <L1Bunny*> (bunny)->setCanJump (true);
        }
    }
    
	//TODO: Aqui va el cambio de hacer siempre un Linear impulse hacia arriva.
	//if (bodyBunny)
		//bodyBunny->SetLinearVelocity (b2Vec2 (0, 1));
	
	}

void L1CollisionListener::EndContact ( b2Contact* contact )
{

}

}
