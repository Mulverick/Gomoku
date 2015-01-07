#include "AMenu.hh"
#include "Game.hh"

AMenu::AMenu(AWidget *parent) :
  AWidget(parent)
{
  _isActive = true;
}

AMenu::~AMenu()
{
}

void AMenu::draw(sf::RenderWindow &window)
{
  if (!_isActive)
    return ;
  window.draw(_backgroundColor);
  for (std::vector<AWidget *>::iterator it = _components.begin(); it != _components.end(); ++it)
    (*it)->draw(window);
}

void AMenu::setActive(bool state)
{
  _isActive = state;
}

void AMenu::setGameInstance(Game *game)
{
  _gameInstance = game;
}

Game		*AMenu::getGameInstance(void) { return (_gameInstance); }
Game const	*AMenu::getGameInstance(void) const { return (_gameInstance); }
