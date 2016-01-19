
#include "ofMain.h"
#include "spring.h"
#include "particle.h"
#include "ofxTriangleMesh.h"


class blob {
    
public:
    
    void setup();
    void update();
    void draw();
    
    
    vector < spring > springs;
    vector < particle * > particles;
    ofPolyline line;
    ofxTriangleMesh mesh;
    
    
    vector < float > distances;
    vector < float > closestAngle;
    float fSooth = 20;
    
    ofColor highlightColor;
    ofColor mainColor;
    ofPoint targetPos;
    
    float randomOffset;
};

