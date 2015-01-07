#pragma once

#include "IPlayer.hh"

class AxelAI : public IPlayer
{
public:
	AxelAI(int color, char const * const *map);
	~AxelAI(void);

	Vector<int>	const	&onClickHandler(Vector<int> const &cellPosition);
	void				placeStone(char * const *map);

	void	changeTurn(void);
	void	wrongMove(void);

	Vector<int> const	&hasPlayed(void) const;
	int					getColor(void) const;
	Type				getType(void) const;

private:
	int					_color;
	bool				_turn;
	Vector<int>			_played;

	char const * const	*_map;
	char				_mapNear[19][19][3];
};
