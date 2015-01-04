#ifndef AMENU_HH
#define AMENU_HH

#include "AWidget.hh"

class Game;

class AMenu : public AWidget
{
public:
  AMenu(AWidget *parent = 0);
  virtual ~AMenu();

  virtual void draw(sf::RenderWindow &window);
  virtual void setActive(bool state);
  void setGameInstance(Game *game);
  Game			*getGameInstance(void);
  Game const	*getGameInstance(void) const;

protected:
  Game *_gameInstance;
};

#endif // AMENU_HH
