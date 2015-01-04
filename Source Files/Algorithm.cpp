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
	//srand((unsigned int)time(NULL));
}

Algorithm::~Algorithm() {}

<<<<<<< HEAD
bool			CheckPatern(int pos, char *map, int color)
{
	int			nb;
	int			next;

	nb = 1;
	next = pos + 1;
	while (next % 19 != 0 && map[next] == color)
	{
		++next;
		++nb;
	}
	next = pos - 1;
	while (next % 19 != 18 && map[next] == color)
	{
		--next;
		++nb;
	}
	if (nb >= 4)
		return true;
	nb = 1;
	next = pos + 19;
	while (next / 19 != 19 && map[next] == color)
	{
		next += 19;
		++nb;
	}
	next = pos - 19;
	while (next / 19 > 0 && map[next] == color)
	{
		next -= 19;
		++nb;
	}
	if (nb >= 4)
		return true;
	nb = 1;
	next = pos + 20;
	while (next % 19 != 0 && next / 19 != 19 && map[next] == color)
	{
		next += 20;
		++nb;
	}
	next = pos - 20;
	while (next % 19 != 18 && next / 19 > 0 && map[next] == color)
	{
		next -= 20;
		++nb;
	}
	if (nb >= 4)
		return true;
	nb = 1;
	next = pos + 18;
	while (next % 19 != 18 && next / 19 != 19 && map[next] == color)
	{
		next += 18;
		++nb;
	}
	next = pos - 18;
	while (next % 19 != 0 && next / 19 > 0 && map[next] == color)
	{
		next -= 18;
		++nb;
	}
	if (nb >= 4)
		return true;
	return false;
}

int				Algorithm::EasyPlay(char *map)
=======
int				Algorithm::EasyPlay(char * const &map)
>>>>>>> GUI
{
	int			pos = -1;

	for (int i = 0; i != MAP_SIZE && pos == -1; ++i)
	{
<<<<<<< HEAD
		if ((map[i] == 0 && CheckPatern(i, map, WHITE))
			|| (map[i] == 0 && CheckPatern(i, map, BLACK)))
=======
		if ((this->_arbitre.checkMove(i, map, WHITE) && this->_arbitre.checkWinner(i, map, WHITE))
			|| (this->_arbitre.checkMove(i, map, BLACK) && this->_arbitre.checkWinner(i, map, BLACK)))
>>>>>>> GUI
			pos = i;
	}
	return pos;
}

<<<<<<< HEAD
bool				NearPiece(int pos, char *map)
{
	if (map[pos] != 0)
		return false;
	else if ((pos >= 19 && map[pos - 19] != 0) || (pos < MAP_SIZE - 20 && map[pos + 19] != 0) || (pos < MAP_SIZE && map[pos + 1] != 0) || (pos > 0 && map[pos - 1] != 0))
		return true;
	else
		return false;
}

std::list<Node *>	Algorithm::CreateNodesList(char *map, int color, int depth)
=======
std::list<Node *>	Algorithm::CreateNodesList(char * const &map, int color, int depth)
>>>>>>> GUI
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
<<<<<<< HEAD
=======
	std::vector<int>::iterator it;
	char			*board = new char[MAP_SIZE];
>>>>>>> GUI
	int				pos;
	int				color = node->GetColor();
	int				ccolor = (color == WHITE ? BLACK : WHITE);
	int				nbsimulation = node->GetNbsimulation();
	int				wins = 0;
	int				loss = 0;
<<<<<<< HEAD
	
	pos = rand() % MAP_SIZE;
	for (int i = 0; i != nbsimulation; ++i)
	{
		while (!cases.empty())
		{
			map[cases.back()] = 0;
			cases.pop_back();
		}
		this->_arbitre.clearArbitre();
		ccolor = (color == WHITE ? BLACK : WHITE);
		while (!this->_arbitre.checkWinner(i, map, ccolor))
=======

	pos = rand() % MAP_SIZE;
	for (int i = 0; i != nbsimulation; ++i)
	{
		cases = freecase;
		memcpy(board, map, MAP_SIZE);
		this->_arbitre._prisoner[0] = 0;
		this->_arbitre._prisoner[1] = 0;
		while (!this->_arbitre.checkWinner(pos, board, ccolor))
>>>>>>> GUI
		{
			if (this->_arbitre.checkMove(pos, map, ccolor))
			{
<<<<<<< HEAD
				map[pos] = ccolor;
				cases.push_back(pos);
=======
				board[pos] = ccolor;
>>>>>>> GUI
				ccolor = (ccolor == WHITE ? BLACK : WHITE);
			}
			pos = rand() % MAP_SIZE;
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