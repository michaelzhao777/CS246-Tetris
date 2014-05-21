#ifndef __BOARD_H__
#define __BOARD_H__
#include "Block.h"
#include <string>
#include <SFML\Graphics.hpp>

const int WIDTH = 10; //Width of game board
const int HEIGHT = 20; //Height of game board, >= width.
const int ROWSTOLEVEL = 5; //How many rows must be cleared to level up
const float LEVEL1TIME = 0.5f; //time interval at level 1. becomes LEVEL1TIME * 0.9^(level) as levels increase

const int WINDOWWIDTH = 800; //window attributes
const int WINDOWHEIGHT = 600;
const float SCALEWINDOW = 0.8f; //size of tetris grid relative to window size

class Board {
	Cell grid[WIDTH][HEIGHT + MAXDIM]; //HEIGHT + MAXDIM gives us invisible rows at top for block spawning
	Block *currentBlock;
	int currentx, currenty;
	float timeInterval;
	int rowsCleared;

	void clearRow(int row); //clear a row given its height
	void shiftBoardDown(int row); //shift board down starting at given row height
	void calculateDifficulty(); //updates timeInterval
	void drawRectangle(int x, int y, int width, int height, sf::Color colour, sf::RenderWindow &window); //draw a rectangle to a window at (x,y) with (width, height)
	void printText(int x, int y, std::string printthis, sf::Font &font, sf::RenderWindow &window);
public:
	Board();
	~Board();
	void spawnBlock(); //spawn a random block
	void clearRows(); //clear rows that are full
	void addBlock(); //add block to where it currently is on grid
	void move(std::string move); //move = "left", "right", "down", "rotateCW", "rotateCCW"
	bool checkCollision(std::string move); // ""
	bool hasBlock(); //check if board has a block
	float getTime(); //get current time interval per drop
	bool gameOver();

	void updateWindow(sf::RenderWindow &window, sf::Font &font); //draw board state to a window
};

#endif