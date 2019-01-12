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

double DICOMobject::getPixelSpacing()
{
    return pixelSpacing;
}

int DICOMobject::getPX()
{
    return pX;
}


int DICOMobject::getPY()
{
    return pY;
}

void DICOMobject::setPX(int x)
{
    pX = x;
}

void DICOMobject::setPY(int y)
{
    pY = y;
}

DICOMobject::Point &DICOMobject::getPoint()
{
    return P;
}

std::string DICOMobject::getPatientPos()
{
    return patient_position;
}

std::vector<double> DICOMobject::imagePosition()
{
    return image_orientation;
}

std::vector<double> DICOMobject::imageOrientation()
{
    return image_orientation;
}

std::vector<std::string> DICOMobject::patientOrientation()
{
    return patient_orientation;
}

void DICOMobject::parseImage(std::string name)
{
    imebra::DataSet* loadedDataSet(imebra::CodecFactory::load(name));
    imebra::Image* image(loadedDataSet->getImageApplyModalityTransform(0));

    width = image->getWidth();
    height = image->getHeight();
    if(loadedDataSet->bufferExists(imebra::TagId(0x0028, 0x0030), 0))
    {
        pixelSpacing = loadedDataSet->getDouble(imebra::TagId(0x0028, 0x0030), 0);
    }
    else
    {
        pixelSpacing = 0.4;
    }

    for (size_t i = 0; i <= 5; i++)
    {
        image_orientation.push_back(loadedDataSet->getDouble(imebra::TagId(0x0020, 0x0037), i));
    }

    for (size_t i = 0; i < 2; i++)
    {
        image_position.push_back(loadedDataSet->getDouble(imebra::TagId(0x0020, 0x0032), i));
        patient_orientation.push_back(loadedDataSet->getString(imebra::TagId(0x0020, 0x0020), i));
    }

    std::cout << pixelSpacing << std::endl;

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
