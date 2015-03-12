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
    glColor3f (1.0, 0.0, 1.0);
    glPointSize(4.0f);
    glLineWidth(20.0f);
    

    glBegin(GL_POINTS);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(0.2f, 0.2f, 0.2f);
    glVertex3f(0.2f, 0.3f, 0.3f);
    glEnd();

        glBegin(GL_TRIANGLES);//start drawing triangles
      glVertex3f(-1.0f,-0.25f,0.0f);//triangle one first vertex
      glVertex3f(-0.5f,-0.25f,0.0f);//triangle one second vertex
      glVertex3f(-0.75f,0.25f,0.0f);//triangle one third vertex
      //drawing a new triangle
      glVertex3f(0.5f,-0.25f,0.0f);//triangle two first vertex
      glVertex3f(1.0f,-0.25f,0.0f);//triangle two second vertex
      glVertex3f(0.75f,0.25f,0.0f);//triangle two third vertex
    glEnd();//end drawing of triangles

    glFlush ();
}
