#include <SFML/Graphics.hpp>
using namespace sf;

void lose(RenderWindow& arkanoid) {
	Texture slose;
	slose.loadFromFile("images/lose.png");
		
	Sprite _lose(slose);

	bool lose_ = 1;
	_lose.setPosition(0, 0);
	

	while (lose_)
	{
		
	}
}