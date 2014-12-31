#ifndef BUTTON_HH
#define BUTTON_HH

#include <functional>
#include <SFML/Graphics/Text.hpp>

#include "AWidget.hh"
#include "Text.hh"

class Button : public AWidget
{
public:
  Button(AWidget *parent = 0);
  virtual ~Button();

  virtual void draw(sf::RenderWindow &window);
  virtual void onClickHandler(const sf::Vector2f &mousePosition);
  void setAction(const std::function<void(void)> &action);
  void setFont(const std::string &fontName);
  void setFontSize(std::size_t size);
  virtual void setSize(const sf::Vector2f &size);
  virtual void setPosition(const sf::Vector2f &position);
  void setText(const std::string &text);

protected:
  virtual void _setObjectPosition();

private:
  void _setTextPosition();

  Text *_text;
  std::function<void(void)> _action;
};

#endif // BUTTON_HH
