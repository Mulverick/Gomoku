#pragma once

#include <vector>
#include <SFML/System/Vector2.hpp>
#include "Utils.hh"
#include <deque>

class Arbitre
{
public:
	Arbitre();
	~Arbitre();
	bool getIsWinner();
	bool checkMove(int, char *, int color);
	int checkDoubleThree(int pos, char const *map, int color, bool recursive = true);
	bool checkWinner(int pos, char const *map, int color);
	std::deque<sf::Vector2i> checkEat(int, char const *, int color);
	void updateRules(bool, bool);

	char _prisoner[2];

private:
	void checkOnEat(int cell, int nb, int color, char const *map, std::deque<sf::Vector2i> &coords);


	bool _isWinner;
	bool _ruleDoublethree;
	bool _ruleOptionalEnd;
	std::vector<DoubleThree> _doubleThree;
};