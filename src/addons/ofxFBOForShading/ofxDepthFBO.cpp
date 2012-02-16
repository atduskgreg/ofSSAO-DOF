/*
 *  ofxDepthFBO.cpp
 *  try_DepthBuffer
 *
 *  Created by Makira on 10/11/08.
 *  Copyright 2010 yesMAYBEno. All rights reserved.
 *
 */

#include "ofxDepthFBO.h"

void ofxDepthFBO::setup(int width, int height) {

	tex = depthTex.genDepthTexture(width, height);

	glGenFramebuffersEXT(1, &fb);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fb);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);	
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT,
							  GL_TEXTURE_2D, tex, 0);

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

}

void ofxDepthFBO::beforeUpdate() {

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fb);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);

}

void ofxDepthFBO::afterUpdate() {

	glDisable(GL_DEPTH_TEST);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

}

void ofxDepthFBO::beforeDraw(int texUnit) {
	
	glActiveTexture(GL_TEXTURE0+texUnit);
	glBindTexture(GL_TEXTURE_2D, tex);
	
//	glBindTexture(GL_TEXTURE_RECTANGLE_ARB, tex);	
//	glBindBuffer(GL_TEXTURE_RECTANGLE_ARB, tex);

}

void ofxDepthFBO::afterDraw() {

	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);
	
}