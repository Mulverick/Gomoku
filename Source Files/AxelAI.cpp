#include "AxelAI.h"

#include <future>
#include <list>
#include <random>
#include <iostream>

#include "utils.hh"
#include "Arbitre.hh"
#include <cstring>

AxelAI::AxelAI(int color, char const * const *map) : _color(color), _turn((color == BLACK)), _played(-1 ,-1), _map(map) {}
AxelAI::~AxelAI(void) {}

Vector<int> const &AxelAI::onClickHandler(Vector<int> const &cellPosition) { return (_played); }
void	AxelAI::placeStone(char * const *map)
{
	if (_played.x != -1)
		map[_played.y][_played.x] = _color;
}

void	AxelAI::changeTurn(void)
{
	_played.x = -1;
	_turn = !_turn;
	if (_turn)
	{
		/*std::async([this]*/ {

			int adv = (_color == WHITE ? BLACK : WHITE);
			std::list<std::pair<Vector<int>, int>>	pos;
			Vector<int>	p;

			char	**map;
			char	**test;

			map = new char*[19];
			test = new char*[19];
			for (int y = 0; y < 19; ++y)
			{
				map[y] = new char[19];
				test[y] = new char[19];
			}

			{

				for (int y = 0; y < 19; ++ y)
					for (int x = 0; x < 19; ++x)
						map[y][x] = _map[y][x];

				Arbitre	ar;
				for (p.y = 0; p.y < 19; ++p.y)
					for (p.x = 0; p.x < 19; ++p.x)
					{
						if (map[p.y][p.x])
							continue;
						map[p.y][p.x] = _color;
						if (ar.checkThree(p, map, 1))
						{
							for (int y = 0; y < 19; ++y)
								for (int x = 0; x < 19; ++x)
									test[y][x] = _map[y][x];
							if (ar.checkMove(p, test, _color))
								pos.emplace_back(p, 0);
						}
						map[p.y][p.x] = adv;
						if (ar.checkThree(p, map, 2))
						{
							for (int y = 0; y < 19; ++y)
								for (int x = 0; x < 19; ++x)
									test[y][x] = _map[y][x];
							if (ar.checkMove(p, test, _color))
								pos.emplace_back(p, 0);
						}
						map[p.y][p.x] = 0;
					}
			}

			if (pos.empty())
			{
				{
					for (int y = 0; y < 19; ++y)
						for (int x = 0; x < 19; ++x)
							map[y][x] = _map[y][x];

					Arbitre	ar;
					for (p.y = 0; p.y < 19; ++p.y)
						for (p.x = 0; p.x < 19; ++p.x)
						{
							if (map[p.y][p.x])
								continue;
							map[p.y][p.x] = _color;
							if (ar.checkTwo(p, map, 1))
							{
								for (int y = 0; y < 19; ++y)
									for (int x = 0; x < 19; ++x)
										test[y][x] = _map[y][x];
								if (ar.checkMove(p, test, _color))
									pos.emplace_back(p, 0);
							}
							map[p.y][p.x] = adv;
							if (ar.checkTwo(p, map, 2))
							{
								for (int y = 0; y < 19; ++y)
									for (int x = 0; x < 19; ++x)
										test[y][x] = _map[y][x];
								if (ar.checkMove(p, test, _color))
									pos.emplace_back(p, 0);
							}
							map[p.y][p.x] = 0;
						}
				}
			}

			if (pos.empty())
			{
				for (p.y = 0; p.y < 19; ++p.y)
					for (p.x = 0; p.x < 19; ++p.x)
						if (!_map[p.y][p.x] && ((p.x + 1 < 19 && _map[p.y][p.x + 1] == _color) || (p.x - 1 >= 0 && _map[p.y][p.x - 1] == _color)
							|| (p.y + 1 < 19 && _map[p.y + 1][p.x] == _color) || (p.y - 1 >= 0 && _map[p.y - 1][p.x] == _color)
							|| (p.x + 1 < 19 && p.y + 1 < 19 && _map[p.y + 1][p.x + 1] == _color) || (p.x - 1 >= 0 && p.y - 1 >= 0 && _map[p.y - 1][p.x - 1] == _color)
							|| (p.x - 1 >= 0 && p.y + 1 < 19 && _map[p.y + 1][p.x - 1] == _color) || (p.x + 1 < 19 && p.y - 1 >= 0 && _map[p.y - 1][p.x + 1] == _color)))
							pos.emplace_back(p, 0);
			}

			if (pos.empty())
			{
				for (p.y = 0; p.y < 19; ++p.y)
					for (p.x = 0; p.x < 19; ++p.x)
						if (!_map[p.y][p.x] && ((p.x + 1 < 19 && _map[p.y][p.x + 1]) || (p.x - 1 >= 0 && _map[p.y][p.x - 1])
							|| (p.y + 1 < 19 && _map[p.y + 1][p.x]) || (p.y - 1 >= 0 && _map[p.y - 1][p.x])
							|| (p.x + 1 < 19 && p.y + 1 < 19 && _map[p.y + 1][p.x + 1]) || (p.x - 1 >= 0 && p.y - 1 >= 0 && _map[p.y - 1][p.x - 1])
							|| (p.x - 1 >= 0 && p.y + 1 < 19 && _map[p.y + 1][p.x - 1]) || (p.x + 1 < 19 && p.y - 1 >= 0 && _map[p.y - 1][p.x + 1])))
							pos.emplace_back(p, 0);
			}

			for (auto it = pos.begin(); it != pos.end(); ++it)
			{
					Vector<int> cell = it->first;
					int			color = _color;
					int			res = 0;
					int			myColor = color;
					Vector<int> myPos = cell;
					
					for (int simu = 0; simu < (pos.size() > 5 ? 10 : 50); ++simu)
					{
						for (int y = 0; y < 19; ++y)
							for (int x = 0; x < 19; ++x)
								map[y][x] = _map[y][x];
						color = myColor;
						cell = myPos;
						Arbitre	ar;
						if (!ar.checkMove(cell, map, color))
							return /*(0)*/;
						map[cell.y][cell.x] = color;
						while (!ar.isWinner())
						{
							color = (color == WHITE ? BLACK : WHITE);
							do {
								cell.x = rand() % 19;
								cell.y = rand() % 19;
							} while (map[cell.y][cell.x] || !ar.checkMove(cell, map, color));
							map[cell.y][cell.x] = color;
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
				_played = Vector<int>(0, 0);
			else
				_played = fina->first;


			for (int y = 0; y < 19; ++y)
			{
				delete[] map[y];
				delete[] test[y];
			}
			delete[] map;
			delete[] test;
			//return (0);
		}/*);*/
		if (_played.x == -1)
		{
			int toto = 0;
		}
	}
}
void	AxelAI::wrongMove(void) { _played.x = -1; }

Vector<int>	const	&AxelAI::hasPlayed(void) const { return (_played); }
int		AxelAI::getColor(void) const { return (_color); }
Type	AxelAI::getType(void) const { return (OTHER); }
