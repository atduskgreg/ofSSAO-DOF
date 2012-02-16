#include "testApp.h"

// SSAO
float camerarangex;
float camerarangey;
float aoCap;
float aoMultiplier;
float depthTolerance;
float aorange;
float readDepthVal;

// DoF
float focus;
float aspectratiox;
float aspectratioy;
float blurclamp;
float bias;

void testApp::addFace(ofMesh& mesh, ofVec3f a, ofVec3f b, ofVec3f c) {
	mesh.addVertex(a);
	mesh.addVertex(b);
	mesh.addVertex(c);
}

void testApp::addFace(ofMesh& mesh, ofVec3f a, ofVec3f b, ofVec3f c, ofVec3f d) {
	addFace(mesh, a, b, c);
	addFace(mesh, a, c, d);
}

ofVec3f testApp::getVertexFromImg(ofImage& img, int x, int y) {
	ofColor color = img.getColor(x, y);
	if(color.a > 0) {
		float z = ofMap(color.a, 0, 255, -480, 480);
		return ofVec3f(x - img.getWidth() / 2, y - img.getHeight() / 2, z);
	} else {
		return ofVec3f(0, 0, 0);
	}
}

//--------------------------------------------------------------
void testApp::setup(){
    
	ofDisableArbTex();
	ofEnableAlphaBlending();
	ofEnableSmoothing();
	ofBackground(255, 255, 255);
    
    ofSetVerticalSync(true);
	ofImage img;
	img.loadImage(ofToDataPath("linzer.png"));
	
	mesh.setMode(OF_PRIMITIVE_TRIANGLES);

	ssaoShader.load("shaders/ssao");	
	dofShader.load("shaders/dof");
	
	depthFBO.allocate(ofGetWidth(), ofGetHeight());
	colorFBO.allocate(ofGetWidth(), ofGetHeight());
	ssaoFBO.allocate(ofGetWidth(), ofGetHeight());
    
    gui.setup();
	gui.addPage("SSAO settings");
	gui.addPage("DoF settings");
	
	ofSetSphereResolution(100);
	numObj = 200;
	for (int i = 0; i < numObj; i++) {
		float x = ofRandom(ofGetWidth()/2-200, ofGetWidth()/2+200);
		float y = ofRandom(ofGetHeight()/2-200, ofGetHeight()/2+200);
		float z = ofRandom(-100, 500);
		ofVec3f pos = ofVec3f(x,y,z);
		float r = ofRandom(0.0, 255.0);
		float g = ofRandom(0.0, 255.0);
		float b = ofRandom(0.0, 255.0);
		float a = ofRandom(200.0, 255.0);
		ofVec4f col = ofVec4f(r,g,b,a);
		int size = ofRandom(10, 50);
		ofQuaternion qua = ofQuaternion(ofRandomf(), ofRandomf(), ofRandomf(), ofRandomf());
		int typ = ofRandom(1, 3);
		objPos.push_back(pos);
		objRot.push_back(qua);
		objCol.push_back(col);
		objSize.push_back(size);
		objType.push_back(typ);
	}	
	
    
    int skip = 5;	
	int width = img.getWidth();
	int height = img.getHeight();
	ofVec3f zero(0, 0, 0);
	for(int y = 0; y < height - skip; y += skip) {
		for(int x = 0; x < width - skip; x += skip) {
			ofVec3f nw = getVertexFromImg(img, x, y);
			ofVec3f ne = getVertexFromImg(img, x + skip, y);
			ofVec3f sw = getVertexFromImg(img, x, y + skip);
			ofVec3f se = getVertexFromImg(img, x + skip, y + skip);
			if(nw != zero && ne != zero && sw != zero && se != zero) {
				addFace(mesh, nw, ne, se, sw);
                mesh.addColor(img.getColor(x, y));
                mesh.addColor(img.getColor(x + skip, y));
                mesh.addColor(img.getColor(x, y + skip));
                
                mesh.addColor(img.getColor(x, y));
                mesh.addColor(img.getColor(x, y + skip));
                mesh.addColor(img.getColor(x + skip, y + skip));

			}
		}
	}
    gui.setPage(0);
	//.setNewColumn(true);
	gui.addTitle("SSAO Setting");
	gui.addSlider("camerarangex", camerarangex, 0, 10000);
	gui.addSlider("camerarangey", camerarangey, 0, 10000);
	gui.addSlider("aoCap", aoCap, 0.0, 2.0);
	gui.addSlider("aoMultiplier", aoMultiplier, 0.0, 20000.0);
	gui.addSlider("depthTolerance", depthTolerance, 0.000, 0.002);
	gui.addSlider("aorange", aorange, 0.0, 2.0);
	gui.addSlider("readDepthVal", readDepthVal, 0.0, 20.0);
    
    gui.setPage(1);
	gui.addTitle("DOF Setting").setNewColumn(true);
	gui.addSlider("focus", focus, 0.0, 2.0);
	gui.addSlider("aspectratiox", aspectratiox, 0.0, ofGetWidth());
	gui.addSlider("aspectratioy", aspectratioy, 0.0, ofGetHeight());
	gui.addSlider("blurclamp", blurclamp, 0.0, 1.0);
	gui.addSlider("bias", bias, 0.0, 1.0);	
	//gui.loadFromXML();
	gui.show();		
	camerarangex = 6113.28;
	camerarangey = 4121.09;
	aoCap = 1.8795;
	aoMultiplier = 1523.5625;
	depthTolerance = 0.0001130;
	aorange = 0.285156;
	readDepthVal = 2.0;
	focus = 0.808594;
	aspectratiox = ofGetWidth();
	aspectratioy = ofGetHeight();	
	blurclamp = 0.0253910;
	bias = 0.041016;
	
}

//--------------------------------------------------------------
void testApp::update(){
    
	//cam.draw();
	/*
	depthFBO.beforeUpdate();
	drawScene();
	depthFBO.afterUpdate();
	
	colorFBO.beforeUpdate();
	drawScene();
	colorFBO.afterUpdate();		
    */
    depthFBO.begin();
    drawScene();
    depthFBO.end();
    
    colorFBO.begin();
    drawScene();
    colorFBO.end();
    
    
	
	/*int colorTexSlot = 4;
	colorFBO.beforeDraw(colorTexSlot);	
	int depthTexSlot = 5;
	depthFBO.beforeDraw(depthTexSlot);
    ssaoFBO.beforeUpdate();
     */
    ssaoFBO.begin();
    ssaoShader.begin();
    ssaoShader.setUniformTexture("texture0", depthFBO.getTextureReference(), 1);
    ssaoShader.setUniformTexture("texture1", colorFBO.getTextureReference(), 2);
    ssaoShader.setUniform2f("screensize", ofGetWidth(), ofGetHeight());
    ssaoShader.setUniform2f("camerarange", camerarangex, camerarangey);
    ssaoShader.setUniform1f("aoCap", aoCap);
    ssaoShader.setUniform1f("aoMultiplier", aoMultiplier);
    ssaoShader.setUniform1f("depthTolerance", depthTolerance);
    ssaoShader.setUniform1f("aorange", aorange);
    ssaoShader.setUniform1f("readDepthVal", readDepthVal);
    drawFullScreenQuad(ofGetWidth(), ofGetHeight());
    ssaoShader.end();
    
    ssaoFBO.end();
    
    /*ssaoFBO.afterUpdate();
	depthFBO.afterDraw();
	colorFBO.afterDraw();	
     */
	
}

//--------------------------------------------------------------
void testApp::draw(){	

	/*int ssaoTexSlot = 6;
	ssaoFBO.beforeDraw(ssaoTexSlot);
	int depthTexSlot = 5;
	depthFBO.beforeDraw(depthTexSlot);*/
    
	dofShader.begin();
	dofShader.setUniformTexture("bgl_RenderedTexture", ssaoFBO.getTextureReference(), 0);
	dofShader.setUniformTexture("bgl_DepthTexture", depthFBO.getTextureReference(), 1);
	dofShader.setUniform1f("focus", focus);
	dofShader.setUniform1f("aspectratiox", aspectratiox);
	dofShader.setUniform1f("aspectratioy", aspectratioy);
	dofShader.setUniform1f("blurclamp", blurclamp);
	dofShader.setUniform1f("bias", bias);
	drawFullScreenQuad(ofGetWidth(), ofGetHeight());
	dofShader.end();	

	ofSetupScreen();

   // ofSetColor(255, 0);

	gui.draw();	
}

//--------------------------------------------------------------
void testApp::drawScene() {
	glEnable(GL_DEPTH_TEST);
    cam.begin();

	for (int i = 0; i < numObj; i++) {
		ofVec3f pos = objPos[i];
		ofVec4f col = objCol[i];
		int size = objSize[i];
		ofSetColor(col.x, col.y, col.z);
		ofQuaternion qua = objRot[i];
		float rad = 0.0; ofVec3f rvec;
		qua.getRotate(rad, rvec);
		ofPushMatrix();
		ofTranslate(pos.x, pos.y, pos.z);
		ofRotate(ofRadToDeg(rad), rvec.x, rvec.y, rvec.z);
		int typ = objType[i];
		if (typ == 1) { 
			ofSphere(0,0,0, size);
		}else {
			ofBox(0,0,0, size);
		}
		ofPopMatrix();
	}
    ofSetColor(255, 255, 255);

/*        
    ofTranslate(ofGetWidth()/4 - 200, ofGetHeight()/4 - 200);

    ofScale(1, -1, 1); // make y point down

	mesh.drawFaces();
 */
    cam.end();
    
}

//--------------------------------------------------------------
void testApp::drawFullScreenQuad(int w, int h) {
	
	ofVec3f a = ofVec3f(0, 0, 0);
	ofVec3f b = ofVec3f(ofGetWidth(), 0, 0);
	ofVec3f c = ofVec3f(ofGetWidth(), ofGetHeight(), 0);
	ofVec3f d = ofVec3f(0, ofGetHeight(), 0);
	//ofRectangle(a, b, c, d);
	
    ofBeginShape();
    ofVertex(a);
    ofVertex(b);
    ofVertex(c);
    ofVertex(d);
    
    ofEndShape();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if (key == ' ') {
		gui.toggleDraw();
	}
}
//--------------------------------------------------------------
void testApp::keyReleased(int key){}
//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){}
//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){}
//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){}
//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){}
//--------------------------------------------------------------
void testApp::windowResized(int w, int h){}

