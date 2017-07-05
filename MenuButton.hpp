/*
 * MenuButton.hpp
 *
 *  Created on: 17.03.2017
 *      Author: jakub
 */
/**
 * \file
 * \brief
 * Definicja klasy MenuButton dziedziczącej po sf::Drawable, Pressable, HaveName i HaveEnabled
 *
 * \class MenuButton
 * \brief
 * Klasa przycisku menu
 *
 * Klasa reprezentująca przycisk menu.
 */

#ifndef MENUBUTTON_HPP_
#define MENUBUTTON_HPP_

#include <functional>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "Conf.hpp"
#include "HaveName.hpp"
#include "HaveEnabled.hpp"
#include "Pressable.hpp"

class MenuButton : public sf::Drawable, public Pressable<const MenuButton&>, public HaveName, public HaveEnabled{
public:
	MenuButton();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	size_t getFontSize() const;
	void setFontSize(size_t fontSize);
	virtual sf::Vector2f getSizeReal()const;
	virtual void doAction();
	const sf::IpAddress& getAdress() const;
	void setAdress(sf::IpAddress);
private:
	sf::IpAddress selectedIpAdress;
	size_t fontSize;
};



#endif /* MENUBUTTON_HPP_ */
