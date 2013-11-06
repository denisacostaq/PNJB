/*! @file AppMacros.h definitions of macros.
    @author Alvaro Denis Acosta Quesada denisacostaq\@gmail.com    
    @date Thu Oct 24 23:18:00 CDT 2013
  
    @brief This file rename some frequentile methods as macros, and too include
    @brief \"ccMacros.h\" from cocos2dx

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


#ifndef _APPMACROS_H
#define _APPMACROS_H

#include "ccMacros.h"

#define CC_OPENGL_VIEW_ cocos2d::CCEGLView::sharedOpenGLView()

#define CC_FILE_ cocos2d::CCFileUtils::sharedFileUtils()

#define CC_DIRECTOR_ cocos2d::CCDirector::sharedDirector()

#define CC_SPRITE_FRM_CACHE_ \
	cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()

#define CC_AUDIO_ CocosDenshion::SimpleAudioEngine::sharedEngine()

	enum z_index
	{
		z_index0,
		z_index1,
		z_index2,
		z_index3,
		z_index4,
		z_index5,
		z_index6
	};

#define PTM_RATIO 70.0f

#endif
