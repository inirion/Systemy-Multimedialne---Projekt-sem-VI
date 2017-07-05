/*
 * ConfDetector.hpp
 *
 *  Created on: 28.04.2017
 *      Author: jakub
 */
/**
 * \file
 * \brief
 * Definicja statycznej klasy ConfDetector
 *
 * \class ConfDetector
 * \brief
 * Statyczna klasa konfiguracji detektora
 *
 * Statyczna klasa ConfDetector, zawiera konfigurację używaną w procesie wykrywania punktów.
 * Klasa ta jest zaprzyjaźniona z klasą Program oraz ConfigurationManager, przez co mogą zmieniać jej stan.
 */
#ifndef CONFDETECTOR_HPP_
#define CONFDETECTOR_HPP_

class Program;
class ConfigurationManager;

class ConfDetector {
	friend Program;
	friend ConfigurationManager;

public:
	static const int& hl;
	static const int& hh;
	static const int& sl;
	static const int& sh;
	static const int& vl;
	static const int& vh;
	static const int& mt;
	static const int& ct1;
	static const int& ct2;
	static const int& pl;
	static const float& ms;

private:
	static int hueLow;
	static int hueHigh;
	static int saturationLow;
	static int saturationHigh;
	static int valueLow;
	static int valueHigh;
	static int moveThreshold;
	static int circleMaskThreshold1;
	static int circleMaskThreshold2;
	static int pointsLimit;
	static float minimumSize;
};

#define defaultDetectorHueLow 0
#define defaultDetectorHueHigh 40
#define defaultDetectorSaturationLow 10
#define defaultDetectorSaturationHigh 255
#define defaultDetectorValueLow 10
#define defaultDetectorValueHigh 255
#define defaultDetectorMoveThreshold 32
#define defaultDetectorCircleMaskThreshold1 300
#define defaultDetectorCircleMaskThreshold2 80
#define defaultDetectorPointsLimit 4
#define defaultDetectorMinimumSize 8.f


#endif /* CONFDETECTOR_HPP_ */
