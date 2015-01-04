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

//class Node;

class Algorithm
{
public:
	Algorithm();
	~Algorithm();
	int					EasyPlay(char *map);
	bool				NearPiece(int pos, char *map);
	bool				CheckPatern(int pos, char *map, int color, int nbp);
	std::list<Node *>	CreateNodesList(char *map, int color, int depth);
	void				MonteCarlo(Node *node, Node *parent, char *map);

private:
	Arbitre		_arbitre;
	bool		_first;
};

#endif