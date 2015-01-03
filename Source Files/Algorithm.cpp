#include	"Algorithm.hh"
#include	"Node.hh"

void	mapdraw(char *map, char *fct)
{
	std::cout << fct << "[" << std::endl;
	for (int i = 0; i != MAP_SIZE; std::cout << (int)map[i++])
	{
		if (!(i % 19))
			std::cout << std::endl;
	}
	std::cout << "\n]" << std::endl;
}

Algorithm::Algorithm()
{
	this->_first = true;
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
	std::list<Node *>		nodes;
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
			if (this->_arbitre.checkMove(i, map, color))
			{
				Node	*newnode = new Node(color, i, depth, map);

				nodes.push_back(newnode);
				newnode->Expand(*this, freecase);
			}
		}
	}
	this->_first = false;
	return nodes;
}

void				Algorithm::MonteCarlo(Node *node, Node *parent, char *map, std::vector<int> freecase)
{
	std::vector<int>	cases;
	std::vector<int>::iterator it;
	char			*board = new char[MAP_SIZE];
	int				pos;
	int				color = node->GetColor();
	int				ccolor = (color == WHITE ? BLACK : WHITE);
	int				nbsimulation = node->GetNbsimulation();
	int				wins = 0;
	int				loss = 0;

	pos = rand() % MAP_SIZE;
	for (int i = 0; i != nbsimulation; ++i)
	{
		cases = freecase;
		memcpy(board, map, MAP_SIZE);
		this->_arbitre._prisoner[0] = 0;
		this->_arbitre._prisoner[1] = 0;
		while (!this->_arbitre.checkWinner(pos, board, ccolor))
		{
			if (this->_arbitre.checkMove(pos, board, ccolor))
			{
				board[pos] = ccolor;
				ccolor = (ccolor == WHITE ? BLACK : WHITE);
			}
			pos = rand() % MAP_SIZE;
		}
		/*std::cout << std::endl;
		mapdraw(board, "Algorithm::MonteCarlo");
		std::cout << std::endl;*/

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