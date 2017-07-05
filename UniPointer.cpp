/*
 * UniPointer.cpp
 *
 *  Created on: 25.03.2017
 *      Author: jakub
 */

#include "UniCameraPointer.hpp"

UniPointer::UniPointer(MousePointer& mousePointer, CameraPointer& cameraPointer):
	mousePointer(mousePointer),
	cameraPointer(cameraPointer)
{

}

sf::Vector2f UniPointer::getPos() {
	if(mousePointer.isMouseFocus()){
		return mousePointer.getPos();
	}else{
		return cameraPointer.getPointerPosRelative();
	}
}

bool UniPointer::isPressed() {
	if(mousePointer.isMouseFocus()){
		return mousePointer.isPressed();
	}else{
		return cameraPointer.isPressed();
	}
}
