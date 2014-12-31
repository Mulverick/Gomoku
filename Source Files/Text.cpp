#include "Text.hh"

Text::Text(AWidget *parent) :
  AWidget(parent)
{
}

Text::~Text()
{
}

void Text::draw(sf::RenderWindow &window)
{
  window.draw(_text);
}

std::size_t Text::getFontSize() const
{
  return _text.getCharacterSize();
}

sf::Vector2f Text::getSize() const
{
  sf::FloatRect tmp(_text.getLocalBounds());
  return sf::Vector2f(tmp.width, tmp.height);
}

void Text::setColor(sf::Color &color)
{
  _text.setColor(color);
}

void Text::setFont(const std::string &fontName)
{
  if (!_font.loadFromFile(fontName))
    return ;
  _text.setFont(_font);
}

void Text::setFontSize(size_t size)
{
  _text.setCharacterSize(size);
}

void Text::setPosition(const sf::Vector2f &position)
{
  AWidget::setPosition(position);
  _text.setPosition(_worldPosition);
}

void Text::setString(const std::string &text)
{
  _text.setString(text);
}
