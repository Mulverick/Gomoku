#include "AI.hh"
#include "Utils.hh"
#include <iostream>

AI::AI(int color){
	_thought = false;
	_played = -1;
	_turn = (color == WHITE ? true : false);
	_color = color;
	_weightMap = new int[MAP_SIZE];
	_thinkMap = new char[MAP_SIZE];
}

AI::~AI(){
	delete _weightMap;
	delete _thinkMap;
}

int AI::onClickHandler(int cellPosition){
	return -1;
}

void AI::placeStone(char * const &map){
	if (_played != -1)
		map[_played] = _color;
}

void AI::wrongMove(){
	_played = -1;
}

int AI::hasPlayed() const{
	return (_played);
}

void AI::changeTurn(){
	_played = -1;
	_turn = (_turn == true ? false : true);
}

int AI::getColor() const{
	return (_color);
}

void AI::think(){
	for (int i = 0; i < MAP_SIZE; i++)
	{
		if (_thinkMap[i] != 0)
		{
			//TODO thinking
		}
	}
}

