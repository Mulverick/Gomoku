#include "Utils.hh"

sf::Vector2i Utils::toCellPosition(const sf::Vector2i &position)
{
	return sf::Vector2i((int)(position.x / CELL_SIZE) * CELL_SIZE, (int)(position.y / CELL_SIZE) * CELL_SIZE);
}