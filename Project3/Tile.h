//
// Created by Lukian Bogdanets on 4/13/20.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Texture.h"
#include "Board.h"

using namespace std;

class Tile {
private:
    unsigned short x;
    unsigned short y;
    bool hidden;
    bool flag;
    bool mine;
    sf::Sprite sprite;
    vector<Tile*> nearbyTiles;

public:
    Tile(unsigned short x, unsigned short y);

    unsigned short getX();
    unsigned short getY();
    bool getHidden();
    bool getFlag();
    bool getMine();
    sf::Sprite getSprite();
    vector<Tile*> getNearbyTiles();

    void setMine(bool value);
    void setFlag(bool value);
    void setHidden();
    void setUnhidden();
    void addNearbyTile(Tile* tile);
    unsigned short minesNearby();
    void texturizeSprite(sf::Texture& texture);
};

Tile::Tile(unsigned short x, unsigned short y) {
    this->x = x;
    this->y = y;
    hidden = true;
    flag = false;
    mine = false;
    sprite.setPosition(sf::Vector2f(x * 32, y * 32));
    texturizeSprite(Texture::textureMap["tile_hidden"]);
}

unsigned short Tile::getX() {
    return x;
}

unsigned short Tile::getY() {
    return y;
}

bool Tile::getHidden() {
    return hidden;
}

bool Tile::getFlag() {
    return flag;
}

bool Tile::getMine() {
    return mine;
}

sf::Sprite Tile::getSprite() {
    return sprite;
}

vector<Tile*> Tile::getNearbyTiles() {
    return nearbyTiles;
}

void Tile::setMine(bool value) {
    if (value) {
        mine = true;
    }
    else {
        mine = false;
    }
}

void Tile::setFlag(bool value) {
    if(value) {
        flag = true;
    }
    else {
        flag = false;
    }
}

void Tile::setHidden() {
    texturizeSprite(Texture::textureMap["tile_hidden"]);
    hidden = true;
}

void Tile::setUnhidden() {
    texturizeSprite(Texture::textureMap["tile_revealed"]);
    hidden = false;
}

void Tile::addNearbyTile(Tile* tile) {
    nearbyTiles.push_back(tile);
}

unsigned short Tile::minesNearby() {
    unsigned short minesNearby = 0;

    for(int i = 0; i < nearbyTiles.size(); i++) {
        if (nearbyTiles[i]->getMine()) {
            minesNearby++;
        }
    }

    return minesNearby;
}

void Tile::texturizeSprite(sf::Texture& texture) {
    sprite.setTexture(texture);
}