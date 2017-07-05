/*
 * NetworkController.cpp
 *
 *  Created on: 20.04.2017
 *      Author: jakub
 */

#include "LanControllerClient.hpp"

LanControllerClient::LanControllerClient(Client &c): client(c) {

}

void LanControllerClient::update(CameraPointer& enemyPointer, CameraPointer& pointer, Puck& ball) {
	SendData(enemyPointer, pointer);
	RecvData(enemyPointer, pointer, ball);
}

void LanControllerClient::SendData(CameraPointer& enemyPointer, CameraPointer&)
{
		sf::Packet p2;
		p2 << packetStates::PLAYING << enemyPointer.getPointerPos().x << enemyPointer.getPointerPos().y << enemyPointer.getPointerPos(1).x << enemyPointer.getPointerPos(1).y;
		if (client.Send(p2)){
			//std::cout << " KlientSend Success" << std::endl;
		}else{
			//std::cout << " KlientSend error" << std::endl;
		}
}

void LanControllerClient::RecvData(CameraPointer& enemyPointer, CameraPointer& pointer, Puck& ball)
{
	float x1, x2, y1, y2,x3,y3, angle, speed;
	int type;
	sf::Packet p;
	if (client.Recive(p)) {
		if (p >> type) {
			switch (type)
			{
			case packetStates::PLAYING: {
				if (p >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> angle >> speed) {
//					std::cout << "przyszło" << std::endl;
					pointer.setTargetPos(0, sf::Vector2f(x1, y1));
					pointer.setTargetPos(1, sf::Vector2f(x2, y2));
					ball.setPosition(sf::Vector2f(x3, y3));
				}
			}break;

			default:
				break;
			}
		}
	}
}
