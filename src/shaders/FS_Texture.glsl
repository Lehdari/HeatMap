/**
    FS_Texture.glsl

    @version    0.1
    @author     Miika 'LehdaRi' Lehtimäki
    @date       2015-04-18
**/


#version 330 core


#define PI 3.14159265359


in vec2 UV;

out vec4 color;

uniform sampler2D tex1;
uniform sampler2D tex2;


const float dx = 1.0 / 1024;
const float dy = 1.0 / 1024;

const int r = 10;


const float r2 = r*r;
const float ir = 1.0/r;
const float tentH = 3.0 / (PI*r*r);

const float n = 1.0 / (r*r);


float distrTent(float x) {
    return tentH - tentH*ir*x;
}

float sample1ch() {
    float s = 0;

    for (int j=-r; j<r; ++j) {
        for (int i=-r; i<r; ++i) {
            float d = sqrt(i*i + j*j);
            if (d>r)
                continue;

            s += texture(tex1, vec2(UV.x+i*dx, UV.y+j*dy)).r * distrTent(d);
        }
    }

    return s;
}

vec3 colFullSat(float x) {
    return vec3(-2.0+4.0*x, 2.0-4.0*abs(x-0.5), 2.0-4.0*x);
}

void main() {
    color = vec4(colFullSat(sample1ch()*100), 1.0);
}
