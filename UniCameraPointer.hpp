/*
 * UniPointer.hpp
 *
 *  Created on: 25.03.2017
 *      Author: jakub
 */
/**
 * \file
 * \brief
 * Definicja klasy UniPointer
 *
 * \class UniPointer
 * \brief
 * Klasa uniwersalnego wskaźnika. Zwraca stan MousePointer lub CameraPointer.
 *
 * Klasa która zawiera referencje na MousePointer i CameraPointer.
 * Kiedy aktywna jest mysz, metody getPos() oraz isPressed() zwracają stan myszki.
 * W przeciwnym wypadku zwracany jest stan wskaźnika obsługiwanego przez kamerkę.
 */

#ifndef UNICAMERAPOINTER_HPP_
#define UNICAMERAPOINTER_HPP_

#include "CameraPointer.hpp"
#include "MousePointer.hpp"

class UniPointer {
public:
	UniPointer(MousePointer& mousePointer, CameraPointer& cameraPointer);
	sf::Vector2f getPos();
	bool isPressed();
private:
	MousePointer& mousePointer;
	CameraPointer& cameraPointer;

};

#endif /* UNICAMERAPOINTER_HPP_ */
