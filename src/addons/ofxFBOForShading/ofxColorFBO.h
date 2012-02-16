/*
 *  ofxColorFBO.h
 *  try_DepthBuffer2
 *
 *  Created by Makira on 10/11/08.
 *  Copyright 2010 yesMAYBEno. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include "ofxTexture.h"

class ofxColorFBO {

public:
	
	void setup(int width, int height);
	void beforeUpdate();
	void afterUpdate();
	void beforeDraw(int texUnit);
	void afterDraw();
	inline GLuint getTexID(){return tex;};
	
private:
	
	ofxTexture	colTex;
	GLuint tex, fb, rb, depth_rb;
	GLuint depthBuffer, colorBuffer, mfbo;

};