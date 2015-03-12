/*

 Author: Daniel Palmer

*/

#include <QtGui/QtGui>
#include <QtOpenGL/QtOpenGL>
#include <math.h>
#include "globj.h"

GLobj::GLobj(QWidget *parent)
    : QGLWidget(parent)
{

}

GLobj::~GLobj()
{

}

//Initialize the GL settings
void GLobj::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

//Set up the viewport based on the screen dimentions
//Function is called implicitly by initializeGL and when screen is resized
void GLobj::resizeGL( int w, int h )
{
    //algorithm to keep scene "square" (preserve aspect ratio)
    //even if screen is streached
    if(w>h)
        glViewport((w-h)/2, 0, h, h);
    else
        glViewport(0, (h-w)/2, w, w);

    //setup the projection and switch to model view for transformations
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //implicit call to paintGL after resized
}

//Paints the GL scene
void GLobj::paintGL()
{
    glClear (GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);

    float radius = 0.5;

    //Draw a quad
    /*
    glBegin(GL_QUADS);
        glColor3f (1.0, 0.0, 0.0);
        glVertex3f(-radius, -radius,  radius);
        glVertex3f( radius, -radius,  radius);
        glVertex3f( radius,  radius,  radius);
        glVertex3f(-radius,  radius,  radius);
    glEnd(); 
    */

    glPointSize(4.0f);
    glLineWidth(20.0f);
    
    glColor3f (1.0, 0.0, 1.0);
    glBegin(GL_POINTS);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glEnd();

    glColor3f (1.0, 0.25, 1.0);
    glBegin(GL_LINES);
    glVertex3f(0.2f, 0.2f, 0.2f);
    glVertex3f(0.2f, 0.3f, 0.3f);
    glEnd();

    glColor3f (1.0, 1.0, 1.0);
    glBegin(GL_TRIANGLES);
    glVertex3f(-1.0f,-0.25f,0.0f);
    glVertex3f(-0.5f,-0.25f,0.0f);
    glVertex3f(-0.75f,0.25f,0.0f);  
    glEnd();

    glColor3f (0.25, 0.25, 1.0);
    glBegin(GL_POLYGON);
      glVertex3f(0.75f,0.75f,0.0f);
      glVertex3f(0.95f,0.95f,0.0f);
      glVertex3f(0.95f,0.95f,0.0f);
      glVertex3f(0.75f,0.95f,0.0f);
  glEnd();

    glColor3f (0.25, 1.0, 1.0);
    glBegin(GL_POLYGON);
      glVertex3f(0.8f,0.90f,0.0f);
      glVertex3f(0.9f,0.90f,0.0f);
      glVertex3f(0.95f,0.85f,0.0f);
      glVertex3f(0.9f,0.8f,0.0f);
      glVertex3f(0.8f,0.8f,0.0f);
      glVertex3f(0.75f,0.85f,0.0f);
    glEnd();

    glFlush ();
}
