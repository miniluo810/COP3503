#include <iostream>
#include <map>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>


using namespace std;

struct Tile {
    Tile() {


    }
    Tile(map<string, sf::Texture> textures) {
       // background.setTexture(textures["hidden"]);
    }

    sf::Sprite front, background, flag;
    bool isMine = false;
    bool isFlagged = false;
    bool isClicked = false;
    bool isDebug = false;
    vector<Tile *> nearbyTiles;
    int mineCount = 0;

    int MineCounter() {
        mineCount = 0;
        for (auto &nearbyTile : nearbyTiles) {
            if (nearbyTile->isMine) {
                mineCount++;
            }

        }
        return mineCount;
    }
};

class Board {
public:
    vector<Tile> tileVec;
    map<string, sf::Texture> textures;
    sf::Sprite face, debug, test1, test2, test3, score1, score2, score3, score4;
    int flagCount = 50;
    bool gameOver = false;
    bool gameWon = false;
    int revealCount = 0;
    int onesDigit, tensDigit, hundredsDigit;

    void LoadTextures() {
        sf::Texture textTemp;
        textTemp.loadFromFile("images/tile_hidden.png");
        textures["hidden"] = textTemp;
        textTemp.loadFromFile("images/tile_revealed.png");
        textures["revealed"] = textTemp;
        textTemp.loadFromFile("images/flag.png");
        textures["flag"] = textTemp;
        textTemp.loadFromFile("images/face_happy.png");
        textures["happy"] = textTemp;
        textTemp.loadFromFile("images/face_lose.png");
        textures["lose"] = textTemp;
        textTemp.loadFromFile("images/face_win.png");
        textures["win"] = textTemp;
        textTemp.loadFromFile("images/mine.png");
        textures["mine"] = textTemp;
        textTemp.loadFromFile("images/test_1.png");
        textures["test1"] = textTemp;
        textTemp.loadFromFile("images/test_2.png");
        textures["test2"] = textTemp;
        textTemp.loadFromFile("images/test_3.png");
        textures["test3"] = textTemp;
        textTemp.loadFromFile("images/debug.png");
        textures["debug"] = textTemp;
        textTemp.loadFromFile("images/number_1.png");
        textures["num1"] = textTemp;
        textTemp.loadFromFile("images/number_2.png");
        textures["num2"] = textTemp;
        textTemp.loadFromFile("images/number_3.png");
        textures["num3"] = textTemp;
        textTemp.loadFromFile("images/number_4.png");
        textures["num4"] = textTemp;
        textTemp.loadFromFile("images/number_5.png");
        textures["num5"] = textTemp;
        textTemp.loadFromFile("images/number_6.png");
        textures["num6"] = textTemp;
        textTemp.loadFromFile("images/number_7.png");
        textures["num7"] = textTemp;
        textTemp.loadFromFile("images/number_8.png");
        textures["num8"] = textTemp;
        textTemp.loadFromFile("images/digits.png");
        textures["digits"] = textTemp;

    }

    void DrawBoard(sf::RenderWindow &window) {

        if (TotalRevealed() + TotalMine() == 400 && !gameOver) {
            gameWon = true;
            gameOver = true;
        }
        if (!gameOver && !gameWon) {
            face.setTexture(textures["happy"]);
        } else if (gameOver && !gameWon) {
            face.setTexture(textures["lose"]);
        } else if (gameWon && gameOver) {
            face.setTexture(textures["win"]);
            for (int i = 0; i < 400; i++) {
                if (tileVec[i].isMine) {
                    tileVec[i].flag.setTexture(textures["flag"]);
                    tileVec[i].front.setTexture(textures["hidden"]);
                    tileVec[i].background.setTexture(textures["flag"]);
                }
            }
        }
        for (int i = 0; i < 400; i++) {
            window.draw(tileVec[i].background);
            window.draw(tileVec[i].front);
            window.draw(tileVec[i].flag);
        }
        face.setPosition(370, 513);
        window.draw(face);
        score1.setTexture(textures["digits"]);
        score2.setTexture(textures["digits"]);
        score3.setTexture(textures["digits"]);
        score4.setTexture(textures["digits"]);
        if (flagCount <= 98) {

            onesDigit = abs(flagCount) % 10;
            tensDigit = (abs(flagCount) / 10) % 10;
            hundredsDigit = abs(flagCount) / 100;
            score1.setTextureRect(sf::IntRect(onesDigit * 21, 0, 21, 32));
            score1.setPosition(44, 513);
            score2.setTextureRect(sf::IntRect(tensDigit * 21, 0, 21, 32));
            score2.setPosition(22, 513);
            if (flagCount <= -100 && flagCount > -400) {
                score4.setTextureRect(sf::IntRect(hundredsDigit * 21, 0, 21, 32));
                score4.setPosition(22, 513);
                score1.setPosition(66, 513);
                score2.setPosition(44, 513);
                window.draw(score4);
            } else if (flagCount < 0 && flagCount > -100) {
                score3.setTextureRect(sf::IntRect(10 * 21, 0, 21, 32));
                score3.setPosition(0, 513);

            } else {
                score3.setTextureRect(sf::IntRect(0, 0, 21, 32));
                score3.setPosition(0, 513);


            }
            window.draw(score1);
            window.draw(score2);
            window.draw(score3);

        }
        debug.setTexture(textures["debug"]);
        debug.setPosition(500, 513);
        window.draw(debug);
        test1.setTexture(textures["test1"]);
        test1.setPosition(565, 513);
        window.draw(test1);
        test2.setTexture(textures["test2"]);
        test2.setPosition(630, 513);
        window.draw(test2);
        test3.setTexture(textures["test3"]);
        test3.setPosition(695, 513);
        window.draw(test3);
        window.display();

    }

    void Neighbors() {

        for (unsigned int i = 0; i < 400; i++) {
            //top left
            if (i == 0) {
                tileVec[0].nearbyTiles.push_back(&tileVec[i + 1]);
                tileVec[0].nearbyTiles.push_back(&tileVec[i + 26]);
                tileVec[0].nearbyTiles.push_back(&tileVec[25]);
            } else if (i == 24) {//top right
                tileVec[24].nearbyTiles.push_back(&tileVec[23]);
                tileVec[24].nearbyTiles.push_back(&tileVec[48]);
                tileVec[24].nearbyTiles.push_back(&tileVec[49]);
            } else if (i == 375) {//bottom left
                tileVec[375].nearbyTiles.push_back(&tileVec[350]);
                tileVec[375].nearbyTiles.push_back(&tileVec[351]);
                tileVec[375].nearbyTiles.push_back(&tileVec[376]);
            } else if (i == 399) {//bottom right
                tileVec[399].nearbyTiles.push_back(&tileVec[374]);
                tileVec[399].nearbyTiles.push_back(&tileVec[373]);
                tileVec[399].nearbyTiles.push_back(&tileVec[398]);
            } else if (i % 25 == 0) {//left border
                tileVec[i].nearbyTiles.push_back(&tileVec[i - 25]);
                tileVec[i].nearbyTiles.push_back(&tileVec[i - 24]);
                tileVec[i].nearbyTiles.push_back(&tileVec[i + 1]);
                tileVec[i].nearbyTiles.push_back(&tileVec[i + 26]);
                tileVec[i].nearbyTiles.push_back(&tileVec[i + 25]);
            } else if (i % 25 == 24) {//right border
                tileVec[i].nearbyTiles.push_back(&tileVec[i - 25]);
                tileVec[i].nearbyTiles.push_back(&tileVec[i - 26]);
                tileVec[i].nearbyTiles.push_back(&tileVec[i - 1]);
                tileVec[i].nearbyTiles.push_back(&tileVec[i + 24]);
                tileVec[i].nearbyTiles.push_back(&tileVec[i + 25]);
            } else if (i < 24 && i > 0) {//top border
                tileVec[i].nearbyTiles.push_back(&tileVec[i - 1]);
                tileVec[i].nearbyTiles.push_back(&tileVec[i + 24]);
                tileVec[i].nearbyTiles.push_back(&tileVec[i + 25]);
                tileVec[i].nearbyTiles.push_back(&tileVec[i + 26]);
                tileVec[i].nearbyTiles.push_back(&tileVec[i + 1]);
            } else if (i > 375 && i < 399) {//bottom border
                tileVec[i].nearbyTiles.push_back(&tileVec[i - 1]);
                tileVec[i].nearbyTiles.push_back(&tileVec[i - 26]);
                tileVec[i].nearbyTiles.push_back(&tileVec[i - 25]);
                tileVec[i].nearbyTiles.push_back(&tileVec[i - 24]);
                tileVec[i].nearbyTiles.push_back(&tileVec[i + 1]);
            } else {//middle tiles
                tileVec[i].nearbyTiles.push_back(&tileVec[i - 26]);
                tileVec[i].nearbyTiles.push_back(&tileVec[i - 25]);
                tileVec[i].nearbyTiles.push_back(&tileVec[i - 24]);
                tileVec[i].nearbyTiles.push_back(&tileVec[i + 1]);
                tileVec[i].nearbyTiles.push_back(&tileVec[i + 26]);
                tileVec[i].nearbyTiles.push_back(&tileVec[i + 25]);
                tileVec[i].nearbyTiles.push_back(&tileVec[i + 24]);
                tileVec[i].nearbyTiles.push_back(&tileVec[i - 1]);
            }
        }
    }

    void Reveal(Tile *tile) {
        revealCount++;
        tile->front.setTexture(textures["revealed"]);
        tile->flag.setTexture(textures["revealed"]);
        if (tile->isMine) {
            tile->flag.setTexture(textures["mine"]);
            for (unsigned int i = 0; i < 400; i++) {
                if (tileVec[i].isMine) {
                    tileVec[i].flag.setTexture(textures["mine"]);
                    tileVec[i].front.setTexture(textures["mine"]);
                    tileVec[i].background.setTexture(textures["revealed"]);

                }
            }
            gameOver = true;

        } else {
            if (tile->MineCounter() == 0) {
                for (unsigned int i = 0; i < tile->nearbyTiles.size(); i++) {
                    if (!tile->nearbyTiles[i]->isClicked && !tile->nearbyTiles[i]->isFlagged) {
                        tile->nearbyTiles[i]->isClicked = true;
                        Reveal(tile->nearbyTiles[i]);
                    }
                }
            } else if (tile->MineCounter() == 1) {
                tile->flag.setTexture(textures["num1"]);
            } else if (tile->MineCounter() == 2) {
                tile->flag.setTexture(textures["num2"]);
            } else if (tile->MineCounter() == 3) {
                tile->flag.setTexture(textures["num3"]);
            } else if (tile->MineCounter() == 4) {
                tile->flag.setTexture(textures["num4"]);
            } else if (tile->MineCounter() == 5) {
                tile->flag.setTexture(textures["num5"]);
            } else if (tile->MineCounter() == 6) {
                tile->flag.setTexture(textures["num6"]);
            } else if (tile->MineCounter() == 7) {
                tile->flag.setTexture(textures["num7"]);
            } else if (tile->MineCounter() == 8) {
                tile->flag.setTexture(textures["num8"]);
            }

        }
        tile->isClicked = true;

    }

    void Flag(Tile *tile) {
        if (!tile->isFlagged && tile->isDebug && tile->isMine) {
            tile->front.setTexture(textures["flag"]);
            tile->flag.setTexture(textures["mine"]);
            tile->background.setTexture(textures["hidden"]);
        } else {

            tile->flag.setTexture(textures["flag"]);

        }
        tile->isFlagged = true;
        flagCount--;
    }

    void Unflag(Tile *tile) {
        if (tile->isFlagged && tile->isDebug && tile->isMine) {
            tile->front.setTexture(textures["hidden"]);
            tile->flag.setTexture(textures["mine"]);
            tile->background.setTexture(textures["revealed"]);
        } else {
            tile->flag.setTexture(textures["hidden"]);
        }
        tile->isFlagged = false;
        flagCount++;
    }

    void Mines() {
        int num;
        for (unsigned int i = 0; i < 50; i++) {
            num = rand() % 400;
            if (!tileVec[num].isMine) {
                tileVec[num].isMine = true;
            } else {
                i--;
            }
        }
    }

    void Debug() {
        for (unsigned int i = 0; i < 400; i++) {
            if (tileVec[i].isMine && !tileVec[i].isFlagged) {
                tileVec[i].flag.setTexture(textures["mine"]);

            } else if (tileVec[i].isMine && tileVec[i].isFlagged) {
                tileVec[i].flag.setTexture(textures["mine"]);
                tileVec[i].front.setTexture(textures["flag"]);
                tileVec[i].background.setTexture(textures["hidden"]);
            }
            tileVec[i].isDebug = true;
        }

    }

    void UnDebug() {
        for (unsigned int i = 0; i < 400; i++) {
            if (tileVec[i].isMine && !tileVec[i].isFlagged) {
                tileVec[i].flag.setTexture(textures["hidden"]);
            } else if (tileVec[i].isMine && tileVec[i].isFlagged) {
                tileVec[i].flag.setTexture(textures["flag"]);
                tileVec[i].front.setTexture(textures["hidden"]);
                tileVec[i].background.setTexture(textures["revealed"]);

            }
            tileVec[i].isDebug = false;
        }

    }

    void Reset() {
        flagCount = 50;
        for (int i = 0; i < 400; i++) {
            tileVec[i].background.setTexture(textures["revealed"]);
            tileVec[i].front.setTexture(textures["hidden"]);
            tileVec[i].flag.setTexture(textures["hidden"]);
            face.setTexture(textures["happy"]);
            gameOver = false;
            gameWon = false;
            tileVec[i].isMine = false;
            tileVec[i].isClicked = false;
            tileVec[i].isFlagged = false;
        }
        revealCount = 0;

    }

    void Test1() {
        flagCount = 1;
        ifstream file("boards/testboard1.brd");
        string board = "";
        string line;
        while (getline(file, line)) {
            board += line;
        }
        for (int i = 0; i < 400; i++) {
            if (board[i] == '1') {
                tileVec[i].isMine = true;
            }
        }

    }

    void Test2() {
        flagCount = 98;
        ifstream file2("boards/testboard2.brd");
        string board2 = "";
        string line2;
        int linecount = 0;
        while (getline(file2, line2)) {
            line2.erase(24, 1);
            board2 += line2;
            linecount++;
            if (linecount == 16) {
                break;
            }
        }
        cout << board2;
        for (int i = 0; i < 400; i++) {
            if (board2[i] == '1') {
                tileVec[i].isMine = true;
            }
        }
        // Neighbors();
    }

    void Test3() {
        flagCount = 83;
        ifstream file3("boards/testboard3.brd");
        string board3 = "";
        string line3;
        int linecount = 0;
        while (getline(file3, line3)) {
            line3.erase(24, 1);
            board3 += line3;
            linecount++;
            if (linecount == 16) {
                break;
            }
        }
        cout << board3;
        for (int i = 0; i < 400; i++) {
            if (board3[i] == '1') {
                tileVec[i].isMine = true;
            }
        }
    }

    int TotalMine() {
        int mines = 0;
        for (int i = 0; i < 400; i++) {
            if (tileVec[i].isMine) {
                mines++;
            }
        }
        return mines;
    }

    int TotalRevealed() {
        int click = 0;
        for (int i = 0; i < 400; i++) {
            if (tileVec[i].isClicked) {
                click++;
            }
        }
        return click;
    }


    Board() {

        LoadTextures();
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 25; j++) {
                //LoadTextures();
                Tile tile1;
                tile1.background.setTexture(textures["revealed"]);
                tile1.front.setTexture(textures["hidden"]);
                tile1.flag.setTexture(textures["hidden"]);
                tile1.background.setPosition(j * 32, i * 32);
                tile1.front.setPosition(j * 32, i * 32);
                tile1.flag.setPosition(j * 32, i * 32);
                tileVec.push_back(tile1);
            }
        }

        Neighbors();
    }


};