#pragma once
class IPlayer
{
public:
	virtual ~IPlayer(){};
	virtual int onClickHandler(int cellPosition) = 0;
	virtual void placeStone(char * const &map) = 0;
	virtual int hasPlayed() const = 0;
	virtual void changeTurn() = 0;
	virtual void wrongMove() = 0;
	virtual int getColor() const = 0;
};