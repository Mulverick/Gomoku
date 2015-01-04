#ifndef AI_HH_
# define	AI_HH_

# include "IPlayer.hh"
# include "Algorithm.hh"
# include "Node.hh"


class AI : public IPlayer
{
public:
	AI(int color);
	AI(int color, char **map);
	~AI();
	Vector<int> const	&onClickHandler(Vector<int> const &cellPosition);
	Vector<int> const	&hasPlayed() const;
	void	placeStone(char * const *map);
	void	changeTurn();
	void	wrongMove();
	int		getColor() const;
	Type	getType() const;

private:
	int					_color;
	bool				_turn;
	Vector<int>			_played;
	Type				_type;
	std::list<Node *>	_nodes;
	char				**_board;
	Algorithm			*_algorithm;

	void				easyPlay();
};

#endif