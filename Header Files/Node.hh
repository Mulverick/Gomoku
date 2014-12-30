#pragma once

#include "Arbitre.hh"
#include <cstdlib> 
#include <ctime>
#include <list>

class Node
{
public:
	Node(int color, int pos, int deth, char * const &board);
	Node(Node *parent, int color, int pos, int deth, char * const &board);
	~Node();
	void				Expand();
	void				Simulate();
	void				SetWins(int win);
	void				SetLoss(int loss);
	const int			WinsRate();

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