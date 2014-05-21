#include "Block.h"
using namespace std;

void Block::rotateCW() { //rotate a piece clockwise 
	for (int i = 0; i < MAXDIM; ++i) {
		int tempx = blocklocation[i].x;
		blocklocation[i].x = blocklocation[i].y;
		blocklocation[i].y = 1 - (tempx - (maxDimension - 2));

		updateShape();
	}
}

void Block::rotateCCW() { //rotate a piece counterclockwise
	for (int i = 0; i < MAXDIM; ++i) {
		int tempy = blocklocation[i].y;
		blocklocation[i].y = blocklocation[i].x;
		blocklocation[i].x = 1 - (tempy - (maxDimension - 2));

		updateShape();
	}
}

Coordinate Block::getBlockLocation(int indice) {
	return blocklocation[indice];
}

Cell Block::getShape(int indiceX, int indiceY) {
	return shape[indiceX][indiceY];
}

sf::Color Block::getColour() {
	return shape[0][0].getColour();
}

int Block::getMaxDim() {
	return maxDimension;
}

IBlock::IBlock() : Block(sf::Color::Cyan) {
	blocklocation[0].set(0, 0); //initial block configuration
	blocklocation[1].set(1, 0);
	blocklocation[2].set(2, 0);
	blocklocation[3].set(3, 0);
	maxDimension = 4;
	updateShape();
}

JBlock::JBlock(): Block(sf::Color::Blue) {
	blocklocation[0].set(0, 0);
	blocklocation[1].set(0, 1);
	blocklocation[2].set(1, 0);
	blocklocation[3].set(2, 0);
	maxDimension = 3;
	updateShape();
}

LBlock::LBlock(): Block(sf::Color(255, 153, 0)) { //orange
	blocklocation[0].set(0, 0);
	blocklocation[1].set(1, 0);
	blocklocation[2].set(2, 0);
	blocklocation[3].set(2, 1);
	maxDimension = 3;
	updateShape();
}

OBlock::OBlock(): Block(sf::Color::Yellow) {
	blocklocation[0].set(0, 0);
	blocklocation[1].set(0, 1);
	blocklocation[2].set(1, 0);
	blocklocation[3].set(1, 1);
	maxDimension = 2;
	updateShape();
}

SBlock::SBlock(): Block(sf::Color::Green) {
	blocklocation[0].set(0, 0);
	blocklocation[1].set(1, 0);
	blocklocation[2].set(1, 1);
	blocklocation[3].set(2, 1);
	maxDimension = 3;
	updateShape();
}

ZBlock::ZBlock(): Block(sf::Color::Red) {
	blocklocation[0].set(0, 1);
	blocklocation[1].set(1, 1);
	blocklocation[2].set(1, 0);
	blocklocation[3].set(2, 0);
	maxDimension = 3;
	updateShape();
}

TBlock::TBlock(): Block(sf::Color::Magenta) {
	blocklocation[0].set(0, 1);
	blocklocation[1].set(1, 1);
	blocklocation[2].set(1, 0);
	blocklocation[3].set(2, 1);
	maxDimension = 3;
	updateShape();
}

Block::Block(sf::Color colour) { //ctor, sets colour of block
	for (int i = 0; i < MAXDIM; ++i) {
		for (int j = 0; j < MAXDIM; ++j) {
			shape[i][j].setState(false);
			shape[i][j].setColour(colour);
		}
	}
}

void Block::updateShape() { //update configuration of block when we rotate
	for (int i = 0; i < MAXDIM; ++i) {
		for (int j = 0; j < MAXDIM; ++j) {
			shape[i][j].setState(false);
		}
	}
	for (int i = 0; i < MAXDIM; ++i) {
		shape[blocklocation[i].x][blocklocation[i].y].setState(true);
	}
}