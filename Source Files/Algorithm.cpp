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
	this->_arbitre.updateRules(true, true);
}

Algorithm::~Algorithm() {}

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

int				Algorithm::EasyPlay(char * const &map)
{
	int			pos = -1;

	for (int i = 0; i < MAP_SIZE && pos == -1; i++)
	{
		/*if ((map[i] == 0 && this->_arbitre.checkWinner(i, map, WHITE))
			|| (map[i] == 0 && this->_arbitre.checkWinner(i, map, BLACK)))
			pos = i;*/
		if ((map[i] == 0 && CheckPatern(i, map, WHITE))
			|| (map[i] == 0 && CheckPatern(i, map, BLACK)))
			pos = i;
	}
	return pos;
}

bool				NearPiece(int pos, char * const &map)
{
	if (map[pos] != 0)
		return false;
	else if ((pos >= 19 && map[pos - 19] != 0) || (pos < MAP_SIZE - 20 && map[pos + 19] != 0) || (pos < MAP_SIZE && map[pos + 1] != 0) || (pos > 0 && map[pos - 1] != 0))
		return true;
	else
		return false;
}

std::list<Node *>	Algorithm::CreateNodesList(char * const &map, int color, int depth)
{
//	std::cout << "Algorithm::CreateNodesList in" << std::endl;

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
		for (int i = 0; i != MAP_SIZE; i++)
		{
			if (this->_arbitre.checkMove(i, map, color) && NearPiece(i, map))
			{
				Node	*newnode = new Node(color, i, depth, map);

				nodes.push_back(newnode);
				newnode->Expand(*this, freecase);
			}
		}
	}
//	std::cout << "Nodes Size : " << nodes.size() << std::endl;
	this->_first = false;
//	std::cout << "Algorithm::CreateNodesList out" << std::endl;
	return nodes;
}

void				Algorithm::MonteCarlo(Node *node, Node *parent, char *map, std::vector<int> freecase)
{
	std::vector<int>	cases;
	char			*board = new char[MAP_SIZE];
	int				pos;
	int				color = node->GetColor();
	int				ccolor;
	int				nbsimulation = node->GetNbsimulation();
	int				wins = 0;
	int				loss = 0;
	
	memcpy(board, map, MAP_SIZE);
	pos = rand() % MAP_SIZE;
	for (int i = 0; i != nbsimulation; ++i)
	{
		while (!cases.empty())
		{
			board[cases.back()] = 0;
			cases.pop_back();
		}
		//memcpy(board, map, MAP_SIZE);
		this->_arbitre._prisoner[0] = 0;
		this->_arbitre._prisoner[1] = 0;
		ccolor = (color == WHITE ? BLACK : WHITE);
		//this->_arbitre._isWinner = false;
		while (!this->_arbitre.checkWinner(i, map, ccolor))
		{
			if (this->_arbitre.checkMove(pos, board, ccolor))
			{
				board[pos] = ccolor;
				cases.push_back(pos);
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