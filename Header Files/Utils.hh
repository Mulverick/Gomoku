#ifndef UTILS_HH
#define UTILS_HH

#include <utility>
#include <SFML/System/Vector2.hpp>

#define AI_THINK 500
#define MAP_SIZE 361
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

template <typename Type> struct Vector
{
	Type	x;
	Type	y;

	Vector(void) {}
	Vector(Type X, Type Y) : x(X), y(Y) {}
	Vector(Vector<Type> const &copy) : x(copy.x), y(copy.y) {}
	~Vector(void) {}

	Vector<Type>	&operator=(Vector<Type> const &second)
	{
		x = second.x;
		y = second.y;
		return (*this);
	}

	Vector<Type>	operator+(Vector<Type> const &second) const
	{
		Vector<Type>	ret;
		ret.x = x + second.x;
		ret.y = y + second.y;
		return (ret);
	}
};

#endif // UTILS_HH
