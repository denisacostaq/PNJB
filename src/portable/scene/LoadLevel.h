/*! @file LoadLevel.cpp Brebe del fichero.    
    @author Alvaro Denis Acosta Quesada denisacostaq\@gmail.com    
    @date Tue Oct 29 12:42:24 CDT 2013
  
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

#ifndef LOADLEVEL_H
#define	LOADLEVEL_H

#include <string>

#include "cocos2d.h"

USING_NS_CC;

class LoadLevel {
public:
    LoadLevel();
    LoadLevel(const LoadLevel& orig);
    virtual ~LoadLevel();
    
    /*! @brief load the level saved, if not found load level1
     */
    CCScene* buildLevel ();
    
private:

};

#endif	/* LOADLEVEL_H */

