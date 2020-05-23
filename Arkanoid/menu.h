#include <SFML/Graphics.hpp>
using namespace sf;

void menu(RenderWindow& arkanoid) {
	Texture sMenuButton1, sMenuButton2, sMenuButton3, sBackground;
	sMenuButton1.loadFromFile("images/menu1.png");
	sMenuButton2.loadFromFile("images/menu2.png");
	sMenuButton3.loadFromFile("images/menu3.png");
	sBackground.loadFromFile("images/menubackground.jpg");

	Sprite menu1(sMenuButton1), menu2(sMenuButton2), menu3(sMenuButton3), menuBg(sBackground);

	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(100, 100);
	menu2.setPosition(100, 200);
	menu3.setPosition(100, 300);
	menuBg.setPosition(0, 0);

	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu1.setScale(int(1), int(1));

		menu2.setColor(Color::White);
		menu2.setScale(int(1), int(1));

		menu3.setColor(Color::White);
		menu3.setScale(int(1), int(1));

		menuNum = 0;

		arkanoid.clear();

		if (IntRect(100, 100, 300, 100).contains(Mouse::getPosition(arkanoid))) { menu1.setScale(double(1.05), double(1.05)); menu1.setColor(Color(180, 180, 180)); menuNum = 1; }
		if (IntRect(100, 200, 600, 100).contains(Mouse::getPosition(arkanoid))) { menu2.setScale(double(1.05), double(1.05)); menu2.setColor(Color(180, 180, 180)); menuNum = 2; }
		if (IntRect(100, 300, 300, 100).contains(Mouse::getPosition(arkanoid))) { menu3.setScale(double(1.05), double(1.05)); menu3.setColor(Color(180, 180, 180)); menuNum = 3; }
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false; 
			if (menuNum == 3) { arkanoid.close(); isMenu = false; }
		}

		arkanoid.draw(menuBg);
		arkanoid.draw(menu1);
		arkanoid.draw(menu2);
		arkanoid.draw(menu3);

		arkanoid.display();
	}

}
