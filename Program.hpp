/*
 * Program.hpp
 *
 *  Created on: 09.03.2017
 *      Author: jakub
 */
/**
 * \file
 * \brief
 * Definicja klasy Program dziedziczącej po sf::Drawable
 *
 * \class Program
 * \brief
 * Główna klasa aplikacji.
 *
 * Steruje przepływem informacji.
 * Zawiera wszystkie widoki menu, inne elemnty interfejsu oraz klasy odpowiedzialne za grę oraz komunikacje sieciową.
 * Aktualizuje swój stan oraz innych obiektów w reakcji na określone zdarzenia.
 */

#ifndef PROGRAM_HPP_
#define PROGRAM_HPP_

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <opencv2/opencv.hpp>

#ifdef __linux__
#include <libv4l2.h>
#include <linux/videodev2.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#endif

#include "Conf.hpp"
#include "ConfigurationManager.hpp"
#include "S.hpp"
#include "TrackBar.hpp"
#include "CameraPointer.hpp"
#include "ButtonView.hpp"
#include "Hockey.hpp"
#include "UniCameraPointer.hpp"
#include "MenuMain.hpp"
#include "MenuOptionsFirst.hpp"
#include "MenuOptionsSecond.hpp"
#include "MenuDefaultsAsk.hpp"
#include "MenuPaint.hpp"
#include "MenuHockey.hpp"
#include "MenuHockeyMulti.hpp"
#include "MenuHockeyConnectServer.hpp"
#include "MenuHockeyCreateServer.hpp"
#include "MenuHockeyCreateSideBySide.hpp"
#include "MenuHockeyLobby.hpp"
#include "MenuHockeyWin.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include "Broadcaster.hpp"
#include "LanControllerClient.hpp"
#include "LanControllerServer.hpp"

#include "TextInput.hpp"
#include "AIController.hpp"

enum State {
	MENU		=	0,
	HOCKEY		=	1,
	PAINT		=	2
};

class Program : public sf::Drawable {
public:
	Program(sf::RenderWindow& window);

	virtual ~Program();

	void events(sf::Event& e);

	void update();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;

	void drawCameraNotFound(sf::RenderTarget& target)const;

	void drawInfo(sf::RenderTarget& target)const;

	void drawMenu(sf::RenderTarget& target)const;

	void drawOptionsFirst(sf::RenderTarget& target) const;

	void drawOptionsDefaultsQuestion(sf::RenderTarget& target) const;

	void drawBackground(sf::RenderTarget& target)const;

	void drawGame(sf::RenderTarget& target)const;

	void drawPaint(sf::RenderTarget& target)const;

	void drawHockeyInfo(sf::RenderTarget& target)const;

	UniPointer& getUniPointer();

	void launchHockeySingleplayerEvent(const MenuButton&);

	void launchHockeySideBySideEvent(const MenuButton&);

	void openOptionsFirstEvent(const MenuButton&);

	void openOptionsSecondEvent(const MenuButton&);

	void optionsBackEvent(const MenuButton&);

	void launchPaintEvent(const MenuButton&);

	void clearCanvasEvent(const MenuButton&);

	void defaultsOptionsEvent(const MenuButton&);

	void gameEscapeEvent(const MenuButton&);

	void returnToMenuEvent(const MenuButton&);

	void hockeySelectEvent(const MenuButton&);

	void hockeySelectMultiEvent(const MenuButton&);

	void hockeyConnectToServerMenuEvent(const MenuButton&);

	void hockeyConnectToServerEvent(const MenuButton&);

	void hockeyCreateServerMenuEvent(const MenuButton&);

	void hockeyCreateServerEvent(const MenuButton&);

	void hockeyCreateSideBySideMenuEvent(const MenuButton&);

	void toggleVideoBackgroundEvent(const MenuButton&);

	void togglePointerCircleEvent(const MenuButton&);

	void togglePointerInGameEvent(const MenuButton&);

	void showAiGameEvent(const MenuButton&);

	void resetGameEvent(const MenuButton&);

	void hockeyLobbyMenuEvent(const MenuButton&);

	void SendStartButtonClickEvent(const MenuButton&);

private:
	sf::RenderWindow &rw;
	ConfigurationObjects configurationObjects;
	ConfigurationManager configurationManager;

	sf::Clock clk;
	sf::Clock gameDrawClk;
	sf::Clock captureUpdateClk;
	std::shared_ptr<sf::Texture> texCapture;
	std::shared_ptr<sf::RenderTexture> texPaint;
	sf::RectangleShape captureBackground;
	sf::Thread captureThread;

	cv::VideoCapture capture;
	cv::Mat frame;
	cv::Mat frameLast;
	cv::Mat frameAvg;
	cv::Mat frameDst;

	std::map<std::string, std::shared_ptr<TrackBarBase>> trackBars;
	std::vector<std::string> trackBarsOrder;
	std::vector<uchar> camData;

	CameraPointer mainCameraPointer;
	CameraPointer secondCameraPointer;

	MousePointer mousePointer;
	UniPointer uniPointer;
	MenuMain menuMain;
	MenuOptionsFirst menuOptionsFirst;
	MenuOptionsSecond menuOptionsSecond;
	MenuDefaultsAsk menuDefaultsAsk;
	MenuButton gameEscape;
	MenuPaint menuPaint;
	MenuHockey menuHockey;
	MenuHockeyMulti menuHockeyMulti;
	MenuHockeyConnectServer menuHockeyConnectServer;
	MenuHockeyCreateServer menuHockeyCreateServer;
	MenuHockeyCreateSideBySide menuHockeyCreateSideBySide;
	MenuHockeyWin menuHockeyWin;
	MenuHockeyLobby menuHockeyLobby;
	

	TextInput serverName;
	TextInput leftNick;
	TextInput rightNick;

	Client c;
	Server s;
	Broadcaster b;

	sf::IpAddress publicIp;
	sf::IpAddress localIp;

	float lastCaptureCheckTime;
	int focusedTrackBar;
	size_t aiGeneration;
	bool optionHold;
	bool frameReady;
	bool windowFocus;
	MenuType lastGame;

	State state;
	Hockey hockey;

	void initTrackBars();

	void resizeEventHandle(sf::Event& e);

	void captureExist();

	void updateCameraSettings();

	void updateOpened();

	void updateConfigTrackbars();

	void updateFrame();

	void updateMenus(bool force = false);

	void updateWindowSize();

	void updatePointers();

	void updateCaputreBackground();

	bool captureCheck();

	void captureThreadFunc();

	void updateGameAreaSize();

	void resetTrackBarValues();

	void updateGame();

	void updatePaint();

	void updateOptionButtonNames();


	inline float now(){
		return clk.getElapsedTime().asSeconds();
	}

};



#endif /* PROGRAM_HPP_ */
