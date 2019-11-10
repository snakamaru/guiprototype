#include "ofApp.h"

//float

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    ofBackground(255);
    ofSetCircleResolution(64);
    
    ofColor initColor = ofColor(0,255,255,255);
    ofColor minColor = ofColor(0,0,0,0);
    ofColor maxColor = ofColor(255,255,255,255);
    
    ofVec2f initPos = ofVec2f(ofGetWidth()/2, ofGetHeight()/2);
    ofVec2f minPos = ofVec2f(0,0);
    ofVec2f maxPos = ofVec2f(ofGetWidth(),ofGetHeight());
    
    gui.setup();
    gui.add(radius.setup("radius", 200, 0, 400));
    gui.add(color.setup("color", initColor, minColor,maxColor));
    gui.add(position.setup("position", initPos, minPos, maxPos));
    
    x=0;
    y=0;
}

//--------------------------------------------------------------
void ofApp::update(){
    x=position->x;
    y=position->y;
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofDrawCircle(ofVec2f(position), radius);
    gui.draw();
    
    ofSetColor(color);
//    ofDrawRectangle(ofGetWidth()*0.1,ofGetHeight()*0.1,x,y);
//    ofPolyline(10,10,10);
//    ofPolyline(10,100,100);
    
    
//        plot.addVertex(x,y);
//        plot.draw();

    //
//    float i = 0;
//    while (i < radius) { // make a heart
////        float r = (2-2*sin(i) + sin(i)*sqrt(abs(cos(i))) / (sin(i)+1.4)) * -80;
//        float x = i;
//        float y = ofGetHeight()/2 + sin(i);
//        plot.addVertex(ofVec3f(x,x,0));
//        i+=1;
//        plot.draw();
//    }
//    plot.close();
    
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
