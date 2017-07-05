/*
 * ConfigurationManager.hpp
 *
 *  Created on: 28.04.2017
 *      Author: jakub
 */
/**
 * \file
 * \brief
 * Definicja klasy ConfigurationManager oraz struktury ConfigurationObjects
 *
 * \class ConfigurationManager
 * \brief
 * Klasa menedżera konfiguracji
 *
 * Klasa menedżera konfiguracji służy do zapisywania i odczytywania istotnych parametrów do pliku tekstowego program.conf.
 *
 * \struct ConfigurationObjects
 * \brief
 * Struktura zawiera referencje na dodatkowe konfigurowane obiekty
 */

#ifndef CONFIGURATIONMANAGER_HPP_
#define CONFIGURATIONMANAGER_HPP_

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <locale>
#include <codecvt>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "S.hpp"
#include "Conf.hpp"
#include "TextInput.hpp"
#include "base64/base64.h"

struct ConfigurationObjects{
	sf::RenderWindow& rw;
	TextInput& serverName;
	TextInput& leftNick;
	TextInput& rightNick;
};

class ConfigurationManager {
public:
	bool load(ConfigurationObjects& co);
	bool save(ConfigurationObjects& co);

private:

};

#endif /* CONFIGURATIONMANAGER_HPP_ */
