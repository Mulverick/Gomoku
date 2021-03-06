#include "AI.hh"

AI::AI(int color)
{
	this->_played.x = -1;
	this->_played.y = -1;
	this->_turn = (color == WHITE ? true : false);
	this->_color = color;
	this->_type = OTHER;
	this->_board = new Mapping();
	srand((unsigned int)time(NULL));
	this->_algorithm = new Algorithm;
}

AI::AI(int color, char **map)
{
	this->_played.x = -1;
	this->_played.y = -1;
	this->_turn = (color == WHITE ? true : false);
	this->_color = color;
	this->_type = OTHER;
	this->_board = new Mapping(map);
	srand((unsigned int)time(NULL));
	this->_algorithm = new Algorithm;
}

AI::~AI() {}

Vector<int> const &AI::onClickHandler(Vector<int> const &cellPosition)
{
	Vector<int> *returned = new Vector<int>(-1, -1);
	return (*returned);
}

void	AI::placeStone(char * const *map)
{
	int		wr = 0;
	int		tmp;
	int		pos = -1;

	this->_board->updateMap(map);

	if (this->_played.x == -1)
		this->_nodes = this->_algorithm->CreateNodesList(this->_board->getMap(), this->_color, 1, NULL);
	for (std::list<Node *>::iterator it = this->_nodes.begin(); it != this->_nodes.end(); ++it)
	{
		tmp = (*it)->WinsRate();
		if (tmp > wr)
		{
			wr = tmp;
			this->_played = (*it)->GetPos();
		}
	}
	this->_nodes.clear();
	map[this->_played.y][this->_played.x] = this->_color;
}

void	AI::wrongMove()
{
	this->_played.x = -1;
	this->_played.y = -1;
}

Vector<int> const	&AI::hasPlayed() const
{
	return (this->_played);
}

void	AI::changeTurn()
{
	this->_played.x = -1;
	this->_played.y = -1;
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