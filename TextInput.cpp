/*
 * TextInput.cpp
 *
 *  Created on: 31.03.2017
 *      Author: jakub
 */

#include "TextInput.hpp"
#include "Conf.hpp"
#include <iostream>
#include <cmath>
#include <sstream>

TextInput::TextInput():
	cursor(0),
	scroll(0)
{
	characterHeight=35;
	size.x = 500.f;
}

void TextInput::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::RectangleShape rs, cur;
	sf::Text t;

	const float margin = 10.f;

	rs.setSize(sf::Vector2f(size.x + margin*2, characterHeight + margin*2));

	rs.setScale(Conf::gs, Conf::gs);
	rs.setFillColor(sf::Color::White);
	if(focus)
		rs.setOutlineColor(sf::Color::Yellow);
	else
		rs.setOutlineColor(sf::Color::Black);

	rs.setOutlineThickness(Conf::gs * 10.f);
	rs.setPosition(position - sf::Vector2f(Conf::gs*margin,Conf::gs*margin));

	t.setFont(Conf::fm);
	t.setCharacterSize(characterHeight);
	t.setScale(Conf::gs, Conf::gs);
	t.setString("_1234567890QWERTYUIOPADFGHJKL_");

	float cwidth = t.getGlobalBounds().width/30.0;
//	float wheight = t.getGlobalBounds().height;

	float w = size.x*Conf::gs;
	int tmpCursor = cursor;
	if(!focus)
		tmpCursor = 0;

	float diff = cwidth*tmpCursor - w;

	std::wstring tmpVal = value;

	if(diff > 0.f){
		int shift = diff / cwidth + 1;
		tmpCursor -= shift;
		tmpVal = value.substr(shift);
	}

	size_t len = tmpVal.size();
	diff = cwidth*len - w;
	if(diff > 0.f){
		diff /= cwidth;
		len -= diff;
		std::wstring ws = tmpVal;
		ws.resize(len);
		t.setString(ws);
	}else{
		t.setString(tmpVal);
	}

	t.setFillColor(sf::Color::Black);
	t.setPosition(position);

	float alpha = (1.f+std::sin(Conf::rt*8.f))*127.f;
	cur.setSize(sf::Vector2f(4.f*Conf::gs, characterHeight*Conf::gs));
	cur.setPosition(position + sf::Vector2f(cwidth*tmpCursor,0.f));
	cur.setFillColor(sf::Color(0,0,0,alpha));
	cur.setOutlineColor(sf::Color(127,127,127,alpha));
	cur.setOutlineThickness(Conf::gs * 2.f);

	target.draw(rs,states);
	target.draw(t,states);

	if(focus)
		target.draw(cur,states);
}

void TextInput::updateInput(sf::Uint32 code) {
	if(code < 32 && code != BACKSPACE_KEY){
		return;
	}

	std::wstring tmp;
	tmp = value;
	int tmpcur = cursor;

	if(code == BACKSPACE_KEY){
		if(tmp.size() != 0 && tmpcur != 0){
			tmp.erase(tmp.begin()+tmpcur-1);
			--tmpcur;
		}
	}else if(code == DELETE_KEY){
		if(tmp.size() != 0 && tmpcur < (int)tmp.size()){
			tmp.erase(tmp.begin()+tmpcur);
		}
	}else{
		tmp.insert(tmp.begin()+tmpcur, code);
		++tmpcur;
	}

	if((filter && filter(tmp)) || !filter){
		value = std::move(tmp);
		cursor = tmpcur;
	}
}

const std::wstring& TextInput::getValue() const {
	return value;
}

void TextInput::setValue(const std::wstring& value) {
	this->value = value;
}

void TextInput::setValue(const std::string& value) {
	std::wstring ws;
	ws.resize(value.length(), L'\0');
	std::mbstowcs(&ws[0], value.c_str(), value.size());
	setValue(ws);
}

size_t TextInput::getCharacterHeight() const {
	return characterHeight;
}

void TextInput::setCharacterHeight(size_t characterHeight) {
	this->characterHeight = characterHeight;
}

sf::Vector2f TextInput::getSizeReal() const {
	sf::Vector2f s;
	s.x = size.x;
	s.y = characterHeight;
	s *= Conf::gs;

	return s;
}

const std::function<bool(std::wstring&)>& TextInput::getFilter() const {
	return filter;
}

void TextInput::setFilter(const std::function<bool(std::wstring&)>& filter) {
	this->filter = filter;
}

void TextInput::moveCursor(int n) {
	cursor += n;

	if(cursor < 0)
		cursor = 0;

	if(cursor > (int)value.size())
		cursor = value.size();
}

bool ipFilter(std::wstring& str) {
	if(str.size() == 0)
		return true;

	for(auto& c : str){
		if(c == L',' || c == L' ')
			c = L'.';
	}

	std::wstringstream ss;
	std::wstring tmp = str;

	size_t counter = 0;
	size_t charNum = 0;
	for(auto& c : tmp){
		if(c == L' '){
			return false;
		}

		if(counter < 3){
			if(c == L'.'){
				++counter;
				c = L' ';
			}else if(c == L':'){
				return false;
			}else if(c < 48 || c > 57){
				return false;
			}else{
				++charNum;
			}
		}else{
			if(c == L'.'){
				return false;
			}else if(c == L':'){
				if(++counter > 4)
					return false;
				c = L' ';
			}else if(c < 48 || c > 57){
				return false;
			}else{
				++charNum;
			}
		}
	}
	if(charNum == 0){
		return true;
	}

	ss.str(tmp);
	counter = 0;
	std::wstring word;
	size_t num = 0;
	while(ss.good()){
		++counter;
		if(counter > 5)
			return false;
		ss >> word;

		try{
			num = std::stoi(word);

			if(counter < 5){
				if(num > 255){
					return false;
				}
			}else{
				if(num > 65535){
					return false;
				}
			}

		}catch(std::exception &ex){
			return false;
		}
	}

	return true;
}

bool portFilter(std::wstring& str) {
	for(auto& c : str){
		if(c < '0' || c > '9'){
			return false;
		}
	}
	std::wstringstream ss;
	ss.str(str);
	int port=0;
	ss >> port;
	if(port > 65535)
		return false;

	return true;
}
