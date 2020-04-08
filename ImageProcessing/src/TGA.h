//
// Created by Lukian Bogdanets on 3/27/20.
//

#pragma once
#include <vector>
using namespace std;

class TGA {
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
        char imageDescriptor;

        int pixelCount;
        struct Pixel {
            unsigned char R;
            unsigned char G;
            unsigned char B;
            Pixel(unsigned char R, unsigned G, unsigned B);
        };
        vector<Pixel> pixels;

        TGA(short width, short height, int pixelCount, vector<Pixel>& pixels);
};

TGA::TGA(short width, short height, int pixelCount, vector<Pixel>& pixels) {
    idLength = 0;
    colorMapType = 0;
    dataTypeCode = 2;
    colorMapOrigin = 0;
    colorMapLength = 0;
    colorMapDepth = 0;
    xOrigin = 0;
    yOrigin = 0;
    this->width = width;
    this->height = height;
    bitsPerPixel = 24;
    imageDescriptor = 0;
    this->pixelCount = pixelCount;
    this->pixels = pixels;
}

TGA::Pixel::Pixel(unsigned char R, unsigned G, unsigned B) {
    this->R = R;
    this->G = G;
    this->B = B;
}
