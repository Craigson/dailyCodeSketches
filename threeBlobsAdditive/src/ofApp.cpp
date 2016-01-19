#include "ofApp.h"




//--------------------------------------------------------------
void ofApp::setup(){

    a.setup();
    a.highlightColor = ofColor::pink;
    a.mainColor = ofColor::yellow;
    
    b.setup();
    b.highlightColor = ofColor::pink;
    b.mainColor = ofColor::darkCyan;
    
    c.setup();
    c.highlightColor = ofColor::pink;
    c.mainColor = ofColor::darkMagenta;
    
}





//--------------------------------------------------------------
void ofApp::update(){

    b.update();
    a.update();
    
    c.update();
    
    ofHideCursor();
    
    // go through every edge, calc its orientation
    // go through every point, calc its distance to closest edge, store that
    // try to do something with orientation...
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofColor tempCo;
    tempCo.setHex(0x300032);
    tempCo = ofColor::peachPuff;
    //tempCo.setBrightness(tempCo.getBrightness() * ofMap(mouseX, 0, ofGetWidth(), 0, 1));
    ofBackground(tempCo);
    
    
    
    b.draw();
    
    ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
    
    ofTranslate(100,0);
    c.draw();
    
    ofTranslate(-300,0);
    a.draw();
    
    ofEnableAlphaBlending();
    
    
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
