#ifndef NODE_HH_
# define	NODE_HH_

/*# include "Algorithm.hh"*/
# include "Arbitre.hh"
# include "Utils.hh"
# include <iostream>
# include <cstdlib> 
# include <ctime>
# include <vector>
# include <list>

class Algorithm;

class Node
{
public:
	Node(int color, Vector<int> const &pos, int deth, char **board);
	Node(Node *parent, int color, Vector<int> const &pos, int deth, char **board);
	~Node();
	void				Expand(Algorithm algorithm);
	void				Simulate(Algorithm algorithm);
	Vector<int> const	&GetPos();
	int					GetColor();
	int					GetNbsimulation();
	void				SetWins(int win);
	void				SetLoss(int loss);
	int					WinsRate();

private:
	int					_nbsimulation;
	std::list<Node *>	_child;
	char				**_board;
	std::string			_map;
	Node				*_parent;
	int					_color;
	int					_wins;
	int					_loss;
	int					_depth;
	Vector<int>			_pos;
};

#endif