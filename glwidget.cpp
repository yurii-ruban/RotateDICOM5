#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    texID = 0;
    m_Image.parseImage("../Lab_2.dcm");
    this->setGeometry(0, 0, m_Image.getWidth()*2, m_Image.getHeight()*2);
}

void GLWidget::initializeGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.2, 0.2, 0.2, 1.0);
    gluOrtho2D(-width()/2, width()/2, -height()/2, height()/2);
    std::cout << "Width: " << width() << std::endl;
    std::cout << "Height: " << height() << std::endl;
}

void GLWidget::paintGL()
{
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, m_Image.getWidth(), m_Image.getHeight(), 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, m_Image.getBuffer());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    std::cout << "Image width: " << m_Image.getWidth() <<std::endl;
    std::cout << "Image height: " << m_Image.getHeight() <<std::endl;
    displayTexture();
    drawAches();
}

void GLWidget::drawAches()
{
    const int START_X = 0;
    const int START_Y = 0;

    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 1.0);
    glLineWidth(1);

    /*Draw X ache*/
    glVertex2f(-width()/2, 0);
    glVertex2f(width()/2, 0);

    /*Draw Y ache*/
    glVertex2f(0, -height()/2);
    glVertex2f(0, height()/2);

    glEnd();
}

void GLWidget::displayTexture()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texID);

    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glTexCoord2f(1, 1);
    glVertex2f(width()/2, 0);
    glTexCoord2f(1, 0);
    glVertex2f(width()/2, -height()/2);
    glTexCoord2f(0, 0);
    glVertex2f(0, -height()/2);
    glTexCoord2f(0, 1);
    glVertex2f(0, 0);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glFlush();
}

DICOMobject GLWidget::Image()
{
    return m_Image;
}

void GLWidget::setImage()
{
    m_Image.parseImage("PUT FILE PATH HERE");
}
