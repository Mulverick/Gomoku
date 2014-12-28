#pragma once
class IPlayer
{
public:
	virtual ~IPlayer(){};
	virtual bool onClickHandler(char * const &map, int cellPosition) = 0;
	virtual bool hasPlayed() const = 0;
	virtual void changeTurn() = 0;
	virtual void wrongMove() = 0;
	virtual int getColor() const = 0;
};