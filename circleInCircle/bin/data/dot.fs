#define M_PI 3.14159265358979323846

uniform float aa;
uniform float bb;
uniform vec3 color;

mat2 rotation = mat2( cos(M_PI/aa), sin(M_PI/aa*3.0),
                           -sin(M_PI/aa*1.0), cos(M_PI/aa*1.0));
void main(void)
{
    vec2 pos = mod(rotation * gl_FragCoord.xy, vec2(bb*2.0)) - vec2(bb*0.6);
    float dist_squared = dot(pos, pos);
    gl_FragColor = mix(vec4(color.x, color.y, color.z, 1.0), vec4(1.0, 1.0, 1.0, 1.0),
    smoothstep(1.25, 4.25, dist_squared));
}