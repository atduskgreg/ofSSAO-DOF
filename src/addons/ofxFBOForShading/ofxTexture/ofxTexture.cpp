/*
 *  ofxTexture.cpp
 *  try_DepthBuffer2
 *
 *  Created by Makira on 10/11/08.
 *  Copyright 2010 yesMAYBEno. All rights reserved.
 *
 */

#include "ofxTexture.h"

int ofxTexture::genDepthTexture(int width, int height) {

	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0,
				 GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);	
	
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
//	glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE);	
	
	glBindTexture(GL_TEXTURE_2D, 0);
	return tex;
	
	

}

int ofxTexture::genColorTexture(int width, int height) {
	
	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F_ARB, width, height, 0,
//				 GL_RGBA, GL_FLOAT, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F_ARB, width, height, 0,
				 GL_RGBA, GL_FLOAT, 0);	
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);	
	
	
	
	glBindTexture(GL_TEXTURE_2D, 0);
	return tex;
	
}


//----------------------------------------------------------
void ofxTexture::allocate(int w, int h, int internalGlDataType){
	allocate(w, h, internalGlDataType, ofGetUsingArbTex());
}

//----------------------------------------------------------
void ofxTexture::allocate(int w, int h, int internalGlDataType, bool bUseARBExtention){
	
	//our graphics card might not support arb so we have to see if it is supported.
#ifndef TARGET_OPENGLES
	if (bUseARBExtention && GLEE_ARB_texture_rectangle){
		texData.tex_w = w;
		texData.tex_h = h;
		texData.tex_t = w;
		texData.tex_u = h;
		texData.textureTarget = GL_TEXTURE_2D;
	} else 
#endif
	{
		//otherwise we need to calculate the next power of 2 for the requested dimensions
		//ie (320x240) becomes (512x256)
		texData.tex_w = ofNextPow2(w);
		texData.tex_h = ofNextPow2(h);
		texData.tex_t = 1.0f;
		texData.tex_u = 1.0f;
		texData.textureTarget = GL_TEXTURE_2D;
	}
	
	texData.glTypeInternal = internalGlDataType;
	
	
	// MEMO: todo, add more types
	switch(texData.glTypeInternal) {
#ifndef TARGET_OPENGLES	
		case GL_RGBA32F_ARB:
			texData.glType		= GL_RGBA;
			texData.pixelType	= GL_FLOAT;
			break;
			
		case GL_RGB32F_ARB:
			texData.glType		= GL_RGB;
			texData.pixelType	= GL_FLOAT;
			break;
			
		case GL_LUMINANCE32F_ARB:
			texData.glType		= GL_LUMINANCE;
			texData.pixelType	= GL_FLOAT;
			break;
			
		case GL_DEPTH_COMPONENT:
			texData.glType		= GL_DEPTH_COMPONENT;
			texData.pixelType	= GL_UNSIGNED_BYTE;
			break;			
#endif			
			
		default:
			texData.glType		= GL_LUMINANCE;
			texData.pixelType	= GL_UNSIGNED_BYTE;
	}
	
	// attempt to free the previous bound texture, if we can:
	clear();
	
	glGenTextures(1, (GLuint *)&texData.textureID);   // could be more then one, but for now, just one
	
	glEnable(texData.textureTarget);
	
	glBindTexture(texData.textureTarget, (GLuint)texData.textureID);
#ifndef TARGET_OPENGLES
	// can't do this on OpenGL ES: on full-blown OpenGL, 
	// internalGlDataType and glDataType (GL_LUMINANCE below)
	// can be different; on ES they must be exactly the same.
	//		glTexImage2D(texData.textureTarget, 0, texData.glTypeInternal, (GLint)texData.tex_w, (GLint)texData.tex_h, 0, GL_LUMINANCE, PIXEL_TYPE, 0);  // init to black...
	glTexImage2D(texData.textureTarget, 0, texData.glTypeInternal, (GLint)texData.tex_w, (GLint)texData.tex_h, 0, texData.glType, texData.pixelType, 0);  // init to black...
#else
	glTexImage2D(texData.textureTarget, 0, texData.glTypeInternal, texData.tex_w, texData.tex_h, 0, texData.glTypeInternal, GL_UNSIGNED_BYTE, 0);
#endif
	
	
	glTexParameterf(texData.textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(texData.textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(texData.textureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(texData.textureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	
	glDisable(texData.textureTarget);
	
	texData.width = w;
	texData.height = h;
#ifdef TARGET_OF_IPHONE
	texData.bFlipTexture = true; // textures need to be flipped for the iphone
#else
	texData.bFlipTexture = false;
#endif
	texData.bAllocated = true;
}
