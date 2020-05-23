#include <SFML/Graphics.hpp>
#include "menu.h"
#include "lose.h"
using namespace sf;

int main()
{
    srand(time(NULL));

    RenderWindow arkanoid(VideoMode(1366, 768), "Arkanoid");
    menu(arkanoid);
    arkanoid.setFramerateLimit(60);

    Texture t1, t2, t3, t4, t5, t6, t7, t8;
    t1.loadFromFile("images/background.jpg");
    t2.loadFromFile("images/ball.png");
    t3.loadFromFile("images/block01.png");
    t4.loadFromFile("images/block02.png");
    t5.loadFromFile("images/block03.png");
    t6.loadFromFile("images/block04.png");
    t7.loadFromFile("images/block05.png");
    t8.loadFromFile("images/paddle.png");
    

    Sprite sBackground(t1), sBall(t2), sPaddle(t8);
    sPaddle.setPosition(600, 740);

    Sprite block[1000];

    int n = 0, min = -3, max = 3;
    for (int i = 1; i <= 14; i++)
        for (int j = 1; j <= 1; j++) {
            block[n].setTexture(t3);
            block[n].setPosition(i * 95 - 77, j * 50 - 30);
            n++;
        }

    for (int i = 1; i <= 14; i++)
        for (int j = 2; j <= 2; j++) {
            block[n].setTexture(t4);
            block[n].setPosition(i * 95 - 65, j * 50 - 30);
            n++;
        }

    for (int i = 1; i <= 14; i++)
        for (int j = 3; j <= 3; j++) {
            block[n].setTexture(t5);
            block[n].setPosition(i * 95 - 77, j * 50 - 30);
            n++;
        }

    for (int i = 1; i <= 14; i++)
        for (int j = 4; j <= 4; j++) {
            block[n].setTexture(t6);
            block[n].setPosition(i * 95 - 65, j * 50 - 30);
            n++;
        }

    for (int i = 1; i <= 14; i++)
        for (int j = 5; j <= 5; j++) {
            block[n].setTexture(t7);
            block[n].setPosition(i * 95 - 77, j * 50 - 30);
            n++;
        }

    float dx = 3, dy = 4, b = 10, score = 0;
    float x = 650, y = 650;

    while (arkanoid.isOpen())
    {
        Event e;
        while (arkanoid.pollEvent(e)) {
            if (e.type == Event::Closed)
                arkanoid.close();
        }

        x += dx;
        for (int i = 0; i < n; i++)
            if (FloatRect(x + 12.5, y + 12.5, 25, 25).intersects(block[i].getGlobalBounds()))
            {
                dx = -dx;
                block[i].setPosition(-500, 0);
            }

        y += dy;
        for (int i = 0; i < n; i++)
            if (FloatRect(x + 12.5, y + 12.5, 25, 25).intersects(block[i].getGlobalBounds()))
            {
                dy = -dy;
                block[i].setPosition(-500, 0); 
            }

        if (x < -15 || x>1323)  dx = -dx;
        if (y < -15)  dy = -dy;
        if (y > 768) {
            arkanoid.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Right)) sPaddle.move(b, 0);

        if (FloatRect(1424, 748, 58, 20).intersects(sPaddle.getGlobalBounds()))
        {
            sPaddle.setPosition(-58, 740);
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) sPaddle.move(-b, 0);

        if (FloatRect(-116, 748, 58, 20).intersects(sPaddle.getGlobalBounds()))
        {
            sPaddle.setPosition(1308, 740);
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape)) menu(arkanoid);


        if (FloatRect(x + 12.5, y + 12.5, 25, 25).intersects(sPaddle.getGlobalBounds())) dy = -(rand() % 5 + 2);

        sBall.setPosition(x, y);

        arkanoid.clear();
        arkanoid.draw(sBackground);
        arkanoid.draw(sBall);
        arkanoid.draw(sPaddle);

        for (int i = 0; i < n; i++)
            arkanoid.draw(block[i]);

        arkanoid.display();
    }

    return 0;
}