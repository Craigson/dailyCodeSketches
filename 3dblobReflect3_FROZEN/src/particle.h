#ifndef PARTICLE_H
#define PARTICLE_H

#include "ofMain.h"

class particle
{
    public:
        ofPoint pos;
        ofPoint vel;
        ofPoint frc;   // frc is also know as acceleration (newton says "f=ma")
			
        particle();
		virtual ~particle(){};

        void resetForce();
		void addForce(float x, float y, float z);
		void addRepulsionForce(float x, float y, float z, float radius, float scale);
		void addAttractionForce(float x, float y, float z, float radius, float scale);
		
		void addRepulsionForce(particle &p, float radius, float scale);
		void addAttractionForce(particle &p, float radius, float scale);
		void addClockwiseForce(particle &p, float radius, float scale);
		void addCounterClockwiseForce(particle &p, float radius, float scale);
	
		
		void addDampingForce();
        
		void setInitialCondition(float px, float py, float pz, float vx, float vy, float vz);
        void update();
        void draw();
	
		void bounceOffWalls();
	
		bool  bFixed;
	
		float damping;

    protected:
    private:
};

#endif // PARTICLE_H
