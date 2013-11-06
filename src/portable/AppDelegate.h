/*! @file AppDelegate.h Brebe del fichero.    
    @author Alvaro Denis Acosta Quesada denisacostaq\@gmail.com    
    @date Thu Oct 24 23:16:12 CDT 2013
  
    FIXME:
    @warning It must be called before the application exit, or a memroy
    @warning leak will be casued. CC_AUDIO_->end();
 
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

#ifndef APPDELEGATE_H
#define APPDELEGATE_H

#include "cocos2d.h"

#include "scene/LoadLevel.h"
#include "scene/MenuLayer.h"

#include <string>
#include <vector>

USING_NS_CC;

class AppDelegate : public cocos2d::CCApplication
{
public:

    AppDelegate();

    /*! Implement CCDirector and CCScene init code here.
	@brief Here is the place for you.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /*! The function be called when the application enter background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /*! The function be called when the application enter foreground
	@param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();
	
private:
};

#endif // APPDELEGATE_H
