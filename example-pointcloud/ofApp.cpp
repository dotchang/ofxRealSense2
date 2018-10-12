#include "ofApp.h"

#pragma comment(lib, "realsense2.lib")

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(1280, 480);
    realsense.setup();

	cam.setNearClip(0.001f);
	cam.setFarClip(1000.f);
	cam.setDistance(4.f);
	cam.setPosition(0.f, 0.f, -1.f);
	cam.lookAt(ofVec3f(0.f, 0.f, 1.f), ofVec3f(0.f, -1.f, 0.f));

	light.setParent(cam);
	light.enable();
}

//--------------------------------------------------------------
void ofApp::update(){
    realsense.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);

	ofEnableLighting();
	ofEnableDepthTest();
	cam.begin();
	realsense.drawMeshVertices();
	cam.end();

    //realsense.draw(0, 0, 640, 480);
    //realsense.drawDepth(640, 60, 640, 360);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
