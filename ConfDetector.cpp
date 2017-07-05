/*
 * ConfDetector.cpp
 *
 *  Created on: 28.04.2017
 *      Author: jakub
 */

#include "ConfDetector.hpp"

int ConfDetector::hueLow = defaultDetectorHueLow;
const int& ConfDetector::hl = ConfDetector::hueLow;
int ConfDetector::hueHigh = defaultDetectorHueHigh;
const int& ConfDetector::hh = ConfDetector::hueHigh;
int ConfDetector::saturationLow = defaultDetectorSaturationLow;
const int& ConfDetector::sl = ConfDetector::saturationLow;
int ConfDetector::saturationHigh = defaultDetectorSaturationHigh;
const int& ConfDetector::sh = ConfDetector::saturationHigh;
int ConfDetector::valueLow = defaultDetectorValueLow;
const int& ConfDetector::vl = ConfDetector::valueLow;
int ConfDetector::valueHigh = defaultDetectorValueHigh;
const int& ConfDetector::vh = ConfDetector::valueHigh;
int ConfDetector::moveThreshold = defaultDetectorMoveThreshold;
const int& ConfDetector::mt = ConfDetector::moveThreshold;

int ConfDetector::circleMaskThreshold1 = defaultDetectorCircleMaskThreshold1;
const int& ConfDetector::ct1 = ConfDetector::circleMaskThreshold1;
int ConfDetector::circleMaskThreshold2 = defaultDetectorCircleMaskThreshold2;
const int& ConfDetector::ct2 = ConfDetector::circleMaskThreshold2;

int ConfDetector::pointsLimit = defaultDetectorPointsLimit;
const int& ConfDetector::pl = ConfDetector::pointsLimit;

float ConfDetector::minimumSize = defaultDetectorMinimumSize;
const float& ConfDetector::ms = ConfDetector::minimumSize;

