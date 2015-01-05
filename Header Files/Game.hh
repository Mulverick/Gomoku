#ifndef GAME_HH
#define GAME_HH

#include <SFML/Graphics.hpp>
#include <utility>

#include <vector>
#include "Arbitre.hh"
#include "Human.hh"
#include "AxelAI.h"
#include "AI.hh"
#include "Text.hh"
#include "Sprite.hh"
#include "MainMenu.hh"
#include "WinnerMenu.hh"

class Game
{
public:
	Game();
	~Game();

	void restart();
	void	run();
	template <typename Type> void	reset(void)
	{
		IPlayer	*(player[2]);
		int		it = rand() % 2;
		player[0] = new Human(BLACK);
		player[1] = new Type(WHITE, _map);

		delete _players.back();
		_players.pop_back();
		delete _players.back();
		_players.pop_back();
		_players.push_back(player[0]);
		_players.push_back(player[1]);
	}
	template <> void	reset<Human>(void)
	{
		IPlayer	*(player[2]);
		int		it = rand() % 2;
		player[0] = new Human(BLACK);
		player[1] = new Human(WHITE);

		delete _players.back();
		_players.pop_back();
		delete _players.back();
		_players.pop_back();
		_players.push_back(player[0]);
		_players.push_back(player[1]);
	}


private:
	void _close();
	void _draw();
	void _drawCursor(Sprite &);
	bool _initialize();
	void _onClick();
	bool _update();

	std::vector<IPlayer*> _players;
	sf::RenderWindow _window;
	Arbitre _arbitre;
	Sprite _goban;
	Sprite _white;
	Sprite _black;
	Sprite _sb;
	Text _text;
	MainMenu _mainMenu;
	WinnerMenu _winnerMenu;
	int _playerColor;
	//char _map[361];
	char	**_map;
};

#endif // GAME_HH
