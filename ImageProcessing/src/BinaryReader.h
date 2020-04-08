//
// Created by Lukian Bogdanets on 3/27/20.
//

#include <string>
#include <utility>
#include <fstream>
#include <iostream>
#pragma once
using namespace std;

class BinaryReader {
public:
    ifstream file;
    
    BinaryReader(const string& path);
    int readChar();
    short readShort();
};

BinaryReader::BinaryReader(const string& path) {
    file.open(path, ios_base::in | ios_base::binary);
    if(!file.is_open()) {
        cout << "Error, could not open " << path << endl;
        throw exception();
    }
}

int BinaryReader::readChar() {
    char temp;
    file.read((char*)&temp, sizeof(temp));
    return temp;
}

short BinaryReader::readShort() {
    short temp;
    file.read((char*)&temp, sizeof(temp));
    return temp;
}




