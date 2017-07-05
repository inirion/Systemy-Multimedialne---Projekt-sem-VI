/*
 * HaveName.cpp
 *
 *  Created on: 17.03.2017
 *      Author: jakub
 */

#include "HaveName.hpp"

HaveName::HaveName(std::string n):
	name(n)
{

}
const std::string& HaveName::getName() const {
	return name;
}

void HaveName::setName(const std::string& name) {
	this->name = name;
}
