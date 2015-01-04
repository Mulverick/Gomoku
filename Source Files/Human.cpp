#include "Human.hh"
#include "Utils.hh"
#include <iostream>

Human::Human(int color)
{
	_played.x = -1;
	_played.y = -1;
	_turn = (color == BLACK ? true : false);
	_color = color;
	_type = HUMAN;
}


Human::~Human()
{
}

Vector<int> const &Human::onClickHandler(Vector<int> const &cellPosition){
	if (_played.x == -1 && _turn == true)
		_played = cellPosition;
	return _played;
}

void Human::placeStone(char * const *map){
	if (_played.x != -1)
		map[_played.y][_played.x] = _color;
}

void Human::wrongMove(){
	_played.x = -1;
}

Vector<int> const	&Human::hasPlayed(void) const { return (_played); }

void Human::changeTurn(){
	_played.x = -1;
	_turn = (_turn == true ? false : true);
}

int Human::getColor() const{
	return (_color);
}

Type Human::getType() const{
	return (_type);
}