#include "AxelAI.h"

#include <future>
#include <list>
#include <random>
#include <iostream>

#include "utils.hh"
#include "Arbitre.hh"
#include <stdlib.h>

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
		if (!map[it] && (((it + 1) % 19 > it % 19 && map[it + 1]) || ((it - 1) % 19 < it % 19 && map[it - 1])
			|| (it + 19 < 19 * 19 && (it + 19) / 19 > it / 19 && map[it + 19]) || (it - 19 >= 0 && (it - 19) / 19 < it / 19 && map[it - 19])))
		{
			std::cout << it << std::endl;
			auto toto =
/*			pos.emplace_back(it, 0);
			results.emplace_back(std::async(std::bind(*/[this](int pos, int color) {
				char	map[19 * 19];
				int res = 0;
				int myColor = color;
				int myPos = pos;

				for (int simu = 0; simu < 100; ++simu)
				{
					std::memcpy(map, _map, sizeof(map));
					color = myColor;
					pos = myPos;
					Arbitre	ar;
					if (!ar.checkMove(pos, map, color))
						return (0);
					map[pos] = color;
					while (!ar.isWinner())
					{
						color = (color == WHITE ? BLACK : WHITE);
						do {
							pos = rand() % (19 * 19);
						} while (map[pos] || !ar.checkMove(pos, map, color));
						//pos = rand() % (19 * 19);
						//while (map[pos] || !ar.checkMove(pos, map, color))
						//	pos = rand() % (19 * 19);
						map[pos] = color;
					}

					if (myColor == color)
						res += 1;
				}

				return (res);
			}/*, it, _color)))*/;
			pos.emplace_back(it, toto(it, _color));
		}
	}
	//auto	itr = results.begin();
	auto	itp = pos.begin();
	//while (itp != pos.end())
	//{
	//	itp->second = itr->get();
	//	if (itp->second)
	//		std::cout << itp->first << "\t" << itp->second << std::endl;
	//	itr = results.erase(itr);
	//	++itp;
	//}
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
