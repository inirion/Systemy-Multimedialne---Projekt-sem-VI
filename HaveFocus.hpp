/*
 * HaveFocus.hpp
 *
 *  Created on: 21.04.2017
 *      Author: jakub
 */
/**
 * \file
 * \brief
 * Definicja bazowej klasy HaveFocus
 *
 * \class HaveFocus
 * \brief
 * Bazowa klasa obiektu "focusowalnego"
 *
 * Bazowa klasa reprezentująca obiekt posiadający pole focus.
 * Poprzednio skupiony obiekt jest zapamiętany w statycznym polu, dzięki temu po wywołaniu metody setFocus(true) stan focus poprzedniego obiektu jest ustawiany na false.
 */

#ifndef HAVEFOCUS_HPP_
#define HAVEFOCUS_HPP_

class HaveFocus {
public:
	HaveFocus(bool f = false);
	bool isFocus() const;
	void setFocus(bool focus);

	static void unFocus();

protected:
	static HaveFocus* lastFocus;
	bool focus;
};

#endif /* HAVEFOCUS_HPP_ */
