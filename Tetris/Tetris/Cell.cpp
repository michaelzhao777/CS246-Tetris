#include "Cell.h"
using namespace std;

Cell::Cell(bool state, sf::Color colour) : state(state), colour(colour) {}

void Cell::setState(bool state) {
	this->state = state;
}

void Cell::setColour(sf::Color colour) {
	this->colour = colour;
}

bool Cell::isOn() { return state; }

sf::Color Cell::getColour() { return colour; }