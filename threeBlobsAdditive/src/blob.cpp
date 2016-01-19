//
//  blob.cpp
//  blobSketch
//
//  Created by zach on 1/18/16.
//
//

#include "blob.h"

float minimum_distance(ofPoint v, ofPoint w, ofPoint p) {
    // Return minimum distance between line segment vw and point p
    const float l2 = (v-w).lengthSquared();  // i.e. |w-v|^2 -  avoid a sqrt
    if (l2 == 0.0) return (p-v).length();   // v == w case
    // Consider the line extending the segment, parameterized as v + t (w - v).
    // We find projection of point p onto the line.
    // It falls where t = [(p-v) . (w-v)] / |w-v|^2
    const float t = (p-v).dot(w - v) / l2;
    if (t < 0.0) return (p-v).length();       // Beyond the 'v' end of the segment
    else if (t > 1.0) return (p-w).length();  // Beyond the 'w' end of the segment
    const ofPoint projection = v + t * (w - v);  // Projection falls on the segment
    return (p-projection).length();
}
    
void blob::setup(){
    
    randomOffset = ofRandom(-PI, PI);
    
    targetPos.set(320,320);
    
    for (int i = 0; i < 100; i++){
        float angle = ofMap(i, 0, 100, 0, TWO_PI);
        ofPoint pos = ofPoint(320,320) + 100 * ofPoint(cos(angle), sin(angle));
        particle * p = new particle();
        p->setInitialCondition(pos.x, pos.y, 0, 0);
        particles.push_back(p);
    }
    
    for (int i = 0; i < particles.size(); i++){
        int m = i;
        int m_p_1 = (i+1) % particles.size();
        spring s;
        s.particleA = particles[m];
        s.particleB = particles[m_p_1];
        s.distance = 5;
        s.springiness = 0.4;
        springs.push_back(s);
    }
}
void blob::update(){
    float f = ofGetElapsedTimef();
    
    for (int i = 0; i < particles.size(); i++){
        particles[i]->resetForce();
        particles[i]->addDampingForce();
        
        particles[i]->addAttractionForce(targetPos.x,targetPos.y, 1000, 0.005);
    }
    
    
    
    fSooth = 0.85 * fSooth + 0.15 * ofMap(sin(f + randomOffset), -1, 1, 20, 100);
    
    for (int i = 0; i < particles.size(); i++){
        for (int j = 0; j < i; j++){
            particles[i]->addRepulsionForce(*(particles[j]), fSooth, 1.0);
        }
    }
    
    for (auto spring : springs){
        spring.update();
    }
    
    
    for (int i = 0; i < particles.size(); i++){
        particles[i]->update();
    }
    
    line.clear();
    
    for (auto p : particles){
        line.addVertex(p->pos);
    }
    ofPolyline lineRespaced = line;
    
    // add the last point (so when we resample, it's a closed polygon)
    lineRespaced.addVertex(lineRespaced[0]);
    // resample
    lineRespaced = lineRespaced.getResampledByCount(200);
    // I want to make sure the first point and the last point are not the same, since triangle is unhappy:
    lineRespaced.getVertices().erase(lineRespaced.getVertices().begin());
    // if we have a proper set of points, mesh them:
    if (lineRespaced.size() > 5){
        
        // angle constraint = 28
        // size constraint = -1 (don't constraint triangles by size);
        
        mesh.triangulate(lineRespaced, 33, -1);
        
        
        // this is an alternative, constrain on size not angle:
        //mesh.triangulate(lineRespaced, -1, 200);
        
        // see ofxTriangleMesh.h for info.
        
    }
    
    
    // lineRespaced
    
    vector < ofPoint > pts = mesh.outputPts;
    
    distances.clear();
    closestAngle.clear();
    
    for (auto pt : pts){
        
        float minDist = 10000;
        float minAngle = 0;
        for (int i = 0; i < lineRespaced.getVertices().size(); i++){
            
            ofPoint a = lineRespaced[i];
            ofPoint b = lineRespaced[ (i+1) % lineRespaced.size()];
            float dist = minimum_distance(a,b, pt);
            if (dist < minDist){
                minDist = dist;
                minAngle = atan2( (b-a).y, (b-a).x);
            }
        }
        //        for (auto origPt : line.getVertices()){
        //            float dist = (origPt - pt).length();
        //            if (dist < minDist){
        //                minDist = dist;
        //            }
        //
        //
        //        }
        distances.push_back(minDist);
        closestAngle.push_back(minAngle);
    }

}
void blob::draw(){
    
    //    for (int i = 0; i < particles.size(); i++){
    //        particles[i]->draw();
    //    }
    //
    //    for (int i = 0; i < springs.size(); i++){
    //        springs[i].draw();
    //    }
    
    ofMesh temp;
    
    temp.setMode(OF_PRIMITIVE_TRIANGLES);
    
    temp.addVertices(mesh.outputPts);
    
    float angToMatch = ofGetElapsedTimef();
    
    for (int i = 0; i < distances.size(); i++){
        
        
        ofPoint up(cos(angToMatch), sin(angToMatch), 0);
        float ang = closestAngle[i];
        ofPoint dir(cos(ang), sin(ang), 0);
        
        float mix = up.dot(dir);
        
        if (mix < 0) mix = fabs(mix);
        //cout << mix << endl;
        
        //mix = ofMap(mix, -1,1, 0,1, true);
        
        float scale = ofMap(distances[i], 0, ofGetMouseX(), 1, 0, true) * mix;
        
        ofPoint a;
        a.set(mainColor.r, mainColor.g, mainColor.b);
        
        ofPoint b;
        b.set(highlightColor.r, highlightColor.g, highlightColor.b);
        
        ofPoint c = scale * b + (1-scale) * a;
        
        temp.addColor(ofColor(c.x, c.y, c.z));
    
    }
    
    for (int i = 0;  i < mesh.triangles.size(); i++){
        temp.addIndex(mesh.triangles[i].index[0]);
        temp.addIndex(mesh.triangles[i].index[1]);
        temp.addIndex(mesh.triangles[i].index[2]);
    }
    
    temp.draw();
    
}
