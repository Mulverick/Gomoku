#ifndef AMENU_HH
#define AMENU_HH

#include "AWidget.hh"

class AMenu : public AWidget
{
public:
  AMenu(AWidget *parent = 0);
  virtual ~AMenu();

  virtual void draw(sf::RenderWindow &window);
  virtual void setActive(bool state);
};

#endif // AMENU_HH
