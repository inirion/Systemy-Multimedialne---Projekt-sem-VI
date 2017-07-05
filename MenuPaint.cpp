/*
 * MenuPaint.cpp
 *
 *  Created on: 30.03.2017
 *      Author: jakub
 */

#include "MenuPaint.hpp"
#include "Program.hpp"

MenuPaint::MenuPaint(Program* p):
	ButtonView(p->getUniPointer())
{
	MenuButton b;
	std::function<void(const MenuButton&)> f;

	b.setFontSize(medFont);

	f = std::bind(&Program::clearCanvasEvent, p, std::placeholders::_1);
	b.setName(S::button::clear);
	b.setAction(f);
	b.setSize(medSize);
	b.setHotKey(sf::Keyboard::C);
	add(b);

	f = std::bind(&Program::gameEscapeEvent, p, std::placeholders::_1);
	b.setName(S::button::back);
	b.setAction(f);
	b.setHotKey(sf::Keyboard::Escape);
	b.setVisible(false);
	add(b);
}

void MenuPaint::update() {
	const float gap = 50.f * Conf::gs;
	sf::Vector2f shift(0,gap);
	MenuButton* b;
	b=get(S::button::clear);
	if(b!=nullptr){
		b->setPosition(Conf::refPos + shift + sf::Vector2f(Conf::ws.x*0.5- b->getSizeReal().x*0.5,0));
		shift.y += gap + b->getSizeReal().y;
	}

	updateButtons();
}
