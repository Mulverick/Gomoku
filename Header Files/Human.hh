#pragma once

#include "IPlayer.hh"

class Human : public IPlayer
{
public:
	Human(int color);
	~Human();
	bool onClickHandler(char * const &map, int cellPosition);
	bool hasPlayed() const;
	void changeTurn();
	void wrongMove();
	int  getColor() const;
private:
	int		_color;
	bool	_turn;
	bool	_played;
};

