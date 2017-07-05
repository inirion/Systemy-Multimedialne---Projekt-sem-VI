/*
 * HaveName.hpp
 *
 *  Created on: 17.03.2017
 *      Author: jakub
 */
/**
 * \file
 * \brief
 * Definicja bazowej klasy HaveName
 *
 * \class HaveName
 * \brief
 * Bazowa klasa obiektu nazywalnego
 *
 * Bazowa klasa posiadająca pole name oraz jego mutator i akcesor.
 */
#ifndef HAVENAME_HPP_
#define HAVENAME_HPP_

#include <string>
class HaveName {
public:
	HaveName(std::string n = "");

	const std::string& getName() const;
	void setName(const std::string& name);
protected:
	std::string name;
};

#endif /* HAVENAME_HPP_ */
