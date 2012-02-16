/*
 *  ofxColorFBO.cpp
 *  try_DepthBuffer2
 *
 *  Created by Makira on 10/11/08.
 *  Copyright 2010 yesMAYBEno. All rights reserved.
 *
 */

#include "ofxColorFBO.h"

void ofxColorFBO::setup(int width, int height) {
	
	tex = colTex.genColorTexture(width, height);

	glGenFramebuffersEXT(1, &fb);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fb);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT,
							  GL_TEXTURE_2D, tex, 0);
	
	glGenRenderbuffersEXT(1, &depth_rb);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, depth_rb);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, depth_rb);	
	
//	glGenRenderbuffersEXT(1, &depthBuffer);
//	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, depthBuffer);
//	glRenderbufferStorageMultisampleEXT(GL_RENDERBUFFER_EXT, 4, GL_DEPTH_COMPONENT, width, height);
//	
//	glGenRenderbuffersEXT(1, &colorBuffer);
//	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, colorBuffer);
//	glRenderbufferStorageMultisampleEXT(GL_RENDERBUFFER_EXT, 4, GL_RGBA8, width, height);
//	
//	glGenFramebuffersEXT(1, &mfbo);
//	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, mfbo);
//	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_RENDERBUFFER_EXT, colorBuffer);
//	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, depthBuffer);	
	
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	
}

void ofxColorFBO::beforeUpdate() {
	
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fb);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
}

void ofxColorFBO::afterUpdate() {
	
	glDisable(GL_DEPTH_TEST);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	
}

void ofxColorFBO::beforeDraw(int texUnit) {
	
	glActiveTexture(GL_TEXTURE0+texUnit);
	glBindTexture(GL_TEXTURE_2D, tex);
	
}

void ofxColorFBO::afterDraw() {
	
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);
	
}