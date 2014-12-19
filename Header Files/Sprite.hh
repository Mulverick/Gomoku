#ifndef SPRITE_HH
#define SPRITE_HH

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Sprite
{
public:
	Sprite();
	~Sprite();

	sf::Sprite &getSprite();
	bool loadFromFile(const std::string &);
	void setColor(const sf::Color &);
	void setPosition(float, float);
	void setPosition(const sf::Vector2i &);

private:
	sf::Sprite _sprite;
	sf::Texture _texture;
};

#endif // SPRITE_HH
