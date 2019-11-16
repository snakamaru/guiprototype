#include "ofApp.h"


void ofApp::setup(){
    //画面の描画についてフレッシュレートとシンク設定
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
//    ofBackground(255);
    
    myTextFile.open("text.csv",ofFile::WriteOnly);

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
    sensor[2].set("sensor3", 128,0,255); //name, default, min, max
//    sensor4.set("sensor4", 128,0,255); //name, default, min, max
//    sensor5.set("sensor5", 128,0,255); //name, default, min, max

    
    gui.setup();
    gui.add(radius.setup("radius", 30, 0, 100));
    gui.add(color.setup("color", initColor, minColor,maxColor));
    gui.add(position.setup("position", initPos, minPos, maxPos));
    gui.add(sensor[0]);
    gui.add(sensor[1]);
    gui.add(sensor[2]);
//    gui.add(sensor3);
//    gui.add(sensor4);
//    gui.add(sensor5);

    //positionへの値入力初期値
    x=0;
    y=0;


    // Arduinoの接続に必要なポート情報
    ard.connect("/dev/cu.usbmodem142101", 57600);
    
    // 初期接続の確認フラグ
    // listen for EInitialized notification. this indicates that
    // the arduino is ready to receive commands and it is safe to
    // call setupArduino()
    ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);
    bSetupArduino    = false;
    // flag so we setup arduino when its ready, you don't need to touch this :)
    
}

//--------------------------------------------------------------
void ofApp::setupArduino(const int & version){
    // remove listener because we don't need it anymore
    ofRemoveListener(ard.EInitialized, this, &ofApp::setupArduino);
    // it is now safe to send commands to the Arduino
    
    
    // print firmware name and version to the console
    ofLogNotice() << ard.getFirmwareName();
    ofLogNotice() << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion();
    
    // Note: pins A0 - A5 can be used as digital input and output.
    // Refer to them as pins 14 - 19 if using StandardFirmata from Arduino 1.0.
    // If using Arduino 0022 or older, then use 16 - 21.
    // Firmata pin numbering changed in version 2.3 (which is included in Arduino 1.0)
    
    //    ピンのアサインを決める
    for (int i=0; i<6; i++){
        //A0-A5をアナログインプットに指定
        ard.sendAnalogPinReporting(i, ARD_ANALOG);
    }
    
    //set up 状態の判定
    bSetupArduino = true;
    
    
}
//--------------------------------------------------------------
void ofApp::updateArduino(){
    //
    ard.update();
    
}

//--------------------------------------------------------------
//--------------------------------------------------------------
void ofApp::update(){
    x=position->x;
    y=position->y;
    updateArduino();
}

//--------------------------------------------------------------
void ofApp::draw(){
      ofBackgroundGradient(ofColor::white, ofColor::gray);
      
    //Arduinoのメッセージ出力
     string msg ="";
     for(int i=0; i<6;i++){
         msg += "Analog IN" + ofToString(i,0) + ":" + ofToString(ard.getAnalog(i),0)+'\n';
     }
     ofSetHexColor(0xFFFFFF);
     ofDrawBitmapString(msg, 20,20);

    //sensor[]にArduinoの値を代入
    sensor[0]=ard.getAnalog(0)/4; //sensor1
    sensor[1]=ard.getAnalog(1)/4; //sensor2
    sensor[2]=ard.getAnalog(2)/4; //sensor3
    
    //選択された円の場所を更新
    for (int i=0; i<NUM; i++){
        if (selectCircle ==i )
        {
         pos[i].x = x;
         pos[i].y = y;
        }
    }
    
    for (int i=0; i<NUM; i++){
    ofSetColor(sensor[0], 0, 255-sensor[0]);
    ofDrawCircle(pos[i],radius);
    }


    
//    Debug for mouse event
    ofSetColor(0, 0, 0);
    string mss = "mposx:" + ofToString(mposx)+'\n';
    ofDrawBitmapString(mss, ofGetWidth()-120,20);

    string mss2 = "mposy:" + ofToString(mposy)+'\n';
        ofDrawBitmapString(mss2, ofGetWidth()-120,40);
 
    string mss3 = "sCircle:" + ofToString(selectCircle)+'\n';
         ofDrawBitmapString(mss3, ofGetWidth()-120,60);
    
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
//        case 's':
//            gui.saveToFile("settings.xml");
//            break;
//
            
        case 's':
            myTextFile.open("text.csv",ofFile::Append);
            myTextFile << "some text"<< endl;
            break;
            
        //lでパラメータ読み込み
        case 'l':
            gui.loadFromFile("settings.xml");
            break;
        
        //Radiusを40にセットするテスト用
        case 'a':
            radius=40;
            break;
            
//        case 'k':
//            position =ofVec2f(pos[selectCircle].x+1,pos[selectCircle].y);
//            break;
    }
    
    //もし押されたキーがキーコードだったら処理を実行する。
    if(key == 'k') {//右に動く
        position =ofVec2f(pos[selectCircle].x+3,pos[selectCircle].y);
      }
       else if (key == 'j') {    //左に動く
        position =ofVec2f(pos[selectCircle].x-3,pos[selectCircle].y);
      }else if (key == 'i') {    //上に動く
        position =ofVec2f(pos[selectCircle].x,pos[selectCircle].y-3);
      }else if (key == 'n') {    //下に動く
        position =ofVec2f(pos[selectCircle].x,pos[selectCircle].y+3);
      }

//    csvファイル保存コード
//    if( key == 's' ){
//       ofBuffer ofbuf;
//       string str;
//        vector<int>x;
//       x.push_back(1);
//       x.push_back(2);
//       x.push_back(3);
//       x.push_back(4);
//       x.push_back(5);
//
//       for( int i = 0; i < x.size(); i++ ){
//         str = str + ofToString(x[i]) + "\r\n"; // \r\nは改行コード
//       }
//
//       ofbuf.append(str);
//       ofBufferToFile(ofToDataPath("data.csv"), ofbuf);
//     }

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
