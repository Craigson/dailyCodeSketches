/*...................................................................................................
Author: Diego Inácio
Shader: iridescence 01
Version: 1.0.0
Dev.: OpenGL Shading Language
Date Upadated: JAN/09/2014
www.diegoinacio.com
.....................................................................................................
Fragment part of a simple iridescent shader using OpenGL Shading Language.

If you have any comment, sent it to me at: diegodci@gmail.com
Thank you! :D
.....................................................................................................
References:

ROST et al. OpenGL Shading Language, 3rd edition.

BAILEY; CUNNINGHAM. Graphics Shaders: Theory and Practice, 2nd Edition.

EBERT et al. Texturing and Modeling: A Procedural Approach, 3rd edition.
.....................................................................................................
Resources:

<OpenGL>
http://www.opengl.org/
...................................................................................................*/

varying vec4 P;
varying float fr;
uniform float time;

float setRange(float value, float oMin, float oMax, float iMin, float iMax){
	return iMin + ((value - oMin)/(oMax - oMin)) * (iMax - iMin);
}

float diNoise(vec4 pos){
	//noise function to create irregularity
	float mult = 1.0;
	float oset = 45.0;		//offset
	return	sin(pos.x*mult*2.0 + 12.0 + oset) + cos(pos.z*mult + 21.0 + oset) *
		sin(pos.y*mult*2.0 + 23.0 + oset) + cos(pos.y*mult + 32.0 + oset) *
		sin(pos.z*mult*2.0 + 34.0 + oset) + cos(pos.x*mult + 43.0 + oset);
}

vec3 iridescence(float orient){
	//this function returns a iridescence value based on orientation
	vec3 irid;
	float freq = 2.1;
	float oset = 10.2 + sin(orient)*15.0 + time*1.0;		//offset
	float noiseMult = 10.2;
	irid.x = abs(cos(orient*freq + diNoise(P*0.001)*noiseMult + 1.0 + oset))*1.1;
	irid.y = abs(cos(orient*freq + diNoise(P*0.001)*noiseMult + 2.0 + oset))*0.9;
	irid.z = abs(cos(orient*freq + diNoise(P*0.001)*noiseMult + 3.0 + oset))*1.3;
	return irid;
}

void main(){
	float Ki = 0.3;			//iridescence multiplicator
	vec4 iridColor = vec4(iridescence(fr), 1.0) * setRange(pow(1.0 - fr, 2.3/0.75), 9.0, 0.3, 0.1, 1.0);
	gl_FragColor = iridColor*Ki;
    gl_FragColor.a = 1.0;
}
