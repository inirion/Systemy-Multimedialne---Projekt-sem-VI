/**
 * \file
 * \brief
 * Definicja klasy MenuHockeyWin dziedziczącej po ButtonView
 *
 * \class MenuHockeyWin
 * \brief
 * Klasa reprezentująca widok menu wygranej gry z możliwością ponownej rozgrywki.
 */

#ifndef _HOCKEY_WIN_MENU
#define _HOCKEY_WIN_MENU
#include "ButtonView.hpp"

class MenuHockeyWin : public ButtonView{
public:
	MenuHockeyWin(Program* p);
	virtual void update();
};

#endif
