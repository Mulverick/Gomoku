#ifndef MAINMENU_HH
#define MAINMENU_HH

#include "AMenu.hh"
#include "Button.hh"

class MainMenu : public AMenu
{
public:
  MainMenu(AWidget *parent = 0);
  ~MainMenu();

  virtual void onClickHandler(const sf::Vector2f &mousePosition);

private:
  Button *_start;
  Button *_pvp;
  Button *_pve;
  Button *_5breakable;
  Button *_doubleThree;
};

#endif // MAINMENU_HH
