/*
 * MenuPaint.hpp
 *
 *  Created on: 30.03.2017
 *      Author: jakub
 */
/**
 * \file
 * \brief
 * Definicja klasy MenuPaint dziedziczącej po ButtonView
 *
 * \class MenuPaint
 * \brief
 * Klasa reprezentująca menu paint testu z przyciskiem do czyszczenia płótna.
 */
#ifndef MENUPAINT_HPP_
#define MENUPAINT_HPP_

#include "ButtonView.hpp"

class MenuPaint : public ButtonView {
public:
	MenuPaint(Program* p);
	virtual void update();

private:


};

#endif /* MENUPAINT_HPP_ */
