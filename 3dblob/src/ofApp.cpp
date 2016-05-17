#include "ofApp.h"



//--------------------------------------------------------------
void blob::setup(){
    
    
    scale= ofRandom(0.9, 1.1);
    offset = ofRandom(0,500);
    for (int i = 0; i < 500; i++){
        float angle = ofMap(i, 0, 100, 0, TWO_PI);
        ofPoint pos = ofPoint(0,0,0) + 100 * ofPoint(cos(angle), sin(angle), sin(i/10.0));
        particle * p = new particle();
        p->setInitialCondition(pos.x,pos.y,pos.z, 0, 0, 0);
        particles.push_back(p);
        
    }
    
    for (int i = 0; i < particles.size(); i++){
        spring s;
        s.particleA = particles[i];
        s.particleB = particles[(i+1) % particles.size()];
        s.distance = 5;
        s.springiness = 0.5;
        springs.push_back(s);
    }
    
    
    
}

//--------------------------------------------------------------
void blob::update(){
    
    for (int i = 0; i < particles.size(); i++){
        particles[i]->resetForce();
        particles[i]->addRepulsionForce(0,0,0,max(ofGetMouseY(), 10) * scale,2.0);
        particles[i]->addAttractionForce(0,0,0,1000,0.1);
    }
    
    float f = ofGetElapsedTimef();
    for (int i = 0; i < particles.size(); i++){
        for (int j = 0; j < i; j++){
            
            float x1 = sin(i/40.0 + f*1 + offset) * 10 + 10;
            float y1 = sin(j/40.0  + f*2.0 + PI + offset) * 10 + 10;
            
            particles[i]->addRepulsionForce( *particles[j], (x1 + y1) * scale, 1.0);
        }
    }
    
    for (int i = 0; i < springs.size(); i++){
        springs[i].update();
    }
    
    
    for (int i = 0; i < particles.size(); i++){
        particles[i]->addDampingForce();
        particles[i]->update();
    }
}

//--------------------------------------------------------------
void blob::draw(){
    
    line.clear();
    for (auto a : particles){
        line.addVertex(a->pos);
    }
    line.setClosed(true);
    line = line.getResampledByCount(2000);
    line = line.getSmoothed(11);
    line.draw();
    //cam.end();
}


//--------------------------------------------------------------
void ofApp::setup(){

    
    b.setup();
    
    b2.setup();
    
}

//--------------------------------------------------------------
void ofApp::update(){

    b.update();
    b2.update();
}

ofMatrix4x4 m;

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(0);
    
    GLfloat fogColor[4] = {0,0,0, 0.3};
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogf(GL_FOG_DENSITY, 0.8);
    glHint(GL_FOG_HINT, GL_DONT_CARE);
    glFogf(GL_FOG_START, -500);
    glFogf(GL_FOG_END, 1200);
    glEnable(GL_FOG);
    
    
    m.rotate(1 + 1 * sin(ofGetElapsedTimef()*0.4), 0, 1, 0);
//     m.rotate(1 + 1 * sin(ofGetElapsedTimef()*0.4+1), 1, 0, 0);
//    
    
    //cam.enableOrtho();
    cam.begin();
    
    ofMultMatrix(m);
    //ofRotate(ofGetElapsedTimef()*40, 0, 1, 0);
    ofScale(1.5, 1.5, 1.5);
    b.draw();
    b2.draw();
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    for (int  i = 0; i < b.line.size(); i++){
        int smallest = -1;
        float smallestDist = 1000000;
        for (int j = 0; j < b2.line.size(); j++){
            float dist = (b2.line[j] - b.line[i]).length();
            if (dist < smallestDist){
                smallestDist = dist;
                smallest = j;
            }
        }
        if (smallest != - 1 && smallestDist < mouseX){
            
            line l;
            l.a = i;
            l.b = smallest;
            l.energy = 1.0;
            //lines.push_back(l);
            ofLine( b.line[i],  b2.line[smallest]);
        }
    }
    
    for (auto & a : lines){
        if (a.energy > 0.01){
            
            ofPoint diff = b2.line[a.b] -b.line[a.a];
            ofPoint center = (b2.line[a.b] + b.line[a.a])/2.0;
            
//            ofSetColor(255);
//            ofLine(b2.line[a.b], b2.line[a.b] - diff * a.energy);
//            
//            ofSetColor(255);
//            ofLine(b.line[a.a], b.line[a.a] + diff * a.energy);
//            
            
            a.energy *= 0.99;;
        }
    }
    
    cam.end();
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
