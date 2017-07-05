/*
 * TextInput.hpp
 *
 *  Created on: 31.03.2017
 *      Author: jakub
 */
/**
 * \file
 * \brief
 * Definicja klasy TextInput dziedziczącej po sf::Drawable i Pressable
 *
 * \class TextInput
 * \brief
 * Klasa reprezentująca jednoliniowe edytowalne pole tekstowe.
 */
#ifndef TEXTINPUT_HPP_
#define TEXTINPUT_HPP_

#include <functional>
#include <string>
#include <SFML/Graphics.hpp>
#include "Pressable.hpp"

#define ENTER_KEY 13
#define BACKSPACE_KEY 8
#define DELETE_KEY 127

bool ipFilter(std::wstring& str);
bool portFilter(std::wstring& str);

class TextInput : public sf::Drawable, public Pressable<void>{
public:
	TextInput();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;

	void updateInput(sf::Uint32 code);

	const std::wstring& getValue() const;

	void setValue(const std::wstring& value);

	void setValue(const std::string& value);

	size_t getCharacterHeight() const;

	void setCharacterHeight(size_t characterHeight);

	virtual sf::Vector2f getSizeReal()const;

	const std::function<bool(std::wstring&)>& getFilter() const;

	void setFilter(const std::function<bool(std::wstring&)>& filter);

	void moveCursor(int n);

private:
	std::wstring value;
	size_t characterHeight;
	int cursor;
	int scroll;
	std::function<bool(std::wstring&)> filter;
};



#endif /* TEXTINPUT_HPP_ */
