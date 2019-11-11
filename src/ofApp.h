#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#define NUM 5 //sensorの数

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        ofParameter<int> sensor[5]; //parameter色表現テスト用
//        ofParameter<float> sensor2; //parameter色表現テスト用
//        ofParameter<float> sensor3; //parameter色表現テスト用
//        ofParameter<float> sensor4; //parameter色表現テスト用
//        ofParameter<float> sensor5; //parameter色表現テスト用

        ofVec2f pos[NUM]; //sensorの表記をする位置ベクトルの配列
    
    
        ofxPanel gui;
        ofxFloatSlider radius;
        ofxColorSlider color;
        ofxVec2Slider position;
        ofPolyline plot;
    
        float x;
        float y;
        
        //マウスのクリック箇所の判定用
        int mposx;
        int mposy;

        //選択した円の番号
        int selectCircle =NUM+1;
};
