#include "ofApp.h"


void ofApp::setup(){
    //画面の描画についてフレッシュレートとシンク設定
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
//    ofBackground(255);

//    円のレゾリューション
    ofSetCircleResolution(64);
    
    ofColor initColor = ofColor(0,255,255,255);
    ofColor minColor = ofColor(0,0,0,0);
    ofColor maxColor = ofColor(255,255,255,255);
    
    ofVec2f initPos = ofVec2f(ofGetWidth()/2, ofGetHeight()/2);
    ofVec2f minPos = ofVec2f(0,0);
    ofVec2f maxPos = ofVec2f(ofGetWidth(),ofGetHeight());
    
    //sensor分繰り返し
    for(int i=0; i<NUM; i++){
        pos[i].x = ofGetWidth()*(i+1)/(NUM+1);
        pos[i].y = ofGetHeight()/2;}

    
    sensor[0].set("sensor1", 128,0,255); //name, default, min, max
    sensor[1].set("sensor2", 128,0,255); //name, default, min, max
//    sensor3.set("sensor3", 128,0,255); //name, default, min, max
//    sensor4.set("sensor4", 128,0,255); //name, default, min, max
//    sensor5.set("sensor5", 128,0,255); //name, default, min, max

    
    gui.setup();
    gui.add(radius.setup("radius", 30, 0, 100));
    gui.add(color.setup("color", initColor, minColor,maxColor));
    gui.add(position.setup("position", initPos, minPos, maxPos));
    gui.add(sensor[0]);
    gui.add(sensor[1]);
//    gui.add(sensor2);
//    gui.add(sensor3);
//    gui.add(sensor4);
//    gui.add(sensor5);

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
      ofBackgroundGradient(ofColor::white, ofColor::gray);
      
//    ofDrawCircle(ofVec2f(position), radius);

//    for (int i=0; i<5; i++)
//    {
//
//        int value = i;
//        ofSetColor(value, 0, 255-value);
//    }
    
    for (int i=0; i<NUM; i++){
    ofSetColor(sensor[0], 0, 255-sensor[0]);
    ofDrawCircle(pos[i],radius);
    }


    
//    Debug for mouse event
    ofSetColor(0, 0, 0);
    string msg = "mposx:" + ofToString(mposx)+'\n';
    ofDrawBitmapString(msg, ofGetWidth()-120,20);

    string msg2 = "mposy:" + ofToString(mposy)+'\n';
        ofDrawBitmapString(msg2, ofGetWidth()-120,40);
 
    string msg3 = "sCircle:" + ofToString(selectCircle)+'\n';
         ofDrawBitmapString(msg3, ofGetWidth()-120,60);
    
    gui.draw();
    
//    ofSetColor(color);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key){
        //fでフルスクリーン
        case 'f':
            ofToggleFullscreen();
             break;
            
        //sでパラメータ記録
        case 's':
            gui.saveToFile("settings.xml");
            break;
            
        //lでパラメータ読み込み
        case 'l':
            gui.loadFromFile("settings.xml");
            break;
        
        //Radiusを40にセットするテスト用
        case 'a':
            radius=40;
            break;
            
    }
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
 
    for (int i=0; i<NUM; i++){
    if (pos[i].x - radius < x && x < pos[i].x+radius && pos[i].y - radius < y && y < pos[i].y+radius){
        mposx = x;
        mposy = y;
        selectCircle = i;
        position =ofVec2f(pos[i].x,pos[i].y);
            }
    }

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
