/*
 * PaddleController.hpp
 *
 *  Created on: 20.04.2017
 *      Author: jakub
 */
/**
 * \file
 * \brief
 * Definicja klasy PaddleController
 *
 * \class PaddleController
 * \brief
 * Abstrakcyjna bazowa klasa kontrolera paletki. Jest używana w klasie Hockey.
 */
#ifndef PADDLECONTROLLER_HPP_
#define PADDLECONTROLLER_HPP_

#include "CameraPointer.hpp"
#include "Puck.hpp"

class PaddleController {
public:
	virtual void update(CameraPointer& enemyPointer, CameraPointer& pointer, Puck& ball)=0;
	virtual ~PaddleController(){}

protected:
	PaddleController(){}
};

#endif /* PADDLECONTROLLER_HPP_ */
