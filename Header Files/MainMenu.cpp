#include "MainMenu.hh"
#include "Arbitre.hh"

MainMenu::MainMenu(AWidget *parent) :
  AMenu(parent)
{
  _start = new Button(this);
  _pvp = new Button(this);
  _pve = new Button(this);
  _5breakable = new Button(this);
  _doubleThree = new Button(this);

  _start->setSize(sf::Vector2f(200, 50));
  _start->setPosition(sf::Vector2f(150, 225));
  _start->setBackgroundTexture("../Assets/button_unselect.png");
  _start->setFont("../Assets/fontBambo.ttf");
  _start->setFontSize(30);
  _start->setText("START");
  _start->setAction([this](){setActive(false); Arbitre::updateRules(_doubleThree->isActive(), _5breakable->isActive());});
  _pvp->setSize(sf::Vector2f(200, 50));
  _pvp->setPosition(sf::Vector2f(25, 25));
  _pvp->setBackgroundTexture("../Assets/button_select.png");
  _pvp->setFont("../Assets/fontBambo.ttf");
  _pvp->setFontSize(30);
  _pvp->setText("PVP");
  _pvp->setAction([this](){_pvp->setBackgroundTexture("../Assets/button_select.png"); _pve->setBackgroundTexture("../Assets/button_unselect.png");});
  _pve->setSize(sf::Vector2f(200, 50));
  _pve->setPosition(sf::Vector2f(275, 25));
  _pve->setBackgroundTexture("../Assets/button_unselect.png");
  _pve->setFont("../Assets/fontBambo.ttf");
  _pve->setFontSize(30);
  _pve->setText("PVE");
  _pve->setAction([this](){_pvp->setBackgroundTexture("../Assets/button_unselect.png"); _pve->setBackgroundTexture("../Assets/button_select.png");});
  _5breakable->setSize(sf::Vector2f(200, 50));
  _5breakable->setPosition(sf::Vector2f(25, 125));
  _5breakable->setBackgroundTexture("../Assets/button_unselect.png");
  _5breakable->setFont("../Assets/fontBambo.ttf");
  _5breakable->setFontSize(30);
  _5breakable->setText("5 Cassables");
  _5breakable->setActive(false);
  _5breakable->setAction([this](){_5breakable->setBackgroundTexture((_5breakable->isActive() ? "../Assets/button_unselect.png" : "../Assets/button_select.png" )); _5breakable->setActive(!_5breakable->isActive());});
  _doubleThree->setSize(sf::Vector2f(200, 50));
  _doubleThree->setPosition(sf::Vector2f(275, 125));
  _doubleThree->setBackgroundTexture("../Assets/button_unselect.png");
  _doubleThree->setFont("../Assets/fontBambo.ttf");
  _doubleThree->setFontSize(30);
  _doubleThree->setText("Double Trois");
  _doubleThree->setActive(false);
  _doubleThree->setAction([this](){_doubleThree->setBackgroundTexture((_doubleThree->isActive() ? "../Assets/button_unselect.png" : "../Assets/button_select.png" )); _doubleThree->setActive(!_doubleThree->isActive());});

  setPosition(sf::Vector2f(149, 249));
  setSize(sf::Vector2f(500, 300));
  setBackgroundColor(sf::Color(0, 0, 0, 127));
}

MainMenu::~MainMenu()
{
}

void MainMenu::onClickHandler(const sf::Vector2f &mousePosition)
{
  for (std::vector<AWidget *>::iterator it = _components.begin(); it != _components.end(); ++it)
    (*it)->onClickHandler(mousePosition);
}
