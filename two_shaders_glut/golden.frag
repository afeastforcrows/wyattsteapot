# version 120
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
 
//varying vec4 myColor;

void main( ){

  const vec3 eyepos = vec3(0,0,0);
  vec4 _mypos = gl_ModelViewMatrix * myVertex;
  vec3 mypos = _mypos.xyz / _mypos.w;
  vec3 eyedirn = normalize(eyepos - mypos);
  
  // Compute normal, needed for shading. 
  vec3 normal = normalize(gl_NormalMatrix * myNormal);

  vec4 W = vec4(1,1,1,0);
  vec4 P = vec4(1,2,20,0);
  
  vec4 newColor = vec4(0,0,0,0);
  
  float myReflect = dot(normal, eyedirn);
  
  for(int x=0; x<3; x++)
  {
  
    newColor[x] = pow( W[x]*((sin(myReflect)+1)/2), P[x]);
  }
  
  gl_FragColor = newColor ;
}
