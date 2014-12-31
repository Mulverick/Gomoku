#include "AI.hh"

AI::AI(int color)
{
	this->_played = -1;
	this->_first = true;
	this->_turn = (color == WHITE ? true : false);
	this->_color = color;
	this->_board = new char[MAP_SIZE];
}


AI::~AI() {}

int		AI::onClickHandler(int cellPosition)
{
	return (-1);
}

void	AI::easyPlay()
{
	for (int i = 0; i != SIZE_MAX && this->_played == -1; ++i)
	{
		if ((this->_arbitre.checkMove(i, this->_board, WHITE) && this->_arbitre.checkWinner(i, this->_board, WHITE))
			|| (this->_arbitre.checkMove(i, this->_board, BLACK) && this->_arbitre.checkWinner(i, this->_board, BLACK)))
			this->_played = i;
	}
}

void	AI::placeStone(char * const &map)
{
	int		wr = 0;
	int		pos = -1;

	/*strcpy_s(this->_board, MAP_SIZE, map);

	this->easyPlay();

	for (int i = 0; i != SIZE_MAX && this->_played == -1; ++i)
	{
		if (this->_board[i] != 0 && this->_arbitre.checkMove(i, this->_board, this->_color))
		{
			Node	*newnode = new Node(this->_color, i, 0, this->_board);

			this->_nodes.push_back(newnode);
			newnode->Expand(this->_algorithm);
			if (newnode->WinsRate() > wr)
			{
				wr = newnode->WinsRate();
				pos = i;
			}
		}
	}
	if (this->_played == -1)
		this->_played = pos;*/

	this->_played = this->_algorithm.EasyPlay(map);
	if (this->_played == -1)
		this->_algorithm.CreateNodesList(map, this->_color);
	for (std::list<Node *>::iterator it = this->_nodes.begin(); it != this->_nodes.end() && this->_played == -1; ++it)
	{
		if ((*it)->WinsRate() > wr)
		{
			wr = (*it)->WinsRate();
			this->_played = (*it)->GetPos();
		}
	}
	map[this->_played] = this->_color;
	if (this->_first == true)
		this->_first = false;
}

void	AI::wrongMove()
{
	this->_played = -1;
}

int		AI::hasPlayed() const
{
	return (this->_played);
}

void	AI::changeTurn()
{
	this->_played = -1;
	this->_turn = (this->_turn == true ? false : true);
}

int		AI::getColor() const
{
	return (this->_color);
}