#include "AI.hh"
#include "Utils.hh"
#include <iostream>
#include <vector>
#include <cstdlib> 
#include <ctime>

AI::AI(int color){
	_thought = false;
	_played = -1;
	_turn = (color == WHITE ? true : false);
	_color = color;
	_weightMap = new int[MAP_SIZE];
	_thinkMap = new char[MAP_SIZE];
	for (int i = 0; i < MAP_SIZE; ++i)
	{
		_thinkMap[i] = 0;
		_weightMap[i] = 0;
	}
	srand(time(NULL));
	_thread = std::thread(&AI::think);
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
	int	currColor = _color;
	char*	map = new char[MAP_SIZE];
	int	r;
	bool win = false;

	for (int j = 0; j < MAP_SIZE; ++j)
	{
		_weightMap[j] = 0;
		for (int i = 0; i < AI_THINK; ++i)
		{
			strcpy(map, _thinkMap);
			r = j;
			while (!_arbitre.checkWinner(r, map, currColor))
			{
				if (_arbitre.checkMove(r, map, currColor))
				{
					map[r] = currColor;
					currColor = (currColor == WHITE ? BLACK : WHITE);
				}
				r = (rand() % MAP_SIZE);
			}
			_weightMap[j] += (_arbitre.checkWinner(r, map, _color) == true ? 1 : -1);
		}
	}
	_thought = true;
}

int AI::onPlay(char * const &map){
	int		best = 0;
	_thread.join();

	for (int i = 0; i < MAP_SIZE; i++){
		if (_weightMap[i] > best && _arbitre.checkMove(i, map, _color))
		{
			best = _weightMap[i];
			_played = i;
		}
	}
	strcpy(_thinkMap, map);
	_thread = std::thread(&AI::think);
	return _played;
}
