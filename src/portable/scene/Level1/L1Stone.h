/*! @file L1Stone.h Brebe del fichero.    
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

#ifndef L1STONE_H
#define L1STONE_H

#include "L1b2Sprite.h"

#include "../../AppMacros.h"

namespace Level1 {
	
	class L1GameLayer;
	
class L1Stone :  public L1b2Sprite
{
public:
    L1Stone(L1GameLayer * game, const char *pszFilename, CCPoint position, int 
type);
    ~L1Stone();
	
	static L1Stone* create (L1GameLayer * game, const char *pszFilename,
						  CCPoint position, int type);
	CC_SYNTHESIZE(bool, _inPlay, InPlay)
	
	//void fusioneWith (L1Splash *fixture);

private:
	void initL1Stone ();
	
	const char *_pszFilename;
	CCPoint _startPosition;
};

};
#endif // L1STONE_H
