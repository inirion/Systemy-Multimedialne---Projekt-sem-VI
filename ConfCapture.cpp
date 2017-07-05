/*
 * ConfCapture.cpp
 *
 *  Created on: 28.04.2017
 *      Author: jakub
 */

#include "ConfCapture.hpp"

int ConfCapture::deviceId = 0;
int ConfCapture::maxId = 5;
float ConfCapture::time = 1000000.f;
const float& ConfCapture::t = ConfCapture::time;
int ConfCapture::exposure = defaultCaptureExposure;
int ConfCapture::gamma = defaultCaptureGamma;
int ConfCapture::whiteBalance = defaultCaptureWhiteBalance;
int ConfCapture::hueShift = defaultCaptureHueShift;
const int& ConfCapture::hs = ConfCapture::hueShift;
bool ConfCapture::optionsUpdate = true;
