#include "AWidget.hh"

#include <iostream>

AWidget::AWidget(AWidget *parent)
{
  if (parent)
    parent->addComponent(this);
  _parent = parent;
  _backgroundColor.setFillColor(sf::Color(255, 255, 255, 0));
  _backgroundColor.setSize(_size);
  _isActive = false;
}

AWidget::~AWidget()
{
  for (std::vector<AWidget *>::iterator it = _components.begin(); it != _components.end(); ++it)
    delete *it;
  _components.clear();
}

void AWidget::addComponent(AWidget *component)
{
  _components.push_back(component);
}

sf::Vector2f AWidget::getPosition() const
{
  return _localPosition;
}

sf::Vector2f AWidget::getSize() const
{
  return _size;
}

bool AWidget::isActive() const
{
  return _isActive;
}

void AWidget::onClickHandler(const sf::Vector2f &mousePosition)
{
  (void)mousePosition;
}

void AWidget::setActive(bool state)
{
  _isActive = state;
}

void AWidget::setBackgroundColor(const sf::Color &color)
{
  _backgroundColor.setFillColor(color);
}

void AWidget::setPosition(const sf::Vector2f &position)
{
  _localPosition = position;
  _setWorldPosition();
  _backgroundColor.setPosition(_worldPosition);
}

void AWidget::setSize(const sf::Vector2f &size)
{
  _size = size;
  _backgroundColor.setSize(_size);
}

void AWidget::_setObjectPosition()
{
}

void AWidget::_setWorldPosition()
{
  _worldPosition = (_parent ? _parent->_worldPosition + _localPosition : _localPosition);
  _setObjectPosition();
  for (std::vector<AWidget *>::iterator it = _components.begin(); it != _components.end(); ++it)
    {
      (*it)->_setWorldPosition();
      (*it)->_setObjectPosition();
    }
}
