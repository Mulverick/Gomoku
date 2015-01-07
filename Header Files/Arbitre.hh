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
	bool checkMove(Vector<int> const &, char * const *, int color);
	int checkDoubleThree(Vector<int> const &pos, char const * const *map, int color, bool recursive = true);
	bool checkWinner(Vector<int> const &pos, char const * const *map, int color);
	bool checkThree(Vector<int> const &pos, char const * const *map, int color);
	bool checkTwo(Vector<int> const &pos, char const * const *map, int color);
	void checkEat(Vector<int> const &pos, char const * const *, int color, std::deque<Vector<Vector<int>>> &);
	static void updateRules(bool, bool);

	void clearArbitre();
	bool	isWinner(void) const;
	int		getWinner(void) const;
	void resetWinner();
	char _prisoner[2];

private:
	void checkOnEat(Vector<int> const &, Vector<int> const &nb, int color, char const * const *map, std::deque<Vector<Vector<int>>> &);


	bool	_isWinner;
	int		_winner;

	static bool _ruleDoublethree;
	static bool _ruleOptionalEnd;
};
