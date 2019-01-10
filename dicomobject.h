#ifndef DICOMOBJECT_H
#define DICOMOBJECT_H

#include <imebra/imebra.h>

class DICOMobject
{
public:
    DICOMobject();
    size_t getWidth();
    size_t getHeight();
    void parseImage(std::string name);

private:
    size_t width;
    size_t height;
};

#endif // DICOMOBJECT_H
