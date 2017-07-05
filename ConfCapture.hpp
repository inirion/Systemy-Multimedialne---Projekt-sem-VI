/*
 * ConfCapture.hpp
 *
 *  Created on: 28.04.2017
 *      Author: jakub
 */
/**
 * \file
 * \brief
 * Definicja statycznej klasy ConfCapture
 *
 * \class ConfCapture
 * \brief
 * Statyczna klasa konfiguracji kamerki
 *
 * Statyczna klasa ConfCapture, zawiera konfigurację urządzenia przechwytującego obraz.
 * Publicznie dostępne są stałe referencje do czasu odczytnia ramki oraz przesunięcia barwy.
 * Klasa ta jest zaprzyjaźniona z klasą Program oraz ConfigurationManager, przez co mogą zmieniać jej stan.
 */
#ifndef CONFCAPTURE_HPP_
#define CONFCAPTURE_HPP_

class Program;
class ConfigurationManager;

class ConfCapture {
	friend Program;
	friend ConfigurationManager;
public:
	static const float& t;
	static const int& hs;

	static void setOptionsUpdate(){
		optionsUpdate = true;
	}

private:
	static int deviceId;
	static int maxId;
	static float time;
	static int exposure;
	static int gamma;
	static int whiteBalance;
	static int hueShift;
	static bool optionsUpdate;

};

#define defaultCaptureExposure 300
#define defaultCaptureGamma 100
#define defaultCaptureWhiteBalance 5000
#define defaultCaptureWidth 640
#define defaultCaptureHeight 480
#define defaultCaptureHueShift 0


#endif /* CONFCAPTURE_HPP_ */
