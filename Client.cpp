#include "Client.hpp"
#include "Conf.hpp"
bool Client::setConnection(sf::IpAddress ip)
{
	this->ip = ip;

	if (socket.connect(ip, port) != sf::Socket::Done) return false;
	else return true;

}
bool Client::Send(sf::Packet packet)
{
	if (socket.send(packet) == sf::TcpSocket::Done) return true;
	else return false;
}

bool Client::Recive(sf::Packet &packet)
{
	packet.clear();
	if (socket.receive(packet) == sf::TcpSocket::Done) return true;
	else return false;
}

void Client::Disconnect()
{
	socket.disconnect();
}

 Client::Client():Networking(Conf::port)
{

	socket.setBlocking(false);

}

 Client::~Client()
{
	 
}
