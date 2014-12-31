#pragma once
#include	"IPlayer.hh"
#include	"Arbitre.hh"
#include	<thread>

class AI : public IPlayer
{
public:
	AI(int color);
	~AI();
	int				onClickHandler(int cellPosition);
	void			placeStone(char * const &map);
	int				onPlay(char *const &map);
	int				hasPlayed() const;
	void			changeTurn();
	void			wrongMove();
	int				getColor() const;
	void			think();
private:
	Arbitre			_arbitre;
	std::thread*	_thread;
	int*			_weightMap;
	char*			_thinkMap;
	int				_color;
	bool			_turn;
	int				_played;
	bool			_thought;
};

