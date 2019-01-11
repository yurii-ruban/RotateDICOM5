#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <dicomobject.h>
#include <GL/glut.h>
#include <iostream>

class GLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = nullptr);
    void initializeGL();
    void paintGL();
    void drawAches();
    void displayTexture();
    DICOMobject Image();
    void setImage();
    //void resizeGL(int w, int h);

private:
    DICOMobject m_Image;
    GLuint texID;
};

#endif // GLWIDGET_H
