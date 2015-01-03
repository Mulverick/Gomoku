#include "Arbitre.hh"
#include <iostream>

Arbitre::Arbitre()
{
	_prisoner[0] = 0;
	_prisoner[1] = 0;
	_isWinner = false;
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
	{
		//std::cout << color << " gagne !" << std::endl;
		return true;
	}
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
		if (R(1, color))
		{
			if (R(2, color) && NR(3))
				nb3 += 1 + (recursive ? checkDoubleThree(PR(1)) + checkDoubleThree(PR(2)) - 2 : 0);
			else if (R(2, 0) && R(3, color) && NR(4))
				nb3 += 1 + (recursive ? checkDoubleThree(PR(1)) + checkDoubleThree(PR(3)) - 2 : 0);
		}
		else if (R(1, 0) && R(2, color) && R(3, color) && NR(4))
			nb3 += 1 + (recursive ? checkDoubleThree(PR(2)) + checkDoubleThree(PR(3)) - 2 : 0);
	if (NR(1))
		if (L(1, color))
		{
			if (L(2, color) && NL(3))
				nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PL(2)) - 2 : 0);
			else if (L(2, 0) && L(3, color) && NL(4))
				nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PL(3)) - 2 : 0);
		}
		else if (L(1, 0) && L(2, color) && L(3, color) && NL(4))
			nb3 += 1 + (recursive ? checkDoubleThree(PL(2)) + checkDoubleThree(PL(3)) - 2 : 0);
	if (NL(2))
	{
		if (NR(2) && L(1, color) && R(1, color))
			nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PR(1)) - 2 : 0);
		else if (NR(3) && L(1, color) && R(1, 0) && R(2, color))
			nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PR(2)) - 2 : 0);
	}
	else if (NL(3) && NR(2) && L(2, color) && L(1, 0) && R(1, color))
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
		if (R(1, color))
		{
			if (R(2, color) && NR(3))
				nb3 += 1 + (recursive ? checkDoubleThree(PR(1)) + checkDoubleThree(PR(2)) - 2 : 0);
			else if (R(2, 0) && R(3, color) && NR(4))
				nb3 += 1 + (recursive ? checkDoubleThree(PR(1)) + checkDoubleThree(PR(3)) - 2 : 0);
		}
		else if (R(1, 0) && R(2, color) && R(3, color) && NR(4))
			nb3 += 1 + (recursive ? checkDoubleThree(PR(2)) + checkDoubleThree(PR(3)) - 2 : 0);
	if (NR(1))
		if (L(1, color))
		{
			if (L(2, color) && NL(3))
				nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PL(2)) - 2 : 0);
			else if (L(2, 0) && L(3, color) && NL(4))
				nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PL(3)) - 2 : 0);
		}
		else if (L(1, 0) && L(2, color) && L(3, color) && NL(4))
			nb3 += 1 + (recursive ? checkDoubleThree(PL(2)) + checkDoubleThree(PL(3)) - 2 : 0);
	if (NL(2))
	{
		if (NR(2) && L(1, color) && R(1, color))
			nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PR(1)) - 2 : 0);
		else if (NR(3) && L(1, color) && R(1, 0) && R(2, color))
			nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PR(2)) - 2 : 0);
	}
	else if (NL(3) && NR(2) && L(2, color) && L(1, 0) && R(1, color))
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
		if (R(1, color))
		{
			if (R(2, color) && NR(3))
				nb3 += 1 + (recursive ? checkDoubleThree(PR(1)) + checkDoubleThree(PR(2)) - 2 : 0);
			else if (R(2, 0) && R(3, color) && NR(4))
				nb3 += 1 + (recursive ? checkDoubleThree(PR(1)) + checkDoubleThree(PR(3)) - 2 : 0);
		}
		else if (R(1, 0) && R(2, color) && R(3, color) && NR(4))
			nb3 += 1 + (recursive ? checkDoubleThree(PR(2)) + checkDoubleThree(PR(3)) - 2 : 0);
	if (NR(1))
		if (L(1, color))
		{
			if (L(2, color) && NL(3))
				nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PL(2)) - 2 : 0);
			else if (L(2, 0) && L(3, color) && NL(4))
				nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PL(3)) - 2 : 0);
		}
		else if (L(1, 0) && L(2, color) && L(3, color) && NL(4))
			nb3 += 1 + (recursive ? checkDoubleThree(PL(2)) + checkDoubleThree(PL(3)) - 2 : 0);
	if (NL(2))
	{
		if (NR(2) && L(1, color) && R(1, color))
			nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PR(1)) - 2 : 0);
		else if (NR(3) && L(1, color) && R(1, 0) && R(2, color))
			nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PR(2)) - 2 : 0);
	}
	else if (NL(3) && NR(2) && L(2, color) && L(1, 0) && R(1, color))
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
#define PL(p)	(pos - (p * 18)),  map, color, false

	if (NL(1))
		if (R(1, color))
		{
			if (R(2, color) && NR(3))
				nb3 += 1 + (recursive ? checkDoubleThree(PR(1)) + checkDoubleThree(PR(2)) - 2 : 0);
			else if (R(2, 0) && R(3, color) && NR(4))
				nb3 += 1 + (recursive ? checkDoubleThree(PR(1)) + checkDoubleThree(PR(3)) - 2 : 0);
		}
		else if (R(1, 0) && R(2, color) && R(3, color) && NR(4))
			nb3 += 1 + (recursive ? checkDoubleThree(PR(2)) + checkDoubleThree(PR(3)) - 2 : 0);
	if (NR(1))
		if (L(1, color))
		{
			if (L(2, color) && NL(3))
				nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PL(2)) - 2 : 0);
			else if (L(2, 0) && L(3, color) && NL(4))
				nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PL(3)) - 2 : 0);
		}
		else if (L(1, 0) && L(2, color) && L(3, color) && NL(4))
			nb3 += 1 + (recursive ? checkDoubleThree(PL(2)) + checkDoubleThree(PL(3)) - 2 : 0);
	if (NL(2))
	{
		if (NR(2) && L(1, color) && R(1, color))
			nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PR(1)) - 2 : 0);
		else if (NR(3) && L(1, color) && R(1, 0) && R(2, color))
			nb3 += 1 + (recursive ? checkDoubleThree(PL(1)) + checkDoubleThree(PR(2)) - 2 : 0);
	}
	else if (NL(3) && NR(2) && L(2, color) && L(1, 0) && R(1, color))
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

static bool isEatable(int next, int dir, char const *map, int color){
	int it1;
	int it2;
	int ocolor;

	ocolor = (color == WHITE ? BLACK : WHITE);
	if (dir != 1)
	{
		it1 = next + 1;
		it2 = next - 1;
		if (it1 % 19 != 0 && it2 % 19 != 18)
			if ((map[it1] == ocolor && map[it2] == color) || (map[it1] == color && map[it2] == ocolor))
				return (true);
	}
	if (dir != 18)
	{ 
		it1 = next + 18;
		it2 = next - 18;
		if (it1 % 19 != 18 && it1 / 19 != 19 && it2 % 19 != 0 && it2 / 19 > 0)
			if ((map[it1] == ocolor && map[it2] == color) || (map[it1] == color && map[it2] == ocolor))
				return (true);
	}
	if (dir != 19)
	{ 
		it1 = next + 19;
		it2 = next - 19;
		if (it1 / 19 != 19 && it2 / 19 > 0)
			if ((map[it1] == ocolor && map[it2] == color) || (map[it1] == color && map[it2] == ocolor))
				return (true);
	}
	if (dir != 20)
	{
		it1 = next + 20;
		it2 = next - 20;
		if (it1 % 19 != 0 && it1 / 19 != 19 && it2 % 19 != 18 && it2 / 19)
			if ((map[it1] == ocolor && map[it2] == color) || (map[it1] == color && map[it2] == ocolor))
				return (true);
	}
	return false;
}

static bool isBreakable(int pos, char const *map, int color, int nb, int dir){
	int next;
	int it;
	bool rt = false;

	while (nb >= 5)
	{
		next = pos;
		it = 0;
		while (it < 5)
		{
			if (isEatable(next, dir, map, color) == true)
			{
				rt = true;
				break;
			}
			next += dir;
			it++;
		}
		if (it == 5)
			return (false);
		if (rt == true)
		{
			nb -= (next % 19 - pos % 19);
			pos = next;
		}
		pos += dir;
		nb--;
	}
	return (rt);
}

bool Arbitre::getIsWinner(){
	return _isWinner;
}

bool Arbitre::checkWinner(int pos, char const *map, int color){
	int	nb;
	int next;
	if (((color == WHITE ? _prisoner[0] : _prisoner[1])) >= 10)
	{
		_isWinner = true;
		return true;
	}
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
	{
		if (_ruleOptionalEnd == false)
		{
			_isWinner = true;
			return true;
		}
		else if (_ruleOptionalEnd == true && isBreakable(++next, map, color, nb, 1) == false)
		{
			_isWinner = true;
			return true;
		}
	}
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
	{
		next += 19;
		if (_ruleOptionalEnd == false)
		{
			_isWinner = true;
			return true;
		}
		else if (_ruleOptionalEnd == true && isBreakable(next, map, color, nb, 19) == false)
		{
			_isWinner = true;
			return true;
		}
	}
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
	{
		next += 20;
		if (_ruleOptionalEnd == false)
		{
			_isWinner = true;
			return true;
		}
		else if (_ruleOptionalEnd == true && isBreakable(next, map, color, nb, 20) == false)
		{
			_isWinner = true;
			return true;
		}
	}
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
	{
		next += 18;
		if (_ruleOptionalEnd == false)
		{
			_isWinner = true;
			return true;
		}
		else if (_ruleOptionalEnd == true && isBreakable(next, map, color, nb, 18) == false)
		{
			_isWinner = true;
			return true;
		}
	}
	return (false);
}
void Arbitre::updateRules(bool r1, bool r2){
	_ruleDoublethree = r1;
	_ruleOptionalEnd = r2;
}

bool	Arbitre::_ruleDoublethree = true;
bool	Arbitre::_ruleOptionalEnd = true;