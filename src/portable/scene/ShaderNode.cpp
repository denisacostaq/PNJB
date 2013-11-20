/*! @file ShaderNode.cpp Brebe del fichero.    
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

#include "ShaderNode.h"

/** @enum This not are used
*/
enum 
{
    SIZE_X = 320,
    SIZE_Y = 480,
};

ShaderNode::ShaderNode ()
:m_center (vertex2(0.0f, 0.0f))
,m_resolution (vertex2(0.0f, 0.0f))
,m_time (0.0f)
,m_uniformCenter (0)
,m_uniformResolution (0)
,m_uniformTime (0)
,m_vertFileName ("")
,m_fragFileName ("")
{
}

ShaderNode::~ShaderNode()
{
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, 
EVENT_COME_TO_FOREGROUND);
}

ShaderNode* ShaderNode::shaderNodeWithVertex(const char *vert, const char *frag)
{
    ShaderNode *node = new ShaderNode();
    node->initWithVertex(vert, frag);
    node->autorelease();

    return node;
}

bool ShaderNode::initWithVertex(const char *vert, const char *frag)
{
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
        callfuncO_selector(ShaderNode::listenBackToForeground),
        EVENT_COME_TO_FOREGROUND,
        NULL);

    loadShaderVertex(vert, frag);

    m_time = 0;

    m_resolution = vertex2(CC_DIRECTOR_->getWinSize ().width,
                           CC_DIRECTOR_->getWinSize ().height);

    scheduleUpdate();

    setContentSize(CCSizeMake(SIZE_X, SIZE_Y));
    setAnchorPoint(ccp(0.5f, 0.5f));
    
    m_vertFileName = vert;
    m_fragFileName = frag;

    return true;
}

void ShaderNode::listenBackToForeground(CCObject *obj)
{
    this->setShaderProgram(NULL);
    loadShaderVertex(m_vertFileName.c_str(), m_fragFileName.c_str());
}

void ShaderNode::loadShaderVertex(const char *vert, const char *frag)
{
    CCGLProgram *shader = new CCGLProgram();
    shader->initWithVertexShaderFilename(vert, frag);

    shader->addAttribute("aVertex", kCCVertexAttrib_Position);
    shader->link();

    shader->updateUniforms();

    m_uniformCenter = glGetUniformLocation(shader->getProgram(), "center");
    m_uniformResolution = glGetUniformLocation(shader->getProgram(),
                                               "resolution");
    m_uniformTime = glGetUniformLocation(shader->getProgram(), "time");

    this->setShaderProgram(shader);

    shader->release();
}

void ShaderNode::update(float dt)
{
    m_time += dt;
}

void ShaderNode::setPosition(const CCPoint &newPosition)
{
    CCNode::setPosition(newPosition);
    CCPoint position = getPosition();
    m_center = vertex2(position.x * CC_CONTENT_SCALE_FACTOR(),
                       position.y * CC_CONTENT_SCALE_FACTOR());
}

void ShaderNode::draw()
{
    CC_NODE_DRAW_SETUP();

    float w = m_resolution.x, h = m_resolution.y;
    GLfloat vertices[12] = {0,0, w,0, w,h, 0,0, 0,h, w,h};

    //
    // Uniforms
    //
    getShaderProgram()->setUniformLocationWith2f(m_uniformCenter,
                                                 m_center.x, m_center.y);
    getShaderProgram()->setUniformLocationWith2f(m_uniformResolution,
                                                 m_resolution.x, m_resolution.y);

    // time changes all the time, so it is Ok to call OpenGL directly, and not 
	//the "cached" version
    glUniform1f(m_uniformTime, m_time);

    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );

    glVertexAttribPointer(kCCVertexAttrib_Position,
                          2, GL_FLOAT, GL_FALSE, 0, vertices);

    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    CC_INCREMENT_GL_DRAWS(1);
}
