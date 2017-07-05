/*
 * ButtonView.cpp
 *
 *  Created on: 17.03.2017
 *      Author: jakub
 */

#include "ButtonView.hpp"

ButtonView::ButtonView(UniPointer& up):
	uniPointer(up)
{

}

void ButtonView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for(auto& b : buttons){
		b.second.draw(target,states);
	}
}

bool ButtonView::add(MenuButton& b) { //return true if overwrite
	std::string n = b.getName();
	if(n.empty()){
		throw std::runtime_error("ButtonView::add Cant add button without name");
	}

	auto k = buttons.find(n);
	if(k == buttons.end()){
		buttons[n] = b;
		return true;
	}else{
		k->second = b;
	}
	return false;
}

MenuButton* ButtonView::get(std::string name) {
	auto k = buttons.find(name);
	if(k == buttons.end()){
		return nullptr;
	}else{
		return &k->second;
	}
}

void ButtonView::updateButtons() {
	sf::Vector2f pp = uniPointer.getPos();
	bool p = uniPointer.isPressed();

	for(auto& b : buttons){
		b.second.update(pp,p);
	}
}
