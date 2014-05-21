#include "Board.h"
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

void Board::clearRow(int row) {
	for (int j = 0; j < WIDTH; ++j) {
		grid[j][row].setState(false);
	}
}

void Board::shiftBoardDown(int row) {
	for (int i = row; i < HEIGHT; ++i) {
		for (int j = 0; j < WIDTH; ++j)
			grid[j][i] = grid[j][i+1];
	}
}

void Board::calculateDifficulty() {
	if (rowsCleared % 5 == 0) {
		rowsCleared++;
		timeInterval *= 0.9f;
	}
}

void Board::drawRectangle(int x, int y, int width, int height, sf::Color colour, sf::RenderWindow &window) {
	sf::RectangleShape shape(sf::Vector2f(width, height));
	//shape.setPosition(sf::Vector2f(x, y));
	shape.setOrigin(sf::Vector2f(0, -WINDOWHEIGHT)); //origin in lower left corner
	shape.move(sf::Vector2f(x, -y)); //interpret coordinates as positive x,y
	shape.setFillColor(colour);
	shape.setOutlineThickness(1);
	shape.setOutlineColor(sf::Color::White);
	window.draw(shape);
}

void Board::printText(int x, int y, string printthis, sf::Font &font, sf::RenderWindow &window) {
	sf::Text text;
	text.setOrigin(sf::Vector2f(0, -WINDOWHEIGHT));
	text.move(sf::Vector2f(x, -y));
	text.setFont(font);
	text.setString(printthis);
	text.setCharacterSize(18);
	text.setColor(sf::Color::White);
	window.draw(text);
}

Board::Board() {
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			grid[j][i].setState(false);
			grid[j][i].setColour(sf::Color::Black);
		}
	}
	timeInterval = LEVEL1TIME;
	rowsCleared = 0;
}

Board::~Board() {
	if (currentBlock)
		delete currentBlock;
}

void Board::spawnBlock() {
	srand(static_cast<unsigned int>(time(NULL)));
	int randomNum = rand() % 7;
	switch (randomNum) {
	case 0:
		currentBlock = new IBlock();
		break;
	case 1:
		currentBlock = new JBlock();
		break;
	case 2:
		currentBlock = new LBlock();
		break;
	case 3:
		currentBlock = new OBlock();
		break;
	case 4:
		currentBlock = new SBlock();
		break;
	case 5:
		currentBlock = new ZBlock();
		break;
	default:
		currentBlock = new TBlock();
		break;
	}
	currentx = (WIDTH / 2) - 1;
	currenty = HEIGHT - MAXDIM/2;
}

void Board::clearRows() {
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			if (!grid[j][i].isOn())
				break;
			else if ( (j == (WIDTH - 1)) && (grid[j][i].isOn()) ) { //row is completely filled
				clearRow(i);
				shiftBoardDown(i);
				rowsCleared++;
				calculateDifficulty();
			}
		}
	}
}

void Board::addBlock() {
	for (int i = 0; i < MAXDIM; ++i) {
		for (int j = 0; j < MAXDIM; ++j) {
			Coordinate piece = currentBlock->getBlockLocation(i);
			grid[piece.x + currentx][piece.y + currenty] = currentBlock->getShape(piece.x, piece.y);
		}		
	}
	delete currentBlock;
}

void Board::move(string move) {
	if (move == "left")
		currentx--;
	else if (move == "right")
		currentx++;
	else if (move == "down")
		currenty--;
	else if (move == "rotateCW")
		currentBlock->rotateCW();
	else if (move == "rotateCCW")
		currentBlock->rotateCCW();
}

bool Board::checkCollision(string move) {
	int tmpX = currentx;
	int tmpY = currenty;
	Block *tmpBlock = new Block(*currentBlock);

	if (move == "left") {
		tmpX--;
	}
	else if (move == "right") {
		tmpX++;
	}
	else if (move == "down") {
		tmpY--;
	}
	else if (move == "rotateCW")
		tmpBlock->rotateCW();
	else if (move == "rotateCCW")
		tmpBlock->rotateCCW();

	for (int i = 0; i < MAXDIM; ++i) {
		Coordinate piece = tmpBlock->getBlockLocation(i);
		if (tmpX + piece.x < 0 || tmpX + piece.x > WIDTH - 1 || tmpY + piece.y < 0) {
			delete tmpBlock;
			return true;
		}
		if (grid[tmpX + piece.x][tmpY + piece.y].isOn()) {
			delete tmpBlock;
			return true;
		}
	}
	delete tmpBlock;
	return false;
}

bool Board::hasBlock() {
	if (currentBlock)
		return true;
	return false;
}

float Board::getTime() {
	return timeInterval;
}

bool Board::gameOver() {
	for (int i = 0; i < MAXDIM; ++i) {
		Coordinate piece = currentBlock->getBlockLocation(i);
		if (grid[currentx + piece.x][currenty + piece.y].isOn()) {
			return true;
		}
	}
	for (int i = HEIGHT; i < HEIGHT + MAXDIM; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			if (grid[j][i].isOn())
				return true;
		}
	}
	return false;
}

void Board::updateWindow(sf::RenderWindow &window, sf::Font &font) {
	int height = (WINDOWHEIGHT * SCALEWINDOW / HEIGHT); //height/width of each block in grid
	int width = (WINDOWWIDTH * SCALEWINDOW / HEIGHT);
	int y = ((WINDOWHEIGHT / 2) - ((HEIGHT / 2) * height)); //finding screen location for grid
	int x = (WINDOWWIDTH / 4) - ((WIDTH / 4) * width);
	window.clear(sf::Color::Black);

	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			if (grid[j][i].isOn())
				drawRectangle(x + (width * j), y + (height * i), width, height, grid[j][i].getColour(), window);
			else
				drawRectangle(x + (width * j), y + (height * i), width, height, sf::Color::Black, window);
			if ((j >= currentx && j < currentx + MAXDIM) && (i >= currenty && i < currenty + MAXDIM)) {
				if (currentBlock->getShape(j - currentx, i - currenty).isOn()) {
					drawRectangle(x + (width * j), y + (height * i), width, height, currentBlock->getColour(), window);
				}
			}
		}
	}

	string level = to_string(rowsCleared / 5 + 1);
	string printlevel = "Level: " + level;
	string rows = to_string(rowsCleared);
	string printRowsCleared = "Lines: " + rows;
	string instructions = "Movement: Arrow Keys\nRotate: Z X";
	printText(x + (width * (WIDTH + 1)), y + (height * HEIGHT), printlevel, font, window);
	printText(x + (width * (WIDTH + 1)), y + (height * (HEIGHT - 1)), printRowsCleared, font, window);
	printText(x + (width * (WIDTH + 1)), y + (height * (HEIGHT - 3)), instructions, font, window);
}