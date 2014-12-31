#include "Button.hh"

#include <iostream>

Button::Button(AWidget *parent) :
  AWidget(parent), _text(new Text(this))
{
}

Button::~Button()
{
}

void Button::draw(sf::RenderWindow &window)
{
  window.draw(_backgroundColor);
  _text->draw(window);
}

void Button::onClickHandler(const sf::Vector2f &mousePosition)
{
  if (_action && _backgroundColor.getGlobalBounds().contains(mousePosition))
    _action();
}

void Button::setAction(const std::function<void()> &action)
{
  _action = action;
}

void Button::setFont(const std::string &fontName)
{
  _text->setFont(fontName);
  _setTextPosition();
}

void Button::setFontSize(std::size_t size)
{
  _text->setFontSize(size);
  _setTextPosition();
}

void Button::setPosition(const sf::Vector2f &position)
{
  AWidget::setPosition(position);
  _backgroundColor.setPosition(_worldPosition);
  _setTextPosition();
}

void Button::setSize(const sf::Vector2f &size)
{
  AWidget::setSize(size);
  _setTextPosition();
}

void Button::setText(const std::string &text)
{
  _text->setString(text);
  _setTextPosition();
}

void Button::_setObjectPosition()
{
  _backgroundColor.setPosition(_worldPosition);
  _setTextPosition();
}

void Button::_setTextPosition()
{
  sf::Vector2f textSize(_text->getSize());

  _text->setPosition(sf::Vector2f((_size.x / 2) - (textSize.x / 2), (_size.y / 2) - (textSize.y / 2) - (_text->getFontSize() / 2)));
}
