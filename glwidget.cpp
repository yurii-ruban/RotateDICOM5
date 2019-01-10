#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent)
{

}

void GLWidget::initializeGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.2, 0.2, 0.2, 1.0);
    gluOrtho2D(0, width(), 0, height());
}

void GLWidget::paintGL()
{
    drawAches();
}

void GLWidget::drawAches()
{
    const int START_X = 0;
    const int START_Y = 0;

    glLineWidth(1);
    glColor3f(1.0, 0.0, 1.0);
    glBegin(GL_LINES);

    /*Draw X ache and arrows*/
    glVertex2f(START_X, height()/2);
    glVertex2f(width(), height()/2);

    /*Draw Y ache and arrows*/
    glVertex2f(width()/2, START_Y);
    glVertex2f(width()/2, height());

    glEnd();
}

DICOMobject GLWidget::Image()
{
    return m_Image;
}

void GLWidget::setImage()
{
    m_Image.parseImage("PUT FILE PATH HERE");
}
