/*
 * MenuButton.cpp
 *
 *  Created on: 17.03.2017
 *      Author: jakub
 */

#include "MenuButton.hpp"
#include <iostream>


MenuButton::MenuButton():
	fontSize(30)
{

}

void MenuButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if(!visible)
		return;

	sf::RectangleShape rs;

	sf::Vector2f s = size * Conf::gs;
	sf::Color tc=sf::Color::White;

	rs.setSize(s);
	rs.setPosition(position);
	rs.setOutlineColor(sf::Color(0,0,0,64));
	if(enabled){
		int alpha = 32;
		if(hover){
			alpha = 48;
			rs.setOutlineColor(sf::Color(128,128,0,128));
			tc = sf::Color::Yellow;

			if(pressed){
				rs.setOutlineColor(sf::Color(128,128,0,200));
				alpha = 64;
				tc = sf::Color::Green;
			}
		}
		rs.setFillColor(sf::Color(255,255,255,alpha));
	}
	else{
		rs.setFillColor(sf::Color(128,128,128,32));
	}

	rs.setOutlineThickness(10.f*Conf::gs);
	target.draw(rs,states);

	sf::Text t(name, Conf::fm, fontSize);
	if(!enabled)
		t.setFillColor(sf::Color(128,128,128));
	else{
		t.setFillColor(tc);
	}
	t.setScale(Conf::gs, Conf::gs);
	t.setOutlineColor(sf::Color::Black);
	t.setOutlineThickness(2.f);
	t.setPosition(position + sf::Vector2f(s.x*0.5, s.y*0.5));
	t.move(-t.getGlobalBounds().width*0.5, -t.getGlobalBounds().height*0.66);

	target.draw(t,states);
}

size_t MenuButton::getFontSize() const {
	return fontSize;
}

void MenuButton::setFontSize(size_t fontSize) {
	this->fontSize = fontSize;
}

sf::Vector2f MenuButton::getSizeReal() const {
	return size*Conf::gs;
}

void MenuButton::doAction() {
	if(action){
		action(*this);
	}
}

const sf::IpAddress & MenuButton::getAdress() const
{
	return selectedIpAdress;
}

void MenuButton::setAdress(sf::IpAddress ipAdd)
{
	selectedIpAdress = ipAdd;
}
