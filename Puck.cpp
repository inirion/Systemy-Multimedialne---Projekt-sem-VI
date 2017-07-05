#include "Puck.hpp"

float Puck::dot(sf::Vector2f v1, sf::Vector2f v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

Puck::Puck() :
	wasCollision(false)
{
	srand(time(NULL));

	angle = rand() % 20 + 40; // between 20 and 60
	color = sf::Color::Red;
}

void Puck::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	sf::CircleShape cs;
	cs.setOutlineThickness(1.f);
	cs.setFillColor(color);
	cs.setOutlineColor(sf::Color::Black);
	float radius = Conf::ballRadius * Conf::gas;

	cs.setRadius(radius);
	cs.setOrigin(cs.getRadius(), cs.getRadius());
	float x = (position.x * Conf::gas);
	float y = (position.y * Conf::gas);

	cs.setPosition(x,y);

//	std::cout<<position.x<<" "<<position.y<<std::endl;
//	std::cout<<Conf::gas<<" "<<(Conf::gaSize.x / Conf::areaWidth)<<" "<<(Conf::gaSize.y / Conf::areaHeight)<<std::endl;
//	cs.setPosition(sf::Vector2f());

	target.draw(cs,states);
}

void Puck::update(bool checkBounds)
{
	linearVelocity -= Conf::bf * Conf::dt/defaultCollisionIterations;

	if(linearVelocity > Conf::ballMaxVelocity)
		linearVelocity = Conf::ballMaxVelocity;

	if(linearVelocity < 0.f)
		linearVelocity = 0.f;


	position.x += linearVelocity * std::cos(angle * (M_PI / 180)) * Conf::dt/defaultCollisionIterations;
	position.y += linearVelocity * std::sin(angle * (M_PI / 180)) * Conf::dt/defaultCollisionIterations;
	
	float radius = Conf::ballRadius;

	if(checkBounds){
		if (position.x - radius < -Conf::areaWidth / 2.0){
			angle = 180 - angle;
			position.x = -Conf::areaWidth / 2.0 + radius;
		}
		else if (position.x + radius > Conf::areaWidth / 2.0){
			angle = 180 - angle;
			position.x = Conf::areaWidth / 2.0 - radius;
		}

		if (position.y - radius < -Conf::areaHeight / 2.0){
			angle = 360 - angle;
			position.y = -Conf::areaHeight / 2.0 + radius;

		}
		else if (position.y + radius > Conf::areaHeight / 2.0){
			angle = 360 - angle;
			position.y = Conf::areaHeight / 2.0 - radius;
		}
	}
}

bool Puck::updateCollision(const Paddle& paddle)
{
	sf::Vector2f rotatedCirclePos;
	sf::Vector2f paddlePos = paddle.getPosition();
	float rad = -paddle.getAngle() * (M_PI / 180);
	rotatedCirclePos.x = std::cos(rad) * (position.x - paddlePos.x) - std::sin(rad) * (position.y - paddlePos.y) + paddlePos.x;
	rotatedCirclePos.y = std::sin(rad) * (position.x - paddlePos.x) + std::cos(rad) * (position.y - paddlePos.y) + paddlePos.y;

	float closestY, closestX;

	paddlePos -= sf::Vector2f(Conf::paddleHeight / 2.f, Conf::paddleWidth / 2.f);

	int collisionSideShort = 0;
	if (rotatedCirclePos.x < paddlePos.x){
		closestX = paddlePos.x;
		collisionSideShort = -1;
	}
	else if (rotatedCirclePos.x > paddlePos.x + Conf::paddleHeight){
		closestX = paddlePos.x + Conf::paddleHeight;
		collisionSideShort = 1;
	}
	else{
		closestX = rotatedCirclePos.x;
	}

	int collisionSideLong=0;
	if (rotatedCirclePos.y < paddlePos.y){
		closestY = paddlePos.y;
		collisionSideLong= 1;
	}
	else if (rotatedCirclePos.y > paddlePos.y + Conf::paddleWidth){
		closestY = paddlePos.y + Conf::paddleWidth;
		collisionSideLong=-1;
	}
	else{
		closestY = rotatedCirclePos.y;
	}


	double a = std::abs(rotatedCirclePos.x - closestX);
	double b = std::abs(rotatedCirclePos.y - closestY);
	float distance = std::sqrt((a * a) + (b * b));

	float radius = Conf::ballRadius;

	bool collision = (distance < radius);
	if (collision) {
		if (!wasCollision) {
			wasCollision = true;
		}else{
			collision = false;
		}
	}else {
		wasCollision = false;
	}

	if(collision){

		float pa1 = paddle.getAngle();
		float pa2 = pa1 - 90;

		sf::Vector2f v1(std::cos(pa1 * (M_PI / 180)), std::sin(pa1 *(M_PI / 180)));
		sf::Vector2f v2(std::cos(pa2 * (M_PI / 180)), std::sin(pa2 *(M_PI / 180)));

		sf::Vector2f v(std::cos(angle * (M_PI / 180)), std::sin(angle * (M_PI / 180)));
		sf::Vector2f n = v2;

		float tempU = dot(v, n) / dot(n, n);
		sf::Vector2f u(n.x * tempU, n.y * tempU);
		sf::Vector2f w = v - u;
		v = w - u;

		angle = std::atan2(v.y, v.x) * (180 / M_PI);

		float collisionDepth = std::abs(distance - radius)+0.01;
		if(collisionSideLong == -1){
			position += v2 * -collisionDepth;
//			std::cout<<"long  -1"<<std::endl;
		}else if(collisionSideLong == 1){
			position += v2 * collisionDepth;
//			std::cout<<"long   1"<<std::endl;
		}else if(collisionSideShort == -1){
			position += v1 * -collisionDepth;
//			std::cout<<"short -1"<<std::endl;
			angle -= 90;
		}else if(collisionSideShort == 1){
			position += v1 * collisionDepth;
//			std::cout<<"short  1"<<std::endl;
			angle -= 90;
		}

		if (angle < 0) angle = 360 + angle;

		if(linearVelocity < 0.5){
			if(collisionSideLong != 0)
				angle = pa2;
			else
				angle = pa1;

			if(collisionSideLong == -1 || collisionSideShort == -1)
				angle += 180;
		}

		if(angle > 360)
			angle -= 360;


		linearVelocity += 0.2f + paddle.getLinearVelocity(); //uproszczone i nieprecyzyjne podejście do tematu
	}

	return collision;
}

void Puck::resetPos() {
	setPosition(sf::Vector2f(0,0));
	setAngle(0);
	linearVelocity = 0.f;
}
