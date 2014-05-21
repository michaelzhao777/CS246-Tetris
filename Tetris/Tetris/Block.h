#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "Coordinate.h"
#include "Cell.h"

const int MAXDIM = 4; //maximum possible dimension of a block (default is IBlock, 4x1)

class Block {
protected:
	Cell shape[MAXDIM][MAXDIM];
	int maxDimension; //max(length,width) of block
	Coordinate blocklocation[MAXDIM]; //which cells in shape are on

	Block(sf::Color colour = sf::Color::Black);
	void updateShape(); //update the shape after rotation
public:
	void rotateCW();	//rotate piece clockwise
	void rotateCCW();	//rotate piece counterclockwise
	Coordinate getBlockLocation(int indice); //return a coordinate at blocklocation[indice]
	Cell getShape(int indiceX, int indiceY);
	sf::Color getColour();	//get colour of block
	int getMaxDim();		//get maxDimension of block
};

class IBlock : public Block{ //straight block
public:
	IBlock();
};

class JBlock : public Block{ //inverse L
public:
	JBlock();
};

class LBlock : public Block{ //L block
public:
	LBlock();
};

class OBlock : public Block{ //square block
public:
	OBlock();
};

class SBlock : public Block{ // __--
public:
	SBlock();
};

class ZBlock : public Block{ // --__
public:
	ZBlock();
};

class TBlock : public Block{ // T shape
public:
	TBlock();
};

#endif