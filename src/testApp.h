#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxDepthFBO.h"
#include "ofxColorFBO.h"
#include "ofxSimpleGuiToo.h"

class testApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);

	ofShader defaultShader;
	ofShader showDepthShader;
	ofShader ssaoShader;	
	ofShader dofShader;
	ofxDepthFBO depthFBO;
	ofxColorFBO colorFBO;
	ofxColorFBO ssaoFBO;
	
	ofEasyCam cam;
	
	void drawScene();
	vector<ofVec4f> objCol;
	vector<ofVec3f> objPos;
	vector<int> objSize;
	vector<ofQuaternion> objRot;
	vector<int> objType;
	int numObj;	
	void drawFullScreenQuad(int w, int h);		
	
};

#endif
