#include "TGA.h"
#include "BinaryReader.h"
#include "BinaryWriter.h"

TGA loadFile(const string& path) {
    BinaryReader f(path);

    short width;
    short height;

    f.file.seekg(12);
    width = f.readShort();
    height = f.readShort();
    f.file.seekg(2, ios_base::cur);

    int pixelCount = width * height;
    unsigned char R;
    unsigned char G;
    unsigned char B;
    vector<TGA::Pixel> pixels;

    for(int i = 0; i < pixelCount; i++) {
    B = f.readChar();
    G = f.readChar();
    R = f.readChar();
    TGA::Pixel pixel(R, G, B);
    pixels.push_back(pixel);
    }

    return TGA(width, height, pixelCount, pixels);
}

void saveFile(TGA& C, const string& path) {
    BinaryWriter f(path);
    f.writeTGA(C);
}

bool compareFiles(const string& examplePath, const string& testPath) {
    TGA example = loadFile(examplePath);
    TGA test = loadFile(testPath);

    if((example.idLength != test.idLength)
    || (example.colorMapType != test.colorMapType)
    || (example.dataTypeCode != test.dataTypeCode)
    || (example.colorMapOrigin != test.colorMapOrigin)
    || (example.colorMapLength != test.colorMapLength)
    || (example.colorMapDepth != test.colorMapDepth)
    || (example.xOrigin != test.xOrigin)
    || (example.yOrigin != test.yOrigin)
    || (example.width != test.width)
    || (example.height != test.height)
    || (example.bitsPerPixel != test.bitsPerPixel)
    || (example.imageDescriptor != test.imageDescriptor)
    || (example.pixelCount != test.pixelCount)) {
        cout << "FAILED! (Different Headers)" << endl;
        return false;
    }

    for (int i = 0; i < example.pixelCount; i++) {
        if((example.pixels[i].R != test.pixels[i].R)
        || (example.pixels[i].G != test.pixels[i].G)
        || (example.pixels[i].B != test.pixels[i].B)) {
            cout << "FAILED! (Different RGB Value)" << endl << endl;
            cout << "Expected RGB value at pixel #" << i << ":" << endl;
            cout << "R: " << example.pixels[i].R << endl;
            cout << "G: " << (int)example.pixels[i].G << endl;
            cout << "B: " << (int)example.pixels[i].B << endl << endl;
            cout << "Actual RGB value at pixel #" << i << ":" << endl;
            cout << "R: " << (int)test.pixels[i].R << endl;
            cout << "G: " << (int)test.pixels[i].G << endl;
            cout << "B: " << (int)test.pixels[i].B << endl << endl;
            return false;
        }
    }

    cout << "PASSED!" << endl;
    return true;
}

unsigned char multiplyChannel(unsigned char top, unsigned char bottom, int scalar) {
    float final;

    final = (scalar * (((float)top/255) * ((float)bottom/255)) * 255) + 0.5f;
    return (unsigned char)final;
}

unsigned char screenChannel(unsigned char top, unsigned char bottom, int scalar) {
    float final;

    final = ((1 - (scalar * (1 - ((float)top/255)) * (1 - ((float)bottom/255)))) * 255) + 0.5f;
    return (unsigned char)final;
}

TGA multiply(TGA& top, TGA& bottom) {
    TGA C(top.width, top.height, top.pixelCount, top.pixels);

    for(int i = 0; i < top.pixelCount; i++) {
        C.pixels[i].R = multiplyChannel(top.pixels[i].R, bottom.pixels[i].R, 1);
        C.pixels[i].G = multiplyChannel(top.pixels[i].G, bottom.pixels[i].G, 1);
        C.pixels[i].B = multiplyChannel(top.pixels[i].B, bottom.pixels[i].B, 1);
    }

    return C;
}

TGA subtract(TGA& top, TGA& bottom) {
    TGA C(top.width, top.height, top.pixelCount, top.pixels);

    for(int i = 0; i < top.pixelCount; i++) {
        float valueC;

        valueC = (float(bottom.pixels[i].R) - float(top.pixels[i].R)) + 0.5f;
        if (valueC < 0) {
            valueC = 0;
        }
        C.pixels[i].R = (char)valueC;

        valueC = (float(bottom.pixels[i].G) - float(top.pixels[i].G)) + 0.5f;
        if (valueC < 0) {
            valueC = 0;
        }
        C.pixels[i].G = (char)valueC;

        valueC = (float(bottom.pixels[i].B) - float(top.pixels[i].B)) + 0.5f;
        if (valueC < 0) {
            valueC = 0;
        }
        C.pixels[i].B = (char)valueC;
    }

    return C;
}

TGA screen(TGA& top, TGA& bottom) {
    TGA C(top.width, top.height, top.pixelCount, top.pixels);

    for(int i = 0; i < top.pixelCount; i++) {
        C.pixels[i].R = screenChannel(top.pixels[i].R, bottom.pixels[i].R, 1);
        C.pixels[i].G = screenChannel(top.pixels[i].G, bottom.pixels[i].G, 1);
        C.pixels[i].B = screenChannel(top.pixels[i].B, bottom.pixels[i].B, 1);
    }

    return C;
}

TGA overlay(TGA& top, TGA& bottom) {
    TGA C(top.width, top.height, top.pixelCount, top.pixels);

    for(int i = 0; i < top.pixelCount; i++) {
        // RED
        if(((float)bottom.pixels[i].R/255) > 0.5) {
            C.pixels[i].R = screenChannel(top.pixels[i].R, bottom.pixels[i].R, 2);
        }
        else {
            C.pixels[i].R = multiplyChannel(top.pixels[i].R, bottom.pixels[i].R, 2);
        }

        // GREEN
        if(((float)bottom.pixels[i].G/255) > 0.5) {
            C.pixels[i].G = screenChannel(top.pixels[i].G, bottom.pixels[i].G, 2);
        }
        else {
            C.pixels[i].G = multiplyChannel(top.pixels[i].G, bottom.pixels[i].G, 2);
        }

        // BLUE
        if(((float)bottom.pixels[i].B/255) > 0.5) {
            C.pixels[i].B = screenChannel(top.pixels[i].B, bottom.pixels[i].B, 2);
        }
        else {
            C.pixels[i].B = multiplyChannel(top.pixels[i].B, bottom.pixels[i].B, 2);
        }
    }

    return C;
}

void rotate180(TGA& tga) {
    vector<TGA::Pixel> reversedPixels;

    for(int i = (tga.pixelCount - 1); i >= 0; i--) {
        reversedPixels.push_back(tga.pixels[i]);
    }

    tga.pixels = reversedPixels;
}

TGA breakChannel(TGA& tga, int channel) {
    vector<TGA::Pixel> oneChannel;

    if(channel == 1) {
        for(int i = 0; i < tga.pixelCount; i++) {
            TGA::Pixel newPixel(tga.pixels[i].R, tga.pixels[i].R, tga.pixels[i].R);
            oneChannel.push_back(newPixel);
        }
    }
    else if(channel == 2) {
        for(int i = 0; i < tga.pixelCount; i++) {
            TGA::Pixel newPixel(tga.pixels[i].G, tga.pixels[i].G, tga.pixels[i].G);
            oneChannel.push_back(newPixel);
        }
    }
    else if(channel == 3) {
        for(int i = 0; i < tga.pixelCount; i++) {
            TGA::Pixel newPixel(tga.pixels[i].B, tga.pixels[i].B, tga.pixels[i].B);
            oneChannel.push_back(newPixel);
        }
    }

    return TGA(tga.width, tga.height, tga.pixelCount, oneChannel);
}

TGA combineChannels(TGA& red, TGA& green, TGA& blue) {
    vector<TGA::Pixel> allChannels;

    for(int i = 0; i < red.pixelCount; i++) {
        TGA::Pixel newPixel(red.pixels[i].R, green.pixels[i].G, blue.pixels[i].B);
        allChannels.push_back(newPixel);
    }

    return TGA(red.width, red.height, red.pixelCount, allChannels);
}

TGA combineTGAs(TGA& bL, TGA& bR, TGA& tL, TGA& tR) {
    vector<TGA::Pixel> bottomPixels;
    vector<TGA::Pixel> topPixels;

    int z = 0;

    for(int i = 0; i < bL.height; i++) {
        for(int j = 0; j < bL.width; j++) {
            bottomPixels.push_back(bL.pixels[j + z]);
        }
        for(int k = 0; k < bR.width; k++) {
            bottomPixels.push_back(bR.pixels[k + z]);
        }
        z += bL.width;
    }

    z = 0;

    for(int i = 0; i < tL.height; i++) {
        for(int j = 0; j < tL.width; j++) {
            bottomPixels.push_back(tL.pixels[j + z]);
        }
        for(int k = 0; k < tR.width; k++) {
            bottomPixels.push_back(tR.pixels[k + z]);
        }
        z += tL.width;
    }

    vector<TGA::Pixel> final;

    for(int i = 0; i < bottomPixels.size(); i++) {
        final.push_back(bottomPixels[i]);
    }
    for(int i = 0; i < topPixels.size(); i++) {
        final.push_back(topPixels[i]);
    }

    return TGA((bL.height + tL.height), (bL.width + bR.width), final.size(), final);
}

int main() {

    // PART 1
    cout << "Test #1...... ";
    TGA layer1 = loadFile("input/layer1.tga");
    TGA pattern1 = loadFile("input/pattern1.tga");
    TGA final = multiply(layer1, pattern1);
    saveFile(final, "part1");
    cout << "COMPLETED...... ";
    compareFiles("examples/EXAMPLE_part1.tga", "output/part1.tga");

    // PART 2
    cout << "Test #2...... ";
    TGA layer2 = loadFile("input/layer2.tga");
    TGA car = loadFile("input/car.tga");
    final = subtract(layer2, car);
    saveFile(final, "part2");
    cout << "COMPLETED...... ";
    compareFiles("examples/EXAMPLE_part2.tga", "output/part2.tga");

    // PART 3
    cout << "Test #3...... ";
    TGA pattern2 = loadFile("input/pattern2.tga");
    TGA temp = multiply(layer1, pattern2);
    TGA text = loadFile("input/text.tga");
    final = screen(temp, text);
    saveFile(final, "part3");
    cout << "COMPLETED...... ";
    compareFiles("examples/EXAMPLE_part3.tga", "output/part3.tga");

    // PART 4
    cout << "Test #4...... ";
    TGA circles = loadFile("input/circles.tga");
    temp = multiply(layer2, circles);
    final = subtract(pattern2, temp);
    saveFile(final, "part4");
    cout << "COMPLETED...... ";
    compareFiles("examples/EXAMPLE_part4.tga", "output/part4.tga");

    // PART 5
    cout << "Test #5...... ";
    final = overlay(layer1, pattern1);
    saveFile(final, "part5");
    cout << "COMPLETED...... ";
    compareFiles("examples/EXAMPLE_part5.tga", "output/part5.tga");

    // PART 6
    cout << "Test #6...... ";
    for(int i = 0; i < car.pixelCount; i++) {
        int gValue = car.pixels[i].G + 200;
        if(gValue > 255) {
            gValue = 255;
        }
        car.pixels[i].G = gValue;
    }
    saveFile(car, "part6");
    cout << "COMPLETED...... ";
    compareFiles("examples/EXAMPLE_part6.tga", "output/part6.tga");

    // PART 7
    cout << "Test #7...... ";
    car = loadFile("input/car.tga");
    for(int i = 0; i < car.pixelCount; i++) {
        // Multiply R by 4
        int rValue = car.pixels[i].R * 4;
        if(rValue > 255) {
            rValue = 255;
        }
        car.pixels[i].R = rValue;

        // Multiply B by 0
        car.pixels[i].B = car.pixels[i].B * 0;
    }
    saveFile(car, "part7");
    cout << "COMPLETED...... ";
    compareFiles("examples/EXAMPLE_part7.tga", "output/part7.tga");

    // PART 8
    cout << "Test #8...... ";
    car = loadFile("input/car.tga");
    TGA red = breakChannel(car, 1);
    TGA green = breakChannel(car, 2);
    TGA blue = breakChannel(car, 3);
    saveFile(red, "part8_r");
    saveFile(green, "part8_g");
    saveFile(blue, "part8_b");
    cout << "COMPLETED...... ";
    compareFiles("examples/EXAMPLE_part8_r.tga", "output/part8_r.tga");
    compareFiles("examples/EXAMPLE_part8_g.tga", "output/part8_g.tga");
    compareFiles("examples/EXAMPLE_part8_b.tga", "output/part8_b.tga");

    // PART 9
    cout << "Test #9...... ";
    TGA layerR = loadFile("input/layer_red.tga");
    TGA layerG = loadFile("input/layer_green.tga");
    TGA layerB = loadFile("input/layer_blue.tga");
    final = combineChannels(layerR, layerG, layerB);
    saveFile(final, "part9");
    cout << "COMPLETED...... ";
    compareFiles("examples/EXAMPLE_part9.tga", "output/part9.tga");


    // PART 10
    cout << "Test #10...... ";
    TGA text2 = loadFile("input/text2.tga");
    rotate180(text2);
    saveFile(text2, "part10");
    cout << "COMPLETED...... ";
    compareFiles("examples/EXAMPLE_part10.tga", "output/part10.tga");

    // PART 11 (Extra Credit)
    cout << "Test Extra Credit...... ";
    final = combineTGAs(text, pattern1, car, circles);
    saveFile(final, "extracredit");
    cout << "COMPLETED...... ";
    compareFiles("examples/EXAMPLE_extracredit.tga", "output/extracredit.tga");

    return 0;
}
