#ifndef NODE_HH_
# define	NODE_HH_

/*# include "Algorithm.hh"*/
# include "Arbitre.hh"
# include "Utils.hh"
# include <iostream>
# include <cstdlib> 
# include <ctime>
# include <list>

class Algorithm;

class Node
{
public:
	Node(int color, int pos, int deth, char * const &board);
	Node(Node *parent, int color, int pos, int deth, char * const &board);
	~Node();
	void				Expand(Algorithm algorithm);
	void				Simulate(Algorithm algorithm);
	int					GetPos();
	int					GetColor();
	int					GetNbsimulation();
	void				SetWins(int win);
	void				SetLoss(int loss);
	int					WinsRate();

private:
	const int			_nbsimulation = 100;
	std::list<Node *>	_child;
	char *				_board;
	Node				*_parent;
	Arbitre				_arbitre;
	int					_color;
	int					_wins;
	int					_loss;
	int					_depth;
	int					_pos;
};

#endif