/*
 * LanControllerClient.hpp
 *
 *  Created on: 20.04.2017
 *      Author: Grzeogorz
 */
/**
 * \file
 * \brief
 * Definicja klasy LanControllerClient dziedzicząca po PaddleController
 *
 * \class LanControllerClient
 * \brief
 * Klasa sieciowego kontrolera paletki przeciwnika po stronie klienta
 *
 * Kontroler paletki przeciwnika po stronie klienta.
 * Odbiera pozycje wskaźnika z serwera oraz pozycje krążka.
 * Wysyła dane paletki klienta.
 */

#ifndef LANCONTROLLERCLIENT_HPP_
#define LANCONTROLLERCLIENT_HPP_

#include "PaddleController.hpp"
#include "Server.hpp"
#include "Client.hpp"

class LanControllerClient : public PaddleController {
public:
	LanControllerClient(Client &c);
	virtual void update(CameraPointer& enemyPointer, CameraPointer& pointer, Puck& ball) override;
	enum packetStates {
		PLAYING,
		SCORE,
	};

private:
	
	Client &client;
	void SendData(CameraPointer& enemyPointer, CameraPointer& pointer);
	void RecvData(CameraPointer& enemyPointer, CameraPointer& pointer, Puck& ball);
};

#endif /* LANCONTROLLERCLIENT_HPP_ */
