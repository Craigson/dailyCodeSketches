#include "ofApp.h"




//--------------------------------------------------------------
void ofApp::setup(){

    
    for (int i = 0; i < 4; i++){
        
        blob b;
        b.setup();
        blobs.push_back(b);
        
    }
//    a.setup();
//    a.highlightColor = ofColor::white;
//    a.mainColor = ofColor::darkTurquoise;
//    
//    b.setup();
//    b.highlightColor = ofColor::white;
//    b.mainColor = ofColor::cyan;

   
    
    
    shader.load("", "dot.fs");
    
//    for (int i = 0; i < b.particles.size(); i++){
//        b.particles[i]->damping *= 0.8;
//    }
}





//--------------------------------------------------------------
void ofApp::update(){

//    for (int i = 0; i < blobs.size(); i++){
//        blobs[i].update();
//    }
    
   
    ofHideCursor();
    
//    // go through every edge, calc its orientation
//    // go through every point, calc its distance to closest edge, store that
//    // try to do something with orientation...
//    
//    
//    
//    lineHistory.push_back(a.lineRespaced);
//    lineHistory[lineHistory.size()-1].setClosed(true);
//    if (lineHistory.size() > 80){
//        lineHistory.erase(lineHistory.begin());
//    }
//    for (int i = 0; i < lineHistory.size(); i++){
//        lineHistory[i] = lineHistory[i].getSmoothed(3);
//    }
}

ofPolyline drawCircle(float x, float y, float r, int num, float startAngle){
    
    ofPolyline temp;
    for (int i = 0; i < num; i++){
        float angle = ofMap(i, 0, num, 0, TWO_PI) + startAngle;
        ofPoint pt(x + cos(angle)*r, y + sin(angle)*r);
        temp.addVertex(pt);
        
    }
    return temp;
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofColor tempCo;
    tempCo.setHex(0x300032);
    tempCo = ofColor::black;
    //tempCo.setBrightness(tempCo.getBrightness() * ofMap(mouseX, 0, ofGetWidth(), 0, 1));
    ofBackground(tempCo);
    
  
//    ofPolyline aLine = a.lineRespaced;
//    ofPolyline bLine = b.lineRespaced;
//    
//    for (int i = 0; i < bLine.size(); i++){
//            ofPoint pt = bLine[i];
//            pt-=ofPoint(320,320);
//            pt*= 2.0;
//            pt+=ofPoint(320,320);
//        bLine[i] = pt;
//    }
//    
//    
//    aLine.setClosed(true);
//    
//    aLine = aLine.getResampledByCount(1000);
//    
//    aLine = aLine.getSmoothed(11);
//    
//    
//    
//    
//    bLine.setClosed(true);
//    
//    bLine = bLine.getResampledByCount(1000);
//    
//    bLine = bLine.getSmoothed(11);
//    
//    for (int i = 0; i < bLine.size(); i++){
//        bLine[i] =  (bLine[i] - ofPoint(320,320)) * ofMap(mouseX, 0, ofGetWidth(), 0, 2) + ofPoint(320,320);
//    }
//    
//    
//    for (int i = 0; i < aLine.size(); i++){
//        aLine[i] =  (aLine[i] - ofPoint(320,320)) * ofMap(mouseY, 0, ofGetHeight(), 0, 2) + ofPoint(320,320);
//    }
//    
    
    //aLine.draw();
    
//    //ofSetColor(255,255,255,20);
//    vector < ofPolyline > vertices;
//    for (int i = 0; i < aLine.size(); i++){
//        ofPolyline temp;
//        vertices.push_back(temp);
//    }
//    
//    int count = 0;
//    for (auto line : lineHistory){
//        
//        ofPolyline temp;
//        for (int i = 0; i < line.size(); i++){
//            ofPoint pt = line[i];
//            pt-=ofPoint(320,320);
//            pt*= 1.0 + ((79-count)/79.0) * mouseX/10.0;
//            pt+=ofPoint(320,320);
//            temp.addVertex(pt);
//            
//            if (i < vertices.size()){
//                vertices[i].addVertex(pt);
//            }
//        }
//        count ++;
//        temp.draw();
//    }
//    
//    for (auto v : vertices){
//        v.draw();
//    }
    
    //a.draw();
    
    ofPath p;
    p.setCircleResolution(1000);
    p.circle(320,320, 300);
    //p.rectangle(5,5,640-10,640-10);
    ofPolyline rectLine = p.getOutline()[0];
    
    rectLine.getVertices().erase(rectLine.getVertices().begin());
    
   // rectLine = rectLine.getResampledByCount(a.lineRespaced.size());
    
    
//    //ofSetColor(255,255,255,10);
//    for (int i = 0; i < bLine.size(); i+=10){
//        ofPoint aa = bLine[i];
//        int smallestIndex = -1;
//        float smallestDistance = 1000000;
//        for (int j = 0; j < aLine.size(); j++){
//            float dist = (aLine[j] - aa).length();
//            if (dist < smallestDistance){
//                smallestDistance = dist;
//                smallestIndex = j;
//            }
//        }
//        ofLine(aa, aLine[smallestIndex]);
//    }
//    
//    
    
//    for (int i = 0; i < aLine.size(); i+=10){
//        ofPoint aa = aLine[i];
//        int smallestIndex = -1;
//        float smallestDistance = 1000000;
//        for (int j = 0; j < bLine.size(); j++){
//            float dist = (bLine[j] - aa).length();
//            if (dist < smallestDistance){
//                smallestDistance = dist;
//                smallestIndex = j;
//            }
//        }
//        ofLine(aa, bLine[smallestIndex]);
//    }

    
    vector < ofxPolylines > linesToTry;
    
    
    float time = ofGetElapsedTimef();
    
    
    
    
//    for (int i = 0; i < 100; i++){
//    
//        float pct = 0.5 + 0.5 * sin(time);
//        
//        float pctMap = ofMap(i,0, 100-1, 0, 1);
//        float angle = ofRandom(0, TWO_PI);
//        pctMap = powf(pctMap, 0.2);
//        ofPoint targetA = ofPoint(320,320) - ofPoint(cos(angle),sin(angle)) * 100;
//        ofPoint targetB = ofPoint(320,320) + ofPoint(cos(angle),sin(angle)) * 100;
//        
//        ofPoint pos = targetA + pct * (targetB - targetA);
//        ofxPolylines t;
//        
//        
//        t.push_back(drawCircle(pos.x, pos.y, 200- i*2, 100 , 0));
//                    
//        linesToTry.push_back(t);
//    }
    
    
    ofSeedRandom(mouseX);
    
    for (int i = 0; i < 100; i++){
        
        float pct = 0.5 + 0.5 * sin(time/2.0);
        
        float pctMap = ofMap(i,0, 100-1, 0, 1);
        float angle = ofRandom(0, TWO_PI);
        pctMap = powf(pctMap, 0.2);
        ofPoint targetA = ofPoint(320,320) - ofPoint(cos(angle),sin(angle)) * 50;
        ofPoint targetB = ofPoint(320,320) + ofPoint(cos(angle),sin(angle)) * 50;
        ofPoint pos = targetA + pct * (targetB - targetA);
        pos.x += ofSignedNoise(time/3.0, i * 100, 0) * 100 * pct;
        pos.y += ofSignedNoise(time/3.0, i * 100, 10000) * 100 * pct;
        
        ofxPolylines t;
        
        t.push_back(drawCircle(pos.x, pos.y, 300- i*2, 100,  ofRandom(0, TWO_PI)));
        
        linesToTry.push_back(t);
    }
    
    
    
    
    ofxPolylines solution;
    solution.clear();
    
    for (int i = 0; i < linesToTry[0].size(); i++){
        solution.push_back(linesToTry[0][i]);
    }
    
    
    for (int i = 1; i < linesToTry.size(); i++){
        
        
      
        clipper.clear();
        for (int j = 0; j < solution.size(); j++){
            clipper.addPolyline(solution[j], OFX_CLIPPER_SUBJECT);
        }
        
        for (int j = 0; j < linesToTry[i].size(); j++){
            clipper.addPolyline(linesToTry[i][j], OFX_CLIPPER_CLIP);
        }
        
        solution.clear();
        
        clipper.clip(OFX_CLIPPER_INTERSECTION ,
                  solution,
                  OF_POLY_WINDING_ODD,
                  OF_POLY_WINDING_ODD);

        for (int j = 0; j < solution.size(); j++){
            solution[j].draw();
        }
//
//            vector < ofPolyline > holes;
//            
//            
//            mesh.triangulate(solution[j], holes, 28, -1);
//            
//            ofMesh temp;
//            
//            temp.setMode(OF_PRIMITIVE_TRIANGLES);
//            
//            temp.addVertices(mesh.outputPts);
//            
//            
//            for (int i = 0;  i < mesh.triangles.size(); i++){
//                temp.addIndex(mesh.triangles[i].index[0]);
//                temp.addIndex(mesh.triangles[i].index[1]);
//                temp.addIndex(mesh.triangles[i].index[2]);
//            }
//            
//            ofSetColor(255,0,i * 50, 255);
//            temp.draw();
//            
//            ofSetColor(255);
//            solution[j].draw();
        }

    
    for (int i = 0; i < linesToTry[0].size(); i++){
        linesToTry[0][i].setClosed(true);
        linesToTry[0][i].draw();
    }
    

    
    
    
    
    
//    clipper.clip(OFX_CLIPPER_INTERSECTION ,
//                 solution,
//                 OF_POLY_WINDING_ODD,
//                 OF_POLY_WINDING_ODD);
//    
//    
//    for (int i = 0; i < solution.size(); i++){
//        solution[i].draw();
//    }
////
//    
//    clipper.clear();
//    
//    for (int i = 0; i < solution.size(); i++){
//        clipper.addPolyline(solution[i], OFX_CLIPPER_SUBJECT);
//    }
//    clipper.addPolyline(bLine, OFX_CLIPPER_CLIP);
////
//    solution.clear();
//    clipper.clip(OFX_CLIPPER_INTERSECTION ,
//              solution,
//              OF_POLY_WINDING_ODD,
//              OF_POLY_WINDING_ODD);
//
//    for (int i = 0; i < solution.size(); i++){
//        solution[i].draw();
//    }
//
//    solution.clear();
//    
//    //aLine.draw();
//    
////    clipper.clip(OFX_CLIPPER_DIFFERENCE ,
////                 solution,
////                 OF_POLY_WINDING_ODD,
////                 OF_POLY_WINDING_ODD);
//    
//    for (int i = 0; i < solution.size(); i++){
//        solution[i].draw();
//    }

    
    
//    ofEnableAlphaBlending();
//    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
//    ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
//    
//    
//    shader.begin();
//    shader.setUniform3f("color", ofVec3f(0.0, 1.0, 1.0));
//    shader.setUniform1f("aa", 4.0 - sin(ofGetElapsedTimef()*0.2)*1.3);
//    shader.setUniform1f("bb", 2.0);
//    
//    a.draw();
//    shader.end();
//    
//    ofScale(1.3, 1.3);
//    ofTranslate(mouseX, mouseY);
//    
//    shader.begin();
//    
//    shader.setUniform1f("bb", 3.0);
//    shader.setUniform3f("color", ofVec3f(1.0, 0.0, 1.0));
//    shader.setUniform1f("aa", PI + sin(ofGetElapsedTimef()*0.2)*1.3);
//    
//    b.draw();
//    shader.end();

    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

//    if (key == 'a'){
//        for (int i = 0; i< 10; i++) a.addVertex();
//    }
//    
//    if (key == 'd'){
//       for (int i = 0; i< 10; i++) a.deleteVertex();
//    }
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
