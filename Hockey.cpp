#include "Hockey.hpp"
#include "LanControllerClient.hpp"

Hockey::Hockey(CameraPointer &pointerLeft, CameraPointer &pointerRight, Server &s, Client &c) :
	startCounter(3),
	winPoints(10),
	pointerLeft(pointerLeft),
	pointerRight(pointerRight),
	server(s),
	client(c)
{
	float halfArea=0.5*Conf::areaWidth;
	gateLeft.setPosition(sf::Vector2f(-halfArea-Conf::gateWidth-0.05,-0.5*Conf::gateHeight));
	gateRight.setPosition(sf::Vector2f(halfArea+0.05,-0.5*Conf::gateHeight));

	setStartState();
}

void Hockey::draw(sf::RenderTarget & target, sf::RenderStates states) const{
	drawAreaBounds(target);
	target.draw(paddleLeft,states);
	target.draw(paddleRight,states);
	target.draw(ball,states);
	target.draw(gateLeft,states);
	target.draw(gateRight,states);

	if (startCounter >= 0) {
		drawCounter(target);
	}
}

void Hockey::drawCounter(sf::RenderTarget & target) const
{
	sf::Text text;
	text.setCharacterSize(100);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(5.f);
	text.setFont(Conf::fm);
	if (startCounter <= 0)
		text.setString("START!");
	else
		text.setString(std::to_string(startCounter));
	text.setPosition(0.f, 0.f);
	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	target.draw(text);
}

void Hockey::drawAreaBounds(sf::RenderTarget & target) const{
	sf::RectangleShape rs;
	rs.setSize(Conf::gaSize);
	rs.setOutlineThickness(0.05f*Conf::gas);
	rs.setOutlineColor(sf::Color::Red);
	rs.setPosition(Conf::refPos);
	rs.setFillColor(sf::Color::Transparent);
	rs.move(
				sf::Vector2f(
						(Conf::ws.x - Conf::gaSize.x) * 0.5f,
						(Conf::ws.y - Conf::gaSize.y) * 0.5f
					)
				);
	target.draw(rs);
	
}

void Hockey::update(bool counterCheck){
	if (counterCheck && startCounter >= 0) {
		updateCounter();
		return;
	}
	for(size_t i = 0; i < defaultCollisionIterations; ++i){
		if(opponentLeftController){
			opponentLeftController->update(pointerRight,pointerLeft,ball);
		}
		pointerLeft.updatePointerPos(defaultCollisionIterations);

		if(opponentRightController){
			opponentRightController->update(pointerLeft,pointerRight,ball);
		}
		pointerRight.updatePointerPos(defaultCollisionIterations);

		paddleLeft.update(pointerLeft);
		paddleRight.update(pointerRight);
		checkPaddlePositions();

		sf::Vector2f bp = ball.getPosition();

		if(bp.x < -Conf::areaWidth/2.0){
			++points.second;
			sendScore();
			recvScore();
			ball.resetPos();
		}else if(bp.x > Conf::areaWidth/2.0){
			++points.first;
			sendScore();
			recvScore();
			ball.resetPos();
		}else{
			float gy = gateLeft.getPosition().y;
			float gh = gateLeft.getSize().y;

			bool boundCheck = true;
			if(bp.y - Conf::ballRadius > gy && bp.y + Conf::ballRadius < gy + gh){
				boundCheck = false;
			}
			if (Conf::isServer || Conf::mt != mt_game_hockey_multiplayer_lan) {
				ball.update(boundCheck);
				
				if (ball.updateCollision(paddleLeft)) {
					ball.setColor(sf::Color::Cyan);
				}
				else if (ball.updateCollision(paddleRight)) {
					ball.setColor(sf::Color::Cyan);
				}
				else ball.setColor(sf::Color::Red);
			}
		}
	}
}

void Hockey::checkPaddlePositions() {
	sf::Vector2f p = paddleLeft.getPosition();
	if(p.x > 0.0){
		p.x = 0.0;
	}
	paddleLeft.setPosition(p);

	p = paddleRight.getPosition();
	if(p.x < 0.0){
		p.x = 0.0;
	}
	paddleRight.setPosition(p);
}

void Hockey::sendScore()
{
	sf::Packet p;
	p << LanControllerClient::packetStates::SCORE <<points.first << points.second;
	server.Send(p);
}

void Hockey::recvScore()
{
	sf::Packet p;
	if (client.Recive(p)) {
		int type, playerScore, enemyScore;
		if (p >> type >> enemyScore >> playerScore) {
			if (type == LanControllerClient::packetStates::SCORE) {
				points.first = playerScore;
				points.second = enemyScore;
			}
		}
	}
}

void Hockey::setStartState(bool resetCounter, bool ResetControllers) {
	pointerLeft.setTargetPos(0, sf::Vector2f(0.1,0.4));
	pointerLeft.setTargetPos(1, sf::Vector2f(0.1,0.6));
	pointerLeft.setTargetPos(0, sf::Vector2f(0.1,0.4));
	pointerLeft.setTargetPos(1, sf::Vector2f(0.1,0.6));

	pointerRight.setTargetPos(0, sf::Vector2f(0.9,0.4));
	pointerRight.setTargetPos(1, sf::Vector2f(0.9,0.6));
	pointerRight.setTargetPos(0, sf::Vector2f(0.9,0.4));
	pointerRight.setTargetPos(1, sf::Vector2f(0.9,0.6));

	if(resetCounter){
		startCounter=3;
		counterClk.restart();
	}
	points.first = points.second = 0;

	ball.resetPos();
	if (ResetControllers) {
		opponentLeftController.reset();
		opponentRightController.reset();
	}
	
}

void Hockey::setOpponentRightController(const std::shared_ptr<PaddleController>& opponentController) {
	this->opponentRightController = opponentController;
}

void Hockey::setOpponentLeftController(const std::shared_ptr<PaddleController>& opponentController) {
	this->opponentLeftController = opponentController;
}

void Hockey::updateCounter()
{
	if (startCounter < 0) return;
	if (counterClk.getElapsedTime().asMilliseconds() >= COUNTER_DELAY) {
		--startCounter;
		counterClk.restart();
	}
}

void Hockey::resetOpponentControllers() {
	opponentRightController.reset();
	opponentLeftController.reset();
}

sf::Time Hockey::getGameTime() const{
	return counterClk.getElapsedTime();
}

const Puck& Hockey::getBall() const {
	return ball;
}

std::pair<int, int> Hockey::getPoints() const {
	return points;
}

bool Hockey::isWin(int &playerId){
	bool isDiffOk = std::abs(points.first - points.second) >= 2;
	if (points.first >= winPoints && isDiffOk) { playerId = 1; return true; }
	else if (points.second >= winPoints && isDiffOk) { playerId = 2; return true; }
	return false;

}
