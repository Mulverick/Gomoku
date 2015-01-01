#include	"Node.hh"
#include	"Algorithm.hh"

Node::Node(int color, int pos, int deth, char * const &board)
{
	this->_pos = pos;
	this->_board = new char[MAP_SIZE];
	std::cout << "Node::Node\n" << (char *)board << std::endl;
	strcpy_s(this->_board, MAP_SIZE, board);
	std::cout << "Node::Node\n" << (char *)this->_board << std::endl;
	std::cout << "POS = " << pos << "COLOR = " << color << std::endl;
	this->_board[pos] = color;
	
	std::cout << "Node::Node\n" << this->_board[pos] << std::endl;

	this->_parent = NULL;
	this->_depth = deth;
	this->_color = color;
	this->_nbsimulation = 10;
	this->_wins = 0;
	this->_loss = 0;
}

Node::Node(Node *parent, int color, int pos, int deth, char * const &board)
{
	this->_pos = pos;
	this->_board = new char[MAP_SIZE];
	strcpy_s(this->_board, MAP_SIZE, board);
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
	std::cout << "Node::Expand : depth = " << this->_depth << std::endl;
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
	/*int				pos = (rand() % MAP_SIZE);
	int				ccolor = (this->_color == WHITE ? BLACK : WHITE);

	for (int i = 0; i != this->_nbsimulation; ++i)
	{

		while (!_arbitre.checkWinner(pos, this->_board, ccolor))
		{
			if (_board[pos] == 0 && _arbitre.checkMove(pos, this->_board, ccolor))
			{
				_board[pos] = ccolor;
				ccolor = (ccolor == WHITE ? BLACK : WHITE);
			}
			pos = (rand() % MAP_SIZE);
		}
		if (this->_parent && ccolor == this->_parent->GetColor())
			this->_wins++;
		else if (!this->_parent && ccolor == this->_color)
			this->_wins++;
		else
			this->_loss++;
	}*/
	std::cout << "Node::Node\n" << (char *)this->_board << std::endl;

	algorithm.MonteCarlo(this, this->_parent, this->_board, freecase);
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
	std::cout << "Node::WinsRate : wins = " << this->_wins << " loss = " << this->_loss << std::endl;
	return (this->_wins / (this->_loss + this->_wins));
}