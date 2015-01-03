#pragma once

#include "IPlayer.hh"

class Human : public IPlayer
{
public:
	Human(int color);
	~Human();
	int onClickHandler(int cellPosition);
	void placeStone(char *map);
	int hasPlayed() const;
	void changeTurn();
	void wrongMove();
	int	 getColor() const;
	Type getType() const;
private:
	int		_color;
	bool	_turn;
	int		_played;
	Type	_type;
};

