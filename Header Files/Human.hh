#pragma once

#include "IPlayer.hh"

class Human : public IPlayer
{
public:
	Human(int color);
	~Human();
	int onClickHandler(int cellPosition);
	void placeStone(char * const &map);
	int hasPlayed() const;
	void changeTurn();
	void wrongMove();
	int  getColor() const;
private:
	int		_color;
	bool	_turn;
	int	_played;
};

