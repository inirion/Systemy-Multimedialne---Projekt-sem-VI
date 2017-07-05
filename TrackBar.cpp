/*
 * TrackBar.cpp
 *
 *  Created on: 15.03.2017
 *      Author: jakub
 */

#include "TrackBar.hpp"
#include <iostream>
TrackBarBase::TrackBarBase(std::string Name, double Value, double Max, double Min):
	HaveName(Name),
	value(Value),
	min(Min),
	max(Max)
	{
	if(min > max){
		throw std::logic_error("TrackBar(...) min > max");
	}
	clampValue();
}

void TrackBarBase::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::RectangleShape rs;
	rs.setPosition(position);
	rs.setSize(size);
	if(hover){
		rs.setFillColor(sf::Color(255,255,255,24));
	}else{
		rs.setFillColor(sf::Color(255,255,255,16));
	}
	target.draw(rs,states);

	const float margin = 40*Conf::gs;
	sf::Text t(name, Conf::fm, 40);
	t.scale(Conf::gs, Conf::gs);
	const float nameWidth = t.getGlobalBounds().width;
	t.setPosition(position+sf::Vector2f(margin, size.y*0.5 - t.getGlobalBounds().height*0.7));
	target.draw(t,states);

	std::string v = std::to_string((int)value);
	sf::Text fr("O", Conf::fm, t.getCharacterSize());
	fr.scale(Conf::gs, Conf::gs);
	const float valueWidth = v.size()*fr.getGlobalBounds().width;
	t.setString(v);
	t.setPosition(rs.getPosition() + sf::Vector2f(size.x - margin - valueWidth, size.y*0.5 - t.getGlobalBounds().height*0.7));
	target.draw(t,states);

	sf::Vector2f s = size;
	s.x -= nameWidth+valueWidth+margin*4;
	rs.move(nameWidth+margin*2, s.y*0.5);
	s.y /= 10.f;

	rs.setSize(s);
	target.draw(rs,states);

	sf::CircleShape cs;
	const float r = s.y*1.5;
	cs.setRadius(r);
	cs.setOrigin(r,r);
	if(hover && pressed){
		cs.setFillColor(sf::Color::Green);
	}else{
		cs.setFillColor(sf::Color(111,111,111));
	}
	cs.setPosition(rs.getPosition() + sf::Vector2f(((value-min)/(max - min))*s.x, s.y*0.5));
	target.draw(cs,states);
}

double TrackBarBase::getMax() const {
	return max;
}

void TrackBarBase::setMax(double max) {
	if(max <= min )
		this->max = max;
	else
		throw std::logic_error("TrackBar::setMax max < min");
}

double TrackBarBase::getMin() const {
	return min;
}

void TrackBarBase::setMin(double min) {
	if(min <= max)
		this->min = min;
	else
		throw std::logic_error("TrackBar::setMin min > max");
}

double TrackBarBase::getValue() const {
	return value;
}

void TrackBarBase::setValue(double value) {
	this->value = value;
	this->clampValue();
}

void TrackBarBase::moveValueABS(double shift) {
	value += shift;
	clampValue();
}

void TrackBarBase::moveValue(float shift) {
	value += shift * ((max - min)/size.x);
	clampValue();
}

void TrackBarBase::clampValue() {
	if(value > max){
		value = max;
	}else if(value < min){
		value = min;
	}
}

void TrackBarBase::update(sf::Vector2f mp, float diff, bool pressed) {
	if(lastFocus == nullptr || lastFocus == this){
		if((updateHover(mp) || lastFocus == this) && pressed){
			setFocus(true);
			setHover(true);
			setPressed(true);
			float a = 2.0*(1.f-(1.f/(0.04*std::fabs(diff)+1)));
			if(a != 0.f)
				moveValue(a*diff);
		}else{
			setPressed(false);
		}
	}
}
