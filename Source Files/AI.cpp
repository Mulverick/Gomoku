#include "AI.hh"

AI::AI(int color)
{
	this->_played = -1;
	this->_turn = (color == WHITE ? true : false);
	this->_color = color;
	this->_board = new char[MAP_SIZE];
	this->_type = OTHER;
	srand((unsigned int)time(NULL));
	this->_algorithm = new Algorithm;
}


AI::~AI() {}

int		AI::onClickHandler(int cellPosition)
{
	return (-1);
}

void	AI::placeStone(char * const &map)
{
	//std::cout << "AI::placeStone in" << std::endl;

	int		wr = 0;
	int		tmp;
	int		pos = -1;

	memcpy(this->_board, map, MAP_SIZE);
	this->_played = this->_algorithm->EasyPlay(map);
	if (this->_played == -1)
		this->_nodes = this->_algorithm->CreateNodesList(this->_board, this->_color, 0);
	for (std::list<Node *>::iterator it = this->_nodes.begin(); it != this->_nodes.end(); ++it)
	{
		tmp = (*it)->WinsRate();
		//std::cout << "CWinsRate = " << wr << " WinsRate = " << tmp << std::endl;
		if (tmp > wr)
		{
			//std::cout << "in" << std::endl;
			wr = tmp;
			this->_played = (*it)->GetPos();
		}
	}
	this->_nodes.clear();
	//std::cout << "AI::placeStone : pos = " << this->_played << " in map[pos] = " << (int)map[this->_played] << std::endl;
	map[this->_played] = this->_color;
	//std::cout << "AI::placeStone out" << std::endl;
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