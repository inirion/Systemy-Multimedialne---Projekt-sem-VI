/**
 * \file
 * \brief
 * Definicja klasy Broadcaster dziedziczącej po Networking
 *
 * \class Broadcaster
 * \brief
 * Klasa broadcastera UDP
 *
 * Klasa Broadcaster służy do rozgłaszania pakietów UDP w sieci lokalnej.
 * Rozgłaszanie jest aktywowane gdy stworzymy nowy serwer i deaktywuje się zaraz po połączeniu klienta.
 */


#ifndef BROADCASTER_HPP
#define BROADCASTER_HPP

#include <SFML/Network.hpp>
#include "Networking.hpp"
#include "Conf.hpp"
#include <vector>
#include <string>
#include <tuple>
#include <chrono>

#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif

enum class STATES {
	BROADCASTING = 0,
	EXIT = 1,
	FAILED = 2
};

#define ConnectionText(btn) (std::get<TupleFields::NAME>(btn))
#define ConnectionIP(btn) (std::get<TupleFields::IPADRESS>(btn))

using serverTuple = std::tuple<sf::IpAddress, std::wstring, STATES, double>;
enum TupleFields { IPADRESS, NAME, STATE, TIMESTAMP};

class Broadcaster : public Networking<sf::UdpSocket>
{
private:
	sf::Int32 lastFrameTime;
	std::wstring serverName;
	sf::IpAddress incomingConnectionAddress;
	std::vector<serverTuple> conns;
	sf::Text list;
	bool checkNewConn();
	void printConns();

	serverTuple onNewConnection();
	void broadcast(STATES);
public:

	bool Send(sf::Packet)override;
	bool Recive(sf::Packet&) override;
	void SetServerName(const std::wstring &serverName);

	void update();
	void close();
	std::vector<std::pair<std::wstring, sf::IpAddress>> getConns();
	Broadcaster();
	virtual ~Broadcaster();
};

#endif
