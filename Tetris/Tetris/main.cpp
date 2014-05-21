#include "Board.h"
using namespace std;

int main() {
	Board b;

	sf::RenderWindow window(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "Tetris");
	sf::Clock clock; //create window and clock instance
	sf::Font font;
	font.loadFromFile("arial.ttf");

	while (window.isOpen()) {
		if (!b.hasBlock()) //spawn block if there is not a current one
			b.spawnBlock();

		sf::Event event;
		while (window.pollEvent(event)) //handle user input
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Left) {
					if (!b.checkCollision("left"))
							b.move("left");
					}
				else if (event.key.code == sf::Keyboard::Right) {
					if (!b.checkCollision("right"))
						b.move("right");
				}
				else if (event.key.code == sf::Keyboard::Down) {
					if (!b.checkCollision("down"))
						b.move("down");
					else {
						b.addBlock();
						b.spawnBlock();
					}
				}
				else if (event.key.code == sf::Keyboard::Z) {
					if (!b.checkCollision("rotateCCW"))
						b.move("rotateCCW");
				}
				else if (event.key.code == sf::Keyboard::X) {
					if (!b.checkCollision("rotateCW"))
						b.move("rotateCW");
				}
			}
		}

		sf::Time elapsed = clock.getElapsedTime(); //check for elapsed time to shift piece down
		if (elapsed > sf::seconds(b.getTime())) {
			if (!b.checkCollision("down")) {
				b.move("down");
			}
			else {
				b.addBlock();
				b.spawnBlock();
			}
			clock.restart();
		}

		if (b.gameOver()) { //check for game over
			window.close();
		}
		b.clearRows(); //clear any complete rows
		b.updateWindow(window, font); //update the window
		window.display(); //display updated window
	}
	return 0;
}