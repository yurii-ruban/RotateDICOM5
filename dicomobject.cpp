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

//Setting of the letters for showing image orientation
void DICOMobject::setDirection()
{
    //First cosinus vector processing
    if(image_orientation.at(0) > 0)
    {
        left+= patient_orientation.at(0); //Taking R or L
    }
    if(image_orientation.at(1) > 0)
    {
        left+= patient_orientation.at(1).at(0); //Taking 1st letter from "PH" or "AF"
    }
    if(image_orientation.at(2) > 0)
    {
        left+= patient_orientation.at(1).at(1); //Taking 2nd letter from "PH" or "AF"
    }


    //Second cosinus vector processing
    if(image_orientation.at(3) > 0)
    {
        top+= patient_orientation.at(0); //Taking R or L
    }
    if(image_orientation.at(4) > 0)
    {
        top+= patient_orientation.at(1).at(0); //Taking 1st letter from "PH" or "AF"
    }
    if(image_orientation.at(5) > 0)
    {
        top+= patient_orientation.at(1).at(1); //Taking 2nd letter from "PH" or "AF"
    }

    calculateBottom(); //Need it because of variant requirement
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

    imebra::ReadingDataHandlerNumeric* dataHandler = image->getReadingDataHandler();
    buffer = (unsigned char*)dataHandler->data(&bufferSize);

    setDirection();
}

const unsigned char* DICOMobject::getBuffer()
{
    return buffer;
}

size_t DICOMobject::getBufferSize()
{
    return bufferSize;
}

//Calculating bottom letters mirrored to top
void DICOMobject::calculateBottom()
{
    for(size_t i = 0; i < top.size(); ++i)
    {
        if(top.at(i) == 'P')
        {
            bottom.push_back('A');
        }
        else if (top.at(i) == 'H')
        {
            bottom.push_back('F');
        }


        //Reverse case
        else if (top.at(i) == 'A')
        {
            bottom.push_back('P');
        }
        else if(top.at(i) == 'F')
        {
            bottom.push_back('H');
        }
    }
}

std::string DICOMobject::getTopLetters()
{
    return top;
}

std::string DICOMobject::getLeftLetters()
{
    return left;
}

std::string DICOMobject::getBottomLetters()
{
    return bottom;
}
