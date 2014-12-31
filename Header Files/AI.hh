#ifndef AI_HH_
# define	AI_HH_

# include "IPlayer.hh"
# include "Algorithm.hh"
//# include "Node.hh"

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
//	Arbitre				_arbitre;
	Algorithm			_algorithm;

	void				easyPlay();
};

#endif