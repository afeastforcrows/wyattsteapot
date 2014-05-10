// 
// Michael Shafae
// mshafae at fullerton.edu
// 
// Procedural module that implements transformations used in
// the homework assignment.
//
// $Id: transformations.cpp 4964 2014-04-25 04:43:20Z mshafae $
//
// STUDENTS _MUST_ ADD THEIR CODE INTO THIS FILE
//

#include "transformations.h"

// Just in case you have a weird cmath header file...
#ifndef M_PI
#define M_PI                3.14159265358979323846264338327950288
#endif
#ifndef PI_OVER_ONE_EIGHTY
#define PI_OVER_ONE_EIGHTY  0.01745329251994329547437168059786927188
#endif
#ifndef ONE_EIGHTY_OVER_PI
#define ONE_EIGHTY_OVER_PI  57.29577951308232286464772187173366546631
#endif

// Don't forget:
// OpenGL's unit for angles is degrees.
// C math library's unit for angles is radians.
#ifndef DEG2RAD
#define DEG2RAD( theta ) ((theta) * (PI_OVER_ONE_EIGHTY))
#endif
#ifndef RAD2DEG
#define RAD2DEG( theta ) ((theta) * (ONE_EIGHTY_OVER_PI))
#endif
// Quick-n-dirty absolute value macro
#ifndef ABS
#define ABS( x ) ((x) < (0) ? (-x) : (x))
#endif
// Don't use pow( ) to square a value.
#ifndef SQR
#define SQR( x ) ((x) * (x))
#endif


#ifndef __SOLUTION__

void rotateCameraLeft(float degrees, float *eyePosition, float *centerPosition, float *upVector){
  
  
  float myRads = (degrees/180)*M_PI;

  float row1[3] = {cos(myRads), 0.0f, sin(myRads)};
  float row2[3] = {0.0f, 1.0f, 0.0f};
  float row3[3] = {-sin(myRads), 0.0f, cos(myRads)};

  float tempEye[4] = {0.0};
  float myTemp[4] = {0.0};

  float tempUp[4] = {0.0};
  float newTemp[4] = {0.0};

  for(int x=0; x<3; x++)
    {
      tempEye[x] = eyePosition[x]-centerPosition[x];
      tempUp[x] = upVector[x];
    }

  for(int x=0; x<3; x++)
    {
      myTemp[x]=tempEye[x]*row1[x];
      newTemp[x]=tempUp[x]*row1[x];
    }

  eyePosition[0] = myTemp[0]+myTemp[1]+myTemp[2];
  upVector[0] = newTemp[0]+newTemp[1]+newTemp[2];

  for(int x=0; x<3; x++)
    {
      myTemp[x]=tempEye[x]*row2[x];
      newTemp[x]=tempUp[x]*row2[x];
    }

  eyePosition[1] = myTemp[0]+myTemp[1]+myTemp[2];
  upVector[1] = newTemp[0]+newTemp[1]+newTemp[2];

  for(int x=0; x<3; x++)
    {
      myTemp[x]=tempEye[x]*row3[x];
      newTemp[x]=tempUp[x]*row3[x];
    }
  
  eyePosition[2] = myTemp[0]+myTemp[1]+myTemp[2];
  upVector[2] = newTemp[0]+newTemp[1]+newTemp[2];

}

void rotateCameraUp(float degrees, float *eyePosition, float *centerPosition, float *upVector){
  
  float myRads = (degrees/180)*M_PI;

  float row1[3] = {1.0f, 0.0f, 0.0f};
  float row2[3] = {0.0f, cos(myRads), -sin(myRads)};
  float row3[3] = {0, sin(myRads), cos(myRads)};

  float tempEye[4] = {0.0};
  float myTemp[4] = {0.0};

  float tempUp[4] = {0.0};
  float newTemp[4] = {0.0};
  
  for(int x=0; x<3; x++)
    {
      tempEye[x] = eyePosition[x]-centerPosition[x];
      tempUp[x] = upVector[x];
    }

  for(int x=0; x<3; x++)
    {
      myTemp[x]=tempEye[x]*row1[x];
      newTemp[x]=tempUp[x]*row1[x];
    }

  eyePosition[0] = myTemp[0]+myTemp[1]+myTemp[2];
  upVector[0] = newTemp[0]+newTemp[1]+newTemp[2];

  for(int x=0; x<3; x++)
    {
      myTemp[x]=tempEye[x]*row2[x];
      newTemp[x]=tempUp[x]*row2[x];
    }

  eyePosition[1] = myTemp[0]+myTemp[1]+myTemp[2];
  upVector[1] = newTemp[0]+newTemp[1]+newTemp[2];

  for(int x=0; x<3; x++)
    {
      myTemp[x]=tempEye[x]*row3[x];
      newTemp[x]=tempUp[x]*row3[x];
    }
  
  eyePosition[2] = myTemp[0]+myTemp[1]+myTemp[2];
  upVector[2] = newTemp[0]+newTemp[1]+newTemp[2];
}
#else
#include "transformations_solution.cpp"
#endif


void myTranslatef( GLfloat *matrix, GLfloat x, GLfloat y, GLfloat z ){
 
  matrix[0] = 1.0f;  matrix[4] = 0.0f;  matrix[8] = 0.0f;   matrix[12] = x;
  matrix[1] = 0.0f;  matrix[5] = 1.0f;  matrix[9] = 0.0f;   matrix[13] = y;
  matrix[2] = 0.0f;  matrix[6] = 0.0f;  matrix[10] = 1.0f;  matrix[14] = z;
  matrix[3] = 0.0f;  matrix[7] = 0.0f;  matrix[11] = 0.0f;  matrix[15] = 1.0f;
}

void myScalef( GLfloat *matrix, GLfloat x, GLfloat y, GLfloat z ){
  // Please implement this function.

  // This code is just a placeholder to demonstrate how this procedure
  // returns the LookAt matrix by reference.
  // YOU MUST REMOVE THE CODE BELOW AND WRITE YOUR OWN ROUTINE.
  int mode;
  glGetIntegerv(GL_MATRIX_MODE, &mode);
  glPushMatrix( );
  glLoadIdentity( );
  glScalef(x, y, z);
  glGetFloatv(mode == GL_MODELVIEW ?
              GL_MODELVIEW_MATRIX : GL_PROJECTION_MATRIX,
              matrix);
  glPopMatrix( );
}

void myRotatef( GLfloat *matrix,
                GLfloat angle, GLfloat x, GLfloat y, GLfloat z ){
  // Remember the Rodrigues' rotation formula?

  // This code is just a placeholder to demonstrate how this procedure
  // returns the LookAt matrix by reference.
  // YOU MUST REMOVE THE CODE BELOW AND WRITE YOUR OWN ROUTINE.
  int mode;
  glGetIntegerv(GL_MATRIX_MODE, &mode);
  glPushMatrix( );
  glLoadIdentity( );
  glRotatef(angle, x, y, z);
  glGetFloatv(mode == GL_MODELVIEW ?
              GL_MODELVIEW_MATRIX : GL_PROJECTION_MATRIX,
              matrix);
  glPopMatrix( );
}

void myLookAt( GLfloat *matrix,
               GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ,
               GLdouble centerX, GLdouble centerY, GLdouble centerZ,
               GLdouble upX, GLdouble upY, GLdouble upZ ){
  // Please implement this function.

  // This code is just a placeholder to demonstrate how this procedure
  // returns the LookAt matrix by reference.
  // YOU MUST REMOVE THE CODE BELOW AND WRITE YOUR OWN ROUTINE.
  int mode;
  glGetIntegerv(GL_MATRIX_MODE, &mode);
  glPushMatrix( );
  glLoadIdentity( );
  gluLookAt(
    eyeX, eyeY, eyeZ,
    centerX, centerY, centerZ,
    upX, upY, upZ
  );
  glGetFloatv(mode == GL_MODELVIEW ?
              GL_MODELVIEW_MATRIX : GL_PROJECTION_MATRIX,
              matrix);
  glPopMatrix( );
}

void myFrustum( GLfloat *matrix,
                GLdouble left, GLdouble right, GLdouble bottom,
                GLdouble top, GLdouble zNear, GLdouble zFar ){
  // Please implement this function.

  // This code is just a placeholder to demonstrate how this procedure
  // returns the LookAt matrix by reference.
  // YOU MUST REMOVE THE CODE BELOW AND WRITE YOUR OWN ROUTINE.
  int mode;
  glGetIntegerv(GL_MATRIX_MODE, &mode);
  glPushMatrix( );
  glLoadIdentity( );
  glFrustum(left, right, bottom, top, zNear, zFar);
  glGetFloatv(mode == GL_MODELVIEW ?
              GL_MODELVIEW_MATRIX : GL_PROJECTION_MATRIX,
              matrix);
  glPopMatrix( );
}

void myPerspective( GLfloat *matrix,
                    GLdouble fovy, GLdouble aspect,
                    GLdouble zNear, GLdouble zFar ){
  // Please implement this function.

  // This code is just a placeholder to demonstrate how this procedure
  // returns the LookAt matrix by reference.
  // YOU MUST REMOVE THE CODE BELOW AND WRITE YOUR OWN ROUTINE.
  int mode;
  glGetIntegerv(GL_MATRIX_MODE, &mode);
  glMatrixMode( GL_MODELVIEW );
  glPushMatrix( );
  glLoadIdentity( );
  gluPerspective(fovy, aspect, zNear, zFar);
  glGetFloatv(mode == GL_MODELVIEW ?
              GL_MODELVIEW_MATRIX : GL_PROJECTION_MATRIX,
              matrix);
  glPopMatrix( );
  glMatrixMode( mode );
}

void myOrtho( GLfloat *matrix,
              GLdouble left, GLdouble right, GLdouble bottom,
              GLdouble top, GLdouble zNear, GLdouble zFar ){
  // Please implement this function.

  // This code is just a placeholder to demonstrate how this procedure
  // returns the LookAt matrix by reference.
  // YOU MUST REMOVE THE CODE BELOW AND WRITE YOUR OWN ROUTINE.
  int mode;
  glGetIntegerv(GL_MATRIX_MODE, &mode);
  glPushMatrix( );
  glLoadIdentity( );
  glOrtho(left, right, bottom, top, zNear, zFar);
  glGetFloatv(mode == GL_MODELVIEW ?
              GL_MODELVIEW_MATRIX : GL_PROJECTION_MATRIX,
              matrix);
  glPopMatrix( );
}
