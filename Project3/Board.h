//
// Created by Lukian Bogdanets on 4/13/20.
//

#pragma once

#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Random.h"

using namespace std;

class Board {
private:
    unsigned int tilesRevealed = 0;
    unsigned int mineCount = 0;
    unsigned int flagCount = 0;
    bool lost = false;
    bool won = false;
    bool debug = false;
    vector<vector<Tile*>> tiles;
    vector<sf::Sprite> flags;
    vector<sf::Sprite> mines;
    vector<sf::Sprite> numbers;

    void randomMines();
    void initializeNearbyTiles();

public:
    Board();

    bool getLost();
    bool getWon();
    unsigned int getTilesRevealed();
    unsigned int getMineCount();
    vector<vector<Tile*>> getTileVector();
    vector<sf::Sprite> getFlagsVector();
    vector<sf::Sprite> getMinesVector();
    vector<sf::Sprite> getNumbersVector();

    void changeFlagCount(bool add);
    void drawBoard(sf::RenderWindow& window);
    void resetBoard(bool randomMinesFunc);
    void debugMode();
    void lose();
    void win();
    void loadBoard(int boardNum);
    void push(sf::Sprite& sprite, string vect);
    void erase(int& i, string vect);
    void addTileRevealed();
};

Board::Board() {
    tiles.resize(16, vector<Tile*>(25));
    for(int y = 0; y < 16; y++) {
        for(int x = 0; x < 25; x++) {
            Tile* newTile = new Tile(x, y);
            tiles[y][x] = newTile;
        }
    }

    initializeNearbyTiles();
    randomMines();
}

unsigned int Board::getMineCount() {
    return mineCount;
}

vector<vector<Tile*>> Board::getTileVector() {
    return tiles;
}

vector<sf::Sprite> Board::getFlagsVector() {
    return flags;
}

vector<sf::Sprite> Board::getMinesVector() {
    return mines;
}

vector<sf::Sprite> Board::getNumbersVector() {
    return numbers;
}

void Board::drawBoard(sf::RenderWindow& window) {
    for(int y = 0; y < 16; y++) {
        for(int x = 0; x < 25; x++) {
            window.draw(tiles[y][x]->getSprite());
        }
    }
}

void Board::resetBoard(bool randomMinesFunc) {
    for(int y = 0; y < 16; y++) {
        for(int x = 0; x < 25; x++) {
            tiles[y][x]->setHidden();
            tiles[y][x]->setMine(false);
            tiles[y][x]->setFlag(false);
        }
    }

    tilesRevealed = 0;
    flagCount = 0;
    mineCount = 0;
    won = false;
    lost = false;
    debug = false;
    flags.clear();
    mines.clear();
    numbers.clear();
    if (randomMinesFunc) {
        randomMines();
    }
}

void Board::randomMines() {
    while(mineCount < 50) {
        int randX = Random::randomInt(0, 24);
        int randY = Random::randomInt(0, 15);

        if (tiles[randY][randX]->getMine()) {
            continue;
        }
        else {
            tiles[randY][randX]->setMine(true);
            mineCount++;
        }

    }

}

void Board::debugMode() {
    if (debug) {
        mines.clear();
        debug = false;
    }
    else {
        for (int y = 0; y < 16; y++) {
            for (int x = 0; x < 25; x++) {
                if (tiles[y][x]->getMine()) {
                    sf::Vector2f minePos(tiles[y][x]->getX() * 32, tiles[y][x]->getY() * 32);
                    sf::Sprite mine(Texture::textureMap["mine"]);
                    mine.setPosition(minePos);
                    push(mine, "mines");
                }
            }
        }
        debug = true;
    }
}

void Board::loadBoard(int boardNum) {
    resetBoard(false);

    ifstream board;
    board.open("/Users/lukian/CLionProjects/Project3/boards/testboard" + to_string(boardNum) + ".brd");

    char digit;

    for(int y = 0; y < 16; y++) {
        for (int x = 0; x < 25; x++) {
            board >> digit;
            if (digit == '1') {
                tiles[y][x]->setMine(true);
                mineCount++;
            }
        }
    }
}

void Board::initializeNearbyTiles() {
    for (int y = 0; y < 16; y++) {
        for (int x = 0; x < 25; x++) {
            bool down = (y + 1 < 16);
            bool up = (y - 1 > (-1));
            bool left = (x - 1 > (-1));
            bool right = (x + 1 < 25);

            if (up) {
                tiles[y][x]->addNearbyTile(tiles[y - 1][x]);
            }
            if (down) {
                tiles[y][x]->addNearbyTile(tiles[y + 1][x]);
            }
            if (right) {
                tiles[y][x]->addNearbyTile(tiles[y][x + 1]);
            }
            if (left) {
                tiles[y][x]->addNearbyTile(tiles[y][x - 1]);
            }
            if (up & left) {
                tiles[y][x]->addNearbyTile(tiles[y - 1][x - 1]);
            }
            if (up & right) {
                tiles[y][x]->addNearbyTile(tiles[y - 1][x + 1]);
            }
            if (down & left) {
                tiles[y][x]->addNearbyTile(tiles[y + 1][x - 1]);
            }
            if (down & right) {
                tiles[y][x]->addNearbyTile(tiles[y + 1][x + 1]);
            }
        }
    }
}

void Board::push(sf::Sprite& sprite, string vect) {
    if (vect == "flags") {
        flags.push_back(sprite);
    }
    else if (vect == "mines") {
        mines.push_back(sprite);
    }
    else if (vect == "numbers") {
        numbers.push_back(sprite);
    }
}

void Board::erase(int& i, string vect) {
    if (vect == "flags") {
        flags.erase(flags.begin() + i);
    }
    else if (vect == "mines") {
        mines.erase(mines.begin() + i);
    }
    else if (vect == "numbers") {
        numbers.erase(numbers.begin() + i);
    }
}

void Board::changeFlagCount(bool add) {
    if (add) {
        flagCount++;
    }
    else {
        flagCount--;
    }
}

void Board::lose() {
   lost = true;
   if (!debug) {
       debugMode();
   }
}

bool Board::getLost() {
    return lost;
}

bool Board::getWon() {
    return won;
}

void Board::win() {
    won = true;
    if (!debug) {
        debugMode();
    }
}

unsigned int Board::getTilesRevealed() {
    return tilesRevealed;
}

void Board::addTileRevealed() {
    tilesRevealed++;
}
