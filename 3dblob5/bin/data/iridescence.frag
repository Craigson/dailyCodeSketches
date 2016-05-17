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
varying vec4 norm;
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
	float freq = 10.1;
	float oset = 1.2 + sin(orient)*10.1 - time*3.1;		//offset
	float noiseMult = 1.0 + 1.2 * cos(orient*1.0);
    //irid.x = abs(cos(orient*freq + diNoise(P*0.001 + time*0.1)*noiseMult + 1.0 + oset))*1.0 > 0.9 ?
    irid.x = 1.5-1.5*((abs(cos(orient*freq + diNoise(P*0.001 + time*0.1)*noiseMult + 1.2 + oset))*1.0 /0.9)*0.84)*2.0;
	irid.y = 0.5-0.5*((abs(cos(orient*freq + diNoise(P*0.001 + time*0.1)*noiseMult + 1.1 + oset))*1.0 /0.9)*0.94)*2.0;
	irid.z = 0.5-0.5*((abs(cos(orient*freq + diNoise(P*0.001 + time*0.1)*noiseMult + 1.00 + oset))*1.0 /0.9)*0.144)*2.0;
	return irid;
}

void main(){
	float Ki = 0.9;			//iridescence multiplicator
	
    float f =  dot(norm, vec4(0.0, 1.0, 0.0, 0.0));;
    float f2 =  dot(norm, vec4(1.0, 1.0, 0.0, 0.0));;
    float f3 =  dot(norm, vec4(0.0, 1.0, 1.0, 0.0));;

    //vec4 iridColor = vec4(iridescence(fr), 1.0) * setRange(pow(1.0 - fr, 2.3/0.75), 9.0, 0.3, 0.1, 1.0);
    gl_FragColor = vec4(vec3(1.0-1.0* iridescence(f3).x * iridescence(f2).x * iridescence(f).x), 1.0);
    gl_FragColor.a = 1.0;
}
