#include "Human.hh"
#include "Utils.hh"
#include <iostream>

Human::Human(int color)
{
	_played = -1;
	_turn = (color == WHITE ? true : false);
	_color = color;
}


Human::~Human()
{
}

int Human::onClickHandler(int cellPosition){
	if (_played == -1 && _turn == true)
		_played = cellPosition;
	return _played;
}

void Human::placeStone(char * const &map){
	if (_played != -1)
		map[_played] = _color;
}

void Human::wrongMove(){
	_played = -1;
}

int Human::hasPlayed() const{
	return (_played);
}

void Human::changeTurn(){
	_played = -1;
	_turn = (_turn == true ? false : true);
}

int Human::getColor() const{
	return (_color);
} 