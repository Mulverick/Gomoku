#pragma once

#include "Utils.hh"

enum Type
{
	HUMAN,
	OTHER
};

class IPlayer
{
public:
	virtual ~IPlayer(void) {}

	virtual Vector<int> const	&onClickHandler(Vector<int> const &cellPosition) = 0;
	virtual void	placeStone(char * const *map) = 0;

	virtual void	changeTurn(void) = 0;
	virtual void	wrongMove(void) = 0;

	virtual Vector<int> const	&hasPlayed(void) const = 0;
	virtual int					getColor(void) const = 0;
	virtual Type				getType(void) const = 0;
};