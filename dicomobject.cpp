#include "dicomobject.h"

DICOMobject::DICOMobject()
{

}

size_t DICOMobject::getWidth()
{
    return width;
}

size_t DICOMobject::getHeight()
{
    return height;
}

void DICOMobject::parseImage(std::string name)
{
    imebra::DataSet* loadedDataSet(imebra::CodecFactory::load(name));
    imebra::Image* image(loadedDataSet->getImageApplyModalityTransform(0));

    width = image->getWidth();
    height = image->getHeight();

    imebra::ReadingDataHandlerNumeric* dataHandler = image->getReadingDataHandler();
    buffer = (unsigned char*)dataHandler->data(&bufferSize);
}

const unsigned char* DICOMobject::getBuffer()
{
    return buffer;
}

size_t DICOMobject::getBufferSize()
{
    return bufferSize;
}
