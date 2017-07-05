/*
 * Pointer.cpp
 *
 *  Created on: 17.03.2017
 *      Author: jakub
 */

#include "CameraPointer.hpp"
#include <algorithm>

float sqdist(sf::Vector2f a, sf::Vector2f b){
	sf::Vector2f d = a - b;
	return d.x * d.x + d.y * d.y;
}

float sqdist(cv::Point a, cv::Point b){
	sf::Vector2f d(a.x - b.x, a.y - b.y);
	return d.x * d.x + d.y * d.y;
}

CamPoint::CamPoint():
	lastDist(0.f)
{}

CameraPointer::CameraPointer(sf::RectangleShape& rs):
	captureBackground(rs),
	radius(0.f)
{
	dp.minThreshold = 100;
	dp.maxThreshold = 200;
	dp.filterByCircularity = true;
	dp.minCircularity = 0.02;
	dp.filterByConvexity = true;
	dp.minConvexity = 0.5;
	dp.filterByInertia = true;
	dp.minInertiaRatio = 0.1;
	dp.filterByColor = true;
	dp.blobColor = 255;
	dp.minDistBetweenBlobs = 32.f;
	detector = cv::SimpleBlobDetector::create(dp);
}

void CameraPointer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::CircleShape cs;
	float r = Conf::gs * 20;
	cs.setRadius(r);
	cs.setOrigin(r, r);

	if (camPoint[0].pressed) {
		cs.setFillColor(sf::Color::Green);
	} else {
		cs.setFillColor(sf::Color::Red);
	}

	sf::Vector2f rp = captureBackground.getPosition();
	sf::Vector2f pp = camPoint[0].pos;
	sf::FloatRect fr = captureBackground.getGlobalBounds();
	pp.x *= fr.width;
	pp.y *= fr.height;

	cs.setPosition(rp + pp);
	target.draw(cs,states);

	float ratio = 1.f * Conf::gaSize.x / defaultCaptureWidth;


	if(Conf::pcc){
		r = ratio * Conf::spr * radius;
		cs.setRadius(r);
		cs.setOrigin(r, r);
		cs.setFillColor(sf::Color(0, 0, 0, 32));
		target.draw(cs,states);

		r = ratio * Conf::pr * radius;
		cs.setRadius(r);
		cs.setOrigin(r, r);
		cs.setFillColor(sf::Color(255, 255, 255, 32));
		target.draw(cs,states);
	}

	r = Conf::gs * 20;
	cs.setRadius(r);
	cs.setOrigin(r, r);

	cs.setFillColor(sf::Color::White);

	pp = camPoint[1].pos;
	pp.x *= fr.width;
	pp.y *= fr.height;

	cs.setPosition(rp + pp);
	target.draw(cs,states);
}

void CameraPointer::computePointers(cv::Mat& frame, CameraPointer* secondPointer) {
	std::vector<CamPoint*> vcp;
	std::vector<CamPoint> vcpTmp;

	vcp.push_back(&camPoint[0]);
	vcp.push_back(&camPoint[1]);
	if(secondPointer != nullptr){
		vcp.push_back(&secondPointer->camPoint[0]);
		vcp.push_back(&secondPointer->camPoint[1]);
	}
	const float bigFloat = 100000000.f;
	for(auto& p : vcp){
		p->lastDist = bigFloat;
		p->lastTargetPos = p->targetPos;

		vcpTmp.push_back(*p);
	}

	float half = frame.cols*0.5f;
	for(size_t j=0; j < vcp.size(); ++j){
		float min=bigFloat;
		float dist=0.f;
		cv::Point2f d;

		CamPoint* nearest=nullptr;
		int toDel=-1;
		for(size_t i=0; i < points.size(); ++i){
			if(secondPointer != nullptr){
				if(j < 2 && points[i].pt.x > half)
					continue;
				else if(j >= 2 && points[i].pt.x < half)
					continue;
			}

			cv::Point2f diff = vcp[j]->key.pt - vcp[j]->lastKey.pt;

			dist = sqdist(vcp[j]->key.pt+diff, points[i].pt);

			if(dist < min && dist < vcpTmp[j].lastDist){
				min = dist;
				nearest = &vcpTmp[j];
				toDel = i;
			}
		}
		if(nearest != nullptr){
			nearest->lastDist = min;
			nearest->lastKey = nearest->key;
			nearest->key = points[toDel];
			nearest->targetPos = gamePos(nearest->key.pt, frame);
			points.erase(points.begin()+toDel);
		}
	}

	for(size_t i=0; i < vcpTmp.size(); i+=2){
		float r1 = 8 * radius;
		float r2 = Conf::pr * radius;
		sf::Vector2f p0 = vcpTmp[i].targetPos;
		sf::Vector2f p1 = vcpTmp[i+1].targetPos;
		p0.x *= frame.cols;
		p1.x *= frame.cols;
		p0.y *= frame.rows;
		p1.y *= frame.rows;

		float dist = sqdist(p0, p1);

		if (dist > r1 * r1) {
			vcpTmp[i].pressed = vcpTmp[i+1].pressed = false;
		} else if (dist < r2 * r2) {
			vcpTmp[i].pressed = vcpTmp[i+1].pressed = true;
		} else {
			vcpTmp[i].pressed = vcpTmp[i+1].pressed = false;
		}
	}


	for(size_t j=0; j < vcp.size(); ++j){
//		if(vcpTmp[j].inertionTime > 0.f && vcpTmp[j].inertionTime < 1.f){
//			vcpTmp[j].targetPos += vcpTmp[j].targetPos - vcpTmp[j].lastTargetPos;
////			std::cerr<<"aaa"<<std::endl;
//		}

		*vcp[j] = vcpTmp[j];
	}
}

sf::Vector2f CameraPointer::gamePos(cv::Point pos, cv::Mat& frame) const {
	sf::Vector2f p = sf::Vector2f(pos.x, pos.y);
	p.x /= frame.cols;
	p.y /= frame.rows;
	return p;
}

void CameraPointer::updatePointerPos(float multiplier) {
	float dot,alpha,beta,gamma;
	sf::Vector2f d = camPoint[0].pos - camPoint[0].targetPos;

	dot = (d.x * d.x + d.y * d.y);
	if(dot != 0.f){
		alpha = ALPHA(dot);
		beta = 1.0f - alpha;
		gamma = alpha*multiplier+beta;
		camPoint[0].pos.x = (alpha * multiplier * camPoint[0].pos.x + beta * camPoint[0].targetPos.x)/gamma;
		camPoint[0].pos.y = (alpha * multiplier * camPoint[0].pos.y + beta * camPoint[0].targetPos.y)/gamma;
	}

	d = camPoint[1].pos - camPoint[1].targetPos;
	dot = (d.x * d.x + d.y * d.y);
	if (dot != 0.f){
		alpha = ALPHA(dot);
		beta = 1.0f - alpha;
		gamma = alpha*multiplier+beta;
		camPoint[1].pos.x = (alpha * multiplier * camPoint[1].pos.x + beta * camPoint[1].targetPos.x)/gamma;
		camPoint[1].pos.y = (alpha * multiplier * camPoint[1].pos.y + beta * camPoint[1].targetPos.y)/gamma;
	}

	radius = (0.95f*radius + 0.05f*camPoint[0].key.size);
}

cv::Mat CameraPointer::detect(cv::Mat& frame, cv::Mat& frameLast, CameraPointer* secondPointer) {
	cv::Mat dst2;
	cv::Mat dst3;
	cv::Mat diff, diffGray, diffMask, circleMask, gray;
	cv::absdiff(frame, frameLast, diff);

	cv::cvtColor(diff, diffGray, cv::COLOR_BGR2GRAY);
	cv::threshold(diffGray, diffMask, Conf::detector.mt, 255, cv::THRESH_BINARY);

	int s = frame.cols / 10;
	cv::Mat kernel = cv::Mat::ones(cv::Size(s, s), CV_8UC1);
	cv::erode(diffMask, diffMask, cv::Mat());
	cv::rectangle(diffMask, camPoint[0].key.pt, camPoint[0].key.pt, cv::Scalar(255), CV_FILLED);
	cv::rectangle(diffMask, camPoint[1].key.pt, camPoint[1].key.pt, cv::Scalar(255), CV_FILLED);

	if(secondPointer != nullptr){
		cv::rectangle(diffMask, secondPointer->camPoint[0].key.pt, secondPointer->camPoint[0].key.pt, cv::Scalar(255), CV_FILLED);
		cv::rectangle(diffMask, secondPointer->camPoint[1].key.pt, secondPointer->camPoint[1].key.pt, cv::Scalar(255), CV_FILLED);
	}

	cv::dilate(diffMask, diffMask, kernel);

	cv::cvtColor(frame, frameDst, cv::COLOR_BGR2HSV);
	cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);


	size_t channel = frameDst.channels();
	size_t end = frameDst.cols * frameDst.rows * channel;

	auto ptr = frameDst.data;
	for(size_t i = 0; i < end; i+=channel){
		int h = ptr[i];
		h += Conf::capture.hs;

		if(h < 0)
			h += 180;
		else if(h > 180)
			h -= 180;

		ptr[i]=h;
	}

	cv::Scalar lowC(Conf::detector.hl, Conf::detector.sl, Conf::detector.vl);
	cv::Scalar highC(Conf::detector.hh, Conf::detector.sh, Conf::detector.vh);

	circles.clear();
	cv::HoughCircles(gray,circles,cv::HOUGH_GRADIENT,4,frame.rows/8, Conf::detector.ct1, Conf::detector.ct2, frame.rows/20, frame.rows/8);
	circleMask = cv::Mat::zeros(cv::Size(frameDst.cols, frameDst.rows), CV_8UC1);
	for(const auto &c: circles){
		cv::circle(circleMask, cv::Point(c[0],c[1]), c[2]*1.5, cv::Scalar(255), cv::FILLED);
	}

	cv::inRange(frameDst, lowC, highC, dst2);
	cv::erode(dst2, dst2, cv::Mat());
	cv::dilate(dst2, dst2, cv::Mat(), cv::Point(0, 0), 2);

	if(camPoint[1].targetPos.x != -1.f){
		cv::Point2f ct = camPoint[0].key.pt + camPoint[1].key.pt;
		ct *= 0.5f;

		sf::Vector2f vel = (camPoint[0].lastTargetPos - camPoint[0].targetPos);
		ct.x -= vel.x  * frame.cols;
		ct.y -= vel.y  *  frame.rows;

		cv::Point2f d = camPoint[0].key.pt - camPoint[1].key.pt;
		float ang = std::atan2(d.y, d.x)+M_PI_2;
		cv::Point2f p1(camPoint[0].key.size * std::cos(ang), camPoint[0].key.size * std::sin(ang));
		cv::Point2f p2 = -p1;
		cv::line(dst2, ct+p1, ct+p2, cv::Scalar(0), camPoint[0].key.size * 0.4);
	}
	if(secondPointer != nullptr && secondPointer->camPoint[1].targetPos.x != -1.f){
		cv::Point2f ct = secondPointer->camPoint[0].key.pt + secondPointer->camPoint[1].key.pt;
		ct *= 0.5f;
		cv::Point2f d = secondPointer->camPoint[0].key.pt - secondPointer->camPoint[1].key.pt;
		float ang = std::atan2(d.y, d.x)+M_PI_2;
		cv::Point2f p1(camPoint[0].key.size * std::cos(ang), camPoint[0].key.size * std::sin(ang));
		cv::Point2f p2 = -p1;
		cv::line(dst2, ct+p1, ct+p2, cv::Scalar(0), camPoint[0].key.size * 0.4);
	}

	cv::bitwise_or(diffMask,circleMask,diffMask);
	cv::bitwise_and(dst2, diffMask, dst2);

	points.clear();
	detector->detect(dst2, points);

	filterPoints();


	if (Conf::mt == MenuType::mt_options_first) {
		cv::Mat r1(frameDst.size(), frameDst.type(), cv::Scalar(0,0,255));
		r1.copyTo(frameDst, diffMask);
		cv::Mat r3(frameDst.size(), frameDst.type(), cv::Scalar(Conf::detector.hh,Conf::detector.sh,Conf::detector.vh));
		r3.copyTo(frameDst, dst2);
		if (points.size() != 0) {
			for (auto& p : points) {
				cv::circle(frameDst, p.pt, p.size, highC, 3);
			}
		}
	}
	computePointers(frameDst, secondPointer);


	return frameDst;
}

sf::Vector2f CameraPointer::getPointerPos(int index) const {
	switch (index) {
		case 1:		return camPoint[1].pos;
		default:	return camPoint[0].pos;
	}
	
}

sf::Vector2f CameraPointer::getPointerPosRelative(int index) const {
	sf::Vector2f pp;
	switch(index){
		default:
		case 0: pp = camPoint[0].pos; break;
		case 1: pp = camPoint[1].pos; break;
	}

	sf::FloatRect fr = captureBackground.getGlobalBounds();
	pp.x *= fr.width;
	pp.y *= fr.height;
	return pp + captureBackground.getPosition();
}

void CameraPointer::setTargetPos(int index, sf::Vector2f pos) {
	switch(index){
		case 0: camPoint[0].targetPos = pos; break;
		case 1: camPoint[1].targetPos = pos; break;
	}
}

bool CameraPointer::isPressed()const {
	return camPoint[0].pressed;
}

void CameraPointer::filterPoints() {
	points.erase(
				std::remove_if(
						points.begin(), points.end(),
						[](const cv::KeyPoint& x){return x.size < Conf::detector.ms;}
				),
				points.end()
			);

    std::sort(points.begin(), points.end(), [](const cv::KeyPoint& a, const cv::KeyPoint& b) {
        return a.size > b.size;
    });

    if((int)points.size() > Conf::detector.pl)
    	points.resize(Conf::detector.pl);
}

void CameraPointer::setTargetGamePos(int index, sf::Vector2f gpos) {
	gpos.x /= Conf::areaWidth;
	gpos.x += 0.5f;
	gpos.y /= Conf::areaHeight;
	gpos.y += 0.5f;

	setTargetPos(index, gpos);
}

sf::Vector2f CameraPointer::getPointerGamePos(int index) const {
	sf::Vector2f p = getPointerPos(index);

	p.x*=Conf::areaWidth;
	p.y*=Conf::areaHeight;
	p.x -= Conf::areaWidth*0.5f;
	p.y -= Conf::areaHeight*0.5f;

	return p;
}
