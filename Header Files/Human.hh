#pragma once

#include "IPlayer.hh"

class Human : public IPlayer
{
public:
	Human(int color);
	~Human();
	bool onClickHandler();
	bool asPlayed() const;
	void changeTurn();
	void wrongMove();

private:
	int		_color;
	bool	_turn;
	bool	_played;
};

