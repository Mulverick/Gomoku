#include "AxelAI.h"

#include <future>
#include <list>
#include <random>

#include "utils.hh"
#include "Arbitre.hh"

AxelAI::AxelAI(int color, char const *map)
	: _color(color),
	_turn((color == BLACK)),
	_played(-1),
	_map(map) {}
AxelAI::~AxelAI(void) {}

int		AxelAI::onClickHandler(int cellPosition) { return (-1); }
void	AxelAI::placeStone(char *map)
{
	std::list<std::future<int>>		results;
	std::list<std::pair<int, int>>	pos;
	for (int it = 0; it < 19 * 19; ++it)
	{
		if (!map[it])
		{
			pos.emplace_back(it, 0);
			results.emplace_back(std::async(std::bind([this] (int pos, int color) {
				char	map[19 * 19];
				std::memcpy(map, _map, sizeof(map));
				int res = 0;
				int myColor = color;

				Arbitre	ar;
				ar.updateRules(true, true);
				if (!ar.checkMove(pos, map, color))
					return (0);
				map[pos] = color;
				std::default_random_engine			generator;
				std::uniform_int_distribution<int>	distribution(0, 19*19 - 1);
				auto getNewPos = std::bind(distribution, generator);
				while (!ar.isWinner())
				{
					color = 2 - color;
					do {
						pos = getNewPos();
					} while (map[pos] || !ar.checkMove(pos, map, color));
					map[pos] = color;
				}
				
				if (myColor == color)
					res += 1;

				return (res);
			}, it, _color)));
			break;
		}
	}
	auto	itr = results.begin();
	auto	itp = pos.begin();
	while (itp != pos.end())
	{
		itp->second = itr->get();
		itr = results.erase(itr);
		++itp;
	}
	auto	fina = pos.begin();
	for (itp = pos.begin(); itp != pos.end(); ++itp)
	{
		if (itp->second > fina->second)
			fina = itp;
	}
	_played = fina->first;
	if (_played != -1)
		map[_played] = _color;
}

void	AxelAI::changeTurn(void) { _turn = !_turn; _played = -1; }
void	AxelAI::wrongMove(void) { _played = -1; }

int		AxelAI::hasPlayed(void) const { return (_played); }
int		AxelAI::getColor(void) const { return (_color); }
Type	AxelAI::getType(void) const { return (OTHER); }
