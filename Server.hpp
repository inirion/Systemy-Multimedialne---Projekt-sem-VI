/**
 * \file
 * \brief
 * Definicja klasy Server dziedziczącej po Networking
 *
 * \class Server
 * \brief
 * Klasa służąca do nawiązania połączenia oraz komunikacji z klientem
 */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <SFML/Network.hpp>
#include "Networking.hpp"
#include "Conf.hpp"
#include <iostream>

class Server : public Networking<sf::TcpSocket>
{
private:
	sf::Packet packet;
	sf::TcpListener listener;

public:
	bool setConnection();
	void Disconnect();
	bool Send(sf::Packet)override;
	bool Recive(sf::Packet&) override;
	inline sf::TcpSocket& getSocket() {
		return socket;
	}
	Server();
	virtual ~Server();
};

#endif
