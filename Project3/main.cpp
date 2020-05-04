#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Board.h"
#include "Texture.h"
#include "Counter.h"

using namespace std;

sf::Sprite loadSprite(const string key);
Tile* tileClicked(vector<vector<Tile*>> tiles, sf::Vector2i& pos);
void drawNumber(Board& board, unsigned short mines, sf::Vector2f& position);
void revealNeighbors(Board& board, vector<Tile*> tiles);

int main()
{

    //===== PROGRAM STAGE 1: INITIALIZATION =====//
    sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper");
    window.setFramerateLimit(60);

    // Load all textures
    Texture::loadTextures();

    // Load sprites
    Board board;
    Counter flagCounter;
    flagCounter.set(board.getMineCount());
    sf::Sprite face = loadSprite("face_happy");
    sf::Sprite debug = loadSprite("debug");
    sf::Sprite test1 = loadSprite("test_1");
    sf::Sprite test2 = loadSprite("test_2");
    sf::Sprite test3 = loadSprite("test_3");

    // Position sprites
    flagCounter.position();
    face.setPosition(sf::Vector2f((window.getSize().x/2.0f)-32,512));
    debug.setPosition(sf::Vector2f((window.getSize().x/2.0f) + 96,512));
    test1.setPosition(sf::Vector2f((window.getSize().x/2.0f) + 160,512));
    test2.setPosition(sf::Vector2f((window.getSize().x/2.0f) + 224,512));
    test3.setPosition(sf::Vector2f((window.getSize().x/2.0f) + 288,512));

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {

            switch (event.type) {

                // "close requested" event: we close the window
                case sf::Event::Closed:
                    window.close();

                // Click Event
                case sf::Event::MouseButtonPressed:
                    auto pos = sf::Mouse::getPosition(window);

                    Tile* tilePos = tileClicked(board.getTileVector(), pos);
                    if (tilePos != nullptr && !board.getLost() && !board.getWon()){

                        // Left Click = Unhide Tile
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            sf::Vector2f position(tilePos->getX() * 32, tilePos->getY() * 32);

                            // Clicked on flag
                            if (tilePos->getFlag()) {
                                break;
                            }

                            // Clicked on mine
                            else if (tilePos->getMine()) {
                                tilePos->setUnhidden();
                                sf::Sprite mine = loadSprite("mine");
                                mine.setPosition(position);
                                board.push(mine, "mines");
                                board.lose();
                                face.setTexture(Texture::textureMap["face_lose"]);
                            }

                            // Clicked on empty tile, potenially showing numbers
                            else {
                                tilePos->setUnhidden();
                                board.addTileRevealed();
                                unsigned short mines = tilePos->minesNearby();

                                // Clicked on tile w/ 0 mines nearby, continues to reveal nearby tiles
                                if (mines == 0) {
                                    revealNeighbors(board, tilePos->getNearbyTiles());
                                }

                                // Clicked on tile w/ mines nearby
                                else {
                                    drawNumber(board, mines, position);
                                }
                            }

                            if (board.getMineCount() + board.getTilesRevealed() == 400) {
                                board.win();
                                face.setTexture(Texture::textureMap["face_win"]);
                            }
                        }

                        // Right Click = Set Flag
                        else if (event.mouseButton.button == sf::Mouse::Right) {
                            if (tilePos->getHidden()) {
                                sf::Vector2f position(tilePos->getX() * 32, tilePos->getY() * 32);

                                // Remove Flag
                                if (tilePos->getFlag()) {
                                    for(int i = 0; i < board.getFlagsVector().size(); i++) {
                                        if (board.getFlagsVector()[i].getGlobalBounds().contains(position)) {
                                            board.erase(i, "flags");
                                            break;
                                        }
                                    }
                                    tilePos->setFlag(false);
                                    board.changeFlagCount(false);
                                    flagCounter.change(false);
                                }

                                // Place Flag
                                else {
                                    sf::Sprite flag = loadSprite("flag");
                                    flag.setPosition(position);
                                    board.push(flag, "flags");
                                    tilePos->setFlag(true);
                                    board.changeFlagCount(true);
                                    flagCounter.change(true);
                                }
                            }
                        }
                    }

                    // Click on face = Reset Board
                    else if (face.getGlobalBounds().contains(sf::Vector2f(pos.x, pos.y))) {
                        board.resetBoard(true);
                        flagCounter.set(board.getMineCount());
                        face.setTexture(Texture::textureMap["face_happy"]);
                    }

                    // Debug Mode
                    else if ((debug.getGlobalBounds().contains(sf::Vector2f(pos.x, pos.y)))) {
                        board.debugMode();
                    }

                    // Test 1
                    else if ((test1.getGlobalBounds().contains(sf::Vector2f(pos.x, pos.y)))) {
                        board.loadBoard(1);
                        flagCounter.set(board.getMineCount());
                        face.setTexture(Texture::textureMap["face_happy"]);
                    }

                    // Test 2
                    else if ((test2.getGlobalBounds().contains(sf::Vector2f(pos.x, pos.y)))) {
                        board.loadBoard(2);
                        flagCounter.set(board.getMineCount());
                        face.setTexture(Texture::textureMap["face_happy"]);
                    }

                    // Test 3
                    else if ((test3.getGlobalBounds().contains(sf::Vector2f(pos.x, pos.y)))) {
                        board.loadBoard(3);
                        flagCounter.set(board.getMineCount());
                        face.setTexture(Texture::textureMap["face_happy"]);
                    }
            }

        }

        //===== PROGRAM STAGE 2: UPDATE =====//

        //===== PROGRAM STAGE 3: DRAW =====//
        window.clear(sf::Color(189,189,189, 255));

        board.drawBoard(window);
        flagCounter.draw(window);
        window.draw(face);
        window.draw(debug);
        window.draw(test1);
        window.draw(test2);
        window.draw(test3);
        for(int i = 0; i < board.getFlagsVector().size(); i++) {
            window.draw(board.getFlagsVector()[i]);
        }
        for(int i = 0; i < board.getMinesVector().size(); i++) {
            window.draw(board.getMinesVector()[i]);
        }
        for(int i = 0; i < board.getNumbersVector().size(); i++) {
            window.draw(board.getNumbersVector()[i]);
        }

        window.display();
    }

    Texture::textureMap.clear();

    return 0;
}

sf::Sprite loadSprite(const string key) {
    sf::Sprite sprite;
    sprite.setTexture(Texture::textureMap[key]);

    return sprite;
}

Tile* tileClicked(vector<vector<Tile*>> tiles, sf::Vector2i& pos) {
    for(int i = 0; i < tiles.size(); i++) {
        for(int j = 0; j < tiles[i].size(); j++) {
            if (tiles[i][j]->getSprite().getGlobalBounds().contains(sf::Vector2f(pos.x, pos.y))) {
                return tiles[i][j];
            }
        }
    }

    return nullptr;
}

void drawNumber(Board& board, unsigned short mines, sf::Vector2f& position) {
    sf::Sprite* num = new sf::Sprite();
    switch (mines) {
        case 0:
            break;
        case 1:
            num->setTexture(Texture::textureMap["number_1"]);
            num->setPosition(position);
            board.push(*num, "numbers");
            break;
        case 2:
            num->setTexture(Texture::textureMap["number_2"]);
            num->setPosition(position);
            board.push(*num, "numbers");
            break;
        case 3:
            num->setTexture(Texture::textureMap["number_3"]);
            num->setPosition(position);
            board.push(*num, "numbers");
            break;
        case 4:
            num->setTexture(Texture::textureMap["number_4"]);
            num->setPosition(position);
            board.push(*num, "numbers");
            break;
        case 5:
            num->setTexture(Texture::textureMap["number_5"]);
            num->setPosition(position);
            board.push(*num, "numbers");
            break;
        case 6:
            num->setTexture(Texture::textureMap["number_6"]);
            num->setPosition(position);
            board.push(*num, "numbers");
            break;
        case 7:
            num->setTexture(Texture::textureMap["number_7"]);
            num->setPosition(position);
            board.push(*num, "numbers");
            break;
        case 8:
            num->setTexture(Texture::textureMap["number_8"]);
            num->setPosition(position);
            board.push(*num, "numbers");
            break;
    }
}

void revealNeighbors(Board& board, vector<Tile*> tiles) {
    for(int i = 0; i < tiles.size(); i++) {
        if (tiles[i]->getMine()) {
            continue;
        }
        else if (tiles[i]->getFlag()) {
            continue;
        }
        else if (!tiles[i]->getHidden()) {
            continue;
        }
        else if (tiles[i]->minesNearby() > 0) {
            tiles[i]->setUnhidden();
            board.addTileRevealed();
            sf::Vector2f position(tiles[i]->getX() * 32, tiles[i]->getY() * 32);
            drawNumber(board, tiles[i]->minesNearby(), position);
        }
        else {
            tiles[i]->setUnhidden();
            board.addTileRevealed();
            revealNeighbors(board, tiles[i]->getNearbyTiles());
        }
    }
}