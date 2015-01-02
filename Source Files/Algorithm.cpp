#include	"Algorithm.hh"
#include	"Node.hh"

Algorithm::Algorithm()
{
	this->_first = true;
	srand(time(NULL));
}

Algorithm::~Algorithm() {}

int				Algorithm::EasyPlay(char * const &map)
{
	int			pos = -1;

	for (int i = 0; i != MAP_SIZE && pos == -1; ++i)
	{
		if ((this->_arbitre.checkMove(i, map, WHITE) && this->_arbitre.checkWinner(i, map, WHITE))
			|| (this->_arbitre.checkMove(i, map, BLACK) && this->_arbitre.checkWinner(i, map, BLACK)))
			pos = i;
	}
	return pos;
}

std::list<Node *>	Algorithm::CreateNodesList(char * const &map, int color, int depth)
{
	std::cout << "Algorithm::CreateNodesList" << std::endl;
	std::list<Node *>	nodes;
	std::vector<int>		freecase;

	if (this->_first == true)
	{
		int	r;

		for (r = (rand() % MAP_SIZE); !this->_arbitre.checkMove(r, map, color); r = (rand() % MAP_SIZE));
		Node	*newnode = new Node(color, r, -1, map);

		nodes.push_back(newnode);
		newnode->SetWins(1);
	}
	else
	{
		for (int i = 0; i != MAP_SIZE; ++i)
		{
			if (map[i] != WHITE && map[i] != BLACK && this->_arbitre.checkMove(i, map, color))
				freecase.push_back(i);
		}
		for (std::vector<int>::iterator it = freecase.begin(); it != freecase.end(); ++it)
		{
			Node	*newnode = new Node(color, (*it), depth, map);

			nodes.push_back(newnode);
			newnode->Expand(*this, freecase);
		}
	}
	this->_first = false;
	return nodes;
}

void				Algorithm::MonteCarlo(Node *node, Node *parent, char * const &map, std::vector<int> freecase)
{
	std::vector<int>	cases;
	std::vector<int>::iterator it;
	int				pos;
	int				color = node->GetColor();
	int				ccolor = (color == WHITE ? BLACK : WHITE);
	int				nbsimulation = node->GetNbsimulation();
	int				wins = 0;
	int				loss = 0;

	for (it = freecase.begin(); (*it) != node->GetPos() && it != freecase.end(); ++it);
	if (it != freecase.end())
		freecase.erase(it);
	pos = freecase[(rand() % freecase.size())];
	std::cout << pos << " " << map[pos] << std::endl;
	std::cout << map << std::endl;
	for (int i = 0; i != nbsimulation; ++i)
	{
		cases = freecase;

		while (!this->_arbitre.checkWinner(pos, map, ccolor) && !cases.empty())
		{
			if (map[pos] != WHITE && map[pos] != BLACK && this->_arbitre.checkMove(pos, map, ccolor))
			{
				std::cout << "in if" << std::endl;
				map[pos] = ccolor;
				ccolor = (ccolor == WHITE ? BLACK : WHITE);
				for (it = cases.begin(); (*it) != pos && it != cases.end(); ++it);
				cases.erase(it);
			}
			pos = cases[(rand() % cases.size())];
		}
		if (parent && ccolor == parent->GetColor())
			wins++;
		else if (!parent && ccolor == color)
			wins++;
		else
			loss++;
		std::cout << "nbwins = " << wins << " nbloss = " << loss << std::endl;
	}
	node->SetWins(wins);
	node->SetLoss(loss);
}