#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <dicomobject.h>
#include <GL/glut.h>

class GLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = nullptr);
    void initializeGL();
    void paintGL();
    void drawAches();
    DICOMobject Image();
    void setImage();
    //void resizeGL(int w, int h);
private:
    DICOMobject m_Image;
};

#endif // GLWIDGET_H
