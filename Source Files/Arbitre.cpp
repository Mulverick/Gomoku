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

bool Arbitre::checkMove(int cell, char *map, int color){
	if (cell == -1)
		return false;
	if (map[cell])
		return false;
	/* if (_ruleDoublethree == true)
	{
	}*/
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

static void checkOnEat(int cell, int nb, int color, char const *map, std::deque<sf::Vector2i> &coords){
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
bool Arbitre::checkDoubleThree(){
	return (false);
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