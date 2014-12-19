#include "Humain.hh"


Humain::Humain()
{
}


Humain::~Humain()
{
}

bool Humain::onClickHandler(){
	_played = true;
	return _played;
}

void Humain::wrongMove(){
	_played = false;
}

bool Humain::asPlayed() const{
	return (_played);
}

void Humain::changeTurn(){
	_played = false;
}
