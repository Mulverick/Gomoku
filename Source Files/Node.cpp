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
	this->_nbsimulation = 1000;
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
	this->_nbsimulation = 1000;
	this->_wins = 0;
	this->_loss = 0;
}

Node::~Node() {}

void				Node::Expand(Algorithm algorithm)
{
	//std::cout << "Node::Expand in depht : " << this->_depth << std::endl;
	if (!this->_depth)
		this->Simulate(algorithm);
	else
		this->_child = algorithm.CreateNodesList(this->_board, (this->_color == WHITE ? BLACK : WHITE), --this->_depth);
	//std::cout << "Node::Expand out" << std::endl;
}

void				Node::Simulate(Algorithm algorithm)
{
//	std::cout << "Node::Simulate in" << std::endl;
	algorithm.MonteCarlo(this, this->_parent, this->_board);
//	std::cout << "Node::Simulate out" << std::endl;
}

void				Node::SetWins(int wins)
{
	this->_wins += wins;
	if (this->_parent)
		this->_parent->SetLoss(this->_wins);
}

void				Node::SetLoss(int loss)
{
	this->_loss += loss;
	if (this->_parent)
		this->_parent->SetWins(this->_loss);
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
	int				nbplay = (this->_loss + this->_wins);
	float			wr = ((float)this->_wins / (float)nbplay) * 100;
//	std::cout << "Node::WinsRate : wins = " << this->_wins << " loss = " << this->_loss << " winsrate = " << wr << " nb play = " << nbplay << std::endl;
	return ((int)wr);
}