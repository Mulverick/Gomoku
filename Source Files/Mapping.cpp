#include		"Mapping.hh"
#include		<iostream>

Mapping::Mapping()
{
	this->_board = new char*[19];
	for (int y = 0; y < 19; ++y)
	{
		this->_board[y] = new char[19];
		for (int x = 0; x < 19; ++x)
			this->_board[y][x] = 0;
	}
}

Mapping::Mapping(char * const *map)
{
	Vector<int>	tmp;

	this->_board = new char*[19];
	for (int y = 0; y < 19; ++y)
	{
		this->_board[y] = new char[19];
		for (int x = 0; x < 19; ++x)
		{
			if (map[y][x] == 0 || map[y][x] == 1 || map[y][x] == 2)
				this->_board[y][x] = map[y][x];
			else
				this->_board[y][x] = 0;
		}
	}
}

Mapping::~Mapping() {}

void		Mapping::VerticalPatern(const Vector<int> &pos, char * const *board, char * const *map, Patern *patern, int i)
{
	Vector<int> tmp;
	int			tmpi;

	tmpi = patern->nbvertblack;
	if (patern->upblack && (pos.y - i >= 0) && (map[pos.y - i][pos.x] == BLACK))
		++patern->nbvertblack;
	else if (patern->upblack)
	{
		patern->upblack = false;
		if ((pos.y - i >= 0) && tmpi > patern->nbvertblack && (map[pos.y - i][pos.x] != WHITE))
		{
			tmp.x = pos.x;
			tmp.y = pos.y - i;
			this->CheckPatern(tmp, board, map);
		}
	}
	tmpi = patern->nbvertwhite;
	if (patern->upwhite && (pos.y - i >= 0) && (map[pos.y - i][pos.x] == WHITE))
		++patern->nbvertwhite;
	else if (patern->upwhite)
	{
		patern->upwhite = false;
		if ((pos.y - i >= 0) && tmpi > patern->nbvertwhite && (map[pos.y - i][pos.x] != BLACK))
		{
			tmp.x = pos.x;
			tmp.y = pos.y - i;
			this->CheckPatern(tmp, board, map);
		}
	}
	tmpi = patern->nbvertblack;
	if (patern->downblack && (pos.y + i < 19) && (map[pos.y + i][pos.x] == BLACK))
		++patern->nbvertblack;
	else if (patern->downblack)
	{
		patern->downblack = false;
		if ((pos.y + i < 19) && tmpi > patern->nbvertblack && (map[pos.y + i][pos.x] != WHITE))
		{
			tmp.x = pos.x;
			tmp.y = pos.y + i;
			this->CheckPatern(tmp, board, map);
		}
	}
	tmpi = patern->nbvertwhite;
	if (patern->downwhite && (pos.y + i < 19) && (map[pos.y + i][pos.x] == WHITE))
		++patern->nbvertwhite;
	else if (patern->downwhite)
	{
		patern->downwhite = false;
		if ((pos.y + i < 19) && tmpi > patern->nbvertwhite && (map[pos.y + i][pos.x] != BLACK))
		{
			tmp.x = pos.x;
			tmp.y = pos.y + i;
			this->CheckPatern(tmp, board, map);
		}
	}
}

void		Mapping::HorizontalPatern(const Vector<int> &pos, char * const *board, char * const *map, Patern *patern, int i)
{
	Vector<int> tmp;
	int			tmpi;

	tmpi = patern->nbhoriblack;
	if (patern->leftblack && pos.x - i >= 0 && map[pos.y][pos.x - i] == BLACK)
		++patern->nbhoriblack;
	else if (patern->leftblack)
	{
		patern->leftblack = false;
		if ((pos.x - i >= 0) && tmpi > patern->nbhoriblack && (map[pos.y][pos.x - i] != WHITE))
		{
			tmp.x = pos.y;
			tmp.y = pos.x - i;
			this->CheckPatern(tmp, board, map);
		}
	}

	tmpi = patern->nbhoriwhite;
	if (patern->leftwhite && pos.x - i >= 0 && map[pos.y][pos.x - i] == WHITE)
		++patern->nbhoriwhite;
	else if (patern->leftwhite)
	{
		patern->leftwhite = false;
		if ((pos.x - i >= 0) && tmpi > patern->nbhoriwhite && (map[pos.y][pos.x - i] != BLACK))
		{
			tmp.x = pos.y;
			tmp.y = pos.x - i;
			this->CheckPatern(tmp, board, map);
		}
	}

	tmpi = patern->nbhoriblack;
	if (patern->rightblack && pos.x + i < 19 && map[pos.y][pos.x + i] == BLACK)
		++patern->nbhoriblack;
	else if (patern->rightblack)
	{
		patern->rightblack = false;
		if ((pos.x + i < 19) && tmpi > patern->nbhoriblack && (map[pos.y][pos.x + i] != WHITE))
		{
			tmp.x = pos.y;
			tmp.y = pos.x + i;
			this->CheckPatern(tmp, board, map);
		}
	}

	tmpi = patern->nbhoriwhite;
	if (patern->rightwhite && pos.x + i < 19 && map[pos.y][pos.x + i] == WHITE)
		++patern->nbhoriwhite;
	else if (patern->rightwhite)
	{
		patern->rightwhite = false;
		if ((pos.x + i < 19) && tmpi > patern->nbhoriwhite && (map[pos.y][pos.x + i] != BLACK))
		{
			tmp.x = pos.y;
			tmp.y = pos.x + i;
			this->CheckPatern(tmp, board, map);
		}
	}
}

void		Mapping::DiagonalOnePatern(const Vector<int> &pos, char * const *board, char * const *map, Patern *patern, int i)
{
	Vector<int> tmp;
	int			tmpi;

	tmpi = patern->nbdionblack;
	if (patern->downleftblack && pos.x - i >= 0 && pos.y + i < 19 && map[pos.y + i][pos.x - i] == BLACK)
		++patern->nbdionblack;
	else if (patern->downleftblack)
	{
		patern->downleftblack = false;
		if ((pos.x - i >= 0) && (pos.y + i < 19) && tmpi > patern->nbdionblack && (map[pos.y + i][pos.x - i] != WHITE))
		{
			tmp.x = pos.y + i;
			tmp.y = pos.x - i;
			this->CheckPatern(tmp, board, map);
		}
	}

	tmpi = patern->nbdionwhite;
	if (patern->downleftwhite && pos.x - i >= 0 && pos.y + i < 19 && map[pos.y + i][pos.x - i] == WHITE)
		++patern->nbdionwhite;
	else if (patern->downleftwhite)
	{
		patern->downleftwhite = false;
		if ((pos.x - i >= 0) && (pos.y + i < 19) && tmpi > patern->nbdionwhite && (map[pos.y + i][pos.x - i] != BLACK))
		{
			tmp.x = pos.y + i;
			tmp.y = pos.x - i;
			this->CheckPatern(tmp, board, map);
		}
	}

	tmpi = patern->nbdionblack;
	if (patern->uprightblack && pos.x + i < 19 && pos.y - i >= 0 && map[pos.y - i][pos.x + i] == BLACK)
		++patern->nbdionblack;
	else if (patern->uprightblack)
	{
		patern->uprightblack = false;
		if ((pos.x + i < 19) && (pos.y - i >= 0) && tmpi > patern->nbdionblack && (map[pos.y - i][pos.x + i] != WHITE))
		{
			tmp.x = pos.y - i;
			tmp.y = pos.x + i;
			this->CheckPatern(tmp, board, map);
		}
	}

	tmpi = patern->nbdionwhite;
	if (patern->uprightwhite && pos.x + i < 19 && pos.y - i >= 0 && map[pos.y - i][pos.x + i] == WHITE)
		++patern->nbdionwhite;
	else if (patern->uprightwhite)
	{
		patern->uprightwhite = false;
		if ((pos.x + i < 19) && (pos.y - i >= 0) && tmpi > patern->nbdionwhite && (map[pos.y - i][pos.x + i] != BLACK))
		{
			tmp.x = pos.y - i;
			tmp.y = pos.x + i;
			this->CheckPatern(tmp, board, map);
		}
	}
}

void		Mapping::DiagonaltwoPatern(const Vector<int> &pos, char * const *board, char * const *map, Patern *patern, int i)
{
	Vector<int> tmp;
	int			tmpi;

	tmpi = patern->nbditwblack;
	if (patern->upleftblack && pos.x - i >= 0 && pos.y - i >= 0 && map[pos.y - i][pos.x - i] == BLACK)
		++patern->nbditwblack;
	else if (patern->upleftblack)
	{
		patern->upleftblack = false;
		if ((pos.x - i >= 0) && (pos.y - i >= 0) && tmpi > patern->nbditwblack && (map[pos.y - i][pos.x - i] != WHITE))
		{
			tmp.x = pos.y - i;
			tmp.y = pos.x - i;
			this->CheckPatern(tmp, board, map);
		}
	}

	tmpi = patern->nbditwwhite;
	if (patern->upleftwhite && pos.x - i >= 0 && pos.y - i >= 0 && map[pos.y - i][pos.x - i] == WHITE)
		++patern->nbditwwhite;
	else if (patern->upleftwhite)
	{
		patern->upleftwhite = false;
		if ((pos.x - i >= 0) && (pos.y - i >= 0) && tmpi > patern->nbditwwhite && (map[pos.y - i][pos.x - i] != BLACK))
		{
			tmp.x = pos.y - i;
			tmp.y = pos.x - i;
			this->CheckPatern(tmp, board, map);
		}
	}

	tmpi = patern->nbditwblack;
	if (patern->downrightblack && pos.x + i < 19 && pos.y + i < 19 && map[pos.y + i][pos.x + i] == BLACK)
		++patern->nbditwblack;
	else if (patern->downrightblack)
	{
		patern->downrightblack = false;
		if ((pos.x + i < 19) && (pos.y + i < 19) && tmpi > patern->nbditwblack && (map[pos.y + i][pos.x + i] != WHITE))
		{
			tmp.x = pos.y + i;
			tmp.y = pos.x + i;
			this->CheckPatern(tmp, board, map);
		}
	}

	tmpi = patern->nbditwwhite;
	if (patern->downrightwhite && pos.x + i < 19 && pos.y + i < 19 && map[pos.y + i][pos.x + i] == WHITE)
		++patern->nbditwwhite;
	else if (patern->downrightwhite)
	{
		patern->downrightwhite = false;
		if ((pos.x + i < 19) && (pos.y + i < 19) && tmpi > patern->nbditwwhite && (map[pos.y + i][pos.x + i] != BLACK))
		{
			tmp.x = pos.y + i;
			tmp.y = pos.x + i;
			this->CheckPatern(tmp, board, map);
		}
	}
}

void		Mapping::CheckPatern(const Vector<int> &pos, char * const *board, char * const *map)
{
	if (map[pos.y][pos.x] == BLACK || map[pos.y][pos.x] == WHITE)
	{
		this->nearPlaces(pos, board, map, WHITE);
		return;
	}
	Patern patern;

	int i = 1;

	while (patern.end != true)
	{
		/*VERTICAL PATERN*/
		this->VerticalPatern(pos, board, map, &patern, i);
		/*VERTICAL PATERN*/

		/*HORIZONTAL PATERN*/
		this->HorizontalPatern(pos, board, map, &patern, i);
		/*HORIZONTAL PATERN*/
	
		/*DIAGONAL ONE PATERN*/
		this->DiagonalOnePatern(pos, board, map, &patern, i);
		/*DIAGONAL ONE PATERN*/

		/*DIAGONAL TWO PATERN*/
		this->DiagonaltwoPatern(pos, board, map, &patern, i);
		/*DIAGONAL TWO PATERN*/

		if (!patern.upblack && !patern.upwhite && !patern.downblack && !patern.downwhite
			&& !patern.rightblack && !patern.rightwhite && !patern.leftblack && !patern.leftwhite
			&& !patern.uprightblack && !patern.uprightwhite && !patern.downleftblack && !patern.downleftwhite
			&& !patern.downrightblack && !patern.downrightwhite && !patern.upleftblack && !patern.upleftwhite)
			patern.end = true;
		++i;
	}

	int nbwhite = patern.nbvertwhite >= patern.nbhoriwhite ? (patern.nbvertwhite >= patern.nbdionwhite ? (patern.nbvertwhite >= patern.nbditwwhite ? patern.nbvertwhite : patern.nbditwwhite) : (patern.nbdionwhite >= patern.nbditwwhite ? patern.nbdionwhite : patern.nbditwwhite))
		: (patern.nbhoriwhite >= patern.nbdionwhite ? (patern.nbhoriwhite >= patern.nbditwwhite ? patern.nbhoriwhite : patern.nbditwwhite) : (patern.nbdionwhite >= patern.nbditwwhite ? patern.nbdionwhite : patern.nbditwwhite));
	int nbblack = patern.nbvertblack >= patern.nbhoriblack ? (patern.nbvertblack >= patern.nbdionblack ? (patern.nbvertblack >= patern.nbditwblack ? patern.nbvertblack : patern.nbditwblack) : (patern.nbdionblack >= patern.nbditwblack ? patern.nbdionblack : patern.nbditwblack))
		: (patern.nbhoriblack >= patern.nbdionblack ? (patern.nbhoriblack >= patern.nbditwblack ? patern.nbhoriblack : patern.nbditwblack) : (patern.nbdionblack >= patern.nbditwblack ? patern.nbdionblack : patern.nbditwblack));

	std::cout << "POS[" << pos.y << "][" << pos.x << "] W[" << nbwhite << "] B[" << nbblack << "]." << std::endl;
	/*if (nbwhite == 5)
		board[pos.y][pos.x] = board[pos.y][pos.x] | FIVE_WHITE;
	else*/ if (nbwhite >= 4)
		board[pos.y][pos.x] = board[pos.y][pos.x] | FOUR_WHITE;
	else if (nbwhite == 3)
		board[pos.y][pos.x] = board[pos.y][pos.x] | THREE_WHITE;

	/*if (nbblack == 5)
		board[pos.y][pos.x] = board[pos.y][pos.x] | FIVE_BLACK;
	else*/ if (nbblack >= 4)
		board[pos.y][pos.x] = board[pos.y][pos.x] | FOUR_BLACK;
	else if (nbblack == 3)
		board[pos.y][pos.x] = board[pos.y][pos.x] | THREE_BLACK;
}

void			Mapping::nearPlaces(Vector<int> const &pos, char *const *board, char * const *map, int color)
{
	Vector<int>	tmp;

	if (pos.x < 18 && map[pos.y][pos.x + 1] == 0)
	{
		tmp.y = pos.y;
		tmp.x = pos.x + 1;
		this->CheckPatern(tmp, board, map);
	}
	if (pos.x > 0 && map[pos.y][pos.x - 1] == 0)
	{
		tmp.y = pos.y;
		tmp.x = pos.x - 1;
		this->CheckPatern(tmp, board, map);
	}
	if (pos.y < 18 && map[pos.y + 1][pos.x] == 0)
	{
		tmp.y = pos.y + 1;
		tmp.x = pos.x;
		this->CheckPatern(tmp, board, map);
	}
	if (pos.y > 0 && map[pos.y - 1][pos.x] == 0)
	{
		tmp.y = pos.y - 1;
		tmp.x = pos.x;
		this->CheckPatern(tmp, board, map);
	}
	if (pos.x < 18 && pos.y < 18 && map[pos.y + 1][pos.x + 1] == 0)
	{
		tmp.y = pos.y + 1;
		tmp.x = pos.x + 1;
		this->CheckPatern(tmp, board, map);
	}
	if (pos.x > 0 && pos.y > 0 && map[pos.y - 1][pos.x - 1] == 0)
	{
		tmp.y = pos.y - 1;
		tmp.x = pos.x - 1;
		this->CheckPatern(tmp, board, map);
	}
	if (pos.y < 18 && pos.x > 0 && map[pos.y + 1][pos.x - 1] == 0)
	{
		tmp.y = pos.y + 1;
		tmp.x = pos.x - 1;
		this->CheckPatern(tmp, board, map);
	}
	if (pos.y > 0 && pos.x < 18 && map[pos.y - 1][pos.x + 1] == 0)
	{
		tmp.y = pos.y - 1;
		tmp.x = pos.x + 1;
		this->CheckPatern(tmp, board, map);
	}
}

void	Mapping::updateMap(char * const *map)
{
	Vector<int>	tmp;

	for (int y = 0; y < 19; ++y)
	{
		for (int x = 0; x < 19; ++x)
		{
			if ((map[y][x] == WHITE && this->_board[y][x] != WHITE)
				|| (map[y][x] == BLACK && this->_board[y][x] != BLACK)
				|| ((map[y][x] == 0) && (this->_board[y][x] == WHITE || this->_board[y][x] == BLACK)))
			{
				this->_board[y][x] = map[y][x];
				tmp.x = x;
				tmp.y = y;
				this->CheckPatern(tmp, this->_board, map);
			}
		}
	}
}

void	Mapping::simpleUpdate(char * const *map)
{
	for (int y = 0; y < 19; ++y)
	{
		for (int x = 0; x < 19; ++x)
		{
			if (((map[y][x] == WHITE || map[y][x] == BLACK) && (this->_board[y][x] != WHITE || this->_board[y][x] != BLACK))
				|| ((map[y][x] == 0) && (this->_board[y][x] == WHITE || this->_board[y][x] == BLACK)))
				this->_board[y][x] = map[y][x];
		}
	}
}

char	**Mapping::getMap()
{
	return this->_board;
}