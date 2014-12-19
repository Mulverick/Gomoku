#pragma once

#include "IPlayer.hh"

class Humain : IPlayer
{
public:
	Humain();
	~Humain();
	bool onClickHandler();
	bool asPlayed() const;
	void changeTurn();
	void wrongMove();

private:
	int		_color;
	bool	_played;
};

