#include	"Algorithm.hh"
#include	"Node.hh"
#include	"Mapping.hh"

Algorithm::Algorithm()
{
	this->_first = true;
}

Algorithm::~Algorithm() {}

bool				Algorithm::NearPiece(Vector<int> const &pos, char **map)
{
	if ((pos.x < 18 && (map[pos.y][pos.x + 1] == WHITE || map[pos.y][pos.x + 1] == BLACK))
		|| (pos.y < 18 && (map[pos.y + 1][pos.x] == WHITE || map[pos.y + 1][pos.x] == BLACK))
		|| (pos.x > 0 && (map[pos.y][pos.x - 1] == WHITE || map[pos.y][pos.x + 1] == BLACK))
		|| (pos.y > 0 && (map[pos.y - 1][pos.x] == WHITE || map[pos.y - 1][pos.x] == BLACK)))
		return true;
	else
		return false;
}

std::list<Node *>	Algorithm::CreateNodesList(char **map, int color, int depth, Node *parent)
{
	std::list<Node *>	nodes;
	std::list<Node *>	maxone;
	std::list<Node *>	maxtwo;
	std::list<Node *>	white;
	std::list<Node *>	black;
	Vector<int>			tmp;

	for (int y = 0; y != 19; ++y)
	{
		for (int x = 0; x != 19; ++x)
		{
			tmp.x = x;
			tmp.y = y;
			if (map[y][x] > 2 || (map[y][x] == 0 && this->NearPiece(tmp, map)))
			{
				Node *newnode;
				if (parent)
					newnode = new Node(parent, color, tmp, depth, map);
				else
					newnode = new Node(color, tmp, depth, map);
				/*if (map[y][x] & FIVE_WHITE)
				{
					white.push_back(newnode);
					newnode->SetWins(1);
					if (color == WHITE)
						return white;
				}
				if (map[y][x] & FIVE_BLACK)
				{
					black.push_back(newnode);
					newnode->SetWins(1);
					if (color == BLACK)
						return black;
				}
				else*/ if ((map[y][x] & FOUR_BLACK) || (map[y][x] & FOUR_WHITE))
					maxone.push_back(newnode);
				else if ((map[y][x] & THREE_BLACK) || (map[y][x] & THREE_WHITE))
					maxtwo.push_back(newnode);
				else
					nodes.push_back(newnode);
			}
		}
	}
	std::cout << "maxone.size[" << maxone.size() << "] maxtwo.size[" << maxtwo.size() << "] nodes.size[" << nodes.size() << "]." << std::endl;
	/*if (!white.empty())
		return white;
	if (!black.empty())
		return black;*/
	if (!maxone.empty())
	{
		for (std::list<Node *>::iterator it = maxone.begin(); it != maxone.end(); (*it++)->Expand(*this));
		return maxone;
	}
	if (!maxtwo.empty())
	{
		for (std::list<Node *>::iterator it = maxtwo.begin(); it != maxtwo.end(); (*it++)->Expand(*this));
		return maxtwo;
	}
	if (!nodes.empty())
		for (std::list<Node *>::iterator it = nodes.begin(); it != nodes.end(); (*it++)->Expand(*this));
	else
	{
		Vector<int>	r;

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