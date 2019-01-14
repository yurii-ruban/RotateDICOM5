#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <dicomobject.h>
#include <GL/glut.h>
#include <QMouseEvent>

class GLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = nullptr);
    void initializeGL();
    void paintGL();
    void mouseMotionCallback(int x, int y);
    void printCoord();
    void printText(std::string str, int x, int y, float r, float g, float b);
    void drawAches();
    void displayTexture();
    void mouseMoveEvent(QMouseEvent* event);
    DICOMobject Image();
    void setImage();
    int shiftDown(int increaser = 0);
    int shiftRight(int increaser = 0);

private:
    DICOMobject m_Image;
    GLuint texID;
    int SHIFT_DOWN;
    int SHIFT_RIGHT;
};

#endif // GLWIDGET_H
