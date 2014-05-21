#ifndef __CELL_H__
#define __CELL_H__

#include <SFML\Graphics\Color.hpp>

class Cell {
	bool state;
	sf::Color colour;
public:
	Cell(bool state = 0, sf::Color colour = sf::Color::Black);	//default values off, black (empty cell)
	void setState(bool state = 0);	//set state on or off
	void setColour(sf::Color colour = sf::Color::Black);	//set colour
	bool isOn();	//get the state of cell
	sf::Color getColour();	//get the colour of cell
};

#endif