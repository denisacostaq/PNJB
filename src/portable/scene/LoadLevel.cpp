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


#include "LoadLevel.h"

#include "Level1/L1Menu.h"
//#include "Level2/L2Menu.h"
#include "Level3/L3Menu.h"
LoadLevel::LoadLevel() {
}

LoadLevel::LoadLevel(const LoadLevel& orig) {
}

LoadLevel::~LoadLevel() {
}

CCScene* LoadLevel::buildLevel()
{
    if (CCUserDefault::sharedUserDefault()->isXMLFileExist())
    {
        int level = CCUserDefault::sharedUserDefault()->getIntegerForKey ("level", 1);
        if (level == 1)
        {
            return Level1::L1Menu::scene();
        }
        else if (level == 3)
        {
            return Level3::L3Menu::scene();
        }
        else
        {
            std::cerr << "Level " << level << " not implemented and found in:\n" <<
                CCUserDefault::sharedUserDefault()->getXMLFilePath() << std::endl;
            exit (-1);
        }
    }
    else
    {
        std::cerr << "File not found for User default data" << std::endl;
        return Level1::L1Menu::scene();
    }
}
