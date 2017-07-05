/**
 * \file
 * \brief
 * Definicja klasy Client dziedziczącej po Networking
 *
 * \class Client
 * \brief
 * Klasa klienta gry
 *
 * Klasa Client służy do nawiązania połączenia z serwerem gry AirHockey.
 */


#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <SFML/Network.hpp>
#include "Networking.hpp"
#include <iostream>

class Client : public Networking<sf::TcpSocket>
{
private:
	sf::IpAddress ip;
public:

	bool setConnection(sf::IpAddress);
	bool Send(sf::Packet)override;
	bool Recive(sf::Packet&) override;
	void Disconnect();
	inline sf::TcpSocket& getSocket() {
		return socket;
	}
	Client();
	virtual ~Client();
};

#endif
