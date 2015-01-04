#pragma once

#include "AMenu.hh"
#include "Button.hh"

class WinnerMenu : public AMenu
{
public:
	WinnerMenu(AWidget *parent = 0);
	~WinnerMenu();
	void setWinner(std::string);
  virtual void onClickHandler(const sf::Vector2f &mousePosition);

private:
  Button *_newGame;
  Text *_winner;
};
