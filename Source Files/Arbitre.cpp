#include "Arbitre.hh"

DoubleThree::DoubleThree(int nb1, int nb2, int nb3) : _first(nb1), _second(nb2), _third(nb3) {}
DoubleThree::DoubleThree(DoubleThree const &cpy) : _first(cpy._first), _second(cpy._second), _third(cpy._third) {}
DoubleThree::~DoubleThree(){}
DoubleThree &DoubleThree::operator=(DoubleThree const &cpy){
	_first = cpy._first;
	_second = cpy._second;
	_third = cpy._third;
	return (*this);
}
bool DoubleThree::operator==(DoubleThree const &a) const {
	if (_first == a._first || _first == a._second || _first == a._third ||
		_second == a._first || _second == a._second || _second == a._third ||
		_third == a._first || _third == a._second || _third == a._third)
		return true;
	return false;
}
int DoubleThree::getFirst() const{
	return _first;
}
int DoubleThree::getSecond() const{
	return _second;
}
int DoubleThree::getThird() const{
	return _third;
}

Arbitre::Arbitre()
{
	_prisoner[0] = 0;
	_prisoner[1] = 0;
}


Arbitre::~Arbitre()
{
}
