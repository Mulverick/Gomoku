#include	"Algorithm.hh"
#include	"Node.hh"

Algorithm::Algorithm()
{
	this->_first = true;
}

Algorithm::~Algorithm() {}

bool			Algorithm::CheckPatern(Vector<int> const &pos, char * const *map, int color, int nbp)
{
//	std::cout << "Algorithm::CheckPatern in" << std::endl;

	int			nb;
	Vector<int>	next;

	nb = 1;
	next.x = pos.x + 1;
	next.y = pos.y;
	while (next.y < 19 && next.x >= 0 && next.y >= 0 && next.x < 19 && map[next.y][next.x] == color)
	{
		++next.x;
		++nb;
	}
	next.x = pos.x - 1;
	while (next.y < 19 && next.x >= 0 && next.y >= 0 && next.x < 19 && map[next.y][next.x] == color)
	{
		--next.x;
		++nb;
	}
	if (nb >= nbp)
		return true;
	nb = 1;
	next.y = pos.y + 1;
	next.x = pos.x;
	while (next.y < 19 && next.x >= 0 && next.y >= 0 && next.x < 19 && map[next.y][next.x] == color)
	{
		++next.y;
		++nb;
	}
	next.y = pos.y - 1;
	while (next.y < 19 && next.x >= 0 && next.y >= 0 && next.x < 19 && map[next.y][next.x] == color)
	{
		--next.y;
		++nb;
	}
	if (nb >= nbp)
		return true;
	nb = 1;
	next.y = pos.y + 1;
	next.x = pos.x + 1;
	while (next.y < 19 && next.x >= 0 && next.y >= 0 && next.x < 19 && map[next.y][next.x] == color)
	{
		++next.y;
		++next.x;
		++nb;
	}
	next.y = pos.y - 1;
	next.x = pos.x - 1;
	while (next.y < 19 && next.x >= 0 && next.y >= 0 && next.x < 19 && map[next.y][next.x] == color)
	{
		--next.y;
		--next.x;
		++nb;
	}
	if (nb >= nbp)
		return true;
	nb = 1;
	next.y = pos.y + 1;
	next.x = pos.x - 1;
	while (next.y < 19 && next.x >= 0 && next.y >= 0 && next.x < 19 && map[next.y][next.x] == color)
	{
		++next.y;
		--next.x;
		++nb;
	}
	next.y = pos.y - 1;
	next.x = pos.x + 1;
	while (next.y < 19 && next.x >= 0 && next.y >= 0 && next.x < 19 && map[next.y][next.x] == color)
	{
		--next.y;
		++next.x;
		++nb;
	}
	if (nb >= nbp)
		return true;
//	std::cout << "Algorithm::CheckPatern out" << std::endl;
	return false;
}

Vector<int> const	&Algorithm::EasyPlay(char * const *map)
{
//	std::cout << "Algorithm::EasyPlay in" << std::endl;
	Vector<int>		*ret = new Vector<int>(-1, -1);
	Vector<int>		*tmp = new Vector<int>(-1, -1);

	for (int y = 0; y < 19; ++y)
	{
		for (int x = 0; x < 19; ++x)
		{
			tmp->x = x;
			tmp->y = y;
			if ((map[y][x] == 0 && this->CheckPatern(*tmp, map, WHITE, 4))
				|| (map[y][x] == 0 && this->CheckPatern(*tmp, map, BLACK, 4)))
				return *tmp;
		}
	}
//	std::cout << "Algorithm::EasyPlay out" << std::endl;
	return *ret;
}

bool				Algorithm::NearPiece(Vector<int> const &pos, char **map)
{
	if ((pos.x < 18 && map[pos.y][pos.x + 1] != 0) || (pos.y < 18 && map[pos.y + 1][pos.x] != 0) || (pos.x > 0 && map[pos.y][pos.x - 1] != 0) || (pos.y > 0 && map[pos.y - 1][pos.x] != 0))
		return true;
	else
		return false;
}

std::list<Node *>	Algorithm::CreateNodesList(char **map, int color, int depth)
{
	std::cout << "Algorithm::CreateNodesList in" << std::endl;
	std::list<Node *>	nodes;
	Vector<int>			tmp;

	if (this->_first == true)
	{
		Vector<int>	r;
		std::cout << "Algorithm::CreateNodesList" << std::endl;

		r.x = (rand() % 19);
		r.y = (rand() % 19);
		while (map[r.y][r.x] != 0)
		{
			r.x = (rand() % 19);
			r.y = (rand() % 19);
		}
		Node	*newnode = new Node(color, r, -1, map);

		nodes.push_back(newnode);
		newnode->SetWins(1);
	}
	else
	{
		for (int y = 0; y != 19; ++y)
		{
			for (int x = 0; x != 19; ++x)
			{
				tmp.x = x;
				tmp.y = y;
				if (this->_arbitre.checkMove(tmp, map, color) && this->NearPiece(tmp, map))
				{
					Node	*newnode = new Node(color, tmp, depth, map);

					nodes.push_back(newnode);
					newnode->Expand(*this);
				}
			}
		}
	}
	this->_first = false;
	std::cout << "Algorithm::CreateNodesList out nodes.size : " << nodes.size() << std::endl;
	return nodes;
}

void				Algorithm::MonteCarlo(Node *node, Node *parent, char **map)
{
	std::vector<Vector<int> >	cases;
	Vector<int>		pos;
	int				color = node->GetColor();
	int				ccolor = (color == WHITE ? BLACK : WHITE);
	int				nbsimulation = node->GetNbsimulation();
	int				wins = 0;
	int				loss = 0;

	pos.x = rand() % 19;
	pos.y = rand() % 19;
	for (int i = 0; i != nbsimulation; ++i)
	{
		while (!cases.empty())
		{
			map[cases.back().y][cases.back().x] = 0;
			cases.pop_back();
		}
		this->_arbitre.clearArbitre();
		ccolor = (color == WHITE ? BLACK : WHITE);
		while (!this->_arbitre.getIsWinner())
		{
			if (this->_arbitre.checkMove(pos, map, ccolor))
			{
				map[pos.y][pos.x] = ccolor;
				cases.push_back(pos);
				ccolor = (ccolor == WHITE ? BLACK : WHITE);
			}
			pos.x = rand() % 19;
			pos.y = rand() % 19;
		}
		if (ccolor == color)
			wins++;
		else
			loss++;
	}
	node->SetWins(wins);
	node->SetLoss(loss);
}