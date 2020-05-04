//
// Created by Lukian Bogdanets on 4/14/20.
//

#pragma once

#include <random>

using namespace std;

class Random {
public:
    static mt19937 random;

    static int randomInt(int min, int max);
    static int randomFloat(int min, int max);
};

mt19937 Random::random;

int Random::randomInt(int min, int max) {
    uniform_int_distribution<int> dist(min, max);

    return dist(random);
}

int Random::randomFloat(int min, int max) {
    uniform_real_distribution<float> dist(min, max);

    return dist(random);
}