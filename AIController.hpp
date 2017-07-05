/*
 * AIController.hpp
 *
 *  Created on: 20.04.2017
 *      Author: jakub
 */

/**
 * \file
 * \brief
 * Definicja klasy AIController dziedziczącej po PaddleController
 *
 * \class AIController
 * \brief
 * Klasa kontrolera paletki
 *
 * Klasa służy do sterowania paletką przez prosty autorski algorytm.
 */

#ifndef AICONTROLLER_HPP_
#define AICONTROLLER_HPP_

#include "PaddleController.hpp"


class AIController : public PaddleController {
public:
	enum Target{
		top,
		bottom,
		middle
	};

	AIController(double enemyGateX);

	virtual void update(CameraPointer& enemyPointer, CameraPointer& pointer, Puck& ball);

	void setEnemyGateX(double enemyGateX);

private:
	double enemyGateX;
	int decisionTimer;
	float decisionNoise;
	bool attack;
	Target target;
};

#endif /* AICONTROLLER_HPP_ */
