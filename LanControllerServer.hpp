/*
* NetworkController.hpp
*
*  Created on: 20.04.2017
*      Author: jakub
*/
/**
 * \file
 * \brief
 * Definicja klasy LanControllerServer dziedzicząca po PaddleController
 *
 * \class LanControllerServer
 * \brief
 * Klasa sieciowego kontrolera paletki przeciwnika po stronie serwera
 *
 * Kontroler paletki po stronie serwera.
 * Odbiera pozycje wskaźnika od klienta.
 * Wysyła dane paletki serwera oraz pozycje krążka.
 */
#ifndef LANCONTROLLERSERVER_HPP_
#define LANCONTROLLERSERVER_HPP_

#include "PaddleController.hpp"
#include "Server.hpp"
#include "Client.hpp"

class LanControllerServer : public PaddleController {
public:
	LanControllerServer(Server &s);
	virtual void update(CameraPointer& enemyPointer, CameraPointer& pointer, Puck& ball) override;
	enum packetStates {
		PLAYING,
		SCORE,
	};

private:

	Server &server;
	void SendData(CameraPointer& enemyPointer, CameraPointer& pointer, Puck& ball);
	void RecvData(CameraPointer& enemyPointer, CameraPointer& pointer);
};

#endif /* LANCONTROLLERSERVER_HPP_ */
