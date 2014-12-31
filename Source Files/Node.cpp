#include	"Node.hh"
#include	"Algorithm.hh"

Node::Node(int color, int pos, int deth, char * const &board)
{
	this->_pos = pos;
	strcpy_s(this->_board, MAP_SIZE, board);
	this->_board[pos] = color;
	this->_parent = NULL;
	this->_depth = deth;
	this->_color = color;
	this->_wins = 0;
	this->_loss = 0;
}

Node::Node(Node *parent, int color, int pos, int deth, char * const &board)
{
	this->_pos = pos;
	strcpy_s(this->_board, MAP_SIZE, board);
	srand(time(NULL));
	this->_board[pos] = color;
	this->_parent = parent;
	this->_depth = deth;
	this->_color = color;
	this->_wins = 0;
	this->_loss = 0;
}

Node::~Node() {}

void				Node::Expand(Algorithm algorithm)
{
	if (!this->_depth)
	{
		this->Simulate(algorithm);
		if (this->_parent)
		{
			this->_parent->SetWins(this->_wins);
			this->_parent->SetLoss(this->_loss);
		}

	}
	else
		this->_child = algorithm.CreateNodesList(this->_board, (this->_color == WHITE ? BLACK : WHITE));
}

void				Node::Simulate(Algorithm algorithm)
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
	algorithm.MonteCarlo(this, this->_parent, this->_board);
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
	return (this->_wins / (this->_loss + this->_wins));
}