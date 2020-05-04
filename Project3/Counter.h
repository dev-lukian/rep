//
// Created by Lukian Bogdanets on 4/16/20.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "Texture.h"

class Counter {
private:
    int display;
    vector<sf::Sprite> digits;
    vector<sf::Sprite> printedDigits;

public:
    Counter();

    void position();
    void draw(sf::RenderWindow& window);
    void change(bool add);
    void set(int mineCount);
    void push(int digit);
};

Counter::Counter() {
    digits.resize(11);
    for(int i = 0; i < 11; i++) {
        digits[i].setTexture(Texture::textureMap["digits"]);
        digits[i].setTextureRect(sf::IntRect(i * 21, 0, 21, 32));
    }
}

void Counter::push(int digit) {
    switch (digit) {
        case 0: {
            printedDigits.push_back(digits[0]);
            break;
        }
        case 1: {
            printedDigits.push_back(digits[1]);
            break;
        }
        case 2: {
            printedDigits.push_back(digits[2]);
            break;
        }
        case 3: {
            printedDigits.push_back(digits[3]);
            break;
        }
        case 4: {
            printedDigits.push_back(digits[4]);
            break;
        }
        case 5: {
            printedDigits.push_back(digits[5]);
            break;
        }
        case 6: {
            printedDigits.push_back(digits[6]);
            break;
        }
        case 7: {
            printedDigits.push_back(digits[7]);
            break;
        }
        case 8: {
            printedDigits.push_back(digits[8]);
            break;
        }
        case 9: {
            printedDigits.push_back(digits[9]);
            break;
        }
        case 10: {
            printedDigits.push_back(digits[10]);
            break;
        }
    }
}

void Counter::position() {
    for(int i = 0; i < printedDigits.size(); i++) {
        printedDigits[i].setPosition(sf::Vector2f(i * 21, 512));
    }
}

void Counter::draw(sf::RenderWindow& window) {
    for(int i = 0; i < printedDigits.size(); i++) {
        window.draw(printedDigits[i]);
    }
}

void Counter::set(int mineCount) {
    printedDigits.clear();
    display = mineCount;

    int ones = display % 10;
    int tens = (display / 10) % 10;
    int hundreds = (display / 100) % 10;

    push(hundreds);
    push(tens);
    push(ones);

    position();
}

void Counter::change(bool add) {
    printedDigits.clear();

    if (add) {
        display--;
    }
    else {
        display++;
    }

    int ones = abs(display) % 10;
    int tens = abs(display / 10) % 10;
    int hundreds = abs(display / 100) % 10;

    if (display < 0) {
        push(10);
    }
    push(hundreds);
    push(tens);
    push(ones);

    position();
}


