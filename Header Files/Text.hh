#ifndef TEXT_HH
#define TEXT_HH

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Color.hpp>

#include "AWidget.hh"

class Text : public AWidget
{
public:
  Text(AWidget *parent = 0);
  virtual ~Text();

  virtual void draw(sf::RenderWindow &window);
  std::size_t getFontSize() const;
  virtual sf::Vector2f getSize() const;
  void setColor(sf::Color &color);
  void setFont(const std::string &fontName);
  void setFontSize(size_t size);
  virtual void setPosition(const sf::Vector2f &position);
  void setString(const std::string &text);

private:
  sf::Text _text;
  sf::Font _font;
};

#endif // TEXT_HH
