/*! @file L1Splash.h Brebe del fichero.    
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

#ifndef SPLASH_H
#define SPLASH_H

#include "L1b2Sprite.h"
#include "L1Stone.h"
#include "L1b2Sprite.h"
#include "../../AppMacros.h"

namespace Level1 {

	#define MAX_BRICKS 6
	#define MAX_VISIBLE_BRICKS 6

class L1Splash : public L1b2Sprite
{
public:
    L1Splash (L1GameLayer * game, const char *pszFilename, CCPoint position,
			int type);
    ~L1Splash();
	static L1Splash* create (L1GameLayer * game, const char *pszFilename,
						   CCPoint position, int color);
	
	L1Stone *getLatestBrink();
	
	/**
	 * @brief ...
	 * 
	 */
	void repositioneBeginningWithLatestBrink();

private:
	
	void initL1Splash ();
    void initBrincks();
	void fusioneWithThis (L1b2Sprite* brick);
	
		/**
	 * @brief ...
	 * 
	 * @param sprite ...
	 * @return int
	 */
	int getRandomX(L1Stone* sprite);
    
	/**
	 * @brief ...
	 * 
	 * @param min ...
	 * @param max ...
	 * @return int
	 */
	int getRandom(int min, int max);


	float _positionRatio;
	
	const char *_pszFilename;
	CCPoint _startPosition;
	
	cocos2d::CCArray *_bricks;
	L1Stone *_latestBrink;
	static L1Splash *_recentSplash;
	cocos2d::CCSize _winSize;
};

};
#endif // SPLASH_H
