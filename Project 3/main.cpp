#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <string>
#include <cmath>
#include <random>
#include"Board.h"

using namespace std;


int main() {
    Board board;
    Tile tile;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper");
    board.DrawBoard(window);
    board.Mines();
    int debug_count = 0;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                auto mouse = sf::Mouse::getPosition(window);
                int xcoord = mouse.x / 32;
                int ycoord = mouse.y / 32;
                if (ycoord < 16 && !board.gameOver) {
                    if (event.mouseButton.button == sf::Mouse::Left &&
                        !board.tileVec[xcoord % 25 + ycoord * 25].isFlagged &&
                        !board.tileVec[xcoord % 25 + ycoord * 25].isClicked) {
                        board.Reveal(&board.tileVec[xcoord % 25 + ycoord * 25]);
                    } else if (event.mouseButton.button == sf::Mouse::Right &&
                               !board.tileVec[xcoord % 25 + ycoord * 25].isClicked) {
                        if (!board.tileVec[xcoord % 25 + ycoord * 25].isFlagged) {
                            board.Flag(&board.tileVec[xcoord % 25 + ycoord * 25]);
                        } else {
                            board.Unflag(&board.tileVec[xcoord % 25 + ycoord * 25]);
                        }
                    }

                } else if (ycoord >= 16) {
                    if (mouse.x >= 500 && mouse.x < 565 && !board.gameOver) {
                        debug_count++;
                    } else if (mouse.x >= 370 && mouse.x < 435) {
                        window.clear();
                        board.Reset();
                        board.Mines();

                    } else if (mouse.x >= 565 && mouse.x < 630 && !board.gameOver) {
                        window.clear();
                        board.Reset();
                        board.Test1();

                    } else if (mouse.x >= 630 && mouse.x < 695 && !board.gameOver) {
                        window.clear();
                        board.Reset();
                        board.Test2();
                    } else if (mouse.x >= 695 && mouse.x < 760 && !board.gameOver) {
                        window.clear();
                        board.Reset();
                        board.Test3();
                    }
                    if (debug_count % 2 != 0) {
                        board.Debug();
                    } else if (debug_count % 2 == 0 && !board.gameOver) {
                        board.UnDebug();
                    }
                }
                board.DrawBoard(window);
            } else {
                break;
            }
        }


    }
    window.display();
    return 0;
}
