/*
 * HaveEnabled.hpp
 *
 *  Created on: 17.03.2017
 *      Author: jakub
 */
/**
 * \file
 * \brief
 * Definicja bazowej klasy HaveEnabled
 *
 * \class HaveEnabled
 * \brief
 * Bazowa klasa obiektu włączalnego
 *
 * Bazowa klasa reprezentująca obiekt który jest włączalny.
 */

#ifndef HAVEENABLED_HPP_
#define HAVEENABLED_HPP_

class HaveEnabled {
public:
	HaveEnabled(bool e = true);
	bool isEnabled() const;
	void setEnabled(bool enabled);

protected:
	bool enabled;
};

#endif /* HAVEENABLED_HPP_ */
