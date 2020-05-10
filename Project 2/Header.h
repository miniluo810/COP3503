//
// Created by Mini Luo on 11/4/19.
//
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#pragma once
using namespace std;

struct Header {
 struct Pixel{
        unsigned char redValue;
        unsigned char blueValue;
        unsigned char greenValue;
        float red;
        float green;
        float blue;
    };

public:
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescription;
    //Pixel pixel;
    vector<Pixel> pixelVec;
    void LoadFile(string filename,Header &imageHeader){
        ifstream file(filename, ios_base::binary);
        if (file.is_open()) {
            file.read(&imageHeader.idLength, sizeof(imageHeader.idLength));
            file.read(&imageHeader.colorMapType, sizeof(imageHeader.colorMapType));
            file.read(&imageHeader.dataTypeCode, sizeof(imageHeader.dataTypeCode));
            file.read((char *) &imageHeader.colorMapOrigin, sizeof(imageHeader.colorMapOrigin));
            file.read((char *) &imageHeader.colorMapLength, sizeof(imageHeader.colorMapLength));
            file.read(&imageHeader.colorMapDepth, sizeof(imageHeader.colorMapDepth));
            file.read((char *) &imageHeader.xOrigin, sizeof(imageHeader.xOrigin));
            file.read((char *) &imageHeader.yOrigin, sizeof(imageHeader.yOrigin));
            file.read((char *) &imageHeader.width, sizeof(imageHeader.width));
            file.read((char *) &imageHeader.height, sizeof(imageHeader.height));
            file.read(&imageHeader.bitsPerPixel, sizeof(imageHeader.bitsPerPixel));
            file.read(&imageHeader.imageDescription, sizeof(imageHeader.imageDescription));
        }
        for (unsigned int i = 0; i < imageHeader.width * imageHeader.height; i++) {
            Pixel pixel;
            //vector<Pixel> pixelVec;
            file.read((char *) &pixel.blueValue, sizeof(pixel.blueValue));
            file.read((char *) &pixel.greenValue, sizeof(pixel.greenValue));
            file.read((char *) &pixel.redValue, sizeof(pixel.redValue));
            pixel.blue = (float) pixel.blueValue;
            pixel.green = (float) pixel.greenValue;
            pixel.red = (float) pixel.redValue;
            pixelVec.push_back(pixel);

        }
        file.close();
    }

    void WriteFile(Header &header, vector<Pixel> &pixels, string writeName){
        string addout="output/";
        ofstream file(addout+writeName, ios_base::out | ios_base::binary);
        if (file.is_open()) {
            file.write(&header.idLength, sizeof(header.idLength));
            file.write(&header.colorMapType, sizeof(header.colorMapType));
            file.write(&header.dataTypeCode, sizeof(header.dataTypeCode));
            file.write((char *) &header.colorMapOrigin, sizeof(header.colorMapOrigin));
            file.write((char *) &header.colorMapLength, sizeof(header.colorMapLength));
            file.write(&header.colorMapDepth, sizeof(header.colorMapDepth));
            file.write((char *) &header.xOrigin, sizeof(header.xOrigin));
            file.write((char *) &header.yOrigin, sizeof(header.yOrigin));
            file.write((char *) &header.width, sizeof(header.width));
            file.write((char *) &header.height, sizeof(header.height));
            file.write(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
            file.write(&header.imageDescription, sizeof(header.imageDescription));
        }
        for (unsigned int i = 0; i < header.width * header.height; i++) {
            file.write((char *) &pixels[i].blueValue, sizeof(pixels[i].blueValue));
            file.write((char *) &pixels[i].greenValue, sizeof(pixels[i].greenValue));
            file.write((char *) &pixels[i].redValue, sizeof(pixels[i].redValue));
        }
        file.close();
    }
    vector<Pixel> Multiply(Header &image1,Header &image2){
        vector<Header::Pixel> newVec;
        for (unsigned int i = 0; i < image1.width * image1.height; i++) {
            Header::Pixel newPixel;
            newPixel.blue = roundf(((image1.pixelVec[i].blue / 255) * (image2.pixelVec[i].blue / 255)) * 255 );//+ .5f;
            newPixel.green = roundf(((image1.pixelVec[i].green / 255) * (image2.pixelVec[i].green / 255)) * 255) ;//+ .5f;
            newPixel.red = roundf(((image1.pixelVec[i].red / 255) * (image2.pixelVec[i].red / 255)) * 255) ;//+ .5f;
            newPixel.blueValue = (unsigned char) newPixel.blue;
            newPixel.greenValue = (unsigned char) newPixel.green;
            newPixel.redValue = (unsigned char) newPixel.red;
            newVec.push_back(newPixel);
        }
        return newVec;
    }
    vector<Pixel> Subtract(Header &image1, Header &image2){
        vector<Header::Pixel> newVec2;
        for (unsigned int i = 0; i < image1.width * image1.height; i++) {
            Header::Pixel newPixel2;
            newPixel2.blue = image2.pixelVec[i].blue - image1.pixelVec[i].blue;
            if(newPixel2.blue<0){
                newPixel2.blue=0;
            }
            newPixel2.green = image2.pixelVec[i].green - image1.pixelVec[i].green;
            if(newPixel2.green<0){
                newPixel2.green=0;
            }
            newPixel2.red = image2.pixelVec[i].red - image1.pixelVec[i].red;
            if(newPixel2.red<0){
                newPixel2.red=0;
            }
            newPixel2.blueValue = (unsigned char) newPixel2.blue;
            newPixel2.greenValue = (unsigned char) newPixel2.green;
            newPixel2.redValue = (unsigned char) newPixel2.red;
            newVec2.push_back(newPixel2);

        }
        return newVec2;

    }
    vector<Pixel> Screen(Header &image1,Header &image2){
        vector<Header::Pixel> newVec3;
        for (unsigned int i = 0; i < image1.width * image1.height; i++) {
            Header::Pixel newPixel3;
            newPixel3.blue =roundf((1 - (1 - (image1.pixelVec[i].blue / 255))* (1 - (image2.pixelVec[i].blue / 255))) * 255) ;
            newPixel3.green =roundf((1 - (1 - (image1.pixelVec[i].green / 255)) * (1 - (image2.pixelVec[i].green / 255))) * 255) ;
            newPixel3.red = roundf((1 - (1 - (image1.pixelVec[i].red / 255)) * (1 - (image2.pixelVec[i].red / 255))) * 255);
            newPixel3.blueValue = (unsigned char) newPixel3.blue;
            newPixel3.greenValue = (unsigned char) newPixel3.green;
            newPixel3.redValue = (unsigned char) newPixel3.red;
            newVec3.push_back(newPixel3);
        }
        return newVec3;
    }
    vector<Pixel> Overlay(Header &image1,Header &image2){
        vector<Header::Pixel> newVec4;
        for (unsigned int i = 0; i < image1.width * image1.height; i++) {
            Header::Pixel newPixel4;
            if(image2.pixelVec[i].blue<127.5){
                newPixel4.blue=roundf(2*(image1.pixelVec[i].blue/255)*(image2.pixelVec[i].blue/255)*255);
                if (newPixel4.blue > 255) {
                    newPixel4.blue = 255;
                }
            }else {
                newPixel4.blue = roundf((1 - 2 * (1 - (image1.pixelVec[i].blue / 255)) * (1 - (image2.pixelVec[i].blue / 255))) * 255);
                if (newPixel4.blue < 0) {
                    newPixel4.blue = 0;
                }
            }
            if(image2.pixelVec[i].green<127.5){
                newPixel4.green=roundf(2*(image1.pixelVec[i].green/255)*(image2.pixelVec[i].green/255)*255);
                if (newPixel4.green > 255) {
                    newPixel4.green = 255;
                }
            }else {
                newPixel4.green = roundf((1 - 2 * (1 - (image1.pixelVec[i].green / 255)) * (1 - (image2.pixelVec[i].green / 255))) * 255);
                if (newPixel4.green < 0) {
                    newPixel4.green = 0;
                }
            }if(image2.pixelVec[i].red<127.5){
                newPixel4.red=roundf(2*(image1.pixelVec[i].red/255)*(image2.pixelVec[i].red/255)*255);
                if (newPixel4.red > 255) {
                    newPixel4.red= 255;
                }
            }else {
                newPixel4.red = roundf((1 - 2 * (1 - (image1.pixelVec[i].red / 255)) * (1 - (image2.pixelVec[i].red / 255))) * 255);
                if (newPixel4.red < 0) {
                    newPixel4.red = 0;
                }
            }
            newPixel4.blueValue = (unsigned char) newPixel4.blue;
            newPixel4.greenValue = (unsigned char) newPixel4.green;
            newPixel4.redValue = (unsigned char) newPixel4.red;
            newVec4.push_back(newPixel4);
        }
        return newVec4;
    }
    vector<Pixel> AddGreenChannel(Header &image1){
        vector<Header::Pixel> newVec5;
        for (unsigned int i = 0; i < image1.width * image1.height; i++) {
            Header::Pixel newPixel5;
            newPixel5.green = 200 + image1.pixelVec[i].green;
            if (newPixel5.green > 255) {
                newPixel5.green = 255;
            }
            newPixel5.blue = image1.pixelVec[i].blue;
            newPixel5.red = image1.pixelVec[i].red;
            newPixel5.blueValue = (unsigned char) newPixel5.blue;
            newPixel5.greenValue = (unsigned char) newPixel5.green;
            newPixel5.redValue = (unsigned char) newPixel5.red;
            newVec5.push_back(newPixel5);
        }
        return newVec5;
    }
    vector<Pixel> Scale(Header &image1){
        vector<Header::Pixel> newVec6;
        for (unsigned int i = 0; i < image1.width * image1.height; i++) {
            Header::Pixel newPixel6;
            newPixel6.red = 4 * image1.pixelVec[i].red;
            if (newPixel6.red > 255) {
                newPixel6.red = 255;
            }
            newPixel6.blue = 0;
            newPixel6.green = image1.pixelVec[i].green;
            newPixel6.blueValue = (unsigned char) newPixel6.blue;
            newPixel6.greenValue = (unsigned char) newPixel6.green;
            newPixel6.redValue = (unsigned char) newPixel6.red;
            newVec6.push_back(newPixel6);
        }
        return newVec6;

    }
    vector<Pixel>WriteChannel(Header&image1, string channel){
        vector<Header::Pixel> newVec7;
        for (unsigned int i = 0; i < image1.width * image1.height; i++) {
            Header::Pixel newPixel7;
            if (channel == "red") {
                newPixel7.red = image1.pixelVec[i].red;
                newPixel7.blue = image1.pixelVec[i].red;
                newPixel7.green = image1.pixelVec[i].red;
            } else if (channel == "blue") {
                newPixel7.red = image1.pixelVec[i].blue;
                newPixel7.blue = image1.pixelVec[i].blue;
                newPixel7.green = image1.pixelVec[i].blue;
            } else if (channel == "green") {
                newPixel7.red = image1.pixelVec[i].green;
                newPixel7.blue = image1.pixelVec[i].green;
                newPixel7.green = image1.pixelVec[i].green;
            }
            newPixel7.blueValue = (unsigned char) newPixel7.blue;
            newPixel7.greenValue = (unsigned char) newPixel7.green;
            newPixel7.redValue = (unsigned char) newPixel7.red;
            newVec7.push_back(newPixel7);
        }

        return newVec7;

    }
    vector<Pixel>CombineChannels(Header&image1, Header&image2,Header&image3){
        vector<Header::Pixel> newVec8;
        for (unsigned int i = 0; i < image1.width * image1.height; i++){
            Header::Pixel newPixel8;
            newPixel8.red = image1.pixelVec[i].red;
            newPixel8.green= image2.pixelVec[i].green;
            newPixel8.blue = image3.pixelVec[i].blue;
            newPixel8.blueValue = (unsigned char) newPixel8.blue;
            newPixel8.greenValue = (unsigned char) newPixel8.green;
            newPixel8.redValue = (unsigned char) newPixel8.red;
            newVec8.push_back(newPixel8);
        }
        return newVec8;

    }
    vector<Pixel> Rotate(Header &image1){
        vector<Header::Pixel> newVec9;
        int size=image1.width * image1.height;
        for (int i = size-1; i >=0; i--) {
            Header::Pixel newPixel9;
            newPixel9.red = image1.pixelVec[i].red;
            newPixel9.green= image1.pixelVec[i].green;
            newPixel9.blue = image1.pixelVec[i].blue;
            newPixel9.blueValue = (unsigned char) newPixel9.blue;
            newPixel9.greenValue = (unsigned char) newPixel9.green;
            newPixel9.redValue = (unsigned char) newPixel9.red;
            newVec9.push_back(newPixel9);
        }
        return newVec9;

    }
};




