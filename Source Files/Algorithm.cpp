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
	std::list<Node *>	nodes;
	if (this->_first)
	{
		int	r;
		for (r = (rand() % MAP_SIZE); !this->_arbitre.checkMove(r, map, color); r = (rand() % MAP_SIZE));
		nodes.push_back(new Node(color, r, -1, map));
	}
	for (int i = 0; i != MAP_SIZE; ++i)
	{
		if (map[i] != 0 && this->_arbitre.checkMove(i, map, color))
		{
			Node	*newnode = new Node(color, i, depth, map);

			nodes.push_back(newnode);
			newnode->Expand(*this);
		}
	}
	this->_first = false;
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