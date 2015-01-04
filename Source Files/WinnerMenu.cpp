#include "Game.hh"
#include "WinnerMenu.hh"
#include "Arbitre.hh"

WinnerMenu::WinnerMenu(AWidget *parent) :
  AMenu(parent)
{
	_newGame = new Button(this);
	_winner = new Text(this);

	_newGame->setSize(sf::Vector2f(250, 50));
	_newGame->setPosition(sf::Vector2f(125, 225));
	_newGame->setBackgroundTexture("../Assets/button_select.png");
	_newGame->setFont("../Assets/fontBambo.ttf");
	_newGame->setFontSize(30);
	_newGame->setText("Nouvelle partie");
	_newGame->setAction([this](){_gameInstance->restart();});
	_winner->setPosition(sf::Vector2f(300, 300));
	_winner->setFont("../Assets/fontBambo.ttf");
	_winner->setColor(sf::Color::Red);
	_winner->setFontSize(42);
  setPosition(sf::Vector2f(149, 249));
  setSize(sf::Vector2f(500, 300));
  setBackgroundColor(sf::Color(0, 0, 0, 127));
}

WinnerMenu::~WinnerMenu()
{
}

void WinnerMenu::setWinner(std::string winner){
	_winner->setString(winner + " win !");
}

void WinnerMenu::onClickHandler(const sf::Vector2f &mousePosition)
{
  for (std::vector<AWidget *>::iterator it = _components.begin(); it != _components.end(); ++it)
    (*it)->onClickHandler(mousePosition);
}
