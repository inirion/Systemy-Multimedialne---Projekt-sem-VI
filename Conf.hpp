/*
 * Conf.hpp
 *
 *  Created on: 09.03.2017
 *      Author: jakub
 */
/**
 * \file
 * \brief
 * Definicja statycznej klasy Conf
 *
 * \class Conf
 * \brief
 * Statyczna klasa konfiguracji
 *
 * Statyczna klasa Conf służy do globalnego dostępu dla wszystkich innych klas.
 * Publicznie dostępne pola stanowią głównie stałe oraz stałe referencje do pól prywatnych.
 * Klasa ta jest zaprzyjaźniona z klasą Program oraz ConfigurationManager, przez co mogą zmieniać jej stan.
 */


#ifndef CONF_HPP_
#define CONF_HPP_
#include <SFML/Graphics.hpp>

class Program;
class ConfigurationManager;
#include "ConfDetector.hpp"
#include "ConfCapture.hpp"

enum MenuType{
	mt_none,
	mt_options_first,
	mt_options_second,
	mt_options_defaults,
	mt_pause,
	mt_main,
	mt_game_hockey_singleplayer,
	mt_game_hockey_multiplayer_sidebyside,
	mt_game_hockey_multiplayer_lan,
	mt_game_hockey_select,
	mt_game_hockey_select_multi,
	mt_game_hockey_connect_server,
	mt_game_hockey_create_server,
	mt_game_hockey_create_sidebyside,
	mt_game_hockey_ai_test,
	mt_game_hockey_win,
	mt_paint,
	mt_game_hockey_lobby
};

class Conf {
	friend Program;
	friend ConfigurationManager;
public:
	static ConfDetector detector;
	static ConfCapture capture;

	static const float& gs;
	static const float& dt;
	static const float& rt;
	static const float& pr;
	static const float& spr;
	static const sf::Vector2u& ws;
	static const sf::Vector2f& refPos;

	static const int areaWidth;
	static const int areaHeight;
	static const float gateWidth;
	static const float gateHeight;
	static const float paddleWidth;
	static const float paddleHeight;
	static const float ballRadius;
	static const float ballMaxVelocity;

	static const sf::Vector2f &gaSize;
	static const float &gas;

	static const MenuType& mt;
	static const sf::Font& fm;
	static const float& bf;
	static const bool& pcc;
	static const bool& pig;

	static bool isServer;
	static bool TCPstart;
	static unsigned short port;
	static sf::Clock clock;

private:
	static float guiScale;
	static float drawTime;
	static float runTime;
	static MenuType menuType;
	static float pressRadius;
	static float secondPointerRadius;
	static sf::Font fmono;
	static sf::Vector2u windowSize;
	static sf::Vector2f referencePos;
	static sf::Vector2f gameAreaSize;
	static float gameAreaScale;
	static float ballFriction;
	static bool pointerClickCircle;
	static bool pointerInGame;
	static bool videoBackground;
};

#define defaultPort 7777
#define defaultBallFriction 1.0
#define defaultCollisionIterations 8


#endif /* CONF_HPP_ */
