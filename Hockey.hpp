/**
 * \file
 * \brief
 * Definicja klasy Hockey dziedzicząca po sf::Drawable
 *
 * \class Hockey
 * \brief
 * Klasa gry Air Hockey
 *
 * Klasa reprezentująca grę Air Hockey. Zawiera między innymi obiekty klas Paddle, Puck, Gate, PaddleController.
 */

#ifndef HOCKEY_HPP
#define HOCKEY_HPP

#include <memory>
#include <SFML/Graphics.hpp>
#include "CameraPointer.hpp"
#include "Conf.hpp"
#include "Paddle.hpp"
#include "PaddleController.hpp"
#include "Gate.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Puck.hpp"

#define COUNTER_DELAY 300

class Hockey : public sf::Drawable {
private:
	Puck ball;
	int startCounter;
	int winPoints;
	sf::Clock counterClk;
	CameraPointer &pointerLeft;
	CameraPointer &pointerRight;
	std::shared_ptr<PaddleController> opponentRightController;
	std::shared_ptr<PaddleController> opponentLeftController;

	Server &server;
	Client &client;

	Paddle paddleLeft;
	Paddle paddleRight;

	Gate gateLeft;
	Gate gateRight;


	std::pair<int,int> points;

public:

	Hockey(CameraPointer &pointerLeft, CameraPointer &pointerRight, Server &s, Client &c);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawCounter(sf::RenderTarget &target) const;
	void drawAreaBounds(sf::RenderTarget &target) const;
	void update(bool counterCheck = true);
	void updateCounter();
	void checkPaddlePositions();
	void sendScore();
	void recvScore();
	void setStartState(bool resetCounter=true, bool ResetControllers = true);
	void setOpponentRightController(const std::shared_ptr<PaddleController>& opponentController);
	void setOpponentLeftController(const std::shared_ptr<PaddleController>& opponentController);
	void resetOpponentControllers();
	sf::Time getGameTime()const;
	std::pair<int,int> getPoints()const;
	const Puck& getBall() const;
	bool isWin(int &playerId);
};

#endif
