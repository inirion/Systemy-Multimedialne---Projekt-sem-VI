#include "Server.hpp"

bool Server::setConnection()
{
	if (listener.accept(socket) != sf::Socket::Done) return false;
	else return true;
}

void Server::Disconnect()
{
	socket.disconnect();
}

bool Server::Send(sf::Packet packet)
{
	if(socket.send(packet) == sf::TcpSocket::Done) return true;
	else return false;
}

bool Server::Recive(sf::Packet& packet)
{
	packet.clear();
	if (socket.receive(packet) == sf::TcpSocket::Done) return true;
	else return false;
}

Server::Server():Networking(Conf::port)
{
	listener.setBlocking(false);
	socket.setBlocking(false);
	if (listener.listen(port) != sf::Socket::Done)
	{
		throw "Couldn't connect socket =(";
	}
}


Server::~Server()
{
}
