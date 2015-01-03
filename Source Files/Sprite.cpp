#include "Sprite.hh"

Sprite::Sprite()
{
}

Sprite::~Sprite()
{
}

sf::Sprite &Sprite::getSprite()
{
	return _sprite;
}

bool Sprite::loadFromFile(const std::string &fileName)
{
	if (!_texture.loadFromFile(fileName))
		return false;
	_sprite.setTexture(_texture);
	return true;
}

void Sprite::setColor(const sf::Color &color)
{
	_sprite.setColor(color);
}

void Sprite::setPosition(float x, float y)
{
	_sprite.setPosition(x, y);
}

void Sprite::setPosition(const sf::Vector2i &position)
{
	_sprite.setPosition((float)position.x, (float)position.y);
}