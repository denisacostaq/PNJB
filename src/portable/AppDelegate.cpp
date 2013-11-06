/*! @file AppDelegate.cpp Brebe del fichero.    
    @author Alvaro Denis Acosta Quesada denisacostaq\@gmail.com    
    @date Thu Oct 24 23:16:12 CDT 2013
  
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


#include "AppDelegate.h"


AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
}


bool AppDelegate::applicationDidFinishLaunching()
{
    CCDirector *pDirector = CC_DIRECTOR_;

    pDirector->setOpenGLView(CC_OPENGL_VIEW_);

    CCSize screenSize = CC_OPENGL_VIEW_->getFrameSize();
    CCSize designSize = CCSizeMake(screenSize.width, screenSize.height);
    CC_OPENGL_VIEW_->setDesignResolutionSize(
		designSize.width, designSize.height, kResolutionExactFit);

    pDirector->setContentScaleFactor (screenSize.width/designSize.width);    
    
    std::vector<std::string> searchPath;
    
	std::string resolution;

	if (screenSize.width == 420 && screenSize.height == 700)
	{
		resolution = "IMG/desktop/";
	}
	else
	{
// 		if (screenSize.width > 640)
// 		{
// 			searchPath.push_back("hd");
// 		} else if (screenSize.width > 320) {
// 			searchPath.push_back("md");
// 		} else {
// 			searchPath.push_back("sd");
// 		}
	}

    searchPath.push_back (resolution);
    
    CC_FILE_->setSearchPaths (searchPath);

    // turn on display FPS
    pDirector->setDisplayStats (false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);   
    
    // scene: it's an autorelease object
    pDirector->runWithScene(MenuLayer::scene());

    return true;
}


void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    //CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}


void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
///CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

