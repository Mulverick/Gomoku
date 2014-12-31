#ifndef ALGORITHM_HH_
# define	ALGORITHM_HH_

# include "Arbitre.hh"
# include "Node.hh"
# include "Utils.hh"
# include <iostream>
# include <cstdlib> 
# include <ctime>
# include <list>

//class Node;

class Algorithm
{
public:
	Algorithm();
	~Algorithm();
	int					EasyPlay(char * const &map);
	std::list<Node *>	CreateNodesList(char * const &map, int color, int depth);
	void				MonteCarlo(Node *node, Node *parent, char * const &map);

private:
	Arbitre		_arbitre;
	bool		_first;
};

#endif