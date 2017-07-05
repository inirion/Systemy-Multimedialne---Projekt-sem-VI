/*
 * Program.cpp
 *
 *  Created on: 09.03.2017
 *      Author: jakub
 */

#include "Program.hpp"

Program::Program(sf::RenderWindow &window) :
		rw(window),
		configurationObjects({rw,serverName,leftNick,rightNick}),
		captureThread(&Program::captureThreadFunc, this),
		mainCameraPointer(captureBackground),
		secondCameraPointer(captureBackground),
		mousePointer(rw),
		uniPointer(mousePointer, mainCameraPointer),
		menuMain(this),
		menuOptionsFirst(this),
		menuOptionsSecond(this),
		menuDefaultsAsk(this),
		menuPaint(this),
		menuHockey(this),
		menuHockeyMulti(this),
		menuHockeyConnectServer(this,c,b),
		menuHockeyCreateServer(this),
		menuHockeyCreateSideBySide(this),
		menuHockeyWin(this),
		menuHockeyLobby(this,b,s),
		lastCaptureCheckTime(0.f),
		focusedTrackBar(-1),
		aiGeneration(0),
		optionHold(false),
		frameReady(false),
		windowFocus(true),
		state(MENU),
		hockey(mainCameraPointer, secondCameraPointer,s,c)
{
//	Conf::menuType = mt_game_hockey_multiplayer_sidebyside;

	configurationManager.load(configurationObjects);
	texCapture = std::make_shared<sf::Texture>();
	texCapture->create(defaultCaptureWidth, defaultCaptureHeight);

	texPaint = std::make_shared<sf::RenderTexture>();
	texPaint->create(defaultCaptureWidth, defaultCaptureHeight);
	texPaint->setSmooth(true);

	if (!Conf::fmono.loadFromFile(S::path::font_mono)) {
		std::cerr << "Cant load " << S::path::font_mono << std::endl;
	}
	sf::View vw = rw.getView();
	vw.setCenter(0.f, 0.f);
	rw.setView(vw);

	initTrackBars();

	captureBackground.setFillColor(sf::Color::White);
	captureThread.launch();

	std::function<void(const MenuButton&)> f = std::bind(&Program::gameEscapeEvent,this, std::placeholders::_1);
	gameEscape.setAction(f);
	gameEscape.setHotKey(sf::Keyboard::Escape);
	gameEscape.setVisible(false);

	//inputIp.setFilter(&ipFilter);
	serverName.setSize(sf::Vector2f(400,0));

	updateOptionButtonNames();
}

Program::~Program() {
	configurationManager.save(configurationObjects);
	cv::destroyAllWindows();
	captureThread.wait();
}

void Program::events(sf::Event& e) {
	switch (e.type) {
		default:
			break;
		case sf::Event::Resized: {
			resizeEventHandle(e);
		}
		break;
		case sf::Event::GainedFocus:{
			windowFocus = true;
		}break;
		case sf::Event::LostFocus:{
			windowFocus = false;
		}break;

		case sf::Event::TextEntered:{
			if(Conf::menuType == mt_game_hockey_connect_server){

			}else if(Conf::menuType == mt_game_hockey_create_server){
				if(serverName.isFocus())
					serverName.updateInput(e.text.unicode);
			}else if(Conf::menuType == mt_game_hockey_create_sidebyside){
				if(leftNick.isFocus()){
					leftNick.updateInput(e.text.unicode);
				}else if(rightNick.isFocus()){
					rightNick.updateInput(e.text.unicode);
				}
			}
		}break;

		case sf::Event::KeyPressed: {
			switch (e.key.code) {
			default:
				break;
				case sf::Keyboard::Q: {
					if(
						Conf::menuType != mt_game_hockey_connect_server &&
						Conf::menuType != mt_game_hockey_create_server &&
						Conf::menuType != mt_game_hockey_create_sidebyside
					){
						configurationManager.save(configurationObjects);
						rw.close();
					}
				}break;

				case sf::Keyboard::Left:{
					if(Conf::menuType == mt_game_hockey_connect_server){

					}else if(Conf::menuType == mt_game_hockey_create_server){
						serverName.moveCursor(-1);
					}else if(Conf::menuType == mt_game_hockey_create_sidebyside){
						if(leftNick.isFocus()){
							leftNick.moveCursor(-1);
						}else if(rightNick.isFocus()){
							rightNick.moveCursor(-1);
						}
					}
				}break;

				case sf::Keyboard::Right:{
					if(Conf::menuType == mt_game_hockey_connect_server){

					}else if(Conf::menuType == mt_game_hockey_create_server){
						if(serverName.isFocus())
							serverName.moveCursor(1);
					}else if(Conf::menuType == mt_game_hockey_create_sidebyside){
						if(leftNick.isFocus()){
							leftNick.moveCursor(1);
						}else if(rightNick.isFocus()){
							rightNick.moveCursor(1);
						}
					}
				}break;
			}
		}
		break;
	}
}

void Program::update() {
	if (!Conf::TCPstart) {
		b.update();
	}
	
	if (lastGame == mt_game_hockey_multiplayer_lan) {
		sf::Packet p;
		int type;
		if (Conf::isServer) {
			s.Recive(p);
			if (p >> type){
//				std::cout << type << std::endl;
				switch (type) {
					case 10: {
						auto *b = menuHockeyWin.get(S::button::hockey_play_again);
						if (b != nullptr) {
							b->setVisible(true);
						}
					}break;
				}
			}
		}
	}

	if (Conf::isServer) {
		sf::Packet p;
		if (s.getSocket().receive(p) == sf::Socket::Disconnected) {
			s.Disconnect();
			state = MENU;
			Conf::TCPstart = false;
			Conf::menuType = mt_main;
		}
	}
	else {
		sf::Packet p;
		if (c.getSocket().receive(p) == sf::Socket::Disconnected) {
			c.Disconnect();
			state = MENU;
			Conf::TCPstart = false;
			Conf::menuType = mt_main;
		}
	}

	Conf::drawTime = gameDrawClk.getElapsedTime().asSeconds();
	gameDrawClk.restart();
	Conf::runTime = now();

	Conf::referencePos = rw.mapPixelToCoords(sf::Vector2i(0, 0));

	updateWindowSize();

	updateGameAreaSize();
	mousePointer.update();
	updateCaputreBackground();

	if(captureCheck() && capture.isOpened()){
		updateOpened();
		switch(state){
			case State::MENU:
				updatePointers();
			break;
			case State::HOCKEY:
				updateGame();
			break;
			case State::PAINT:
				updatePaint();
			break;
		}
	}
}

void Program::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	drawBackground(target);
	drawGame(target);
	drawPaint(target);
	drawMenu(target);

	switch(Conf::mt){
		case MenuType::mt_game_hockey_singleplayer:
		case MenuType::mt_game_hockey_multiplayer_lan:
		case MenuType::mt_game_hockey_multiplayer_sidebyside:
			if(Conf::pointerInGame){
				secondCameraPointer.draw(target, states);
				mainCameraPointer.draw(target,states);
			}
		break;
		default:
			mainCameraPointer.draw(target,states);
		break;
	}
	drawCameraNotFound(target);
	drawInfo(target);
}

void Program::drawBackground(sf::RenderTarget& target) const {
	switch(Conf::mt){
		case mt_game_hockey_singleplayer:
		case mt_game_hockey_multiplayer_lan:
		case mt_game_hockey_multiplayer_sidebyside:
		case mt_game_hockey_ai_test:
		case mt_options_first:
		case mt_options_second:
		case mt_options_defaults:
		{
			if(
				!Conf::videoBackground &&
				Conf::mt != mt_options_first &&
				Conf::mt != mt_options_defaults
			){
				sf::RectangleShape rs = captureBackground;
				rs.setTexture(nullptr);
				rs.setFillColor(sf::Color::Black);
				target.draw(rs);
			}else{
				target.draw(captureBackground);
			}
		}break;

		default: break;
	}
}

void Program::drawCameraNotFound(sf::RenderTarget& target) const {
	if (!capture.isOpened()) {
		sf::RectangleShape rs;
		rs.setSize(sf::Vector2f(Conf::windowSize.x, Conf::windowSize.y));
		rs.setPosition(Conf::referencePos);
		rs.setFillColor(sf::Color(0, 0, 0));

		target.draw(rs);

		sf::Text t(S::text::camera_not_found, Conf::fmono, 50);
		t.scale(Conf::gs, Conf::gs);
		sf::FloatRect fr = t.getGlobalBounds();

		sf::Vector2f rss = rs.getSize();
		rss.x *= 0.5;
		rss.y *= 0.5;

		t.setPosition(rs.getPosition() + rss);
		t.move(-fr.width / 2, -fr.height / 2);
		target.draw(t);
	}
}

void Program::drawInfo(sf::RenderTarget& target) const {
	std::string s = S::version;
	sf::Text t(s, Conf::fmono, 30);

	t.setPosition(Conf::referencePos);
	t.setScale(Conf::gs, Conf::gs);

	target.draw(t);
}

void Program::drawMenu(sf::RenderTarget& target) const {
	switch (Conf::mt) {
		default:
			break;
		case MenuType::mt_options_first: {
			drawOptionsFirst(target);
			target.draw(menuOptionsFirst);
		}break;

		case MenuType::mt_options_second: {
			target.draw(menuOptionsSecond);
		}break;

		case MenuType::mt_options_defaults:{
			drawOptionsFirst(target);
			target.draw(menuOptionsFirst);
			drawOptionsDefaultsQuestion(target);
			target.draw(menuDefaultsAsk);
		}break;

		case MenuType::mt_main:{
			target.draw(menuMain);
		}break;
		
		case MenuType::mt_game_hockey_lobby: {
			target.draw(menuHockeyLobby);
		}break;

		case MenuType::mt_paint:{
			target.draw(menuPaint);
		}break;

		case MenuType::mt_game_hockey_select:{
			target.draw(menuHockey);
		}break;

		case MenuType::mt_game_hockey_select_multi:{
			target.draw(menuHockeyMulti);
		}break;

		case MenuType::mt_game_hockey_connect_server:{
			target.draw(menuHockeyConnectServer);
			//target.draw(inputIp);
		}break;

		case MenuType::mt_game_hockey_create_server:{
			target.draw(menuHockeyCreateServer);
			target.draw(serverName);

			sf::Text text;
			text.setString("Server name :");
			text.setFont(Conf::fm);
			text.setCharacterSize(40);
			text.setScale(Conf::gs, Conf::gs);
			sf::Vector2f p;
			p.x += Conf::ws.x * 0.5f - serverName.getSizeReal().x * 0.5f;
			p.y += Conf::ws.y * 0.5f - serverName.getSizeReal().y * 4.0f;
			text.setPosition(Conf::refPos + sf::Vector2f(p));
			target.draw(text);
		}break;

		case MenuType::mt_game_hockey_create_sidebyside:{
			target.draw(menuHockeyCreateSideBySide);
			target.draw(leftNick);
			target.draw(rightNick);
		}break;
		case MenuType::mt_game_hockey_win: {
			target.draw(menuHockeyWin);
		}break;
	}
}

void Program::drawOptionsFirst(sf::RenderTarget& target) const {
	sf::RectangleShape rs;
	rs.setPosition(Conf::referencePos);
	rs.setSize(sf::Vector2f(Conf::windowSize.x, Conf::windowSize.y));
	rs.setFillColor(sf::Color(0, 0, 0, 127));

	target.draw(rs);

	std::string s = S::text::options_window_name;

	sf::Text t(s, Conf::fmono, 50);
	t.setScale(Conf::gs, Conf::gs);
	t.setPosition(Conf::referencePos + sf::Vector2f(Conf::windowSize.x / 2, 0));
	t.move(-t.getGlobalBounds().width / 2, 0);
	target.draw(t);

	cv::Mat hsv(1,1,CV_8UC3);
	cv::Mat rgb,rgb2;
	hsv.data[0] = Conf::detector.hueHigh;
	hsv.data[1] = Conf::detector.saturationHigh;
	hsv.data[2] = Conf::detector.valueHigh;
	cv::cvtColor(hsv, rgb, cv::COLOR_HSV2RGB);
	const float h = t.getGlobalBounds().height;
	rs.setSize(sf::Vector2f(h,h));
	rs.setFillColor(sf::Color(rgb.data[0],rgb.data[1],rgb.data[2]));
	rs.setPosition(Conf::referencePos + sf::Vector2f(Conf::windowSize.x-h,0.f));
	rs.setOutlineColor(sf::Color::White);
	rs.setOutlineThickness(2.f);
	target.draw(rs);

	hsv.data[0] = Conf::detector.hueLow;
	hsv.data[1] = Conf::detector.saturationLow;
	hsv.data[2] = Conf::detector.valueLow;
	cv::cvtColor(hsv, rgb2, cv::COLOR_HSV2RGB);
	rs.move(-h,0);
	rs.setFillColor(sf::Color(rgb2.data[0],rgb2.data[1],rgb2.data[2]));
	target.draw(rs);


	for(const auto &t: trackBars){
		target.draw(*t.second);
	}
}

void Program::resizeEventHandle(sf::Event& e) {
	sf::View vw = rw.getView();
	vw.setSize(e.size.width, e.size.height);
	rw.setView(vw);

	Conf::guiScale = (float) (e.size.width * e.size.height) / 3000000;
	Conf::guiScale = std::pow(Conf::guiScale, 0.5);

	updateMenus(true);
}

void Program::captureExist() {
#ifdef __linux__
	std::string path = "/dev/video" + std::to_string(Conf::capture.deviceId);
	std::ifstream file(path);
	if (file.is_open()) {
		file.close();
	} else {
		std::cerr << "Camera unpluged" << std::endl;
		capture.release();
	}

#elif _WIN32

#endif
}

void Program::updateCameraSettings() {
	if (Conf::capture.optionsUpdate) {
		Conf::capture.optionsUpdate = false;

#ifdef __linux__
		// open capture
		std::string path = "/dev/video" + std::to_string(Conf::capture.deviceId);
		int descriptor = v4l2_open(path.c_str(), O_RDWR);

		// manual exposure control
#define IFCTL(STR) 	if(v4l2_ioctl(descriptor, VIDIOC_S_CTRL, &c) != 0) std::cerr<<STR<<std::endl

		v4l2_control c;
		c.id = V4L2_CID_EXPOSURE_AUTO;
		c.value = V4L2_EXPOSURE_MANUAL;

		IFCTL("Exposure manual error");

		// auto priority control
		c.id = V4L2_CID_EXPOSURE_AUTO_PRIORITY;
		c.value = 0;
		IFCTL("Exposure auto priority error");

		c.id = V4L2_CID_EXPOSURE_ABSOLUTE;
		c.value = Conf::capture.exposure;
		IFCTL("Exposure set error");

		c.id = V4L2_CID_GAMMA;
		c.value = Conf::capture.gamma;
		IFCTL("Gamma set error");

		c.id = V4L2_CID_AUTO_WHITE_BALANCE;
		c.value = 0;
		IFCTL("Auto white ballance off error");

		c.id = V4L2_CID_WHITE_BALANCE_TEMPERATURE;
		c.value = Conf::capture.whiteBalance;
		IFCTL("White balance temperature set error");

		v4l2_close(descriptor);

#else
#define IFCTL(C,V,E) 	if(!capture.set(C,V)) std::cerr<<E<<std::endl

		IFCTL(cv::CAP_PROP_AUTO_EXPOSURE,0, "Exposure manual error");
		IFCTL(cv::CAP_PROP_EXPOSURE, Conf::capture.exposure, "Exposure manual error");
		IFCTL(cv::CAP_PROP_GAMMA, Conf::capture.gamma, "gamma");
		IFCTL(cv::CAP_PROP_TEMPERATURE, Conf::capture.whiteBalance, "wb");

#endif
	}
}

void Program::updateOpened() {
	updateConfigTrackbars();
	updateMenus();
	updateCameraSettings();

	if(frameReady){
		
		camData.resize(frameDst.total() * 4);
		cv::Mat continuousRGBA(frameDst.size(), CV_8UC4, camData.data());
		cv::cvtColor(frameDst, continuousRGBA, cv::COLOR_HSV2RGB, 4);
		texCapture->update(camData.data());
		frameReady = false;
	}
}

void Program::updateConfigTrackbars() {
	if (Conf::mt == MenuType::mt_options_first) {
		float shift = Conf::gs * 80;
		float th = 1.f*(Conf::windowSize.y - 4*shift)/trackBars.size();
		bool pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
		float d = 0.f;
		if(!pressed){
			HaveFocus::unFocus();
		}else{
			d = mousePointer.getPosDiff().x;
		}

		sf::Vector2f mp = mousePointer.getPos();
		size_t i = 0;
		for(const auto &s : trackBarsOrder){
			auto& bar = trackBars[s];
			bar->setSize(sf::Vector2f(Conf::windowSize.x, th));
			bar->setPosition(Conf::referencePos + sf::Vector2f(0.f, i*th+shift));
			if(windowFocus)
				bar->update(mp, d, pressed);
			++i;
		}
	}
}

void Program::updateFrame() {
	frameLast = frame.clone();
	capture >> frame;
	cv::flip(frame,frame,1);
}

void Program::initTrackBars() {
	std::function<void()> f = Conf::capture.setOptionsUpdate;

	trackBars[S::option::exposure]=(std::make_shared<TrackBar<int>>(S::option::exposure, &Conf::capture.exposure, 1000.0, 0.0));
	trackBarsOrder.push_back(S::option::exposure);
	trackBars[S::option::exposure]->setAction(f);
	trackBars[S::option::gamma]=(std::make_shared<TrackBar<int>>(S::option::gamma, &Conf::capture.gamma, 500.0, 0.0));
	trackBarsOrder.push_back(S::option::gamma);
	trackBars[S::option::gamma]->setAction(f);
	trackBars[S::option::white_balance]=(std::make_shared<TrackBar<int>>(S::option::white_balance, &Conf::capture.whiteBalance, 6500.0, 2800.0));
	trackBarsOrder.push_back(S::option::white_balance);
	trackBars[S::option::white_balance]->setAction(f);
	trackBars[S::option::hue_shift]=(std::make_shared<TrackBar<int>>(S::option::hue_shift, &Conf::capture.hueShift, 90.0, -90.0));
	trackBarsOrder.push_back(S::option::hue_shift);
	trackBars[S::option::detector_h_l]=(std::make_shared<TrackBar<int>>(S::option::detector_h_l, &Conf::detector.hueLow,180.0, 0.0, nullptr, &Conf::detector.hueHigh));
	trackBarsOrder.push_back(S::option::detector_h_l);
	trackBars[S::option::detector_h_h]=(std::make_shared<TrackBar<int>>(S::option::detector_h_h, &Conf::detector.hueHigh,180.0, 0.0, &Conf::detector.hueLow));
	trackBarsOrder.push_back(S::option::detector_h_h);
	trackBars[S::option::detector_s_l]=(std::make_shared<TrackBar<int>>(S::option::detector_s_l, &Conf::detector.saturationLow, 255.0, 0.0, nullptr, &Conf::detector.saturationHigh));
	trackBarsOrder.push_back(S::option::detector_s_l);
	trackBars[S::option::detector_s_h]=(std::make_shared<TrackBar<int>>(S::option::detector_s_h, &Conf::detector.saturationHigh,255.0, 0.0, &Conf::detector.saturationLow));
	trackBarsOrder.push_back(S::option::detector_s_h);
	trackBars[S::option::detector_v_l]=(std::make_shared<TrackBar<int>>(S::option::detector_v_l, &Conf::detector.valueLow, 255.0, 0.0, nullptr, &Conf::detector.valueHigh));
	trackBarsOrder.push_back(S::option::detector_v_l);
	trackBars[S::option::detector_v_h]=(std::make_shared<TrackBar<int>>(S::option::detector_v_h, &Conf::detector.valueHigh, 255.0, 0.0, &Conf::detector.valueLow));
	trackBarsOrder.push_back(S::option::detector_v_h);
	trackBars[S::option::move_th]=(std::make_shared<TrackBar<int>>(S::option::move_th, &Conf::detector.moveThreshold,100.0, 0.0));
	trackBarsOrder.push_back(S::option::move_th);
	trackBars[S::option::circle_th_1]=(std::make_shared<TrackBar<int>>(S::option::circle_th_1, &Conf::detector.circleMaskThreshold1,1000.0,1.0));
	trackBarsOrder.push_back(S::option::circle_th_1);
	trackBars[S::option::circle_th_2]=(std::make_shared<TrackBar<int>>(S::option::circle_th_2, &Conf::detector.circleMaskThreshold2,1000.0,1.0));
	trackBarsOrder.push_back(S::option::circle_th_2);
	trackBars[S::option::min_size]=(std::make_shared<TrackBar<float>>(S::option::min_size, &Conf::detector.minimumSize, 100.0, 1.0));
	trackBarsOrder.push_back(S::option::min_size);
	trackBars[S::option::points_limit]=(std::make_shared<TrackBar<int>>(S::option::points_limit, &Conf::detector.pointsLimit, 8.0, 4.0));
	trackBarsOrder.push_back(S::option::points_limit);
}

void Program::captureThreadFunc() {
	while(rw.isOpen()){
		if(capture.isOpened()){
			if(!frameReady){
				if (frame.cols == 0 && frame.rows == 0) {					
					captureBackground.setTexture(texCapture.get());
				}
				updateFrame();
				Conf::capture.time = captureUpdateClk.getElapsedTime().asSeconds();
				captureUpdateClk.restart();

				if (
					texCapture &&
					!frame.empty() &&
					frame.size == frameLast.size
				){
					switch(Conf::mt){
						default:
						case MenuType::mt_game_hockey_singleplayer:
							frameDst = mainCameraPointer.detect(frame,frameLast);
							break;

						case MenuType::mt_game_hockey_multiplayer_sidebyside:
							frameDst = mainCameraPointer.detect(frame,frameLast, &secondCameraPointer);
							break;
						case MenuType::mt_game_hockey_multiplayer_lan:
							frameDst = mainCameraPointer.detect(frame, frameLast, &secondCameraPointer);
							break;
					}

					frameReady=true;
				}
			}else{
				sf::sleep(sf::milliseconds(1));
			}
		}else{
			sf::sleep(sf::milliseconds(16));
		}
	}
}

void Program::updateMenus(bool force) {
	MenuType mt = Conf::menuType;

	if(force)
		mt = MenuType::mt_none;

	bool mousePress = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	sf::Vector2f mp = mousePointer.getPos();


	switch(mt){
		default: if(!force) break;
		/* no break if force */
		case mt_main: 	menuMain.update(); if(!force) break;
		/* no break if force */
		case mt_options_first: 	menuOptionsFirst.update(); if(!force) break;
		/* no break if force */
		case mt_options_second:	menuOptionsSecond.update(); if(!force) break;
		/* no break if force */
		case mt_options_defaults: 	menuDefaultsAsk.update(); if(!force) break;
		/* no break if force */
		case mt_paint: menuPaint.update(); if(!force) break;
		/* no break if force */
		case mt_game_hockey_select: menuHockey.update(); if(!force) break;
		/* no break if force */
		case mt_game_hockey_select_multi: menuHockeyMulti.update(); if(!force) break;
		/* no break if force */
		case mt_game_hockey_lobby:menuHockeyLobby.update(); if (!force) break;
		/* no break if force */
		case mt_game_hockey_connect_server:{
			if (menuHockeyConnectServer.GetStartButtonClick()) {
				Conf::menuType = mt_game_hockey_multiplayer_lan;
				lastGame = Conf::menuType;
				state = HOCKEY;
				hockey.setOpponentLeftController(std::make_shared<LanControllerClient>(c));
			}
			menuHockeyConnectServer.update();
		} if(!force) break;
		/* no break if force */
		case mt_game_hockey_create_server:{
			sf::Vector2f p = Conf::refPos;
			p.x += Conf::ws.x * 0.5f - serverName.getSizeReal().x * 0.5f;
			p.y += Conf::ws.y * 0.5f - serverName.getSizeReal().y;
			serverName.setPosition(p);
			serverName.update(mp, mousePress);

			menuHockeyCreateServer.update();
		}if(!force) break;
		/* no break if force */
		case mt_game_hockey_create_sidebyside:{
			menuHockeyCreateSideBySide.update();
			sf::Vector2f p = Conf::refPos;
			float space = Conf::gs * 100;
			p.x += Conf::ws.x * 0.5f - (leftNick.getSizeReal().x+rightNick.getSizeReal().x + space) *0.5f;
			p.y += Conf::ws.y * 0.5f - leftNick.getSizeReal().y;
			leftNick.setPosition(p);
			p.x += leftNick.getSizeReal().x + space;
			rightNick.setPosition(p);
			leftNick.update(mp, mousePress);
			rightNick.update(mp, mousePress);
		}if(!force) break;
		/* no break if force */
		case mt_game_hockey_win: {
			menuHockeyWin.update();
		}if(!force) break;
		/* no break if force */
	}
}

void Program::launchHockeySingleplayerEvent(const MenuButton& b) {
	std::cerr<<"Button name: "<<b.getName()<<"; Game start"<<std::endl;
	state = HOCKEY;
	Conf::menuType = mt_game_hockey_singleplayer;
	hockey.setStartState();
	hockey.setOpponentRightController(std::make_shared<AIController>(-0.5*Conf::areaWidth));
}

void Program::drawGame(sf::RenderTarget & target) const
{
 	switch (state) {
		case HOCKEY:
			target.draw(hockey);
			drawHockeyInfo(target);
			break;
		default: return;
	}
}

void Program::openOptionsFirstEvent(const MenuButton&) {
	if (Conf::mt == MenuType::mt_options_first) {
		Conf::menuType = MenuType::mt_main;
		configurationManager.save(configurationObjects);
	} else {
		Conf::menuType = MenuType::mt_options_first;
	}
}

void Program::openOptionsSecondEvent(const MenuButton&) {
	Conf::menuType = MenuType::mt_options_second;
}

void Program::updateCaputreBackground() {
	if(frame.total() != 0){
		const float margin = 1.2;

		float r1 = 1.f * Conf::windowSize.x / (defaultCaptureWidth*margin);
		float r2 = 1.f * Conf::windowSize.y / (defaultCaptureHeight*margin);
		float ratio = r1;
		if (r2 < ratio)
			ratio = r2;

		sf::Vector2f rss(ratio * defaultCaptureWidth, ratio * defaultCaptureHeight);
		captureBackground.setSize(rss);
		captureBackground.setPosition(Conf::refPos);
		captureBackground.move(
				sf::Vector2f(
						(Conf::windowSize.x - rss.x) * 0.5f,
						(Conf::windowSize.y - rss.y) * 0.5f
					)
				);
	}
}

void Program::optionsBackEvent(const MenuButton&) {
	configurationManager.save(configurationObjects);
	Conf::menuType = MenuType::mt_main;
}

void Program::defaultsOptionsEvent(const MenuButton& mb) {
	std::string n = mb.getName();
	if(n == S::button::defaults){
		Conf::menuType = MenuType::mt_options_defaults;
	}else if(n == S::button::yes){
		resetTrackBarValues();
		Conf::menuType = MenuType::mt_options_first;
	}else if(n == S::button::no){
		Conf::menuType = MenuType::mt_options_first;
	}
}

void Program::updateGameAreaSize(){
	const float margin = 1.2;

	float r1 = 1.f * Conf::windowSize.x / (Conf::areaWidth * margin);
	float r2 = 1.f * Conf::windowSize.y / (Conf::areaHeight * margin);
	float ratio = r1;
	if (r2 < ratio)
		ratio = r2;


//	(1.0*Conf::ws.x/Conf::ws.y > 1.0*aw/ah) ? r = 1.f * Conf::ws.y / ah : r = 1.f * Conf::ws.x / aw;

	Conf::gameAreaSize = sf::Vector2f(Conf::areaWidth * ratio, Conf::areaHeight * ratio);

	Conf::gameAreaScale = Conf::gaSize.x / Conf::areaWidth;
}

void Program::drawOptionsDefaultsQuestion(sf::RenderTarget& target) const {
	sf::RectangleShape rs;
	rs.setSize(sf::Vector2f(Conf::windowSize.x, Conf::windowSize.y));
	rs.setFillColor(sf::Color(0,0,0,200));
	rs.setPosition(Conf::refPos);
	target.draw(rs);

	sf::Text t(S::text::to_defaults_ask, Conf::fm, 50);
	t.setScale(Conf::gs,Conf::gs);
	sf::FloatRect fr = t.getGlobalBounds();
	t.setPosition(Conf::refPos + sf::Vector2f(Conf::windowSize.x*0.5 - fr.width*0.5, Conf::windowSize.y*0.5 - fr.height*0.5));
	target.draw(t);

}

void Program::resetTrackBarValues() {
	trackBars[S::option::exposure]->setValue(defaultCaptureExposure);
	trackBars[S::option::gamma]->setValue(defaultCaptureGamma);
	trackBars[S::option::white_balance]->setValue(defaultCaptureWhiteBalance);
	trackBars[S::option::hue_shift]->setValue(defaultCaptureHueShift);
	trackBars[S::option::detector_h_h]->setValue(defaultDetectorHueHigh);
	trackBars[S::option::detector_h_l]->setValue(defaultDetectorHueLow);
	trackBars[S::option::detector_s_h]->setValue(defaultDetectorSaturationHigh);
	trackBars[S::option::detector_s_l]->setValue(defaultDetectorSaturationLow);
	trackBars[S::option::detector_v_h]->setValue(defaultDetectorValueHigh);
	trackBars[S::option::detector_v_l]->setValue(defaultDetectorValueLow);
	trackBars[S::option::move_th]->setValue(defaultDetectorMoveThreshold);
	trackBars[S::option::circle_th_1]->setValue(defaultDetectorCircleMaskThreshold1);
	trackBars[S::option::circle_th_2]->setValue(defaultDetectorCircleMaskThreshold2);
	trackBars[S::option::points_limit]->setValue(defaultDetectorPointsLimit);
	trackBars[S::option::min_size]->setValue(defaultDetectorMinimumSize);
}

UniPointer& Program::getUniPointer() {
	return uniPointer;
}

void Program::launchPaintEvent(const MenuButton&) {
	Conf::menuType = MenuType::mt_paint;
	state = State::PAINT;
}

void Program::drawPaint(sf::RenderTarget& target) const {
	if(state == PAINT){
		sf::RectangleShape rs, mask;
		rs = captureBackground;
		mask = rs;
		rs.setOutlineThickness(0.f);
		rs.setTexture(&texPaint->getTexture());

		mask.setTexture(nullptr);
		mask.setFillColor(sf::Color(0,0,0,128));
		target.draw(mask);
		target.draw(rs);
	}
}

void Program::updateGame(){
	
	int playerId;
	if (hockey.isWin(playerId)) {
		if(Conf::menuType != mt_game_hockey_win) lastGame = Conf::menuType;
		Conf::menuType = mt_game_hockey_win;
		std::wstring nick = (playerId == 1)? leftNick.getValue() : rightNick.getValue();
		std::string sNick(nick.begin(), nick.end());
		menuHockeyWin.get(S::button::hockey_win_info)->setName(S::button::hockey_player_won + sNick);
	}
	else hockey.update();
	gameEscape.update();
}

void Program::gameEscapeEvent(const MenuButton& mb) {
	if(state == State::HOCKEY || state == State::PAINT){
		if(Conf::mt == mt_game_hockey_ai_test){
			returnToMenuEvent(mb);
			Conf::menuType = mt_options_second;
		}else{
			returnToMenuEvent(mb);
		}
	}
}

void Program::clearCanvasEvent(const MenuButton&) {
	texPaint->clear(sf::Color::Transparent);
}

void Program::returnToMenuEvent(const MenuButton&) {
	state = State::MENU;
	sf::Packet p;
	if (lastGame == mt_game_hockey_multiplayer_lan) {
		
		if (Conf::isServer) {
			s.Disconnect();
			Conf::TCPstart = false;
		}
		else {
			c.Disconnect();
			Conf::TCPstart = false;
		}
	}
	Conf::menuType = mt_main;
}

void Program::hockeyConnectToServerMenuEvent(const MenuButton&) {
	Conf::menuType = MenuType::mt_game_hockey_connect_server;
}

void Program::hockeyConnectToServerEvent(const MenuButton&) {
	Conf::isServer = false;
}

void Program::hockeyCreateServerMenuEvent(const MenuButton&) {
	Conf::menuType = MenuType::mt_game_hockey_create_server;
	publicIp = sf::IpAddress::getPublicAddress();
	localIp = sf::IpAddress::getLocalAddress();
}

void Program::hockeyCreateServerEvent(const MenuButton&) {
	Conf::isServer = true;

	b.SetServerName(serverName.getValue());
	Conf::TCPstart = s.setConnection();
	Conf::menuType = MenuType::mt_game_hockey_lobby;
	hockey.setStartState(true);
}

void Program::hockeyCreateSideBySideMenuEvent(const MenuButton&) {
	Conf::menuType = MenuType::mt_game_hockey_create_sidebyside;
}

bool Program::captureCheck() {
	if (now() - lastCaptureCheckTime > 1.f) {
		lastCaptureCheckTime = now();

		rw.setTitle("Game FPS = "+std::to_string(1/Conf::dt)+" Camera FPS = "+std::to_string(1/Conf::capture.t));

		if (capture.isOpened()) {
			captureExist();
		}
		if (!capture.isOpened()) {
			if (
				Conf::capture.deviceId != -1 &&
				!capture.open(Conf::capture.deviceId)
			) {
				if (Conf::capture.deviceId < Conf::capture.maxId) {
					++Conf::capture.deviceId;
				} else {
					Conf::capture.deviceId = 0;
				}
			} else {
				if(!capture.set(cv::CAP_PROP_FRAME_WIDTH, defaultCaptureWidth)) std::cerr<<"Cant set CV_CAP_PROP_FRAME_WIDTH"<<std::endl;
				if(!capture.set(cv::CAP_PROP_FRAME_HEIGHT, defaultCaptureHeight)) std::cerr<<"Cant set CV_CAP_PROP_FRAME_HEIGHT"<<std::endl;

				Conf::capture.setOptionsUpdate();
			}
			return false;
		}
	}
	return true;
}

void Program::updateWindowSize() {
	sf::Vector2u ws = rw.getSize();
	if(Conf::windowSize.x != ws.x || Conf::windowSize.y != ws.y){
		Conf::windowSize = ws;
		sf::Event e;
		e.size.width = ws.x;
		e.size.height = ws.y;
		resizeEventHandle(e);
	}
}

void Program::updatePointers() {
	mainCameraPointer.updatePointerPos();
	secondCameraPointer.updatePointerPos();
}

void Program::drawHockeyInfo(sf::RenderTarget& target) const {
	sf::RectangleShape rs;
	rs.setSize(sf::Vector2f(Conf::ws.x, 0.1*Conf::gaSize.y-0.05*Conf::gas));
	rs.setFillColor(sf::Color(0,0,0,200));
	rs.setPosition(Conf::refPos);
	target.draw(rs);

	rs.move(0,Conf::ws.y-rs.getGlobalBounds().height);
	target.draw(rs);


	sf::Text txt(leftNick.getValue(), Conf::fm, 0.05*Conf::gaSize.y);

	if(Conf::mt == mt_game_hockey_ai_test)
		txt.setString("AI "+std::to_string(aiGeneration));


	sf::Vector2f p = captureBackground.getPosition();
	p.y = Conf::refPos.y;

	sf::Vector2f s = captureBackground.getSize();
	const float margin = 40*Conf::gs;
	txt.setPosition(p+sf::Vector2f(margin,0));
	txt.setOutlineThickness(2.f);
	txt.setFillColor(sf::Color(255,255,255,200));
	txt.setOutlineColor(sf::Color(0,0,0,200));
	target.draw(txt);


	if(Conf::mt == mt_game_hockey_singleplayer || Conf::mt == mt_game_hockey_ai_test)
		txt.setString("AI "+std::to_string(aiGeneration));
	else
		txt.setString(rightNick.getValue());
	txt.setPosition(p + sf::Vector2f(s.x-margin-txt.getGlobalBounds().width, 0));
	target.draw(txt);


	int seconds = hockey.getGameTime().asSeconds();
	int minutes = seconds/60;
	seconds %= 60;

	std::string zero1,zero2;
	if(minutes < 10)
		zero1 = "0";

	if(seconds < 10)
		zero2 = "0";

	txt.setString("["+zero1+std::to_string(minutes)+":"+zero2+std::to_string(seconds)+"]");
	txt.setPosition(p+sf::Vector2f(s.x*0.5f-txt.getGlobalBounds().width*0.5f , 0));
	txt.setFillColor(sf::Color(255,255,200,200));
	target.draw(txt);

	auto points = hockey.getPoints();
	txt.setString(std::to_string(points.first)+" : "+std::to_string(points.second));

	p.y = rs.getPosition().y;
	txt.setPosition(p+sf::Vector2f(s.x*0.5f-txt.getGlobalBounds().width*0.5f , 0));
	txt.setFillColor(sf::Color(200,200,255,200));
	target.draw(txt);


}

void Program::toggleVideoBackgroundEvent(const MenuButton&) {
	if(Conf::videoBackground)
		Conf::videoBackground=false;
	else
		Conf::videoBackground=true;

	updateOptionButtonNames();
}

void Program::updatePaint() {

	for(size_t i = 0; i < defaultCollisionIterations; ++i){
		mainCameraPointer.updatePointerPos(defaultCollisionIterations);
		if(mainCameraPointer.isPressed()){
			sf::Vector2f p = mainCameraPointer.getPointerPosRelative(0);
			sf::Vector2f size = captureBackground.getSize();
			p.y *= -1;

			sf::CircleShape cs;
			cs.setRadius(captureBackground.getSize().x*0.01f);
			cs.setOrigin(cs.getRadius(), cs.getRadius());
			cs.setFillColor(sf::Color::White);
			cs.setPosition(p);

			sf::View vw;

			vw.setSize(size);
			vw.setCenter(sf::Vector2f(0, 0));
			texPaint->setView(vw);

			texPaint->draw(cs);
		}
	}
}

void Program::hockeySelectEvent(const MenuButton&) {
	Conf::menuType = MenuType::mt_game_hockey_select;
}

void Program::hockeySelectMultiEvent(const MenuButton&) {
	Conf::menuType = MenuType::mt_game_hockey_select_multi;
}

void Program::launchHockeySideBySideEvent(const MenuButton& b) {
	std::cerr<<"Button name: "<<b.getName()<<"; Game start"<<std::endl;
	state = HOCKEY;
	Conf::menuType = mt_game_hockey_multiplayer_sidebyside;
	hockey.resetOpponentControllers();
	hockey.setStartState();
}

void Program::togglePointerCircleEvent(const MenuButton&) {
	if(Conf::pointerClickCircle)
		Conf::pointerClickCircle=false;
	else
		Conf::pointerClickCircle=true;

	updateOptionButtonNames();
}

void Program::togglePointerInGameEvent(const MenuButton&) {
	if(Conf::pointerInGame)
		Conf::pointerInGame=false;
	else
		Conf::pointerInGame=true;

	updateOptionButtonNames();
}

void Program::showAiGameEvent(const MenuButton&) {
	Conf::menuType = mt_game_hockey_ai_test;
	state = HOCKEY;
	hockey.setStartState();

	float halfArea=Conf::areaWidth*0.5;
	hockey.setOpponentLeftController(std::make_shared<AIController>(halfArea));
	hockey.setOpponentRightController(std::make_shared<AIController>(-halfArea));
}
	
void Program::resetGameEvent(const MenuButton &b){
	if (lastGame == mt_game_hockey_multiplayer_lan) {
		hockey.setStartState(true, false);
		sf::Packet p;
		if (!Conf::isServer) {
			p << 10;
			c.Send(p);
		}
		else {
			SendStartButtonClickEvent(b);
		}
	}
	else hockey.setStartState(true, false);
	Conf::menuType = lastGame;
}

void Program::hockeyLobbyMenuEvent(const MenuButton &)
{
	
}

void Program::SendStartButtonClickEvent(const MenuButton&)
{
	int i = 0;
	sf::Packet p;
	p << i;
	if (s.Send(p)) {
		Conf::menuType = mt_game_hockey_multiplayer_lan;
		lastGame = Conf::menuType;
		state = HOCKEY;
		hockey.setOpponentRightController(std::make_shared<LanControllerServer>(s));
		auto *bb = menuHockeyWin.get(S::button::hockey_play_again);
		if (bb != nullptr) {
			bb->setVisible(false);
		}
	}
}

void Program::updateOptionButtonNames() {
#define ONOFF(A,B) if(A) menuOptionsSecond.get(B)->setName(std::string(B)+S::text::on); else menuOptionsSecond.get(B)->setName(std::string(B)+S::text::off);

	ONOFF(Conf::videoBackground, S::button::video_background);
	ONOFF(Conf::pointerInGame, S::button::pointer_in_game);
	ONOFF(Conf::pointerClickCircle, S::button::pointer_click_circle);

#undef ONOFF

}
