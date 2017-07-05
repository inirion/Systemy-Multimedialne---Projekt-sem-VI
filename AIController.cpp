/*
 * AIController.cpp
 *
 *  Created on: 20.04.2017
 *      Author: jakub
 */

#include "AIController.hpp"
#include "Conf.hpp"

void AIController::update(CameraPointer& enemyPointer, CameraPointer& pointer, Puck& ball) {
//	float h = 0.25*(std::sin(Conf::rt*3)+1.0) + 0.25;
//	float angle = Conf::rt*3;

	bool newDecision=false;
	if(--decisionTimer < 0){
		decisionTimer = 120 + rand()%360;
		decisionNoise = 0.5f - 1.f*rand()/RAND_MAX;
		newDecision = true;
	}

	sf::Vector2f ep0 = enemyPointer.getPointerGamePos(0);
	sf::Vector2f ep1 = enemyPointer.getPointerGamePos(1);
	sf::Vector2f ec = (ep0+ep1)*0.5f;

	sf::Vector2f lp0 = pointer.getPointerGamePos(0);
	sf::Vector2f lp1 = pointer.getPointerGamePos(1);
	sf::Vector2f lc = (lp0 + lp1)*0.5f;

	sf::Vector2f bp = ball.getPosition();

	sf::Vector2f bd = bp - lc;
	float ballDist = bd.x*bd.x + bd.y*bd.y;
	sf::Vector2f ebd = bp - ec;
	float enemyBallDist = ebd.x*ebd.x + ebd.y*ebd.y;


	if(newDecision){
		if(
			ballDist < enemyBallDist ||
			(enemyGateX > 0.f && bp.x < Conf::ballRadius) ||
			(enemyGateX < 0.f && bp.x > -Conf::ballRadius)
		){
			attack = true;
		}else{
			attack = false;
		}

		if(bp.y > Conf::paddleHeight){
			target = bottom;
		}else if(bp.y < -Conf::paddleHeight){
			target = top;
		}else{
			target = middle;
		}
	}

	sf::Vector2f tp;
	if(attack){
		tp = bp;
	}else{
		tp = (bp + sf::Vector2f(-1*enemyGateX, 0.f))*0.5f;
	}

	if(enemyGateX < 0.f){
		if(tp.x < 0.f)
			tp.x = 0.f;
	}else{
		if(tp.x > 0.f)
			tp.x = 0.f;
	}

	sf::Vector2f p0,p1;
	sf::Vector2f tg((enemyGateX+bp.x)*0.5, 0.f);
	switch(target){
		case top:{
			tg.y = -Conf::areaHeight*0.5f;
		}break;
		case bottom:{
			tg.y = Conf::areaHeight*0.5f;
		}break;
		case middle:{
			tg.y = 0.f;
		}break;
	}

	float a = std::atan2(tg.y, tg.x) + M_PI_2 + decisionNoise;

	const float r = 0.3;
	p0.x = tp.x + r*std::cos(a);
	p0.y = tp.y + r*std::sin(a);

	p1.x = tp.x + r*std::cos(a-M_PI);
	p1.y = tp.y + r*std::sin(a-M_PI);

	pointer.setTargetGamePos(0, p0);
	pointer.setTargetGamePos(1, p1);
}

AIController::AIController(double enemyGateX):
	enemyGateX(enemyGateX),
	decisionTimer(0),
	decisionNoise(0.f),
	attack(false),
	target(middle)
{
}

void AIController::setEnemyGateX(double enemyGateX) {
	this->enemyGateX = enemyGateX;
}
