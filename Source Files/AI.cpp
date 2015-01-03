#include "AI.hh"

AI::AI(int color)
{
	this->_played = -1;
	this->_turn = (color == WHITE ? true : false);
	this->_color = color;
	this->_board = new char[MAP_SIZE];
	this->_type = OTHER;
	srand(time(NULL));
	this->_algorithm = new Algorithm;
}


AI::~AI() {}

int		AI::onClickHandler(int cellPosition)
{
	return (-1);
}

void	AI::easyPlay()
{
}

void	AI::placeStone(char * const &map)
{
	int		wr = 0;
	int		tmp;
	int		pos = -1;

	this->_played = this->_algorithm->EasyPlay(map);
	if (this->_played == -1)
		this->_nodes = this->_algorithm->CreateNodesList(map, this->_color, 0);
	for (std::list<Node *>::iterator it = this->_nodes.begin(); it != this->_nodes.end(); ++it)
	{
		tmp = (*it)->WinsRate();
		if (tmp > wr)
		{
			wr = tmp;
			this->_played = (*it)->GetPos();
		}
	}

	//std::cout << "AI::placeStone : final pos = " << this->_played << " nodes size = " << this->_nodes.size() << std::endl;
	this->_nodes.clear();
	map[this->_played] = this->_color;
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

Type	AI::getType() const
{
	return (this->_type);
}