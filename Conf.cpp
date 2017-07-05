/*
 * Conf.cpp
 *
 *  Created on: 09.03.2017
 *      Author: jakub
 */

#include "Conf.hpp"

ConfDetector Conf::detector;
ConfCapture Conf::capture;

float Conf::guiScale = 1.f;
const float& Conf::gs = Conf::guiScale;
float Conf::drawTime = 1000000.f;
const float& Conf::dt = Conf::drawTime;
float Conf::runTime = 0.f;
const float& Conf::rt = Conf::runTime;

float Conf::pressRadius = 2.f;
const float& Conf::pr = Conf::pressRadius;
float Conf::secondPointerRadius = 8.f;
const float& Conf::spr = Conf::secondPointerRadius;

MenuType Conf::menuType = MenuType::mt_main;
const MenuType& Conf::mt = Conf::menuType;

sf::Font Conf::fmono;
const sf::Font& Conf::fm = Conf::fmono;

const int Conf::areaWidth = 4;
const int Conf::areaHeight = 3;
const float Conf::gateWidth = 0.3f;
const float Conf::gateHeight = 1.0f;
const float Conf::paddleWidth = 0.1f;
const float Conf::paddleHeight = 0.5f;

const float Conf::ballRadius = 0.1f;
const float Conf::ballMaxVelocity = 8.f;

sf::Vector2u Conf::windowSize=sf::Vector2u();
const sf::Vector2u& Conf::ws = Conf::windowSize;

sf::Vector2f Conf::referencePos;
const sf::Vector2f& Conf::refPos = Conf::referencePos;

sf::Vector2f Conf::gameAreaSize;
const sf::Vector2f& Conf::gaSize = Conf::gameAreaSize;

float Conf::ballFriction = defaultBallFriction;
const float& Conf::bf = Conf::ballFriction;

bool Conf::pointerClickCircle = true;
const bool& Conf::pcc = Conf::pointerClickCircle;

bool Conf::pointerInGame = true;
const bool& Conf::pig = Conf::pointerInGame;

bool Conf::videoBackground = true;

float Conf::gameAreaScale = 0.0;
const float& Conf::gas = Conf::gameAreaScale;

bool Conf::isServer = false;
bool Conf::TCPstart = false;
unsigned short Conf::port = 50001;
sf::Clock Conf::clock;


