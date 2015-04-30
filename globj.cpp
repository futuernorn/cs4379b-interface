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
  data = NULL;
  methodType = -1;
}

GLobj::~GLobj()
{
  if (data != NULL)
    delete [] data;
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
    glFlush ();

    if (methodType == 0)
      methodA();





}

void GLobj::methodA() {
  glClear (GL_COLOR_BUFFER_BIT);
  glClear(GL_DEPTH_BUFFER_BIT);
  glPointSize(4.0f);
  glLineWidth(2.0f);
    float currentX = -1;
    float totalX = 0;
    for (int i = 0; i < numValues; i++) {
      float proportionalSize = (float) *(data + i) / (float) maxValue;
      totalX += proportionalSize;
      qDebug() << "Loop1-- Index:" << i << " data[i]:" << *(data + i) << " proportionalSize:" << proportionalSize;
      currentX += proportionalSize;


    }
    currentX = -1.0;
    float scaleFactor = 2.0/totalX;
    qDebug() << "Checking:: TotalX:" << totalX << " 2/totalX" << scaleFactor;
    for (int i = 0; i < numValues; i++) {
      float proportionalSize = ((float) *(data + i) / (float) maxValue) * (float) scaleFactor;
      qDebug() << "Loop2-- Index:" << i << " data[i]:" << *(data + i) << " proportionalSize:" << proportionalSize;
      glBegin(GL_TRIANGLES);
      glVertex3f(currentX,-1.0f,1.0f);

      glVertex3f(((currentX+(proportionalSize/2))),(-1 + proportionalSize),1.0f);
      glVertex3f((currentX + proportionalSize),-1.0f,1.0f);
      glEnd();
      currentX += proportionalSize;
      glFlush ();
  }

}
