#ifndef DICOMOBJECT_H
#define DICOMOBJECT_H

#include <imebra/imebra.h>
#include <vector>
#include <iostream>

class DICOMobject
{
private:
    size_t width;
    size_t height;
    size_t bufferSize;
    unsigned char* buffer;
    std::vector<double> image_position;
    std::vector<double> image_orientation;
    std::vector <std::string> patient_orientation;
    double pixelSpacing;
    int pX, pY;
    struct Point
    {
        double x;
        double y;
        double z;
    }P;

    //Variables to store letters of orientation for showing with the image
    std::string top;
    std::string left;
    std::string bottom;
    std::string right;

    //Check inclinations of the plane and store direction
    void setDirection();
    void calculateBottom();
    void calculateRight();

public:
    DICOMobject();
    size_t getWidth();
    size_t getHeight();
    double getPixelSpacing();
    int getPX();
    int getPY();
    void setPX(int x);
    void setPY(int y);
    Point& getPoint();
    std::vector<double> imagePosition();
    std::vector<double> imageOrientation();
    std::vector<std::string> patientOrientation();
    void parseImage(std::string name);
    const unsigned char* getBuffer();
    size_t getBufferSize();
    std::string getTopLetters();
    std::string getLeftLetters();
    std::string getBottomLetters();
    std::string getRightLetters();

    static const int correcter = -1; //Change direction to increasing or decreasing x coordinate
};

#endif // DICOMOBJECT_H
