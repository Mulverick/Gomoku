#pragma once

#include <vector>
#include <SFML/System/Vector2.hpp>
#include "Utils.hh"
#include <deque>

class DoubleThree{
public:
	DoubleThree(int, int ,int);
	DoubleThree(DoubleThree const &);
	~DoubleThree();
	DoubleThree &operator=(DoubleThree const &);
	bool operator==(DoubleThree const &)const;
	int getFirst() const;
	int getSecond() const;
	int getThird() const;

private:
	int _first;
	int _second;
	int _third;
};

class Arbitre
{
public:
	Arbitre();
	~Arbitre();
	bool checkMove(int, char * const &, int color);
	bool checkDoubleThree();
	bool checkWinner();
	std::deque<sf::Vector2i> checkEat(int, char * const &, int color);
	void updateRules(bool, bool);

private:
	bool _isWinner;
	bool _ruleDoublethree;
	bool _ruleOptionalEnd;
	char _prisoner[2];
	std::vector<DoubleThree> _doubleThree;
};

