#include "ofApp.h"



ofIcoSpherePrimitive prim;
//--------------------------------------------------------------
void blob::setup(){
    
    
    prim.setRadius(100);
    prim.setResolution(3);
    
    vector<ofMeshFace> triangles = prim.getMesh().getUniqueFaces();
    
    for (int i = 0; i < triangles.size(); i++){
    
        ofPoint a = triangles[i].getVertex(0);
        ofPoint b = triangles[i].getVertex(1);
        ofPoint c = triangles[i].getVertex(2);
        
        int aWho = -1;
        int bWho = -1;
        int cWho = -1;
        for (int j = 0; j < particles.size(); j++){
            if ( (a - particles[j]->pos).length() < 1){
                aWho = j;
            }
            if ( (b - particles[j]->pos).length() < 1){
                bWho = j;
            }
            if ( (c - particles[j]->pos).length() < 1){
                cWho = j;
            }
        }
        
        if (aWho == -1){
            particle * p = new particle();
            p->setInitialCondition(a.x,a.y,a.z, 0, 0, 0);
            particles.push_back(p);
        }
        
        if (bWho == -1){
            particle * p = new particle();
            p->setInitialCondition(b.x,b.y,b.z, 0, 0, 0);
            particles.push_back(p);
        }
        
        if (cWho == -1){
            particle * p = new particle();
            p->setInitialCondition(c.x,c.y,c.z, 0, 0, 0);
            particles.push_back(p);
        }
        
        
    }
    
    

    for (int i = 0; i < triangles.size(); i++){
        
        ofPoint a = triangles[i].getVertex(0);
        ofPoint b = triangles[i].getVertex(1);
        ofPoint c = triangles[i].getVertex(2);
        
        int aWho = -1;
        int bWho = -1;
        int cWho = -1;
        for (int j = 0; j < particles.size(); j++){
            if ( (a - particles[j]->pos).length() < 1){
                aWho = j;
            }
            if ( (b - particles[j]->pos).length() < 1){
                bWho = j;
            }
            if ( (c - particles[j]->pos).length() < 1){
                cWho = j;
            }
        }
        
        //cout << aWho << " " << bWho << " " << cWho << endl;
        
        
        spring s;
        s.particleA = particles[aWho];
        s.particleB = particles[bWho];
        s.distance = 30;
        s.springiness = 0.1;
        springs.push_back(s);
        
        s.particleA = particles[bWho];
        s.particleB = particles[cWho];
        s.distance = 30;
        s.springiness = 0.1;
        springs.push_back(s);
        
        s.particleA = particles[aWho];
        s.particleB = particles[cWho];
        s.distance = 30;
        s.springiness = 0.1;
        springs.push_back(s);
    }
////
    
    
}

//--------------------------------------------------------------
void blob::update(){
    
    for (int i = 0; i < particles.size(); i++){
        particles[i]->resetForce();
        //particles[i]->addRepulsionForce(0,0,0,200,2.0);
        particles[i]->addAttractionForce(0,0,0,1000,0.3);
    }
//
float f = ofGetElapsedTimef();
    for (int i = 0; i < particles.size(); i++){
        for (int j = 0; j < i; j++){
            
            float x1 = powf((sin(i/100.0 + f*1.8 + 0)), 1.0) * ofGetMouseX()/10.0 + 30;
            float y1 = powf((sin(j/100.0  + f*1.8 + PI + 0)), 1.0) * ofGetMouseY()/10.0 +30;
            
            
             particles[i]->addAttractionForce( *particles[j], 100, 1.3);
            particles[i]->addRepulsionForce( *particles[j], MAX(x1 + y1, 1), 4.3);
        }
    }
//
    for (int i = 0; i < springs.size(); i++){
        springs[i].update();
    }
//
//    
    for (int i = 0; i < particles.size(); i++){
        particles[i]->addDampingForce();
        particles[i]->update();
    }
}

//--------------------------------------------------------------
void blob::draw(ofPoint camPt){
    
    for (int i = 0; i < particles.size(); i++){

        //cout << particles[i]->pos << endl;
        //ofCircle(particles[i]->pos, 3);
    }
    
    cout << ofGetMouseX() << " " << ofGetMouseY() << endl;
    
    for (int i = 0; i < springs.size(); i++){
        
        float dista = (camPt -springs[i].particleA->pos).length();
         float distb = (camPt -springs[i].particleB->pos    ).length();
        
        float f = ofMap(dista, 732, 420, 0, 255, true);
        float f2 = ofMap(distb, 732, 420, 0, 255, true);
        
        
        glPointSize( powf((f/255.0), 4.5) * 14.0 );
        
        
        glBegin(GL_POINTS);
        glColor3f(f/255.0, f/255.0, f/255.0);
        glVertex3f(springs[i].particleA->pos.x, springs[i].particleA->pos.y, springs[i].particleA->pos.z);
        
        glColor3f(f2/255.0, f2/255.0, f2/255.0);
        glVertex3f(springs[i].particleB->pos.x, springs[i].particleB->pos.y, springs[i].particleB->pos.z);
        
        glEnd();
        
        glBegin(GL_LINES);
        glColor3f(f/255.0, f/255.0, f/255.0);
        glVertex3f(springs[i].particleA->pos.x, springs[i].particleA->pos.y, springs[i].particleA->pos.z);
        
        glColor3f(f2/255.0, f2/255.0, f2/255.0);
        glVertex3f(springs[i].particleB->pos.x, springs[i].particleB->pos.y, springs[i].particleB->pos.z);
        
        glEnd();

    
        //ofDrawLine(springs[i].particleA->pos, springs[i].particleB->pos);
    }
    
//    line.clear();
//    for (auto a : particles){
//        line.addVertex(a->pos);
//    }
//    line.setClosed(true);
//    line = line.getResampledByCount(2000);
//    line = line.getSmoothed(11);
//    line.draw();
    //cam.end();
}


//--------------------------------------------------------------
void ofApp::setup(){

    ofEnableDepthTest();
    
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
    
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_NOTEQUAL, 0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_POINT_SMOOTH );
    glPointSize( 10.0 );
    
    //cout << cam.getPosition() << endl;
    
//    GLfloat fogColor[4] = {0,0,0, 0.3};
//    glFogi(GL_FOG_MODE, GL_LINEAR);
//    glFogfv(GL_FOG_COLOR, fogColor);
//    glFogf(GL_FOG_DENSITY, 0.8);
//    glHint(GL_FOG_HINT, GL_DONT_CARE);
//    glFogf(GL_FOG_START, mouseY*10);
//    glFogf(GL_FOG_END, mouseY * 10);
//    glEnable(GL_FOG);
    ofBackground(0);


//    ofBackground(0);
//    
//    GLfloat fogColor[4] = {0,0,0, 0.3};
//    glFogi(GL_FOG_MODE, GL_LINEAR);
//    glFogfv(GL_FOG_COLOR, fogColor);
//    glFogf(GL_FOG_DENSITY, 0.8);
//    glHint(GL_FOG_HINT, GL_DONT_CARE);
//    glFogf(GL_FOG_START, -500);
//    glFogf(GL_FOG_END, 1200);
//    glEnable(GL_FOG);
//    
//    
//    m.rotate(1 + 1 * sin(ofGetElapsedTimef()*0.4), 0, 1, 0);
////     m.rotate(1 + 1 * sin(ofGetElapsedTimef()*0.4+1), 1, 0, 0);
////    
//    
//    //cam.enableOrtho();
cam.begin();
    //ofRotate(ofGetElapsedTimef()*30, 0,1,0);
    //prim.drawWireframe();
    b.draw(cam.getPosition());
//    
//    ofMultMatrix(m);
//    //ofRotate(ofGetElapsedTimef()*40, 0, 1, 0);
//    ofScale(1.5, 1.5, 1.5);
//    b.draw();
//    b2.draw();
//    
//    ofEnableBlendMode(OF_BLENDMODE_ADD);
//    
//    for (int  i = 0; i < b.line.size(); i++){
//        int smallest = -1;
//        float smallestDist = 1000000;
//        for (int j = 0; j < b2.line.size(); j++){
//            float dist = (b2.line[j] - b.line[i]).length();
//            if (dist < smallestDist){
//                smallestDist = dist;
//                smallest = j;
//            }
//        }
//        if (smallest != - 1 && smallestDist < mouseX){
//            
//            line l;
//            l.a = i;
//            l.b = smallest;
//            l.energy = 1.0;
//            //lines.push_back(l);
//            ofLine( b.line[i],  b2.line[smallest]);
//        }
//    }
//    
//    for (auto & a : lines){
//        if (a.energy > 0.01){
//            
//            ofPoint diff = b2.line[a.b] -b.line[a.a];
//            ofPoint center = (b2.line[a.b] + b.line[a.a])/2.0;
//            
////            ofSetColor(255);
////            ofLine(b2.line[a.b], b2.line[a.b] - diff * a.energy);
////            
////            ofSetColor(255);
////            ofLine(b.line[a.a], b.line[a.a] + diff * a.energy);
////            
//            
//            a.energy *= 0.99;;
//        }
//    }
    
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
