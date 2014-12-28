#include "Human.hh"
#include "Utils.hh"
#include <iostream>

Human::Human(int color)
{
	_played = false;
	_turn = (color == WHITE ? true : false);
	_color = color;
}


Human::~Human()
{
}

bool Human::onClickHandler(char * const &map, int cellPosition){
	if (map[cellPosition])
		return _played;
	map[cellPosition] = _color;
	if (_played == false && _turn == true)
		_played = true;
	return _played;
}

void Human::wrongMove(){
	_played = false;
}

bool Human::hasPlayed() const{
	return (_played);
}

void Human::changeTurn(){
	_played = false;
	_turn = (_turn == true ? false : true);
}

int Human::getColor() const{
	return (_color);
} 