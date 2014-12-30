#include	"Node.hh"

Node::Node(int color, int pos, int deth, char * const &board)
{
	this->_pos = pos;
	strcpy_s(this->_board, MAP_SIZE, board);

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
	this->_parent = parent;
	this->_depth = deth;
	this->_color = color;
	this->_wins = 0;
	this->_loss = 0;
	srand(time(NULL));
}

Node::~Node() {}

void				Node::Expand()
{
	if (!this->_depth)
		return;
}

void				Node::Simulate()
{
	int				pos = this->_pos;
	int				ccolor = this->_color;

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
		if (ccolor == this->_color)
			this->_wins++;
		else
			this->_loss++;
	}
}

void				Node::SetWins(int wins)
{
	this->_wins += wins;
}

void				Node::SetLoss(int loss)
{
	this->_loss += loss;
}

const int			Node::WinsRate()
{
	return (this->_wins / (this->_loss + this->_wins));
}