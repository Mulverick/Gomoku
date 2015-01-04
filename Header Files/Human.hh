#pragma once

#include "IPlayer.hh"

class Human : public IPlayer
{
public:
	Human(int color);
	~Human();

	Vector<int> const	&onClickHandler(Vector<int> const &cellPosition);
	void				placeStone(char * const *map);

	void	changeTurn(void);
	void	wrongMove(void);

	Vector<int> const	&hasPlayed(void) const;
	int					getColor(void) const;
	Type				getType(void) const;
private:
	int				_color;
	bool			_turn;
	Vector<int>		_played;
	Type			_type;
};

