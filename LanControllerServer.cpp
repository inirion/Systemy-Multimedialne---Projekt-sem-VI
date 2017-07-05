#include "LanControllerServer.hpp"



LanControllerServer::LanControllerServer(Server&s) : server(s) {

}

void LanControllerServer::update(CameraPointer& enemyPointer, CameraPointer& pointer, Puck& ball) {
	SendData(enemyPointer, pointer, ball);
	RecvData(enemyPointer, pointer);
}

void LanControllerServer::SendData(CameraPointer& enemyPointer, CameraPointer& pointer, Puck& ball)
{
	sf::Packet p;
	p << packetStates::PLAYING << enemyPointer.getPointerPos().x << enemyPointer.getPointerPos().y << enemyPointer.getPointerPos(1).x << enemyPointer.getPointerPos(1).y << ball.getPosition().x << ball.getPosition().y<< ball.getAngle() << ball.getLinearVelocity();
	if (server.Send(p)){
		//std::cout << " KlientSend Success" << std::endl;
	}else{
		//std::cout << " KlientSend error" << std::endl;
	}
}

void LanControllerServer::RecvData(CameraPointer& enemyPointer, CameraPointer& pointer)
{
	float x1, x2, y1, y2;
	int type;
	sf::Packet p;
	if (server.Recive(p)) {
		if (p >> type) {
			switch (type)
			{
			case packetStates::PLAYING: {
				if (p >> x1 >> y1 >> x2 >> y2) {
					pointer.setTargetPos(0, sf::Vector2f(x1, y1));
					pointer.setTargetPos(1, sf::Vector2f(x2, y2));
				}
			}break;

			default:
				break;
			}
		}
	}
}
