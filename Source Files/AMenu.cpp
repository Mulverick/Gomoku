#include "AMenu.hh"

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
  for (std::vector<AWidget *>::iterator it = _components.begin(); it != _components.end(); ++it)
    (*it)->setActive(state);
}
