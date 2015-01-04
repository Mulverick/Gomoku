#include "AI.hh"

AI::AI(int color)
{
	this->_played.x = -1;
	this->_played.y = -1;
	this->_turn = (color == WHITE ? true : false);
	this->_color = color;
	this->_board = new char*[19];
	for (int y = 0; y < 19; ++y)
		this->_board[y] = new char[19];
	this->_type = OTHER;
	srand((unsigned int)time(NULL));
	this->_algorithm = new Algorithm;
}

AI::AI(int color, char **map)
{
	this->_played.x = -1;
	this->_played.y = -1;
	this->_turn = (color == WHITE ? true : false);
	this->_color = color;
	this->_board = new char*[19];
	for (int y = 0; y < 19; ++y)
		this->_board[y] = new char[19];
	this->_type = OTHER;
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
//	std::cout << "AI::placeStone in played[" << this->_played.y << "][" << this->_played.x << "]" << std::endl;
	int		wr = 0;
	int		tmp;
	int		pos = -1;

	this->_played = this->_algorithm->EasyPlay(map);
	for (int y = 0; y < 19; ++y)
		for (int x = 0; x < 19; ++x)
			this->_board[y][x] = map[y][x];
	if (this->_played.x == -1)
		this->_nodes = this->_algorithm->CreateNodesList(this->_board, this->_color, 1, NULL);
	for (std::list<Node *>::iterator it = this->_nodes.begin(); it != this->_nodes.end(); ++it)
	{
		tmp = (*it)->WinsRate();
		if (tmp > wr)
		{
			wr = tmp;
			this->_played = (*it)->GetPos();
		}
	}
	//std::cout << "AI::placeStone out played[" << this->_played.y << "][" << this->_played.x << "]" << std::endl;
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