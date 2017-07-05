/*
 * Pointer.hpp
 *
 *  Created on: 17.03.2017
 *      Author: jakub
 */

/**
 * \file
 * \brief
 * Definicja klasy CameraPointer dziedziczącej po sf::Drawable oraz klasy CamPoint dziedziczącej po HavePressed
 *
 * \class CameraPointer
 * \brief
 * Klasa wskaźnika sterowanego przez kamerkę
 *
 * Klasa CameraPointer reprezentuje wskaźnik sterowany przez kamerkę, który składa się z dwóch punktów klasy CamPoint.
 * Wskaźnik ten zawiera w sobie instancję cv::SimpleBlobDetector która pozwala wykrywać punkty z ramki cv::Mat.
 * Wszelkie parametry służące do konfiguracji procesu wykrywania punktów są odczytywane ze statycznej klasy Conf.
 *
 * \class CamPoint
 * \brief
 * Obiekty tej klasy są zawarte w klasie CameraPointer.
 *
 * Klasa ta reprezentuje pojedynczy punkt. Zawiera odpowiednie pola aktualnego stanu oraz poprzedniego.
 *
 */

#ifndef CAMERAPOINTER_HPP_
#define CAMERAPOINTER_HPP_

#define ALPHA(x)  (1.f / (1000.f * x + 2) + 0.5)

#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <opencv2/opencv.hpp>
#include "Conf.hpp"
#include "S.hpp"
#include "HavePressed.hpp"

float sqdist(sf::Vector2f, sf::Vector2f);

float sqdist(cv::Point, cv::Point);

class CameraPointer;

class CamPoint : public HavePressed{
	friend CameraPointer;
public:
	cv::KeyPoint key;
	cv::KeyPoint lastKey;
	sf::Vector2f pos;
	sf::Vector2f targetPos, lastTargetPos;
	float lastDist;

	CamPoint();
};


class CameraPointer : public sf::Drawable{
public:
	CameraPointer(sf::RectangleShape& rs);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;

	void computePointers(cv::Mat& frame, CameraPointer* secondPointer = nullptr);

	void updatePointerPos(float multiplier=1.f);

	cv::Mat detect(cv::Mat& frame, cv::Mat& frameLast, CameraPointer* secondPointer = nullptr);

	sf::Vector2f gamePos(cv::Point, cv::Mat& frame)const;

	sf::Vector2f getPointerPos(int index = 0) const;

	sf::Vector2f getPointerGamePos(int index = 0) const;

	sf::Vector2f getPointerPosRelative(int index = 0)const;

	void setTargetPos(int index, sf::Vector2f pos);
	void setTargetGamePos(int index, sf::Vector2f pos);

	bool isPressed()const;

private:
	CamPoint camPoint[2];

	std::vector<cv::KeyPoint> points;
	std::vector<cv::Vec3f> circles;

	cv::SimpleBlobDetector::Params dp;
	cv::Ptr<cv::SimpleBlobDetector> detector;
	cv::Mat frameDst;

	sf::RectangleShape& captureBackground;
	float radius;

	void filterPoints();

};

#endif /* CAMERAPOINTER_HPP_ */
