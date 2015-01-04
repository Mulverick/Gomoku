#include	"Node.hh"
#include	"Algorithm.hh"

Node::Node(int color, int pos, int deth, char *board)
{
	this->_pos = pos;
	this->_board = new char[MAP_SIZE];

	memcpy(this->_board, board, MAP_SIZE);
	this->_board[pos] = color;

	this->_parent = NULL;
	this->_depth = deth;
	this->_color = color;
	this->_nbsimulation = 5;
	this->_wins = 0;
	this->_loss = 0;
}

Node::Node(Node *parent, int color, int pos, int deth, char *board)
{
	this->_pos = pos;
	this->_board = new char[MAP_SIZE];

	memcpy(this->_board, board, MAP_SIZE);
	this->_board[pos] = color;

	this->_parent = parent;
	this->_depth = deth;
	this->_color = color;
	this->_nbsimulation = 10;
	this->_wins = 0;
	this->_loss = 0;
}

Node::~Node() {}

void				Node::Expand(Algorithm algorithm, std::vector<int> freecase)
{
	if (!this->_depth)
	{
		this->Simulate(algorithm, freecase);
		if (this->_parent)
		{
			this->_parent->SetWins(this->_wins);
			this->_parent->SetLoss(this->_loss);
		}

	}
	else
		this->_child = algorithm.CreateNodesList(this->_board, (this->_color == WHITE ? BLACK : WHITE), --this->_depth);
}

void				Node::Simulate(Algorithm algorithm, std::vector<int> freecase)
{
	algorithm.MonteCarlo(this, this->_parent, this->_board, freecase);
<<<<<<< HEAD

//	std::cout << "Node::Simulate out" << std::endl;
=======
>>>>>>> GUI
}

void				Node::SetWins(int wins)
{
	this->_wins += wins;
}

void				Node::SetLoss(int loss)
{
	this->_loss += loss;
}

int					Node::GetPos()
{
	return this->_pos;
}

int					Node::GetColor()
{
	return this->_color;
}

int					Node::GetNbsimulation()
{
	return this->_nbsimulation;
}


int					Node::WinsRate()
{
	//std::cout << "Node::WinsRate : wins = " << this->_wins << " loss = " << this->_loss << std::endl;
	return (this->_wins / (this->_loss + this->_wins));
}