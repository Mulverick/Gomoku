#include "Arbitre.hh"
#include <iostream>

Arbitre::Arbitre()
{
	_prisoner[0] = 0;
	_prisoner[1] = 0;
	_isWinner = false;
	_winner = 0;
}


Arbitre::~Arbitre()
{
}

void Arbitre::resetWinner(){
	if (_isWinner == true)
		_isWinner = false;
}

bool Arbitre::checkMove(Vector<int> const &pos, char * const *map, int color)
{
	if (pos.x == -1 || pos.y == -1)
		return false;
	if (map[pos.y][pos.x])
		return false;
	map[pos.y][pos.x] = color;
	//checkWinner(pos, map, color);
	if (_ruleDoublethree == true /*&& !_isWinner*/ && checkDoubleThree(pos, map, color) > 1)
	{
		map[pos.y][pos.x] = 0;
		return (false);
	}
	std::deque<Vector<Vector<int>>> coord;
	std::deque<Vector<int>> toCheck;
	checkEat(pos, map, color, coord);
	if (coord.empty() == false)
	{
		while (coord.empty() == false)
		{
			color == BLACK ? _prisoner[0] += 2 : _prisoner[1] += 2;
			map[coord.front().x.y][coord.front().x.x] = 0;
			map[coord.front().y.y][coord.front().y.x] = 0;
			coord.pop_front();
		}
		toCheck.push_back(pos + Vector<int>(0,	3));
		toCheck.push_back(pos + Vector<int>(0,	-3));
		toCheck.push_back(pos + Vector<int>(3,	0));
		toCheck.push_back(pos + Vector<int>(-3,	0));
		toCheck.push_back(pos + Vector<int>(3, 3));
		toCheck.push_back(pos + Vector<int>(3, -3));
		toCheck.push_back(pos + Vector<int>(-3, 3));
		toCheck.push_back(pos + Vector<int>(-3, -3));
	}
	auto it = toCheck.begin();
	while (it != toCheck.end())
		if (it->x < 0 || it->y < 0 || it->x >= 19 || it->y >= 19)
			it = toCheck.erase(it);
		else
			++it;
	toCheck.push_back(pos);
	while (toCheck.size())
	{
		if (checkWinner(toCheck.front(), map, color) == true)
		{
			map[pos.y][pos.x] = 0;
			if (_winner == 0)
				_winner = color;
			return true;
		}
		toCheck.pop_front();
	}
	map[pos.y][pos.x] = 0;
	return (true);
}

int		Arbitre::checkDoubleThree(Vector<int> const &pos, char const * const *map, int color, bool recursive)
{
	int	nb3 = 0;

	if (!recursive && map[pos.y][pos.x] != color)
		return (0);

	// horizontal

#define R(p, c)	((pos.x + p) < 19 && map[pos.y][pos.x + p] == c)
#define NR(p)	((pos.x + p) >= 19 || map[pos.y][pos.x + p] != color)
#define PR(p)	Vector<int>(pos.x + p, pos.y), map, color, false
#define L(p, c)	((pos.x - p) >= 0 && map[pos.y][pos.x - p] == c)
#define NL(p)	((pos.x - p) < 0 || map[pos.y][pos.x - p] != color)
#define PL(p)	Vector<int>(pos.x - p, pos.y), map, color, false

	if (L(1, 0))
		if (R(1, color))
		{
			if (R(2, color) && R(3, 0))
				nb3 += 1 + (recursive ? checkDoubleThree(PR(1)) + checkDoubleThree(PR(2)) - 2 : 0);
			else if (R(2, 0) && R(3, color) && R(4, 0))
				nb3 += 1 + (recursive ? checkDoubleThree(PR(1)) + checkDoubleThree(PR(3)) - 2 : 0);
		}
		else if (R(1, 0) && R(2, color) && R(3, color) && R(4, 0))
			nb3 += 1 + (recursive ? checkDoubleThree(PR(2)) + checkDoubleThree(PR(3)) - 2 : 0);
	if (R(1, 0))
		if (L(1, color))
		{
			if (L(2, color) && L(3, 0))
				nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PL(2)) - 2 : 0);
			else if (L(2, 0) && L(3, color) && L(4, 0))
				nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PL(3)) - 2 : 0);
		}
		else if (L(1, 0) && L(2, color) && L(3, color) && L(4, 0))
			nb3 += 1 + (recursive ? checkDoubleThree(PL(2)) + checkDoubleThree(PL(3)) - 2 : 0);
	if (L(2, 0))
	{
		if (R(2, 0) && L(1, color) && R(1, color))
			nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PR(1)) - 2 : 0);
		else if (R(3, 0) && L(1, color) && R(1, 0) && R(2, color))
			nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PR(2)) - 2 : 0);
	}
	else if (L(3, 0) && R(2, 0) && L(2, color) && L(1, 0) && R(1, color))
		nb3 += 1 + (recursive ? checkDoubleThree(PL(2)) + checkDoubleThree(PR(1)) - 2 : 0);

#undef R
#undef NR
#undef PR
#undef L
#undef NL
#undef PL

	// vertical

#define R(p, c)	((pos.y + p) < 19 && map[pos.y + p][pos.x] == c)
#define NR(p)	((pos.y + p) >= 19 || map[pos.y + p][pos.x] != color)
#define PR(p)	Vector<int>(pos.x, pos.y + p),  map, color, false
#define L(p, c)	((pos.y - p) >= 0 && map[pos.y - p][pos.x] == c)
#define NL(p)	((pos.y - p) < 0 || map[pos.y - p][pos.x] != color)
#define PL(p)	Vector<int>(pos.x, pos.y - p),  map, color, false

	if (L(1, 0))
	if (R(1, color))
	{
		if (R(2, color) && R(3, 0))
			nb3 += 1 + (recursive ? checkDoubleThree(PR(1)) + checkDoubleThree(PR(2)) - 2 : 0);
		else if (R(2, 0) && R(3, color) && R(4, 0))
			nb3 += 1 + (recursive ? checkDoubleThree(PR(1)) + checkDoubleThree(PR(3)) - 2 : 0);
	}
	else if (R(1, 0) && R(2, color) && R(3, color) && R(4, 0))
		nb3 += 1 + (recursive ? checkDoubleThree(PR(2)) + checkDoubleThree(PR(3)) - 2 : 0);
	if (R(1, 0))
	if (L(1, color))
	{
		if (L(2, color) && L(3, 0))
			nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PL(2)) - 2 : 0);
		else if (L(2, 0) && L(3, color) && L(4, 0))
			nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PL(3)) - 2 : 0);
	}
	else if (L(1, 0) && L(2, color) && L(3, color) && L(4, 0))
		nb3 += 1 + (recursive ? checkDoubleThree(PL(2)) + checkDoubleThree(PL(3)) - 2 : 0);
	if (L(2, 0))
	{
		if (R(2, 0) && L(1, color) && R(1, color))
			nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PR(1)) - 2 : 0);
		else if (R(3, 0) && L(1, color) && R(1, 0) && R(2, color))
			nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PR(2)) - 2 : 0);
	}
	else if (L(3, 0) && R(2, 0) && L(2, color) && L(1, 0) && R(1, color))
		nb3 += 1 + (recursive ? checkDoubleThree(PL(2)) + checkDoubleThree(PR(1)) - 2 : 0);

#undef R
#undef NR
#undef PR
#undef L
#undef NL
#undef PL


	// Diago 1

#define R(p, c)	((pos.x + p) < 19 && (pos.y + p) < 19 && map[pos.y + p][pos.x + p] == c)
#define NR(p)	((pos.x + p) >= 19 || (pos.y + p) >= 19 || map[pos.y + p][pos.x + p] != color)
#define PR(p)	Vector<int>(pos.x + p, pos.y + p),  map, color, false
#define L(p, c)	((pos.x - p) >= 0 && (pos.y - p) >= 0 && map[pos.y - p][pos.x - p] == c)
#define NL(p)	((pos.x - p) < 0 || (pos.y - p) < 0 || map[pos.y - p][pos.x - p] != color)
#define PL(p)	Vector<int>(pos.x - p, pos.y - p),  map, color, false

	if (L(1, 0))
	if (R(1, color))
	{
		if (R(2, color) && R(3, 0))
			nb3 += 1 + (recursive ? checkDoubleThree(PR(1)) + checkDoubleThree(PR(2)) - 2 : 0);
		else if (R(2, 0) && R(3, color) && R(4, 0))
			nb3 += 1 + (recursive ? checkDoubleThree(PR(1)) + checkDoubleThree(PR(3)) - 2 : 0);
	}
	else if (R(1, 0) && R(2, color) && R(3, color) && R(4, 0))
		nb3 += 1 + (recursive ? checkDoubleThree(PR(2)) + checkDoubleThree(PR(3)) - 2 : 0);
	if (R(1, 0))
	if (L(1, color))
	{
		if (L(2, color) && L(3, 0))
			nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PL(2)) - 2 : 0);
		else if (L(2, 0) && L(3, color) && L(4, 0))
			nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PL(3)) - 2 : 0);
	}
	else if (L(1, 0) && L(2, color) && L(3, color) && L(4, 0))
		nb3 += 1 + (recursive ? checkDoubleThree(PL(2)) + checkDoubleThree(PL(3)) - 2 : 0);
	if (L(2, 0))
	{
		if (R(2, 0) && L(1, color) && R(1, color))
			nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PR(1)) - 2 : 0);
		else if (R(3, 0) && L(1, color) && R(1, 0) && R(2, color))
			nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PR(2)) - 2 : 0);
	}
	else if (L(3, 0) && R(2, 0) && L(2, color) && L(1, 0) && R(1, color))
		nb3 += 1 + (recursive ? checkDoubleThree(PL(2)) + checkDoubleThree(PR(1)) - 2 : 0);

#undef R
#undef NR
#undef PR
#undef L
#undef NL
#undef PL


	// Diago 2

#define R(p, c)	((pos.x - p) >= 0 && (pos.y + p) < 19 && map[pos.y + p][pos.x - p] == c)
#define NR(p)	((pos.x - p) < 0 || (pos.y + p) >= 19 || map[pos.y + p][pos.x - p] != color)
#define PR(p)	Vector<int>(pos.x - p, pos.y + p),  map, color, false
#define L(p, c)	((pos.x + p) < 19 && (pos.y - p) >= 0 && map[pos.y - p][pos.x + p] == c)
#define NL(p)	((pos.x + p) >= 19 || (pos.y - p) < 0 || map[pos.y - p][pos.x + p] != color)
#define PL(p)	Vector<int>(pos.x + p, pos.y - p),  map, color, false

	if (L(1, 0))
	if (R(1, color))
	{
		if (R(2, color) && R(3, 0))
			nb3 += 1 + (recursive ? checkDoubleThree(PR(1)) + checkDoubleThree(PR(2)) - 2 : 0);
		else if (R(2, 0) && R(3, color) && R(4, 0))
			nb3 += 1 + (recursive ? checkDoubleThree(PR(1)) + checkDoubleThree(PR(3)) - 2 : 0);
	}
	else if (R(1, 0) && R(2, color) && R(3, color) && R(4, 0))
		nb3 += 1 + (recursive ? checkDoubleThree(PR(2)) + checkDoubleThree(PR(3)) - 2 : 0);
	if (R(1, 0))
	if (L(1, color))
	{
		if (L(2, color) && L(3, 0))
			nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PL(2)) - 2 : 0);
		else if (L(2, 0) && L(3, color) && L(4, 0))
			nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PL(3)) - 2 : 0);
	}
	else if (L(1, 0) && L(2, color) && L(3, color) && L(4, 0))
		nb3 += 1 + (recursive ? checkDoubleThree(PL(2)) + checkDoubleThree(PL(3)) - 2 : 0);
	if (L(2, 0))
	{
		if (R(2, 0) && L(1, color) && R(1, color))
			nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PR(1)) - 2 : 0);
		else if (R(3, 0) && L(1, color) && R(1, 0) && R(2, color))
			nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PR(2)) - 2 : 0);
	}
	else if (L(3, 0) && R(2, 0) && L(2, color) && L(1, 0) && R(1, color))
		nb3 += 1 + (recursive ? checkDoubleThree(PL(2)) + checkDoubleThree(PR(1)) - 2 : 0);

#undef R
#undef NR
#undef PR
#undef L
#undef NL
#undef PL

	return (nb3);
}

void	Arbitre::checkOnEat(Vector<int> const &pos, Vector<int> const &nb, int color, char const * const *map, std::deque<Vector<Vector<int>>> &coords)
{
	Vector<int> tmpx, tmpy, tmpz;
	int ocolor;

	ocolor = color == WHITE ? BLACK : WHITE;
	tmpx = pos + nb;
	tmpy = tmpx + nb;
	tmpz = tmpy + nb;
	if (tmpx.x >= 0 && tmpy.x >= 0 && tmpz.x >= 0
		&& tmpx.x < 19 && tmpy.x < 19 && tmpz.x < 19
		&& tmpx.y >= 0 && tmpy.y >= 0 && tmpz.y >= 0
		&& tmpx.y < 19 && tmpy.y < 19 && tmpz.y < 19
		&& map[tmpx.y][tmpx.x] == ocolor
		&& map[tmpy.y][tmpy.x] == ocolor
		&& map[tmpz.y][tmpz.x] == color)
		coords.emplace_back(tmpx, tmpy);
}

void	Arbitre::checkEat(Vector<int> const &cell, char const * const *map, int color, std::deque<Vector<Vector<int>>> &coords)
{
	checkOnEat(cell, Vector<int>(0, -1), color, map, coords);
	checkOnEat(cell, Vector<int>(-1, 0), color, map, coords);
	checkOnEat(cell, Vector<int>(0, 1), color, map, coords);
	checkOnEat(cell, Vector<int>(1, 0), color, map, coords);
	checkOnEat(cell, Vector<int>(-1, -1), color, map, coords);
	checkOnEat(cell, Vector<int>(1, -1), color, map, coords);
	checkOnEat(cell, Vector<int>(1, 1), color, map, coords);
	checkOnEat(cell, Vector<int>(-1, 1), color, map, coords);
}

static bool isCoord(Vector<int> it)
{
	if (it.x >= 0 && it.x < 19 && it.y >= 0 && it.y < 19)
		return true;
	return false;
}

static bool isEatable(Vector<int> const &next, Vector<int> const &dir, char const * const *map, int color)
{
	Vector<int> it1;
	Vector<int> it2;
	Vector<int> it3;
	Vector<int> it4;
	int ocolor;


	ocolor = (color == WHITE ? BLACK : WHITE);
	if (dir.x != 1 || dir.y != 0)
	{
		it1 = next + Vector<int>(1, 0);
		it2 = it1 + Vector<int>(1, 0);
		it3 = next + Vector<int>(-1, 0);
		it4 = it3 + Vector<int>(-1, 0);
		if ((isCoord(it1) == true && isCoord(it2) == true && isCoord(it3) == true && map[next.y][next.x] == color && map[it1.y][it1.x] == color && map[it2.y][it2.x] == ocolor && map[it3.y][it3.x] == 0)
			|| (isCoord(it1) == true && isCoord(it2) == true && isCoord(it3) == true && map[next.y][next.x] == color && map[it1.y][it1.x] == color && map[it3.y][it3.x] == ocolor && map[it2.y][it2.x] == 0)
			|| (isCoord(it1) == true && isCoord(it3) == true && isCoord(it4) == true && map[next.y][next.x] == color && map[it3.y][it3.x] == color && map[it4.y][it4.x] == ocolor && map[it1.y][it1.x] == 0)
			|| (isCoord(it1) == true && isCoord(it3) == true && isCoord(it4) == true && map[next.y][next.x] == color && map[it3.y][it3.x] == color && map[it1.y][it1.x] == ocolor && map[it4.y][it4.x] == 0))
		{
			return (true);
		}
	}
	if (dir.y != 1 || dir.x != -1)
	{ 
		it1 = next + Vector<int>(1, -1);
		it2 = it1 + Vector<int>(1, -1);
		it3 = next + Vector<int>(-1, 1);
		it4 = it3 + Vector<int>(-1, 1);

		if ((isCoord(it1) == true && isCoord(it2) == true && isCoord(it3) == true && map[next.y][next.x] == color && map[it1.y][it1.x] == color && map[it2.y][it2.x] == ocolor && map[it3.y][it3.x] == 0)
			|| (isCoord(it1) == true && isCoord(it2) == true && isCoord(it3) == true && map[next.y][next.x] == color && map[it1.y][it1.x] == color && map[it3.y][it3.x] == ocolor && map[it2.y][it2.x] == 0)
			|| (isCoord(it1) == true && isCoord(it3) == true && isCoord(it4) == true && map[next.y][next.x] == color && map[it3.y][it3.x] == color && map[it4.y][it4.x] == ocolor && map[it1.y][it1.x] == 0)
			|| (isCoord(it1) == true && isCoord(it3) == true && isCoord(it4) == true && map[next.y][next.x] == color && map[it3.y][it3.x] == color && map[it1.y][it1.x] == ocolor && map[it4.y][it4.x] == 0))		{
			return (true);
		}
	}
	if (dir.y != 1)
	{ 
		it1 = next + Vector<int>(0, 1);
		it2 = it1 + Vector<int>(0, 1);
		it3 = next + Vector<int>(0, -1);
		it4 = it3 + Vector<int>(0, -1);
		if ((isCoord(it1) == true && isCoord(it2) == true && isCoord(it3) == true && map[next.y][next.x] == color && map[it1.y][it1.x] == color && map[it2.y][it2.x] == ocolor && map[it3.y][it3.x] == 0)
			|| (isCoord(it1) == true && isCoord(it2) == true && isCoord(it3) == true && map[next.y][next.x] == color && map[it1.y][it1.x] == color && map[it3.y][it3.x] == ocolor && map[it2.y][it2.x] == 0)
			|| (isCoord(it1) == true && isCoord(it3) == true && isCoord(it4) == true && map[next.y][next.x] == color && map[it3.y][it3.x] == color && map[it4.y][it4.x] == ocolor && map[it1.y][it1.x] == 0)
			|| (isCoord(it1) == true && isCoord(it3) == true && isCoord(it4) == true && map[next.y][next.x] == color && map[it3.y][it3.x] == color && map[it1.y][it1.x] == ocolor && map[it4.y][it4.x] == 0))		{
			return (true);
		}
	}
	if (dir.y != 1 || dir.x != 1)
	{
		it1 = next + Vector<int>(1, 1);
		it2 = it1 + Vector<int>(1, 1);
		it3 = next + Vector<int>(-1, -1);
		it4 = it3 + Vector<int>(-1, -1);
		if ((isCoord(it1) == true && isCoord(it2) == true && isCoord(it3) == true && map[next.y][next.x] == color && map[it1.y][it1.x] == color && map[it2.y][it2.x] == ocolor && map[it3.y][it3.x] == 0)
			|| (isCoord(it1) == true && isCoord(it2) == true && isCoord(it3) == true && map[next.y][next.x] == color && map[it1.y][it1.x] == color && map[it3.y][it3.x] == ocolor && map[it2.y][it2.x] == 0)
			|| (isCoord(it1) == true && isCoord(it3) == true && isCoord(it4) == true && map[next.y][next.x] == color && map[it3.y][it3.x] == color && map[it4.y][it4.x] == ocolor && map[it1.y][it1.x] == 0)
			|| (isCoord(it1) == true && isCoord(it3) == true && isCoord(it4) == true && map[next.y][next.x] == color && map[it3.y][it3.x] == color && map[it1.y][it1.x] == ocolor && map[it4.y][it4.x] == 0))		{
			return (true);
		}
	}
	return (false);
}

static bool isBreakable(Vector<int> const &pos, char const * const *map, int color, int nb, Vector<int> const &dir){
	Vector<int> next;
	Vector<int> npos = pos;
	int it;
	bool rt = false;

	while (nb >= 5)
	{
		next = npos;
		it = 0;
		while (it < 5)
		{
			if (isEatable(next, dir, map, color) == true)
			{
				rt = true;
				break;
			}
			next = next + dir;
			it++;
		}
		if (it == 5)
			return (false);
		if (rt == true)
		{
			nb -= it;
			npos = next;
		}
		npos = npos + dir;
		nb--;
	}
	return (rt);
}

bool Arbitre::getIsWinner(){
	return _isWinner;
}

bool Arbitre::checkWinner(Vector<int> const &pos, char const * const *map, int color, bool recusive)
{
	int	nb;
	Vector<int> next = pos;
	if (((color == BLACK ? _prisoner[0] : _prisoner[1])) >= 10)
	{
		_isWinner = true;
		_winner = color;
		return true;
	}
	nb = 1;
	++next.x;
	while (next.x < 19 && map[next.y][next.x] == color)
	{
		if (recusive) checkWinner(next, map, color, false);
		++next.x;
		++nb;
	}
	next.x = pos.x - 1;
	while (next.x >= 0 && map[next.y][next.x] == color)
	{
		if (recusive) checkWinner(next, map, color, false);
		--next.x;
		++nb;
	}
	if (nb >= 5)
	{
		++next.x;
		if (_ruleOptionalEnd == false)
		{
			_isWinner = true;
			return true;
		}
		else if (_ruleOptionalEnd == true && isBreakable(next, map, color, nb, Vector<int>(1, 0)) == false)
		{
			_isWinner = true;
			return true;
		}
	}
	nb = 1;
	next.x = pos.x;
	next.y = pos.y + 1;
	while (next.y < 19 && map[next.y][next.x] == color)
	{
		if (recusive) checkWinner(next, map, color, false);
		++next.y;
		++nb;
	}
	next.y = pos.y - 1;
	while (next.y >= 0 && map[next.y][next.x] == color)
	{
		if (recusive) checkWinner(next, map, color, false);
		--next.y;
		++nb;
	}
	if (nb >= 5)
	{
		++next.y;
		if (_ruleOptionalEnd == false)
		{
			_isWinner = true;
			return true;
		}
		else if (_ruleOptionalEnd == true && isBreakable(next, map, color, nb, Vector<int>(0, 1)) == false)
		{
			_isWinner = true;
			return true;
		}
	}
	nb = 1;
	next.x = pos.x + 1;
	next.y = pos.y + 1;
	while (next.x < 19 && next.y < 19 && map[next.y][next.x] == color)
	{
		if (recusive) checkWinner(next, map, color, false);
		++next.x;
		++next.y;
		++nb;
	}
	next.x = pos.x - 1;
	next.y = pos.y - 1;
	while (next.x >= 0 && next.y >= 0 && map[next.y][next.x] == color)
	{
		if (recusive) checkWinner(next, map, color, false);
		--next.x;
		--next.y;
		++nb;
	}
	if (nb >= 5)
	{
		++next.x;
		++next.y;
		if (_ruleOptionalEnd == false)
		{
			_isWinner = true;
			return true;
		}
		else if (_ruleOptionalEnd == true && isBreakable(next, map, color, nb, Vector<int>(1, 1)) == false)
		{
			_isWinner = true;
			return true;
		}
	}
	nb = 1;
	next.x = pos.x - 1;
	next.y = pos.y + 1;
	while (next.x >= 0 && next.y < 19 && map[next.y][next.x] == color)
	{
		if (recusive) checkWinner(next, map, color, false);
		--next.x;
		++next.y;
		++nb;
	}
	next.x = pos.x + 1;
	next.y = pos.y - 1;
	while (next.x < 19 && next.y >= 0 && map[next.y][next.x] == color)
	{
		if (recusive) checkWinner(next, map, color, false);
		++next.x;
		--next.y;
		++nb;
	}
	if (nb >= 5)
	{
		--next.x;
		++next.y;
		if (_ruleOptionalEnd == false)
		{
			_isWinner = true;
			return true;
		}
		else if (_ruleOptionalEnd == true && isBreakable(next, map, color, nb, Vector<int>(-1, 1)) == false)
		{
			_isWinner = true;
			return true;
		}
	}
	return (false);
}

bool Arbitre::checkThree(Vector<int> const &pos, char const * const *map, int color)
{
	int	nb;
	Vector<int> next = pos;
	nb = 1;
	++next.x;
	while (next.x < 19 && map[next.y][next.x] == color)
	{
		++next.x;
		++nb;
	}
	next.x = pos.x - 1;
	while (next.x >= 0 && map[next.y][next.x] == color)
	{
		--next.x;
		++nb;
	}
	if (nb >= 4)
		return true;
	nb = 1;
	next.x = pos.x;
	next.y = pos.y + 1;
	while (next.y < 19 && map[next.y][next.x] == color)
	{
		++next.y;
		++nb;
	}
	next.y = pos.y - 1;
	while (next.y >= 0 && map[next.y][next.x] == color)
	{
		--next.y;
		++nb;
	}
	if (nb >= 4)
		return true;
	nb = 1;
	next.x = pos.x + 1;
	next.y = pos.y + 1;
	while (next.x < 19 && next.y < 19 && map[next.y][next.x] == color)
	{
		++next.x;
		++next.y;
		++nb;
	}
	next.x = pos.x - 1;
	next.y = pos.y - 1;
	while (next.x >= 0 && next.y >= 0 && map[next.y][next.x] == color)
	{
		--next.x;
		--next.y;
		++nb;
	}
	if (nb >= 4)
		return true;
	nb = 1;
	next.x = pos.x - 1;
	next.y = pos.y + 1;
	while (next.x >= 0 && next.y < 19 && map[next.y][next.x] == color)
	{
		--next.x;
		++next.y;
		++nb;
	}
	next.x = pos.x + 1;
	next.y = pos.y - 1;
	while (next.x < 19 && next.y >= 0 && map[next.y][next.x] == color)
	{
		++next.x;
		--next.y;
		++nb;
	}
	if (nb >= 4)
		return true;
	return (false);
}

bool Arbitre::checkTwo(Vector<int> const &pos, char const * const *map, int color)
{
	int	nb;
	Vector<int> next = pos;
	nb = 1;
	++next.x;
	while (next.x < 19 && map[next.y][next.x] == color)
	{
		++next.x;
		++nb;
	}
	next.x = pos.x - 1;
	while (next.x >= 0 && map[next.y][next.x] == color)
	{
		--next.x;
		++nb;
	}
	if (nb >= 3)
		return true;
	nb = 1;
	next.x = pos.x;
	next.y = pos.y + 1;
	while (next.y < 19 && map[next.y][next.x] == color)
	{
		++next.y;
		++nb;
	}
	next.y = pos.y - 1;
	while (next.y >= 0 && map[next.y][next.x] == color)
	{
		--next.y;
		++nb;
	}
	if (nb >= 3)
		return true;
	nb = 1;
	next.x = pos.x + 1;
	next.y = pos.y + 1;
	while (next.x < 19 && next.y < 19 && map[next.y][next.x] == color)
	{
		++next.x;
		++next.y;
		++nb;
	}
	next.x = pos.x - 1;
	next.y = pos.y - 1;
	while (next.x >= 0 && next.y >= 0 && map[next.y][next.x] == color)
	{
		--next.x;
		--next.y;
		++nb;
	}
	if (nb >= 3)
		return true;
	nb = 1;
	next.x = pos.x - 1;
	next.y = pos.y + 1;
	while (next.x >= 0 && next.y < 19 && map[next.y][next.x] == color)
	{
		--next.x;
		++next.y;
		++nb;
	}
	next.x = pos.x + 1;
	next.y = pos.y - 1;
	while (next.x < 19 && next.y >= 0 && map[next.y][next.x] == color)
	{
		++next.x;
		--next.y;
		++nb;
	}
	if (nb >= 3)
		return true;
	return (false);
}

void Arbitre::updateRules(bool r1, bool r2){
	_ruleDoublethree = r1;
	_ruleOptionalEnd = r2;
}

void Arbitre::clearArbitre()
{
	_isWinner = false;
	_prisoner[0] = 0;
	_prisoner[1] = 0;
}

bool	Arbitre::_ruleDoublethree = true;
bool	Arbitre::_ruleOptionalEnd = true;

bool	Arbitre::isWinner(void) const { return (_isWinner); }
int		Arbitre::getWinner(void) const { return (_winner); }
