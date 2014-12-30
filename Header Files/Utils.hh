#ifndef UTILS_HH
#define UTILS_HH

#include <SFML/System/Vector2.hpp>

#define AI_THINK 500
#define	MAP_SIZE 361
#define WIN_SIZE 798
#define CELL_SIZE 42
#define WHITE 1
#define BLACK 2

class Utils
{
public:
	static sf::Vector2i toCellPosition(const sf::Vector2i &);
};

#endif // UTILS_HH
