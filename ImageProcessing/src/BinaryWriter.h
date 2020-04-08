#include <string>
#include <utility>
#include <fstream>
#include <iostream>
#pragma once
using namespace std;

class BinaryWriter {
public:
    ofstream file;

    BinaryWriter(const string& path);
    void writeTGA(TGA& tga);
};

BinaryWriter::BinaryWriter(const string& path) {
    string fullPath = "output/" + path + ".tga";
    file.open(fullPath, ios_base::out | ios_base::binary);
    if(!file.is_open()) {
        cout << "Error, could not open " << fullPath << endl;
        throw exception();
    }
}

void BinaryWriter::writeTGA(TGA& tga) {
    file.write(&(tga.idLength), sizeof(tga.idLength));
    file.write(&(tga.colorMapType), sizeof(tga.colorMapType));
    file.write(&(tga.dataTypeCode), sizeof(tga.dataTypeCode));
    file.write((char*)(&(tga.colorMapOrigin)), sizeof(tga.colorMapOrigin));
    file.write((char*)(&(tga.colorMapLength)), sizeof(tga.colorMapLength));
    file.write(&(tga.colorMapDepth), sizeof(tga.colorMapDepth));
    file.write((char*)(&(tga.xOrigin)), sizeof(tga.xOrigin));
    file.write((char*)(&(tga.yOrigin)), sizeof(tga.yOrigin));
    file.write((char*)(&(tga.width)), sizeof(tga.width));
    file.write((char*)(&(tga.height)), sizeof(tga.height));
    file.write(&(tga.bitsPerPixel), sizeof(tga.bitsPerPixel));
    file.write(&(tga.imageDescriptor), sizeof(tga.imageDescriptor));

    for(int i = 0; i < tga.pixelCount; i++) {
        file.write((char*)(&(tga.pixels[i].B)), sizeof(tga.pixels[i].B));
        file.write((char*)(&(tga.pixels[i].G)), sizeof(tga.pixels[i].G));
        file.write((char*)(&(tga.pixels[i].R)), sizeof(tga.pixels[i].R));
    }
}
