#include "Paddle.hpp"

Paddle::Paddle(){
	size = sf::Vector2f(Conf::paddleHeight, Conf::paddleWidth);
}

void Paddle::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	sf::RectangleShape rs;
	float x = (position.x * (Conf::gaSize.x / Conf::areaWidth));
	float y = (position.y * (Conf::gaSize.y / Conf::areaHeight));
	rs.setPosition(x, y);
	rs.setSize(sf::Vector2f(size.x * Conf::gas, size.y * Conf::gas));
	rs.setOrigin(rs.getGlobalBounds().width / 2.f, rs.getGlobalBounds().height / 2.f);
	rs.setFillColor(sf::Color::Blue);
	rs.setOutlineThickness(2.f);
	rs.setOutlineColor(sf::Color::Black);
	rs.rotate(angle);
	target.draw(rs,states);
}

void Paddle::update(CameraPointer & pointer)
{
	sf::Vector2f ctr = pointer.getPointerPos(0);
	ctr += pointer.getPointerPos(1);
	ctr*=0.5f;

	lastPosition = position;
	position.x = -(Conf::areaWidth / 2.f) + ctr.x * Conf::areaWidth;
	position.y = -(Conf::areaHeight / 2.f) + ctr.y * Conf::areaHeight;

	updateLinearVelocity();

	sf::Vector2f p1,p2;
	p1.x = -(Conf::areaWidth / 2.f) + pointer.getPointerPos().x * Conf::areaWidth;
	p1.y = -(Conf::areaHeight / 2.f) + pointer.getPointerPos().y * Conf::areaHeight;

	p2.x = -(Conf::areaWidth / 2.f) + pointer.getPointerPos(1).x * Conf::areaWidth;
	p2.y = -(Conf::areaHeight / 2.f) + pointer.getPointerPos(1).y * Conf::areaHeight;

	float dX = p2.x - p1.x;
	float dY = p2.y - p1.y;

	lastAngle = angle;
	angle = std::atan2(dY, dX);
	angle *= 180.f / M_PI; //rad->deg conversion

	updateAngularVelocity();

//	std::cout<<"angV = "<<angularVelocity<<std::endl<<"linV = "<<linearVelocity<<std::endl;
}

