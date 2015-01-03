#include <SFML/Window/Event.hpp>
#include <iostream>
#include <sstream>
#include "Game.hh"
#include "Utils.hh"

Game::Game()
{
	for (int i = 0; i < 361; ++i)
		_map[i] = 0;
}

Game::~Game()
{
}

void Game::run()
{
	if (!_initialize())
		return;
	while (_update())
	{
		if (_players[0]->hasPlayed() != -1)
		{
			_players[0]->changeTurn();
			_players[1]->changeTurn();
		}
		else if (_players[1]->hasPlayed() != -1)
		{
			_players[0]->changeTurn();
			_players[1]->changeTurn();
		}
		_window.clear();
		_draw();
		_window.display();
	}
	_close();
}

void Game::_close()
{
	_window.close();
}

void Game::_draw()
{
	Human *tmp;
	std::stringstream ss;
	std::stringstream ss2;

	_window.draw(_goban.getSprite());
	_white.setColor(sf::Color(255, 255, 255, 255));
	_black.setColor(sf::Color(255, 255, 255, 255));
	for (int i = 0; i < 361; ++i)
	{
		switch (_map[i])
		{
		case WHITE:
			_white.setPosition((float)((i % 19) * CELL_SIZE), (float)((i / 19) * CELL_SIZE));
			_window.draw(_white.getSprite());
			break;
		case BLACK:
			_black.setPosition((float)((i % 19) * CELL_SIZE), (float)((i / 19) * CELL_SIZE));
			_window.draw(_black.getSprite());
			break;
		default:
			break;
		}
	}
	_sb.setPosition(0.0f, 798.0f);
	_window.draw(_sb.getSprite());
	_white.setPosition(30.0f, 825.0f);
	_window.draw(_white.getSprite());
	ss << (int)_arbitre._prisoner[0];
	std::string str = ss.str();
	_text.setString(" X " + str);
	_text.setPosition(sf::Vector2f(70.0f, 830.0f));
	_text.draw(_window);
	ss2 << (int)_arbitre._prisoner[1];
	str = ss2.str();
	_text.setString(str + " X ");
	_text.setPosition(sf::Vector2f(670.0f, 830.0f));
	_text.draw(_window);
	_black.setPosition(725.0f, 825.0f);
	_window.draw(_black.getSprite());
	if (_players[0]->getType() == HUMAN)
		_text.setString("Player 1");
	else
		_text.setString("Ia 1");
	_text.setPosition(sf::Vector2f(260.0f, 830.0f));
	_text.draw(_window);
	if (_players[1]->getType() == HUMAN)
		_text.setString("Player 2");
	else
		_text.setString("Ia 2");
	_text.setPosition(sf::Vector2f(430.0f, 830.0f));
	_text.draw(_window);
	if (dynamic_cast<Human*>(_players[0]) != 0 && dynamic_cast<Human*>(_players[1]) != 0)
		_drawCursor((_playerColor == WHITE ? _white : _black));
	else if (((tmp = dynamic_cast<Human*>(_players[0])) != 0 && dynamic_cast<Human*>(_players[1]) == 0)
			|| (dynamic_cast<Human*>(_players[0]) == 0 && (tmp = dynamic_cast<Human*>(_players[1])) != 0))
	{
		_drawCursor((tmp->getColor() == WHITE ? _white : _black));
	}
}

void Game::_drawCursor(Sprite &sprite)
{
	if (_map[(sf::Mouse::getPosition(_window).y / CELL_SIZE) * 19 + (sf::Mouse::getPosition(_window).x / CELL_SIZE)])
		return;
	sf::Vector2i mousePosition = sf::Mouse::getPosition(_window);
	if (mousePosition.x >= 0 && mousePosition.x < WIN_SIZE && mousePosition.y >= 0 && mousePosition.y < WIN_SIZE)
	{
		sprite.setPosition(Utils::toCellPosition(mousePosition));
		sprite.setColor(sf::Color(255, 255, 255, 128));
		_window.draw(sprite.getSprite());
	}
}

bool Game::_initialize()
{
	_window.create(sf::VideoMode(WIN_SIZE, WIN_SIZE + 100), "Gomoku", sf::Style::Titlebar | sf::Style::Close);
	if (!_window.isOpen())
		return false;
	_goban.loadFromFile("../Assets/goban.png");
	_sb.loadFromFile("../Assets/scoreBoard.png");
	_black.loadFromFile("../Assets/black.png");
	_white.loadFromFile("../Assets/white.png");
	_text.setFont("../Assets/fontBambo.ttf");
	_text.setColor(sf::Color::Black);
	_text.setFontSize(30);
	_playerColor = BLACK;
	_players.push_back(new Human(BLACK));
	_players.push_back(new Human(WHITE));
	_arbitre.updateRules(false, false);
	return true;
}

void Game::_onClick()
{
	bool ret;
	int cellPosition = (sf::Mouse::getPosition(_window).y / CELL_SIZE) * 19 + (sf::Mouse::getPosition(_window).x / CELL_SIZE);
	if ((ret = _arbitre.checkMove((_playerColor == BLACK ? _players[0]->onClickHandler(cellPosition) : _players[1]->onClickHandler(cellPosition)), _map, _playerColor)) == true)
	{
		if (_playerColor == BLACK)
			_players[0]->placeStone(_map);
		else
			_players[1]->placeStone(_map);
		_playerColor = (_playerColor == WHITE ? BLACK : WHITE);
		
	}
	else
		_playerColor == BLACK ? _players[0]->wrongMove() : _players[1]->wrongMove();
}

bool Game::_update()
{
	if (!_window.isOpen())
		return false;
	Type type = _playerColor == BLACK ? _players[0]->getType() : _players[1]->getType();

	if (type == HUMAN)
	{
		sf::Event e;
		while (_window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				return false;
			if (e.type == sf::Event::MouseButtonPressed)
				_onClick();
		}
	}
	else
	{
		_playerColor == BLACK ? _players[0]->placeStone(_map) : _players[1]->placeStone(_map);
		_playerColor = (_playerColor == WHITE ? BLACK : WHITE);
	}
	return true;
}