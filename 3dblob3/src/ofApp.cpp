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
void blob::draw(ofPoint camPt, bool bWireFrame){
    
    for (int i = 0; i < particles.size(); i++){

        //cout << particles[i]->pos << endl;
        //ofCircle(particles[i]->pos, 3);
    }
    
    //cout << ofGetMouseX() << " " << ofGetMouseY() << endl;
    
    
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    
    for (int i = 0; i < particles.size(); i++){
        mesh.addVertex(particles[i]->pos);
    }
    
    for (int i = 0; i < normalCalcs.size(); i++){
        mesh.addNormal(normalCalcs[i].normal);
    }
    for (int i = 0; i < tris.size(); i++){
        mesh.addIndex(tris[i].a);
        mesh.addIndex(tris[i].b);
        mesh.addIndex(tris[i].c);
        
    }
    
    if (!bWireFrame){
        mesh.draw();
    } else {
    
    
    
    for (int i = 0; i < springs.size(); i++){
        
        float dista = (camPt -springs[i].particleA->pos).length();
         float distb = (camPt -springs[i].particleB->pos    ).length();
        
        float f = ofMap(dista, 732, 420, 0, 255, true);
        float f2 = ofMap(distb, 732, 420, 0, 255, true);
        
        
        glPointSize( powf((f/255.0), 4.5) * 4 + 2);
        
        
        ofPoint a = springs[i].particleA->pos;
        ofPoint b = springs[i].particleB->pos;
        ofPoint diffa =camPt-a;
        a += diffa.getNormalized() * 2.0;
        ofPoint diffb =camPt-b;
        b += diffb.getNormalized() * 2.0;
        
        glBegin(GL_POINTS);
        glColor3f(0,0,0);
        glVertex3f(a.x, a.y, a.z);
        
        glColor3f(0,0,0);
        glVertex3f(b.x, b.y, b.z);
        
        glEnd();
        
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
    
    }
//    for (int i = 0; i < tris.size(); i++){
//        ofLine(tris[i].midPt, tris[i].midPt + tris[i].normal * 100);
//    }
    
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

   // ofEnableLighting();
    // ofSetSmoothLighting(true);
    
    ofEnableDepthTest();
    
    b.setup();
    
    b2.setup();
    
    shader.load("iridescence");
    
}

//--------------------------------------------------------------
void ofApp::update(){

    
    if (ofGetFrameNum() % 30 == 0){
        shader.load("iridescence");
        
    }
    // Point lights emit light in all directions //
    // set the diffuse color, color reflected from the light source //
    pointLight.setDiffuseColor( ofColor(100,100,100));
    
    // specular color, the highlight/shininess color //
    pointLight.setSpecularColor( ofColor(255.f, 255.f, 255.f));
    pointLight.setPosition(mouseX, mouseY, 0);
    
    
    
    b.update();
    b2.update();
}

ofMatrix4x4 m;

//--------------------------------------------------------------
void ofApp::draw(){
    
    
//    ofEnableLighting();
//    
//    pointLight.enable();
//    
    
//    glEnable(GL_ALPHA_TEST);
//    glAlphaFunc(GL_NOTEQUAL, 0);
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glEnable( GL_POINT_SMOOTH );
//    glPointSize( 10.0 );
    
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
    shader.begin();
    
    shader.setUniform1f("time", ofGetElapsedTimef());
    b.draw(cam.getPosition(), false);
    
    
    shader.end();
    
    ///b.draw(cam.getPosition(), true);
    
    
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
    
    ofDisableLighting();

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
