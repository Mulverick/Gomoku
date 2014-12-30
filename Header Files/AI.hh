#pragma once

#include "IPlayer.hh"
#include "Node.hh"

class AI : public IPlayer
{
public:
	AI(int color);
	~AI();
	int					onClickHandler(int cellPosition);
	void				placeStone(char * const &map);
	int					hasPlayed() const;
	void				changeTurn();
	void				wrongMove();
	int					getColor() const;

private:
	int					_color;
	bool				_turn;
	int					_played;
	std::list<Node *>	_nodes;
	char				*_board;
	Arbitre				_arbitre;

	void				easyPlay();
};