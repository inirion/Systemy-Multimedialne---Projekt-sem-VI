/*
 * MenuOptionsSecond.cpp
 *
 *  Created on: 01.05.2017
 *      Author: jakub
 */

#include "MenuOptionsSecond.hpp"
#include "Program.hpp"

MenuOptionsSecond::MenuOptionsSecond(Program* p) :
	ButtonView(p->getUniPointer())
{
	MenuButton b;
	std::function<void(const MenuButton&)> f;

	f = std::bind(&Program::optionsBackEvent, p, std::placeholders::_1);
	b.setName(S::button::back);
	b.setAction(f);
	b.setFontSize(smallFont);
	b.setSize(sf::Vector2f(300,100));
	b.setHotKey(sf::Keyboard::Escape);
	add(b);

	f = std::bind(&Program::defaultsOptionsEvent, p, std::placeholders::_1);
	b.setName(S::button::defaults);
	b.setAction(f);
	b.setHotKey(sf::Keyboard::F12);
	add(b);

	f = std::bind(&Program::openOptionsFirstEvent, p, std::placeholders::_1);
	b.setName(S::button::options_first);
	b.setAction(f);
	b.setHotKey(sf::Keyboard::O);
	add(b);

	f = std::bind(&Program::toggleVideoBackgroundEvent, p, std::placeholders::_1);
	b.setName(S::button::video_background);
	b.setAction(f);
	b.setSize(sf::Vector2f(600,100));
	b.setHotKey(sf::Keyboard::V);
	add(b);

	f = std::bind(&Program::togglePointerInGameEvent, p, std::placeholders::_1);
	b.setName(S::button::pointer_in_game);
	b.setAction(f);
	add(b);

	f = std::bind(&Program::togglePointerCircleEvent, p, std::placeholders::_1);
	b.setName(S::button::pointer_click_circle);
	b.setAction(f);
	add(b);

	f = std::bind(&Program::showAiGameEvent, p, std::placeholders::_1);
	b.setName(S::button::show_ai_game);
	b.setAction(f);
	add(b);
}

void MenuOptionsSecond::update() {
	const float gap = 50.f * Conf::gs;
	sf::Vector2f shift(0,gap);

	MenuButton* b;
	b=get(S::button::back);
	if(b!=nullptr){
		sf::Vector2f rs = b->getSizeReal();
		b->setPosition(Conf::refPos + sf::Vector2f(gap, Conf::ws.y - rs.y-gap));
	}
	b=get(S::button::defaults);
	if(b!=nullptr){
		sf::Vector2f rs = b->getSizeReal();
		b->setPosition(Conf::refPos + sf::Vector2f(Conf::ws.x - rs.x - gap, Conf::ws.y - rs.y-gap));
	}
	b=get(S::button::options_first);
	if(b!=nullptr){
		sf::Vector2f rs = b->getSizeReal();
		b->setPosition(Conf::refPos + sf::Vector2f(Conf::ws.x*0.5f - rs.x*0.5f, Conf::ws.y - rs.y-gap));
	}
	b=get(S::button::video_background);
	if(b!=nullptr){
		sf::Vector2f rs = b->getSizeReal();
		b->setPosition(Conf::refPos + sf::Vector2f(Conf::ws.x*0.5f - rs.x*0.5f, shift.y));
		shift.y += gap + rs.y;
	}
	b=get(S::button::pointer_click_circle);
	if(b!=nullptr){
		sf::Vector2f rs = b->getSizeReal();
		b->setPosition(Conf::refPos + sf::Vector2f(Conf::ws.x*0.5f - rs.x*0.5f, shift.y));
		shift.y += gap + rs.y;
	}
	b=get(S::button::pointer_in_game);
	if(b!=nullptr){
		sf::Vector2f rs = b->getSizeReal();
		b->setPosition(Conf::refPos + sf::Vector2f(Conf::ws.x*0.5f - rs.x*0.5f, shift.y));
		shift.y += gap + rs.y;
	}
	b=get(S::button::show_ai_game);
	if(b!=nullptr){
		sf::Vector2f rs = b->getSizeReal();
		b->setPosition(Conf::refPos + sf::Vector2f(Conf::ws.x*0.5f - rs.x*0.5f, shift.y));
		shift.y += gap + rs.y;
	}

	updateButtons();
}
