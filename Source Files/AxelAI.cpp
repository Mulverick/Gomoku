#include "AxelAI.h"

#include <future>
#include <list>
#include <random>
#include <iostream>

#include "utils.hh"
#include "Arbitre.hh"
#include <stdlib.h>

AxelAI::AxelAI(int color, char const *map) : _color(color), _turn((color == BLACK)), _played(-1), _map(map) {}
AxelAI::~AxelAI(void) {}

int		AxelAI::onClickHandler(int cellPosition) { return (-1); }
void	AxelAI::placeStone(char *map)
{
	if (_played != -1)
		map[_played] = _color;
}

void	AxelAI::changeTurn(void)
{
	_played = -1;
	_turn = !_turn;
	if (_turn)
	{
		std::async([this] {

			int adv = (_color == WHITE ? BLACK : WHITE);
			std::list<std::pair<int, int>>	pos;

			{
				char	map[19 * 19];
				char	test[19 * 19];
				std::memcpy(map, _map, sizeof(map));

				Arbitre	ar;
				for (int it = 0; it < 19 * 19; ++it)
				{
					if (map[it])
						continue;
					map[it] = _color;
					if (ar.checkThree(it, map, 1))
					{
						std::memcpy(test, _map, sizeof(map));
						if (ar.checkMove(it, test, _color))
							pos.emplace_back(it, 0);
					}
					map[it] = adv;
					if (ar.checkThree(it, map, 2))
					{
						std::memcpy(test, _map, sizeof(map));
						if (ar.checkMove(it, test, _color))
							pos.emplace_back(it, 0);
					}
					map[it] = 0;
				}
			}

			if (pos.empty())
			{
				{
					char	map[19 * 19];
					char	test[19 * 19];
					std::memcpy(map, _map, sizeof(map));

					Arbitre	ar;
					for (int it = 0; it < 19 * 19; ++it)
					{
						if (map[it])
							continue;
						map[it] = _color;
						if (ar.checkTwo(it, map, 1))
						{
							std::memcpy(test, _map, sizeof(map));
							if (ar.checkMove(it, test, _color))
								pos.emplace_back(it, 0);
						}
						map[it] = adv;
						if (ar.checkTwo(it, map, 2))
						{
							std::memcpy(test, _map, sizeof(map));
							if (ar.checkMove(it, test, _color))
								pos.emplace_back(it, 0);
						}
						map[it] = 0;
					}
				}
			}

			if (pos.empty())
			{
				for (int it = 0; it < 19 * 19; ++it)
					if (!_map[it] && (((it + 1) % 19 > it % 19 && _map[it + 1]) || ((it - 1) % 19 < it % 19 && _map[it - 1])
						|| (it + 19 < 19 * 19 && (it + 19) / 19 > it / 19 && _map[it + 19]) || (it - 19 >= 0 && (it - 19) / 19 < it / 19 && _map[it - 19])
						|| (it + 18 < 19 * 19 && (it - 1) % 19 < it % 19 && (it + 19) / 19 > it / 19 && _map[it + 18]) || (it - 18 >= 0 && (it + 1) % 19 > it % 19 && (it - 19) / 19 < it / 19 && _map[it - 18])
						|| (it + 20 < 19 * 19 && (it + 1) % 19 > it % 19 && (it + 19) / 19 > it / 19 && _map[it + 20]) || (it - 20 >= 0 && (it - 1) % 19 < it % 19 && (it - 19) / 19 < it / 19 && _map[it - 20])))
						pos.emplace_back(it, 0);
			}

			std::list<std::future<int>>		results;

			for (auto it = pos.begin(); it != pos.end(); ++it)
			{
					int cell = it->first;
					int color = _color;
					char	map[19 * 19];
					int res = 0;
					int myColor = color;
					int myPos = cell;
					
					for (int simu = 0; simu < (pos.size() > 5 ? 10 : 50); ++simu)
					{
						std::memcpy(map, _map, sizeof(map));
						color = myColor;
						cell = myPos;
						Arbitre	ar;
						if (!ar.checkMove(cell, map, color))
							return (0);
						map[cell] = color;
						while (!ar.isWinner())
						{
							color = (color == WHITE ? BLACK : WHITE);
							do {
								cell = rand() % (19 * 19);
							} while (map[cell] || !ar.checkMove(cell, map, color));
							map[cell] = color;
						}

						if (myColor == color)
							res += 1;
					}
					it->second = res;
			}
			auto	itp = pos.begin();
			auto	fina = pos.end();
			for (itp = pos.begin(); itp != pos.end(); ++itp)
			{
				if (fina == pos.end() || itp->second > fina->second)
					fina = itp;
			}
			if (fina == pos.end())
				_played = 0;
			else
				_played = fina->first;
			return (0);
		});
	}
}
void	AxelAI::wrongMove(void) { _played = -1; }

int		AxelAI::hasPlayed(void) const { return (_played); }
int		AxelAI::getColor(void) const { return (_color); }
Type	AxelAI::getType(void) const { return (OTHER); }
