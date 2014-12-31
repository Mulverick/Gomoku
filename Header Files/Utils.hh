#ifndef UTILS_HH
#define UTILS_HH

#include <SFML/System/Vector2.hpp>

#define WIN_SIZE 798
#define CELL_SIZE 42
#define WHITE 1
#define BLACK 2

class Utils
{
public:
  static sf::Vector2i toCellPosition(const sf::Vector2i &);
  static sf::Vector2f toVector2f(const sf::Vector2i &);
};

#endif // UTILS_HH
