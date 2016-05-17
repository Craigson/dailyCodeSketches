#pragma once

#include "ofMain.h"
#include "particle.h"
#include "spring.h"



typedef struct {
    int a,b,c;
    ofPoint normal;
    ofPoint midPt;
} tri;

typedef struct {
    int nNormals;
    ofPoint normal;
} normalCalc;


class blob{
  
public:
    
    float scale;
    float offset;
    vector < particle *  > particles;
    vector < spring > springs;
    
    void setup();
    void update();
    void draw(ofPoint camPt);
    

    
    vector < tri > tris;
    vector < normalCalc > normalCalcs;
    
    
    ofPolyline line;
};


typedef struct  {
    
    int a;
    int b;
    float energy;
}line;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    
    vector < line > lines;
    
    ofEasyCam cam;
    blob b;
    blob b2;
};
