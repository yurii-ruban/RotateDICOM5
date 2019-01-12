#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    texID = 0;
    m_Image.parseImage("../Lab_2.dcm");
    this->setGeometry(0, 0, m_Image.getWidth()*2, m_Image.getHeight()*2);
    setMouseTracking(true);
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    mouseMotionCallback(event->pos().x() + width()/2, event->pos().y() + height()/2);
    update();

}

void GLWidget::initializeGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.2, 0.2, 0.2, 1.0);
    glClearColor(0, 0, 0, 1.0);
    gluOrtho2D(-width()/2, width()/2, -height()/2, height()/2);
}

void GLWidget::paintGL()
{
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, m_Image.getWidth(), m_Image.getHeight(), 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, m_Image.getBuffer());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    printCoord();
    drawAches();
}

void GLWidget::drawAches()
{
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

void GLWidget::printText(std::string str, int x, int y, float r = 0, float g = 1, float b = 0.5 )
{
    glColor3f(r, g, b);
    glRasterPos2f(x, y);

    for (int i = 0; i < str.size(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
    }
}

void GLWidget::printCoord()
{
    int SHIFT_DOWN = 18;
    printText("Pixels:" , -width() / 2 + 20, height() / 2 - SHIFT_DOWN);
    SHIFT_DOWN+=18;
    printText("x: " + std::to_string(m_Image.getPX()), -width() / 2 + 25, height() / 2 - SHIFT_DOWN);
    SHIFT_DOWN+=18;
    printText("y: " + std:: to_string(m_Image.getPY()), -width() / 2 + 25, height() / 2 - SHIFT_DOWN);
    SHIFT_DOWN+=22;

    printText("Milimeters: ", -width() / 2 + 20, height() / 2 - SHIFT_DOWN);
    SHIFT_DOWN+=18;
    printText("x: " + std::to_string(m_Image.getPoint().x), -width() / 2 + 25, height() / 2 - SHIFT_DOWN);
    SHIFT_DOWN+=18;
    printText("y: " + std::to_string(m_Image.getPoint().y), -width() / 2 + 25, height() / 2 - SHIFT_DOWN);
    SHIFT_DOWN+=18;
    printText("z: " + std::to_string(m_Image.getPoint().z), -width() / 2 + 25, height() / 2 - SHIFT_DOWN);

    if(m_Image.patientOrientation().at(0) == "L" && m_Image.patientOrientation().at(1) == "PH")
    {
        displayTexture();
        printText("L", 0, -height() / 4);
        printText("AF", width() / 4 - 4, -height() / 2);
        printText("PH", width() / 4 - 4, 0);
    }
}

DICOMobject GLWidget::Image()
{
    return m_Image;
}

void GLWidget::setImage()
{
    m_Image.parseImage("PUT FILE PATH HERE");
}

void GLWidget::mouseMotionCallback(int x, int y)
{
    m_Image.setPX(x - width());
    m_Image.setPY(height() - y);

    if (width() / 2 > m_Image.getPX() > 0 && 0 > m_Image.getPY() > - height() / 2 )
    {
        m_Image.getPoint().x = m_Image.imagePosition().at(0) + m_Image.getPixelSpacing() * m_Image.imageOrientation().at(0) * m_Image.getPX() + m_Image.getPixelSpacing() * m_Image.imageOrientation().at(3) * m_Image.getPY();
        m_Image.getPoint().y = m_Image.imagePosition().at(1) + m_Image.getPixelSpacing() * m_Image.imageOrientation().at(4) * m_Image.getPY() + m_Image.getPixelSpacing() * m_Image.imageOrientation().at(1) * m_Image.getPX();
        m_Image.getPoint().z = m_Image.imagePosition().at(2) + m_Image.imageOrientation().at(2) * m_Image.getPX() / m_Image.imagePosition().at(0) + m_Image.imageOrientation().at(5) * m_Image.getPY() / m_Image.imagePosition().at(0);
    }
}
