#pragma once

#include "IPlayer.hh"

class AxelAI : public IPlayer
{
public:
	AxelAI(int color, char const *map);
	~AxelAI(void);

	int		onClickHandler(int cellPosition);
	void	placeStone(char *map);

	void	changeTurn(void);
	void	wrongMove(void);

	int		hasPlayed(void) const;
	int		getColor(void) const;
	Type	getType(void) const;

private:
	int					_color;
	bool				_turn;
	int				_played;

	char const			*_map;
};
