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
    const unsigned char* getBuffer();
    size_t getBufferSize();

private:
    size_t width;
    size_t height;
    size_t bufferSize;
    unsigned char* buffer;
};

#endif // DICOMOBJECT_H
