#pragma once

enum Type
{
	HUMAN,
	OTHER
};

class IPlayer
{
public:
	virtual ~IPlayer(void) {}

	virtual int		onClickHandler(int cellPosition) = 0;
	virtual void	placeStone(char *map) = 0;

	virtual void	changeTurn(void) = 0;
	virtual void	wrongMove(void) = 0;

	virtual int	hasPlayed(void) const = 0;
	virtual int		getColor(void) const = 0;
	virtual Type	getType(void) const = 0;
};