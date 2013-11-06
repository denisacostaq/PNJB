/*! @file ShaderNode.h Brebe del fichero.    
    @author Alvaro Denis Acosta Quesada denisacostaq\@gmail.com    
    @date Thu Oct 24 23:56:47 CDT 2013
  
    @brief This coe become from 
	@brief cocos2d-x-2.2.0/samples/Cpp/TestCpp/Classes/ShaderTest/ShaderTest.h
 
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

#ifndef SHADERNODEAA_H
#define SHADERNODEAA_H

//#include "CCGLProgram.h"
#include "cocos2d.h"

#include "CCPointExtension.h"
#include "CCEventType.h"
#include "CCNotificationCenter.h"

#include "CCPlatformMacros.h"
#include "CCDirector.h"
#include "cocos2d.h"

USING_NS_CC;

#include "CCNode.h"

#include "CCGLBufferedNode.h"

#include "GL/gl.h"

#include "../AppMacros.h"


class ShaderNode : public CCNode
{
public:
    ShaderNode();
    ~ShaderNode();

    bool initWithVertex(const char *vert, const char *frag);
    void loadShaderVertex(const char *vert, const char *frag);
    void listenBackToForeground(CCObject *obj);

    virtual void update(float dt);
    virtual void setPosition(const CCPoint &newPosition);
    virtual void draw();

    static ShaderNode* shaderNodeWithVertex(const char *vert, const char *frag);

private:

    ccVertex2F m_center;
    ccVertex2F m_resolution;
    float      m_time;
    GLuint     m_uniformCenter, m_uniformResolution, m_uniformTime;
    std::string m_vertFileName;
    std::string m_fragFileName;
};


#endif // SHADERNODE_H
