#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace sf; 

void leaderboard(RenderWindow& arkanoid) {

	Texture sBg, Lbmenu1;
	sBg.loadFromFile("images/LbBg.png");
	Lbmenu1.loadFromFile("images/Back.png");

	Font font;
	font.loadFromFile("ScoreFont.ttf");
	Text text2("", font, 50);

	Sprite LbBg(sBg), exitButton(Lbmenu1);

	bool LbMenu = 1;
	int LbNum = 0;
	LbBg.setPosition(0, 0);
	exitButton.setPosition(966, 648);

	while (LbMenu)
	{
		exitButton.setColor(Color::White);
		
		LbMenu = true;

		LbNum = 0;

		arkanoid.clear();

		if (IntRect(966, 648, 300, 100).contains(Mouse::getPosition(arkanoid))) {  exitButton.setColor(Color(180, 180, 180)); LbNum = 1; }
		if (Mouse::isButtonPressed(Mouse::Left))
		{if (LbNum == 1) LbMenu = false;}

		arkanoid.draw(LbBg);
		arkanoid.draw(exitButton);

		std::string line;

		std::ifstream first("resources/Firstplace.TXT");
		if (first.is_open())
		{
			while (getline(first, line, '-'))
			{
				std::ostringstream Top1;
				Top1 << line;
				text2.setString("Top high score\n1. " + Top1.str());
				text2.setPosition(50, 50);
				arkanoid.draw(text2);
			}
		}
		first.close();


		std::string line_;

		std::ifstream second("resources/Secondplace.TXT");
		if (second.is_open())
		{
			while (getline(second, line_, '-'))
			{
				std::ostringstream Top2;
				Top2 << line_;
				text2.setString("3. " + Top2.str());
				text2.setPosition(50, 150);
				arkanoid.draw(text2);
			}
		}
		second.close();


		std::string line__;

		std::ifstream third("resources/Thirdplace.TXT");
		if (third.is_open())
		{
			while (getline(third, line__, '-'))
			{
				std::ostringstream Top3;
				Top3 << line__;
				text2.setString("3. " + Top3.str());
				text2.setPosition(50, 200);
				arkanoid.draw(text2);
			}
		}
		third.close();

		arkanoid.display();
	}

}