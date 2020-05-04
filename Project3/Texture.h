//
// Created by Lukian Bogdanets on 4/14/20.
//

#pragma once

#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

class Texture {
public:
    static map<string, sf::Texture> textureMap;

    static void loadTextures();
};

map<string, sf::Texture> Texture::textureMap;

void Texture::loadTextures() {
    sf::Texture texture;
    texture.loadFromFile("/Users/lukian/CLionProjects/Project3/images/debug.png");
    textureMap.emplace("debug", texture);
    texture.loadFromFile("/Users/lukian/CLionProjects/Project3/images/digits.png");
    textureMap.emplace("digits", texture);
    texture.loadFromFile("/Users/lukian/CLionProjects/Project3/images/face_happy.png");
    textureMap.emplace("face_happy", texture);
    texture.loadFromFile("/Users/lukian/CLionProjects/Project3/images/face_lose.png");
    textureMap.emplace("face_lose", texture);
    texture.loadFromFile("/Users/lukian/CLionProjects/Project3/images/face_win.png");
    textureMap.emplace("face_win", texture);
    texture.loadFromFile("/Users/lukian/CLionProjects/Project3/images/flag.png");
    textureMap.emplace("flag", texture);
    texture.loadFromFile("/Users/lukian/CLionProjects/Project3/images/mine.png");
    textureMap.emplace("mine", texture);
    texture.loadFromFile("/Users/lukian/CLionProjects/Project3/images/number_1.png");
    textureMap.emplace("number_1", texture);
    texture.loadFromFile("/Users/lukian/CLionProjects/Project3/images/number_2.png");
    textureMap.emplace("number_2", texture);
    texture.loadFromFile("/Users/lukian/CLionProjects/Project3/images/number_3.png");
    textureMap.emplace("number_3", texture);
    texture.loadFromFile("/Users/lukian/CLionProjects/Project3/images/number_4.png");
    textureMap.emplace("number_4", texture);
    texture.loadFromFile("/Users/lukian/CLionProjects/Project3/images/number_5.png");
    textureMap.emplace("number_5", texture);
    texture.loadFromFile("/Users/lukian/CLionProjects/Project3/images/number_6.png");
    textureMap.emplace("number_6", texture);
    texture.loadFromFile("/Users/lukian/CLionProjects/Project3/images/number_7.png");
    textureMap.emplace("number_7", texture);
    texture.loadFromFile("/Users/lukian/CLionProjects/Project3/images/number_8.png");
    textureMap.emplace("number_8", texture);
    texture.loadFromFile("/Users/lukian/CLionProjects/Project3/images/test_1.png");
    textureMap.emplace("test_1", texture);
    texture.loadFromFile("/Users/lukian/CLionProjects/Project3/images/test_2.png");
    textureMap.emplace("test_2", texture);
    texture.loadFromFile("/Users/lukian/CLionProjects/Project3/images/test_3.png");
    textureMap.emplace("test_3", texture);
    texture.loadFromFile("/Users/lukian/CLionProjects/Project3/images/tile_hidden.png");
    textureMap.emplace("tile_hidden", texture);
    texture.loadFromFile("/Users/lukian/CLionProjects/Project3/images/tile_revealed.png");
    textureMap.emplace("tile_revealed", texture);
}

