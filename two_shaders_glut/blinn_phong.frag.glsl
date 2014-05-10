# version 120
//#include <stdlib.h>
//#include <time.h>   
/*
 * Michael Shafae
 * mshafae at fullerton.edu
 * 
 * A simple Blinn-Phong shader with two light sources.
 * This file is the fragment shader which calculates
 * the halfway vector between the viewer and light source
 * vector and then calculates the color on the surface
 * given the material properties passed in from the CPU program.
 *
 * For more information see:
 *     <http://en.wikipedia.org/wiki/Blinn–Phong_shading_model>
 *
 * $Id: blinn_phong.frag.glsl 4891 2014-04-05 08:36:23Z mshafae $
 *
 * Be aware that for this course, we are limiting ourselves to
 * GLSL v.1.2. This is not at all the contemporary shading
 * programming environment, but it offers the greatest degree
 * of compatability.
 *
 * Please do not use syntax from GLSL > 1.2 for any homework
 * submission.
 *
 */

// These are passed from the vertex shader to here, the fragment shader
// In later versions of GLSL these are 'in' variables.
varying vec4 myColor;
varying vec3 myNormal;
varying vec4 myVertex;

// These are passed in from the CPU program, camera_control_*.cpp
uniform int isLightOn;
uniform vec4 light0_position;
uniform vec4 light0_color;
uniform vec4 light1_position;
uniform vec4 light1_color;
uniform vec4 ambient;
uniform vec4 diffuse;
uniform vec4 specular;
uniform float shininess;

//a function that approximates a random number (like the noise function)
float rand(vec3 co){
      return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

vec4 ComputeLight (const in vec3 direction, const in vec4 lightcolor, const in vec3 normal, const in vec3 halfvec, const in vec4 mydiffuse, const in vec4 myspecular, const in float myshininess){

  float nDotL = dot(normal, direction);
  vec4 lambert = mydiffuse * lightcolor * max (nDotL, 0.0);

  float nDotH = dot(normal, halfvec);
  vec4 phong = myspecular * lightcolor * pow (max(nDotH, 0.0), myshininess);

  vec4 retval = lambert + phong;
  return retval;
}       

void main (void){
  
  if( isLightOn == 0 ){
    gl_FragColor = myColor;
  }else{ 
    // They eye is always at (0,0,0) looking down -z axis 
    // Also compute current fragment position and direction to eye 

    const vec3 eyepos = vec3(0,0,0);
    vec4 _mypos = gl_ModelViewMatrix * myVertex;
    vec3 mypos = _mypos.xyz / _mypos.w;
    vec3 eyedirn = normalize(eyepos - mypos);

    // Compute normal, needed for shading. 
    vec3 normal = normalize(gl_NormalMatrix * myNormal);

    // Light 0, point
    vec3 position0 = light0_position.xyz / light0_position.w;
    vec3 direction0 = normalize (position0 - mypos);
    vec3 half0 = normalize (direction0 + eyedirn); 
    vec4 color0 = ComputeLight(direction0, light0_color, normal, half0, diffuse, specular, shininess) ;

    // Light 1, point 
    vec3 position1 = light1_position.xyz / light1_position.w;
    vec3 direction1 = normalize(position1 - mypos);
    vec3 half1 = normalize(direction1 + eyedirn); 
    vec4 color1 = ComputeLight(direction1, light1_color, normal, half1, diffuse, specular, shininess) ;
   
    
    //divide the teapot into vertical stripes, and shade them in 2 different colors of brown
    
    if(myNormal[0]>0.9)
    {
      color0 = vec4(0.21, 0.16, 0.10, 0.0);
    }
    else if (myNormal[0]>0.7)
    {
      color0 = vec4(0.0, 0.00, 0.0, 0.0);
    }
    else if (myNormal[0]>0.5)
    {
      color0 = vec4(0.21, 0.16, 0.10, 0.0);
    }
    else if (myNormal[0]>0.3)
    {
      color0 = vec4(0.0, 0.00, 0.0, 0.0);
    }
    else if (myNormal[0]>0.1)
    {
      color0 = vec4(0.21, 0.16, 0.10, 0.0);
    }
    else if(myNormal[0]<-0.9)
    {
      color0 = vec4(0.21, 0.16, 0.10, 0.0);
    }
    else if (myNormal[0]<-0.7)
    {
      color0 = vec4(0.0, 0.00, 0.0, 0.0);
    }
    else if (myNormal[0]<-0.5)
    {
      color0 = vec4(0.21, 0.16, 0.10, 0.0);
    }
    else if (myNormal[0]<-0.3)
    {
      color0 = vec4(0.0, 0.00, 0.0, 0.0);
    }
    else if (myNormal[0]<-0.1)
    {
      color0 = vec4(0.21, 0.16, 0.10, 0.0);
    }
    else 
    {
      color0 = vec4(0.0, 0.00, 0.0, 0.0);
    }
    
    //to make the top of the teapot a solid color we first find the top
    float top = dot(eyedirn[2], myNormal[2]);
    //then we shade the top dark brown
    if (top > 0.9 && myNormal[2]>0.9)      color0 = vec4(0.0, 0.00, 0.0, 0.0);
    else if (top > 0.9) color0 = vec4(0.0, 0.0, 0.0, 0.0);
    else if (top > 0.6 && myNormal[2]>0.9) color0 = vec4(0.0, 0.00, 0.0, 0.0);

    //come up with a random number, seed with myNormal
    float myRandom = rand(myNormal);
    
    float red = 0.2;//*myRandom;
    //only take random numbers above 0.7 to reduce the total amount and intensity of noise
    if(myRandom>=0.7)
    {
      red *= myRandom;
    }
    //add the noise to the color of the pixel
    vec4 randomColor = vec4(red, 0.0, 0.02, 0.0);
    
    gl_FragColor = color0 + randomColor;
  }
}
