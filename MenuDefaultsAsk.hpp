/*
 * MenuDefaultsAsk.hpp
 *
 *  Created on: 25.03.2017
 *      Author: jakub
 */
/**
 * \file
 * \brief
 * Definicja klasy MenuDefaultsAsk dziedziczącej po ButtonView
 *
 * \class MenuDefaultsAsk
 * \brief
 * Klasa reprezentująca widok menu z pytaniem o przywrócenie domyślnych ustawień.
 */

#ifndef MENUDEFAULTSASK_HPP_
#define MENUDEFAULTSASK_HPP_

#include "ButtonView.hpp"

class MenuDefaultsAsk : public ButtonView {
public:
	MenuDefaultsAsk(Program* p);
	virtual void update();

private:

};

#endif /* MENUDEFAULTSASK_HPP_ */
