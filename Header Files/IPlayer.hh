#pragma once
class IPlayer
{
public:
	virtual ~IPlayer(){};
	virtual bool onClickHandler() = 0;
	virtual bool asPlayed() const = 0;
	virtual void changeTurn() = 0;
	virtual void wrongMove() = 0;
};