#include "ofApp.h"



inline ofPoint getNormalFacing ( ofPoint const incident, ofPoint const norma, ofPoint const normb){        // assume normalized....
    
    float a = incident.dot(norma);
    float b = incident.dot(normb);
    if (a < b) return norma;
    else return normb;
}


ofPoint getReflect( ofPoint const incident, ofPoint const norma, ofPoint const normb){     // assume normalized....
    ofPoint normal = getNormalFacing(incident, norma, normb);
    return incident - normal * 2.f * normal.dot(incident);
}




ofIcoSpherePrimitive prim;
//--------------------------------------------------------------
void blob::setup(){
    
    ofHideCursor();
    
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
        if (ofGetMousePressed())particles[i]->update();
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
    
   // cout << ofGetMouseX() << " " << ofGetMouseY() << endl;
    
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
        
        glBegin(GL_LINES);
        glColor3f(0.2, 0.2, 0.2); //glColor3f(f/255.0, f/255.0, f/255.0);
        glVertex3f(springs[i].particleA->pos.x, springs[i].particleA->pos.y, springs[i].particleA->pos.z);
        
        glColor3f(0.2, 0.2, 0.2); // glColor3f(f2/255.0, f2/255.0, f2/255.0);
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
    
//    ofSetColor(255);
//    for (int i = 0; i < tris.size(); i++){
//        float dista = (camPt -tris[i].midPt).length();
//        
//        float f = ofMap(dista, 732, 420, 0, 255, true);
//        
//        
//        ofSetColor(ofMap(f, 0, 255, 50, 255));
//        ofLine(tris[i].midPt, tris[i].midPt + tris[i].normal * f*0.1 );
//    }
//    
//    
//    for (int i = 0; i < tris.size(); i++){
//        for (int j = 0; j < 3; j++){
//            
//            ofPoint to;
//            ofPoint normalTo;
//            if (j == 0){
//                to = particles[tris[i].a]->pos;
//                normalTo = normalCalcs[tris[i].a].normal;
//            } else if (j == 1){
//                to = particles[tris[i].b]->pos;
//                normalTo = normalCalcs[tris[i].b].normal;
//            } else {
//                to = particles[tris[i].c]->pos;
//                normalTo = normalCalcs[tris[i].c].normal;
//            }
//            ofPoint pt = (tris[i].midPt + to)/2.0;
//            
//            
//            float dista = (camPt -pt).length();
//         
//            ofPoint normal = (tris[i].normal  + normalTo).normalize();
//            float f = ofMap(dista, 732, 420, 0, 255, true);
//            ofSetColor(ofMap(f, 0, 255, 50, 255));
//            
//            ofLine(pt, pt + normal * f*0.1 );
//        }
//    }
//    
//    for (int i = 0; i < particles.size(); i++){
//        float dista = (camPt -particles[i]->pos).length();
//        
//        float f = ofMap(dista, 732, 420, 0, 255, true);
//        ofSetColor(ofMap(f, 0, 255, 50, 255));
//        
//        ofLine(particles[i]->pos, particles[i]->pos + normalCalcs[i].normal * f*0.1 );
//    }
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


class IntersectInfo
{
public:
    IntersectInfo()
    {
        bIntersect = false;
    }
    int who;
    bool bIntersect;
    ofPoint intersectPos;
    float distance;
};

ofVec3f getNormal(vector<ofVec3f> pverts)
{
    ofVec3f t0 = pverts.at(1)-pverts.at(0);
    ofVec3f t1 = pverts.at(2)-pverts.at(0);
    ofVec3f normal = t0.getCrossed(t1);
    normal.normalize();
    return  normal;
}


IntersectInfo judgeRayTri(ofVec3f rayStart, ofVec3f rayDir, vector<ofVec3f> tri)
{
    IntersectInfo result;
    
    rayDir.normalize();
    
    ofVec3f triNorm = getNormal(tri);
    triNorm = triNorm;
    float vn = rayDir.dot(triNorm);
    
    ofVec3f aa = rayStart - tri.at(0);
    float xpn = aa.dot(triNorm);
    float distance = -xpn / vn;
    
    if (distance < 0) {
        return result; // behind ray origin. fail
    }
    ofPoint hitPos(rayDir.x * distance + rayStart.x,
                   rayDir.y * distance + rayStart.y,
                   rayDir.z * distance + rayStart.z);
    
    ofVec3f hit00 = hitPos - tri.at(0);
    ofVec3f hit01 = tri.at(1) - tri.at(0);
    ofVec3f cross0 = hit00.cross(hit01);
    if (cross0.dot(triNorm) > 0.000000001) return result;; // not in tri. fail
    
    ofVec3f hit10 = hitPos - tri.at(1);
    ofVec3f hit11 = tri.at(2) - tri.at(1);
    ofVec3f cross1 = hit10.cross(hit11);
    if (cross1.dot(triNorm) > 0.000000001) return result;; // not in tri. fail
    
    ofVec3f hit20 = hitPos - tri.at(2);
    ofVec3f hit21 = tri.at(0) - tri.at(2);
    ofVec3f cross2 = hit20.cross(hit21);
    if (cross2.dot(triNorm) > 0.000000001) return result;; // not in tri. fail
    
    // intersect!
    result.bIntersect = true;
    result.intersectPos = hitPos;
    result.distance = distance;
    return result;
    
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

    ofMatrix4x4 mat;
    mat.rotate(1, 0,1,0);
    cam.setPosition(  mat*cam.getPosition());
    cam.lookAt(ofPoint(0,0,0));
    cam.begin();
    

    //ofRotateY(ofGetElapsedTimef()*50);
    
    b.draw(cam.getPosition());
    
    
    vector < Box > boxes;
    
    for (int i = 0; i < b.tris.size(); i++){
        
        ofPoint min;
        ofPoint max;
        
        ofPoint verts[3];
        verts[0] = (b.particles[b.tris[i].a]->pos);
        verts[1] = (b.particles[b.tris[i].b]->pos);
        verts[2] = (b.particles[b.tris[i].c]->pos);
        
        for (int j = 0; j < 3; j++){
            if (j == 0) min = max = verts[j];
            else {
                min.x = MIN(min.x, verts[j].x);
                min.y = MIN(min.y, verts[j].y);
                min.z = MIN(min.z, verts[j].z);
                max.x = MAX(max.x, verts[j].x);
                max.y = MAX(max.y, verts[j].y);
                max.z = MAX(max.z, verts[j].z);
                
            }
        }
        Box b(min, max);
        boxes.push_back(b);
        
    }
    
    ofSetColor(255);

    ofDisableDepthTest();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    
    if (!ofGetMousePressed()){
    ofSeedRandom(0);
    }else {
        ofSeedRandom();
    }
 
    for (int i = 0; i < b.tris.size(); i++){
        
        if (i < mouseX){
            float pct = (float)(i / (float)b.tris.size());
            
            ofPoint aa = ofPoint(ofRandom(-100,100), ofRandom(-100,100), ofRandom(-100,100)) * (3 + pct*8);
            float f = 1.0;
            ofPoint dir = ofPoint(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1)) * f;
            dir = dir.getNormalized();
            Ray r (aa, dir);
            
            int bounceCount = 0;
            bool bKeepBouncing = true;
            int lastHit = i;
            
            while (bKeepBouncing){
                
                bool bHitAny;
                vector < IntersectInfo > hits;
                for (int j = 0; j < boxes.size(); j++){
                    if (j != lastHit){
                        if (boxes[j].intersect(r, 0,10000)){
                            
                            vector < ofPoint >  pts;
                            pts.resize(3);
                            pts[0] = (b.particles[b.tris[j].a]->pos);
                            pts[1] = (b.particles[b.tris[j].b]->pos);
                            pts[2] = (b.particles[b.tris[j].c]->pos);
                            
                            
                            IntersectInfo ii = judgeRayTri(aa, dir, pts);
                            ii.who = j;
                            if (ii.bIntersect == true){
                                hits.push_back(ii);
                            }
                        }
                    }
                }
                
                //cout << hits.size() << endl;
                
                if (hits.size() == 0) bKeepBouncing = false;
                else {
                    int closeest = -1;
                    float closestDist = 100000;
                    int whichHit = -1;
                    
                    for (int j = 0; j < hits.size(); j++){
                        float dist = (hits[j].intersectPos - aa).length();
                        if (dist < closestDist){
                            closestDist = dist;
                            closeest = hits[j].who;
                            whichHit = j;
                        }
                    }
                    if (closeest != -1){
                        ofSetColor(255,255,255);
                        
                        //cout << hits[closeest].intersectPos << endl;
                        
                        //ofLine(aa, hits[whichHit].intersectPos);
                        
                        ofPoint camPt = cam.getPosition();
                        ofPoint bb = hits[whichHit].intersectPos;
                        
                        float dista = (camPt - aa).length();
                        float distb = (camPt - bb   ).length();
                        
                        float f = ofMap(dista, 732, 420, 0, 255, true);
                        float f2 = ofMap(distb, 732, 420, 0, 255, true);
                        
                        
                        glBegin(GL_LINES);
                        glColor3f(f/255.0, f/255.0, f/255.0);
                        glVertex3f(aa.x, aa.y, aa.z);
                        glColor3f(f2/255.0, f2/255.0, f2/255.0);
                        glVertex3f(bb.x, bb.y, bb.z);
                        
                        glEnd();
                        
                        
                        ofSetColor(255);
                        
                       // ofLine( b.particles[b.tris[closeest].a]->pos, b.particles[b.tris[closeest].b]->pos);
                       // ofLine( b.particles[b.tris[closeest].b]->pos, b.particles[b.tris[closeest].c]->pos);
                       // ofLine( b.particles[b.tris[closeest].c]->pos, b.particles[b.tris[closeest].a]->pos);
                        
                        dir = getReflect(dir, b.tris[closeest].normal,  -1*b.tris[closeest].normal );
                        
                        
                        
                        aa = hits[whichHit].intersectPos;
  //                      ofSetColor(255,0,0);
                        lastHit = closeest;
//                         ofLine(aa, aa  + dir*100.0);
                        r = Ray(aa, dir);
                        
                        bounceCount++;
                        if (bounceCount == 100){
                            bKeepBouncing = false;
                        }
                        
                    } else {
                        bKeepBouncing = false;
                    }
                    
                    
                }
                
                
            }
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
