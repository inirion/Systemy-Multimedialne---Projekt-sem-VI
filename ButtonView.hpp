/*
 * ButtonView.hpp
 *
 *  Created on: 17.03.2017
 *      Author: jakub
 */

/**
 * \file
 * \brief
 * Definicja klasy ButtonView dziedziczącej po sf::Drawable
 *
 * \class ButtonView
 * \brief
 * Bazowa klasa widoku z przyciskami
 *
 * Klasa ButtonView jest bazową klasą dla pojedynczego widoku menu.
 * Można dodawać do niego przyciski klasy MenuButton.
 * Należy implementować metodę update() która odpowiada za pozycjonowanie zawartych przycisków.
 */

#ifndef BUTTONVIEW_HPP_
#define BUTTONVIEW_HPP_

#include <map>

#include <SFML/Graphics.hpp>
#include "MenuButton.hpp"
#include "UniCameraPointer.hpp"

#define bigSize	sf::Vector2f(900,300)
#define medSize	sf::Vector2f(400,150)

class ButtonView : public sf::Drawable{
public:
	ButtonView(UniPointer &up);
	virtual ~ButtonView(){}
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
	bool add(MenuButton& b);
	MenuButton* get(std::string name);

	virtual void update() = 0;
	void updateButtons();

	const int bigFont = 90;
	const int medFont = 65;
	const int smallFont = 40;

protected:
	std::map<std::string, MenuButton> buttons;
	UniPointer& uniPointer;

};

#endif /* BUTTONVIEW_HPP_ */
