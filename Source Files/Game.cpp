#include <SFML/Window/Event.hpp>
#include <iostream>
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

	_window.draw(_goban.getSprite());
	_white.setColor(sf::Color(255, 255, 255, 255));
	_black.setColor(sf::Color(255, 255, 255, 255));
	for (int i = 0; i < 361; ++i)
	{
		switch (_map[i])
		{
		case WHITE:
			_white.setPosition((i % 19) * CELL_SIZE, (i / 19) * CELL_SIZE);
			_window.draw(_white.getSprite());
			break;
		case BLACK:
			_black.setPosition((i % 19) * CELL_SIZE, (i / 19) * CELL_SIZE);
			_window.draw(_black.getSprite());
			break;
		default:
			break;
		}
	}
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
	_window.create(sf::VideoMode(WIN_SIZE, WIN_SIZE), "Gomoku", sf::Style::Titlebar | sf::Style::Close);
	if (!_window.isOpen())
		return false;
	_goban.loadFromFile("../Assets/goban.png");
	_white.loadFromFile("../Assets/white.png");
	_black.loadFromFile("../Assets/black.png");
	_playerColor = WHITE;
	_players.push_back(new Human(WHITE));
	_players.push_back(new Human(BLACK));
	_arbitre.updateRules(true, false);
	return true;
}

void Game::_onClick()
{
	int cellPosition = (sf::Mouse::getPosition(_window).y / CELL_SIZE) * 19 + (sf::Mouse::getPosition(_window).x / CELL_SIZE);
	if (_arbitre.checkMove((_playerColor == WHITE ? _players[0]->onClickHandler(cellPosition) : _players[1]->onClickHandler(cellPosition)), _map, _playerColor) == true)
	{
		_playerColor == WHITE ? _players[0]->placeStone(_map) : _players[1]->placeStone(_map);
		_playerColor = (_playerColor == WHITE ? BLACK : WHITE);
		
	}
	else
		_playerColor == WHITE ? _players[0]->wrongMove() : _players[1]->wrongMove();
}

bool Game::_update()
{
	if (!_window.isOpen())
		return false;
	sf::Event e;
	while (_window.pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
			return false;
		if (e.type == sf::Event::MouseButtonPressed)
			_onClick();
	}
	return true;
}