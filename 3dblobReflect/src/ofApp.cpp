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
            aWho = particles.size()-1;
        }
        
        if (bWho == -1){
            particle * p = new particle();
            p->setInitialCondition(b.x,b.y,b.z, 0, 0, 0);
            particles.push_back(p);
            bWho = particles.size()-1;
        }
        
        if (cWho == -1){
            particle * p = new particle();
            p->setInitialCondition(c.x,c.y,c.z, 0, 0, 0);
            particles.push_back(p);
            cWho = particles.size()-1;
        }
        
        tri myTri;
        myTri.a = aWho;
        myTri.b = bWho;
        myTri.c = cWho;
        tris.push_back(myTri);
        
        
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
    
    
    for (int i = 0; i < tris.size(); i++){
        ofPoint a = particles[tris[i].a]->pos;
        ofPoint b = particles[tris[i].b]->pos;
        ofPoint c = particles[tris[i].c]->pos;
        ofPoint diff = a-b;
        ofPoint diff2 = c-b;
        diff.normalize();
        diff2.normalize();
        
        ofPoint normal = diff.cross(diff2);
        tris[i].normal = normal;
        tris[i].midPt = (a+b+c)/3.0;
    }
    
    
    normalCalcs.clear();
    
    for (int i = 0; i < particles.size(); i++){
        normalCalc calc;
        calc.normal.set(0,0,0);
        calc.nNormals = 0;
        normalCalcs.push_back(calc);
    }
    
    for (int i = 0; i < tris.size(); i++){
        normalCalcs[tris[i].a].nNormals++;
        normalCalcs[tris[i].a].normal+= tris[i].normal;
        normalCalcs[tris[i].b].nNormals++;
        normalCalcs[tris[i].b].normal+= tris[i].normal;
        normalCalcs[tris[i].c].nNormals++;
        normalCalcs[tris[i].c].normal+= tris[i].normal;
    }
    
    for (int i = 0; i < normalCalcs.size(); i++){
        normalCalcs[i].normal /= (float)normalCalcs[i].nNormals;
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
        
        
//        glBegin(GL_POINTS);
//        glColor3f(f/255.0, f/255.0, f/255.0);
//        glVertex3f(springs[i].particleA->pos.x, springs[i].particleA->pos.y, springs[i].particleA->pos.z);
//        
//        glColor3f(f2/255.0, f2/255.0, f2/255.0);
//        glVertex3f(springs[i].particleB->pos.x, springs[i].particleB->pos.y, springs[i].particleB->pos.z);
//        
//        glEnd();
//        
//        glBegin(GL_LINES);
//        glColor3f(f/255.0, f/255.0, f/255.0);
//        glVertex3f(springs[i].particleA->pos.x, springs[i].particleA->pos.y, springs[i].particleA->pos.z);
//        
//        glColor3f(f2/255.0, f2/255.0, f2/255.0);
//        glVertex3f(springs[i].particleB->pos.x, springs[i].particleB->pos.y, springs[i].particleB->pos.z);
//        
//        glEnd();

    
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
    
    ofSetColor(255);
    for (int i = 0; i < tris.size(); i++){
        float dista = (camPt -tris[i].midPt).length();
        
        float f = ofMap(dista, 732, 420, 0, 255, true);
        
        
        ofSetColor(ofMap(f, 0, 255, 50, 255));
        ofLine(tris[i].midPt, tris[i].midPt + tris[i].normal * f*0.1 );
    }
    
    
    for (int i = 0; i < tris.size(); i++){
        for (int j = 0; j < 3; j++){
            
            ofPoint to;
            ofPoint normalTo;
            if (j == 0){
                to = particles[tris[i].a]->pos;
                normalTo = normalCalcs[tris[i].a].normal;
            } else if (j == 1){
                to = particles[tris[i].b]->pos;
                normalTo = normalCalcs[tris[i].b].normal;
            } else {
                to = particles[tris[i].c]->pos;
                normalTo = normalCalcs[tris[i].c].normal;
            }
            ofPoint pt = (tris[i].midPt + to)/2.0;
            
            
            float dista = (camPt -pt).length();
         
            ofPoint normal = (tris[i].normal  + normalTo).normalize();
            float f = ofMap(dista, 732, 420, 0, 255, true);
            ofSetColor(ofMap(f, 0, 255, 50, 255));
            
            ofLine(pt, pt + normal * f*0.1 );
        }
    }
    
    for (int i = 0; i < particles.size(); i++){
        float dista = (camPt -particles[i]->pos).length();
        
        float f = ofMap(dista, 732, 420, 0, 255, true);
        ofSetColor(ofMap(f, 0, 255, 50, 255));
        
        ofLine(particles[i]->pos, particles[i]->pos + normalCalcs[i].normal * f*0.1 );
    }
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


bool testRayThruTriangle( ofPoint P1, ofPoint P2, ofPoint P3, ofPoint R1, ofPoint R2, ofPoint& PIP)
{
    ofPoint Normal, IntersectPos;
    
    // Find Triangle Normal
    Normal = (P3 - P1).cross( P2 - P1 );
    Normal.normalize(); // not really needed?  ofPoint does this with cross.
    
    // Find distance from LP1 and LP2 to the plane defined by the triangle
    float Dist1 = (R1-P1).dot( Normal );
    float Dist2 = (R2-P1).dot( Normal );
    
    if ( (Dist1 * Dist2) >= 0.0f) {
        //SFLog(@"no cross");
        return false;
    } // line doesn't cross the triangle.
    
    if ( Dist1 == Dist2) {
        //SFLog(@"parallel");
        return false;
    } // line and plane are parallel
    
    // Find point on the line that intersects with the plane
    IntersectPos = R1 + (R2-R1) * ( -Dist1/(Dist2-Dist1) );
    
    // Find if the interesection point lies inside the triangle by testing it against all edges
    ofPoint vTest;
    
    vTest = Normal.cross( P2-P1 );
    if ( vTest.dot( IntersectPos-P1) < 0.0f ) {
        //SFLog(@"no intersect P2-P1");
        return false;
    }
    
    vTest = Normal.cross( P3-P2 );
    if ( vTest.dot( IntersectPos-P2) < 0.0f ) {
        //SFLog(@"no intersect P3-P2");
        return false;
    }
    
    vTest = Normal.cross( P1-P3 );
    if ( vTest.dot( IntersectPos-P1) < 0.0f ) {
        //SFLog(@"no intersect P1-P3");
        return false;
    }
    
    PIP = IntersectPos;
    
    return true;
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
    
    ofBackground(0);

cam.begin();
    b.draw(cam.getPosition());

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
