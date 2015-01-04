#ifndef GAME_HH
#define GAME_HH

#include <SFML/Graphics.hpp>

#include <vector>
#include "Arbitre.hh"
#include "Human.hh"
#include "AI.hh"
#include "Text.hh"
#include "Sprite.hh"
#include "MainMenu.hh"

class Game
{
public:
	Game();
	~Game();

	void run();

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
	int _playerColor;
	char _map[361];
};

#endif // GAME_HH
