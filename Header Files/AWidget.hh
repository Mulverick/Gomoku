#ifndef AWIDGET_HH
#define AWIDGET_HH

#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>

class AWidget
{
public:
  AWidget(AWidget *parent = 0);
  virtual ~AWidget();

  void addComponent(AWidget *component);
  virtual void draw(sf::RenderWindow &window) = 0;
  sf::Vector2f getPosition() const;
  virtual sf::Vector2f getSize() const;
  bool isActive() const;
  virtual void onClickHandler(const sf::Vector2f &mousePosition);
  virtual void setActive(bool state);
  void setBackgroundColor(const sf::Color &color);
  void setBackgroundTexture(const std::string &textName);
  virtual void setPosition(const sf::Vector2f &position);
  virtual void setSize(const sf::Vector2f &size);

protected:
  virtual void _setObjectPosition();

  bool _isActive;
  sf::Vector2f _localPosition;
  sf::Vector2f _worldPosition;
  sf::Vector2f _size;
  sf::RectangleShape _backgroundColor;
  sf::Texture _backgroundTexture;
  AWidget *_parent;
  std::vector<AWidget *> _components;

private:
  void _setWorldPosition();
};

#endif // AWIDGET_HH
