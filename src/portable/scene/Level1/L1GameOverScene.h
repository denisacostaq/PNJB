/*! @file L1GameOverScene.h Brebe del fichero.    
    @author Alvaro Denis Acosta Quesada denisacostaq\@gmail.com    
    @date Wed Oct 23 12:05:21 CDT 2013
  
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

#ifndef _GAME_OVER_SCENE_H_
#define _GAME_OVER_SCENE_H_

#include "cocos2d.h"
using namespace cocos2d;

namespace Level1 {
class GameOverLayer : public cocos2d::CCLayerColor
{
public:
    GameOverLayer():_label(NULL) {};
    virtual ~GameOverLayer();
    bool init();
    CREATE_FUNC(GameOverLayer);

    void gameOverDone();

    CC_SYNTHESIZE_READONLY(cocos2d::CCLabelTTF*, _label, Label);
};

class GameOverScene : public cocos2d::CCScene
{
public:
		/**
	 * @brief ...
	 * 
	 * @return cocos2d::CCScene*
	 */
	static cocos2d::CCScene* scene();
	
    GameOverScene():_layer(NULL) {};
    ~GameOverScene();
    bool init();
    CREATE_FUNC(GameOverScene);
  
    CC_SYNTHESIZE_READONLY(GameOverLayer*, _layer, Layer);
};

};
#endif // _GAME_OVER_SCENE_H_