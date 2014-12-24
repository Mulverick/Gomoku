#include "Human.hh"

Human::Human(int color)
{
	_played = false;
	_turn = false;
	_color = color;
}


Human::~Human()
{
}

bool Human::onClickHandler(){
	if (_played == false && _turn == true)
		_played = true;
	return _played;
}

void Human::wrongMove(){
	_played = false;
}

bool Human::asPlayed() const{
	return (_played);
}

void Human::changeTurn(){
	_played = false;
	_turn = (_turn == true ? false : true);
}