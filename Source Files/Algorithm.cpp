#include	"Algorithm.hh"
#include	"Node.hh"

Algorithm::Algorithm()
{
	srand(time(NULL));
}

Algorithm::~Algorithm() {}

int				Algorithm::EasyPlay(char * const &map)
{
	int			pos = -1;

	for (int i = 0; i != SIZE_MAX && pos == -1; ++i)
	{
		if ((this->_arbitre.checkMove(i, map, WHITE) && this->_arbitre.checkWinner(i, map, WHITE))
			|| (this->_arbitre.checkMove(i, map, BLACK) && this->_arbitre.checkWinner(i, map, BLACK)))
			pos = i;
	}
	return pos;
}

std::list<Node *>	Algorithm::CreateNodesList(char * const &map, int color)
{
	std::list<Node *>	nodes;

	for (int i = 0; i != SIZE_MAX; ++i)
	{
		if (map[i] != 0 && this->_arbitre.checkMove(i, map, color))
		{
			Node	*newnode = new Node(color, i, 0, map);

			nodes.push_back(newnode);
			newnode->Expand(*this);
		}
	}
	return nodes;
}

void				Algorithm::MonteCarlo(Node *node, Node *parent, char * const &map)
{
	int				pos = (rand() % MAP_SIZE);
	int				color = node->GetColor();
	int				ccolor = (color == WHITE ? BLACK : WHITE);
	int				nbsimulation = node->GetNbsimulation();
	int				wins = 0;
	int				loss = 0;

	for (int i = 0; i != nbsimulation; ++i)
	{

		while (!this->_arbitre.checkWinner(pos, map, ccolor))
		{
			if (map[pos] == 0 && this->_arbitre.checkMove(pos, map, ccolor))
			{
				map[pos] = ccolor;
				ccolor = (ccolor == WHITE ? BLACK : WHITE);
			}
			pos = (rand() % MAP_SIZE);
		}
		if (parent && ccolor == parent->GetColor())
			wins++;
		else if (!parent && ccolor == color)
			wins++;
		else
			loss++;
	}
	node->SetWins(wins);
	node->SetLoss(loss);
}