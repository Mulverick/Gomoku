#ifndef ALGORITHM_HH_
# define	ALGORITHM_HH_

# include "Arbitre.hh"
# include "Node.hh"
# include "Utils.hh"
# include <iostream>
# include <cstdlib> 
# include <ctime>
# include <vector>
# include <list>
# include "utils.hh"

//class Node;

class Algorithm
{
public:
	Algorithm();
	~Algorithm();
	bool				NearPiece(Vector<int> const &pos, char **map);
	std::list<Node *>	CreateNodesList(char **map, int color, int depth, Node *parent);
	void				MonteCarlo(Node *node, Node *parent, char **map);

private:
	Arbitre		_arbitre;
	bool		_first;
};

#endif