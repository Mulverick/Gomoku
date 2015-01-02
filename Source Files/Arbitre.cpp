#include "Arbitre.hh"
#include <iostream>

DoubleThree::DoubleThree(int nb1, int nb2, int nb3) : _first(nb1), _second(nb2), _third(nb3) {}
DoubleThree::DoubleThree(DoubleThree const &cpy) : _first(cpy._first), _second(cpy._second), _third(cpy._third) {}
DoubleThree::~DoubleThree(){}
DoubleThree &DoubleThree::operator=(DoubleThree const &cpy){
	_first = cpy._first;
	_second = cpy._second;
	_third = cpy._third;
	return (*this);
}
bool DoubleThree::operator==(DoubleThree const &a) const {
	if (_first == a._first || _first == a._second || _first == a._third ||
		_second == a._first || _second == a._second || _second == a._third ||
		_third == a._first || _third == a._second || _third == a._third)
		return true;
	return false;
}
int DoubleThree::getFirst() const{
	return _first;
}
int DoubleThree::getSecond() const{
	return _second;
}
int DoubleThree::getThird() const{
	return _third;
}

Arbitre::Arbitre()
{
	_prisoner[0] = 0;
	_prisoner[1] = 0;
}


Arbitre::~Arbitre()
{
}

bool Arbitre::checkMove(int cell, char *map, int color)
{
	if (cell == -1)
		return false;
	if (map[cell])
		return false;
	map[cell] = color;
	if (_ruleDoublethree == true && checkDoubleThree(cell, map, color) > 1)
	{
		map[cell] = 0;
		return (false);
	}
	map[cell] = 0;
	std::deque<sf::Vector2i> coord;
	if ((coord = checkEat(cell, map, color)).empty() == false)
	{
		while (coord.empty() == false)
		{
			color == WHITE ? _prisoner[0] += 2 : _prisoner[1] += 2;
			map[coord.front().x] = 0;
			map[coord.front().y] = 0;
			coord.pop_front();
		}
	}
	 if (checkWinner(cell, map, color) == true)
		return true; 
	return (true);
}

int		Arbitre::checkDoubleThree(int pos, char const *map, int color, bool recursive)
{
	int	nb3 = 0;

	if (!recursive && map[pos] != color)
		return (0);

	// horizontal

#define R(p, c)	((pos + p) % 19 > pos % 19 && map[pos + p] == c)
#define NR(p)	((pos + p) % 19 <= pos % 19 || map[pos + p] != color)
#define PR(p)	(pos + p), map, color, false
#define L(p, c)	((pos - p) % 19 < pos % 19 && map[pos - p] == c)
#define NL(p)	((pos - p) % 19 >= pos % 19 || map[pos - p] != color)
#define PL(p)	(pos - p), map, color, false

	if (NL(1))
	{
		if (R(1, color) && R(2, color) && NR(3))
			nb3 += 1 + (recursive ? checkDoubleThree(PR(1)) + checkDoubleThree(PR(2)) - 2 : 0);
		if (R(1, 0) && R(2, color) && R(3, color) && NR(4))
			nb3 += 1 + (recursive ? checkDoubleThree(PR(2)) + checkDoubleThree(PR(3)) - 2 : 0);
		if (R(1, color) && R(2, 0) && R(3, color) && NR(4))
			nb3 += 1 + (recursive ? checkDoubleThree(PR(1)) + checkDoubleThree(PR(3)) - 2 : 0);		
	}
	if (NR(1))
	{
		if (L(1, color) && L(2, color) && NL(3))
			nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PL(2)) - 2 : 0);
		if (L(1, 0) && L(2, color) && L(3, color) && NL(4))
			nb3 += 1 + (recursive ? checkDoubleThree(PL(2)) + checkDoubleThree(PL(3)) - 2 : 0);
		if (L(1, color) && L(2, 0) && L(3, color) && NL(4))
			nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PL(3)) - 2 : 0);
	}
	if (NL(2) && NR(2) && L(1, color) && R(1, color))
		nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PR(1)) - 2 : 0);
	if (NL(2) && NR(3) && L(1, color) && R(1, 0) && R(2, color))
		nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PR(2)) - 2 : 0);
	if (NL(3) && NR(2) && L(2, color) && L(1, 0) && R(1, color))
		nb3 += 1 + (recursive ? checkDoubleThree(PL(2)) + checkDoubleThree(PR(1)) - 2 : 0);

#undef R
#undef NR
#undef PR
#undef L
#undef NL
#undef PL

	// vertical

#define R(p, c)	((pos + (p * 19)) / 19 > pos / 19 && map[pos + (p * 19)] == c)
#define NR(p)	((pos + (p * 19)) / 19 <= pos / 19 || map[pos + (p * 19)] != color)
#define PR(p)	(pos + (p * 19)),  map, color, false
#define L(p, c)	((pos - (p * 19)) / 19 < pos / 19 && map[pos - (p * 19)] == c)
#define NL(p)	((pos - (p * 19)) / 19 >= pos / 19 || map[pos - (p * 19)] != color)
#define PL(p)	(pos - (p * 19)),  map, color, false

	if (NL(1))
	{
		if (R(1, color) && R(2, color) && NR(3))
			nb3 += 1 + (recursive ? checkDoubleThree(PR(1)) + checkDoubleThree(PR(2)) - 2 : 0);
		if (R(1, 0) && R(2, color) && R(3, color) && NR(4))
			nb3 += 1 + (recursive ? checkDoubleThree(PR(2)) + checkDoubleThree(PR(3)) - 2 : 0);
		if (R(1, color) && R(2, 0) && R(3, color) && NR(4))
			nb3 += 1 + (recursive ? checkDoubleThree(PR(1)) + checkDoubleThree(PR(3)) - 2 : 0);
	}
	if (NR(1))
	{
		if (L(1, color) && L(2, color) && NL(3))
			nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PL(2)) - 2 : 0);
		if (L(1, 0) && L(2, color) && L(3, color) && NL(4))
			nb3 += 1 + (recursive ? checkDoubleThree(PL(2)) + checkDoubleThree(PL(3)) - 2 : 0);
		if (L(1, color) && L(2, 0) && L(3, color) && NL(4))
			nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PL(3)) - 2 : 0);
	}
	if (NL(2) && NR(2) && L(1, color) && R(1, color))
		nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PR(1)) - 2 : 0);
	if (NL(2) && NR(3) && L(1, color) && R(1, 0) && R(2, color))
		nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PR(2)) - 2 : 0);
	if (NL(3) && NR(2) && L(2, color) && L(1, 0) && R(1, color))
		nb3 += 1 + (recursive ? checkDoubleThree(PL(2)) + checkDoubleThree(PR(1)) - 2 : 0);

#undef R
#undef NR
#undef PR
#undef L
#undef NL
#undef PL


	// Diago 1

#define R(p, c)	((pos + p) % 19 > pos % 19 && (pos + (p * 19)) / 19 > pos / 19 && map[pos + (p * 20)] == c)
#define NR(p)	((pos + p) % 19 <= pos % 19 && (pos + (p * 19)) / 19 <= pos / 19 || map[pos + (p * 20)] != color)
#define PR(p)	(pos + (p * 20)),  map, color, false
#define L(p, c)	((pos - p) % 19 < pos % 19 && (pos - (p * 19)) / 19 < pos / 19 && map[pos - (p * 20)] == c)
#define NL(p)	((pos - p) % 19 >= pos % 19 && (pos - (p * 19)) / 19 >= pos / 19 || map[pos - (p * 20)] != color)
#define PL(p)	(pos - (p * 20)),  map, color, false

	if (NL(1))
	{
		if (R(1, color) && R(2, color) && NR(3))
			nb3 += 1 + (recursive ? checkDoubleThree(PR(1)) + checkDoubleThree(PR(2)) - 2 : 0);
		if (R(1, 0) && R(2, color) && R(3, color) && NR(4))
			nb3 += 1 + (recursive ? checkDoubleThree(PR(2)) + checkDoubleThree(PR(3)) - 2 : 0);
		if (R(1, color) && R(2, 0) && R(3, color) && NR(4))
			nb3 += 1 + (recursive ? checkDoubleThree(PR(1)) + checkDoubleThree(PR(3)) - 2 : 0);
	}
	if (NR(1))
	{
		if (L(1, color) && L(2, color) && NL(3))
			nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PL(2)) - 2 : 0);
		if (L(1, 0) && L(2, color) && L(3, color) && NL(4))
			nb3 += 1 + (recursive ? checkDoubleThree(PL(2)) + checkDoubleThree(PL(3)) - 2 : 0);
		if (L(1, color) && L(2, 0) && L(3, color) && NL(4))
			nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PL(3)) - 2 : 0);
	}
	if (NL(2) && NR(2) && L(1, color) && R(1, color))
		nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PR(1)) - 2 : 0);
	if (NL(2) && NR(3) && L(1, color) && R(1, 0) && R(2, color))
		nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PR(2)) - 2 : 0);
	if (NL(3) && NR(2) && L(2, color) && L(1, 0) && R(1, color))
		nb3 += 1 + (recursive ? checkDoubleThree(PL(2)) + checkDoubleThree(PR(1)) - 2 : 0);

#undef R
#undef NR
#undef PR
#undef L
#undef NL
#undef PL


	// Diago 1

#define R(p, c)	((pos - p) % 19 < pos % 19 && (pos + (p * 19)) / 19 > pos / 19 && map[pos + (p * 18)] == c)
#define NR(p)	((pos - p) % 19 >= pos % 19 && (pos + (p * 19)) / 19 <= pos / 19 || map[pos + (p * 18)] != color)
#define PR(p)	(pos + (p * 18)),  map, color, false
#define L(p, c)	((pos + p) % 19 > pos % 19 && (pos - (p * 19)) / 19 < pos / 19 && map[pos - (p * 18)] == c)
#define NL(p)	((pos + p) % 19 <= pos % 19 && (pos - (p * 19)) / 19 >= pos / 19 || map[pos - (p * 18)] != color)
#define PL(p)	(pos + (p * 18)),  map, color, false

	if (NL(1))
	{
		if (R(1, color) && R(2, color) && NR(3))
			nb3 += 1 + (recursive ? checkDoubleThree(PR(1)) + checkDoubleThree(PR(2)) - 2 : 0);
		if (R(1, 0) && R(2, color) && R(3, color) && NR(4))
			nb3 += 1 + (recursive ? checkDoubleThree(PR(2)) + checkDoubleThree(PR(3)) - 2 : 0);
		if (R(1, color) && R(2, 0) && R(3, color) && NR(4))
			nb3 += 1 + (recursive ? checkDoubleThree(PR(1)) + checkDoubleThree(PR(3)) - 2 : 0);
	}
	if (NR(1))
	{
		if (L(1, color) && L(2, color) && NL(3))
			nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PL(2)) - 2 : 0);
		if (L(1, 0) && L(2, color) && L(3, color) && NL(4))
			nb3 += 1 + (recursive ? checkDoubleThree(PL(2)) + checkDoubleThree(PL(3)) - 2 : 0);
		if (L(1, color) && L(2, 0) && L(3, color) && NL(4))
			nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PL(3)) - 2 : 0);
	}
	if (NL(2) && NR(2) && L(1, color) && R(1, color))
		nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PR(1)) - 2 : 0);
	if (NL(2) && NR(3) && L(1, color) && R(1, 0) && R(2, color))
		nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PR(2)) - 2 : 0);
	if (NL(3) && NR(2) && L(2, color) && L(1, 0) && R(1, color))
		nb3 += 1 + (recursive ? checkDoubleThree(PL(2)) + checkDoubleThree(PR(1)) - 2 : 0);

#undef R
#undef NR
#undef PR
#undef L
#undef NL
#undef PL

	return (nb3);
}

void	Arbitre::checkOnEat(int cell, int nb, int color, char const *map, std::deque<sf::Vector2i> &coords)
{
	int tmpx, tmpy, tmpz;
	int ocolor;

	ocolor = color == WHITE ? BLACK : WHITE;
	tmpx = cell + nb;
	tmpy = tmpx + nb;
	tmpz = tmpy + nb;
	if (nb < 0)
	{
		if (tmpz >= 0 && map[tmpx] == ocolor && map[tmpy] == ocolor && map[tmpz] == color)
		{
			if (((nb == -1 || nb == -20) && (cell % 19) < (tmpz % 19)) || ((nb == -18) && (cell % 19) > (tmpz % 19)))
				return;
			coords.push_back(sf::Vector2i(tmpx, tmpy));
		}
	}
	else
	{
		if (tmpz < 361 && map[tmpx] == ocolor && map[tmpy] == ocolor && map[tmpz] == color)
		{
			if (((nb == 1 || nb == 20) && (cell % 19) >(tmpz % 19)) || ((nb == 18) && (cell % 19) < (tmpz % 19)))
				return;
			coords.push_back(sf::Vector2i(tmpx, tmpy));
		}
	}
}

std::deque<sf::Vector2i> Arbitre::checkEat(int cell, char const *map, int color){
	std::deque<sf::Vector2i> coords;

	checkOnEat(cell, -19, color, map, coords);
	checkOnEat(cell, -1, color, map, coords);
	checkOnEat(cell, 19, color, map, coords);
	checkOnEat(cell, 1, color, map, coords);
	checkOnEat(cell, -20, color, map, coords);
	checkOnEat(cell, -18, color, map, coords);
	checkOnEat(cell, 20, color, map, coords);
	checkOnEat(cell, 18, color, map, coords);
	return coords;
}

bool Arbitre::checkWinner(int pos, char const *map, int color){
	int	nb;
	int next;
	if (((color == WHITE ? _prisoner[0] : _prisoner[1])) >= 10)
		return true;
	nb = 1;
	next = pos + 1;
	while (next % 19 != 0 && map[next] == color)
	{
		++next;
		++nb;
	}
	next = pos - 1;
	while (next % 19 != 18 && map[next] == color)
	{
		--next;
		++nb;
	}
	if (nb >= 5)
		return (true);
	nb = 1;
	next = pos + 19;
	while (next / 19 != 19 && map[next] == color)
	{
		next += 19;
		++nb;
	}
	next = pos - 19;
	while (next / 19 > 0 && map[next] == color)
	{
		next -= 19;
		++nb;
	}
	if (nb >= 5)
		return (true);
	nb = 1;
	next = pos + 20;
	while (next % 19 != 0 && next / 19 != 19 && map[next] == color)
	{
		next += 20;
		++nb;
	}
	next = pos - 20;
	while (next % 19 != 18 && next / 19 > 0 && map[next] == color)
	{
		next -= 20;
		++nb;
	}
	if (nb >= 5)
		return (true);
	nb = 1;
	next = pos + 18;
	while (next % 19 != 18 && next / 19 != 19 && map[next] == color)
	{
		next += 18;
		++nb;
	}
	next = pos - 18;
	while (next % 19 != 0 && next / 19 > 0 && map[next] == color)
	{
		next -= 18;
		++nb;
	}
	if (nb >= 5)
		return (true);
	return (false);
}
void Arbitre::updateRules(bool r1, bool r2){
	_ruleDoublethree = r1;
	_ruleOptionalEnd = r2;
}