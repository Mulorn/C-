#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "menu.h"
#include "sorting.h"
using namespace sf;

int main()
{
    srand(time(NULL));

    RenderWindow arkanoid(VideoMode(1366, 768), "Arkanoid");
    arkanoid.setFramerateLimit(60);

    Font font;
    font.loadFromFile("ScoreFont.ttf");
    Text text1("", font, 20);

    Texture t1, t2, t3, t4, t5, t6, t7, t8, t9, t10;
    t1.loadFromFile("images/background.jpg");
    t2.loadFromFile("images/ball.png");
    t3.loadFromFile("images/block01.png");
    t4.loadFromFile("images/block02.png");
    t5.loadFromFile("images/block03.png");
    t6.loadFromFile("images/block04.png");
    t7.loadFromFile("images/block05.png");
    t8.loadFromFile("images/paddle.png");
    t9.loadFromFile("images/lose.png");
    t10.loadFromFile("images/Win.png");

    Sprite sBackground(t1), sBall(t2), sPaddle(t8), sLose(t9), sWin(t10);
    sPaddle.setPosition(600, 740);

    Sprite block[1000];

    int n = 0;
    for (int i = 1; i <= 13; i++)
        for (int j = 1; j <= 1; j++) {
            block[n].setTexture(t3);
            block[n].setPosition(i * 102 - 77, j * 50 - 20);
            n++;
        }

    for (int i = 1; i <= 13; i++)
        for (int j = 2; j <= 2; j++) {
            block[n].setTexture(t4);
            block[n].setPosition(i * 102 - 65, j * 50 - 20);
            n++;
        }

    for (int i = 1; i <= 13; i++)
        for (int j = 3; j <= 3; j++) {
            block[n].setTexture(t5);
            block[n].setPosition(i * 102 - 77, j * 50 - 20);
            n++;
        }

    for (int i = 1; i <= 13; i++)
        for (int j = 4; j <= 4; j++) {
            block[n].setTexture(t6);
            block[n].setPosition(i * 102 - 65, j * 50 - 20);
            n++;
        }

    for (int i = 1; i <= 13; i++)
        for (int j = 5; j <= 5; j++) {
            block[n].setTexture(t7);
            block[n].setPosition(i * 102 - 77, j * 50 - 20);
            n++;
        }

    float dx = 0, dy = 0, ex = dx, ey = dy, blocks = 1;
    float x = 650, y = 650;
    int b = 10, bonus = 0, sc = 1, clear = -1;
    bool sorting_ = 1;

    Clock clock;
    Clock gameTimeClock;
    float gameTime = 1;

    ofstream out;
    out.open("resources/Fourthplace.TXT");
    if (out.is_open())
    {
        out << clear;
    }

    while (arkanoid.isOpen())
    {
        Event e;
        while (arkanoid.pollEvent(e)) {
            if (e.type == Event::Closed)
                arkanoid.close();

            if (e.type == Event::KeyPressed)
                if ((e.key.code == Keyboard::R)) {


                    switch (sorting_) {

                    case true: {
                        sorting();
                        sorting_ = false;
                        break;
                    }
                    case false: {
                        sorting_ = true;
                        break;
                        }
                    }
                }
        }

        float time = clock.getElapsedTime().asMicroseconds();

        if (dx != 0) gameTime = gameTimeClock.getElapsedTime().asSeconds();
        clock.restart();
        time = time / 800;

        x += dx;
        for (int i = 0; i < n; i++)
            if (FloatRect(x + 12.5, y + 12.5, 25, 25).intersects(block[i].getGlobalBounds()))
            {
                dx = -dx;
                block[i].setPosition(-500, 0);
                blocks++;
            }

        y += dy;
        for (int i = 0; i < n; i++)
            if (FloatRect(x + 12.5, y + 12.5, 25, 25).intersects(block[i].getGlobalBounds()))
            {
                dy = -dy;
                block[i].setPosition(-500, 0);
                blocks++;
            }

        if (x < -15 || x>1323)  dx = -dx;
        if (y < -15)  dy = -dy;

        sc = (blocks * 10)*(blocks * 10)/gameTime + bonus - 500;

        if (Keyboard::isKeyPressed(Keyboard::Right)) sPaddle.move(b, 0);

        if (FloatRect(1424, 748, 58, 20).intersects(sPaddle.getGlobalBounds()))
        {
            sPaddle.setPosition(-58, 740);
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) sPaddle.move(-b, 0);

        if (FloatRect(-116, 748, 58, 20).intersects(sPaddle.getGlobalBounds()))
        {
            sPaddle.setPosition(1308, 740);
            blocks++;
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape)) { menu(arkanoid); 
        ex = dx; 
        ey = dy; 
        dx = 0; 
        dy = 0;
        }

        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            if (ex == 0) ex = 3;
            if (ey == 0) ey = -4;
            if (dx == 0) dx = ex;
            if (dy == 0) dy = ey;
        }

        if (blocks > 10 && dx > 0 && dy > 0) { dx = 5; dy = 6; }
        if (blocks > 25 && dx > 0 && dy > 0) { dx = 6; dy = 7; }
        if (blocks > 50 && dx > 0 && dy > 0) { dx = 7; dy = 8; }

        if (FloatRect(x + 12.5, y + 12.5, 25, 25).intersects(sPaddle.getGlobalBounds())) dy = -(rand() % 5 + 2);

        sBall.setPosition(x, y);
        sLose.setPosition(423, 239);
        sWin.setPosition(423, 210);

        arkanoid.clear();
        arkanoid.draw(sBackground);
        arkanoid.draw(sBall);
        arkanoid.draw(sPaddle);

        for (int i = 0; i < n; i++)
            arkanoid.draw(block[i]);

        if (blocks <= 66) bonus = 500;

        if (y > 768) {
            arkanoid.draw(sLose);
            b = 0;
            dx = 0; dy = 0;
            text1.setString("              Your score is: " + std::to_string(sc) + "\nTap 'R' to refresh the leaderboard");
            text1.setPosition(520, 550);
            arkanoid.draw(text1);
            
            ofstream out;
            out.open("resources/Fourthplace.TXT");
            if (out.is_open())
            {
                out << sc;
            }
        }

        if (blocks == 66) {
            arkanoid.draw(sWin);
            b = 0;
            dx = 0; dy = 0;
            text1.setString("              Your score is: " + std::to_string(sc) + "\nTap 'R' to refresh the leaderboard");
            text1.setPosition(520, 620);
            arkanoid.draw(text1);

            ofstream out;
            out.open("resources/Fourthplace.TXT");
            if (out.is_open())
            {
                out << sc;
            }
        }

        arkanoid.display();
    }

    return 0;
}

