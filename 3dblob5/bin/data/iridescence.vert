/*...................................................................................................
Author: Diego Inácio
Shader: iridescence 01
Version: 1.0.0
Dev.: OpenGL Shading Language
Date Upadated: JAN/09/2014
www.diegoinacio.com
.....................................................................................................
Vertex part of a simple iridescent shader using OpenGL Shading Language.

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
varying vec4 norm;

void main(){
	P = gl_Vertex;							//vertex position vector
	vec4 N = vec4(gl_Normal, 1.0);				//vertex normal vector
	vec4 V = gl_ModelViewMatrix * gl_Vertex;			//eye to vertex vector
	vec4 E = normalize(-V);						//normalized vertex to eye vector
	fr = dot(N, vec4(1.0, 0.0, 0.0, 0.1));							//facing ratio
    norm = N;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
