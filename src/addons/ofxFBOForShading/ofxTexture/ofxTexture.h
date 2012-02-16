/*
 *  ofxTexture.h
 *  try_DepthBuffer2
 *
 *  Created by Makira on 10/11/08.
 *  Copyright 2010 yesMAYBEno. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"

class ofxTexture: public ofTexture {

public:
	int genDepthTexture(int width, int height);
	int genColorTexture(int width, int height);
	
	void allocate(int w, int h, int internalGlDataType); //uses the currently set OF texture type - default ARB texture
	void allocate(int w, int h, int internalGlDataType, bool bUseARBExtention); //lets you overide the default OF texture type
	
	
};