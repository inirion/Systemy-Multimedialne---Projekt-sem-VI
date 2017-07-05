/*
 * ConfigurationManager.cpp
 *
 *  Created on: 28.04.2017
 *      Author: jakub
 */

#include "ConfigurationManager.hpp"

bool ConfigurationManager::load(ConfigurationObjects& co) {
	std::fstream file;
	std::string line;
	std::map<std::string, std::string> m;
	std::stringstream ss;
	std::string name, value;
	size_t count = 0;
	file.open(S::path::config_file);
	if (file.is_open()) {
		while (file.good()) {
			count++;
			try {
				getline(file, line);
				ss.clear();
				ss.str(line);
				ss >> name;
				ss >> value;
				m[name] = value;
			} catch (std::exception &e) {
				std::cerr << "Error parse config line " << count << ": "
						<< e.what() << std::endl;
			}
		}
		auto iter = m.end();
#define VH(PREFIX, VAR, FUN)\
		if((iter=m.find(#VAR))!=m.end()){\
		try{PREFIX VAR=FUN(iter->second);}\
		catch(std::exception &e){std::cerr<<"Error parse value "<<iter->second<<" in "<<iter->first<<": "<<e.what()<<std::endl;}\
		}
#define SH(PREFIX, VAR) if((iter=m.find(#VAR))!=m.end()) PREFIX VAR=iter->second;

		int winSizeX=co.rw.getSize().x;
		int winSizeY=co.rw.getSize().y;
		int winPosX=co.rw.getPosition().x;
		int winPosY=co.rw.getPosition().y;

		std::string leftNick=base64_encode((const unsigned char*)S::text::player_one, sizeof(S::text::player_one));
		std::string rightNick=base64_encode((const unsigned char*)S::text::player_two, sizeof(S::text::player_two));
		std::string serverName=base64_encode((const unsigned char*)S::text::player_one, sizeof(S::button::multiplayer));

#include "config.inc"

		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		std::wstring ws;
		try{
			leftNick = base64_decode(leftNick);
			ws=converter.from_bytes(leftNick);
			co.leftNick.setValue(ws);
			co.leftNick.moveCursor(leftNick.size());
		}catch(std::exception& e){
			std::cerr<<"Invalid utf chars in left nick"<<std::endl;
		}

		try{
			rightNick = base64_decode(rightNick);
			ws=converter.from_bytes(rightNick);
			co.rightNick.setValue(ws);
			co.rightNick.moveCursor(rightNick.size());
		}catch(std::exception& e){
			std::cerr<<"Invalid utf chars in right nick"<<std::endl;
		}

		try{
			serverName = base64_decode(serverName);
			ws=converter.from_bytes(serverName);
			co.serverName.setValue(ws);
			co.serverName.moveCursor(serverName.size());
		}catch(std::exception& e){
			std::cerr<<"Invalid utf chars in server name"<<std::endl;
		}


		if(winSizeX > 0 && winSizeY > 0)
			co.rw.setSize(sf::Vector2u(winSizeX, winSizeY));

		co.rw.setPosition(sf::Vector2i(winPosX, winPosY));

#undef VH
#undef SH


		return true;
	} else {
		std::cerr << "Can not read config file " << S::path::config_file << std::endl;
	}
	return false;
}

bool ConfigurationManager::save(ConfigurationObjects& co) {
	std::fstream file;
	file.open(S::path::config_file, std::ios::out);
	if (file.is_open()) {

#define VH(PREFIX,VAR,FUN) file<<#VAR<<" "<<std::to_string(PREFIX VAR)<<std::endl;
#define SH(PREFIX,VAR) file<<#VAR<<" "<<(PREFIX VAR)<<std::endl;


		std::wstring ws;

		int winSizeX=co.rw.getSize().x;
		int winSizeY=co.rw.getSize().y;
		int winPosX=co.rw.getPosition().x;
		int winPosY=co.rw.getPosition().y;

		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

		std::string s;

		std::string leftNick,rightNick,serverName;

		try{
			ws=co.leftNick.getValue();
			s=converter.to_bytes(ws);
			leftNick=base64_encode((const unsigned char*)s.data(), s.size());
		}catch(std::exception& e){
			std::cerr<<"Invalid utf chars in left nick"<<std::endl;
		}

		try{
			ws=co.rightNick.getValue();
			s=converter.to_bytes(ws);
			rightNick=base64_encode((const unsigned char*)s.data(), s.size());
		}catch(std::exception& e){
			std::cerr<<"Invalid utf chars in left nick"<<std::endl;
		}

		try{
			ws=co.serverName.getValue();
			s=converter.to_bytes(ws);
			serverName=base64_encode((const unsigned char*)s.data(), s.size());
		}catch(std::exception& e){
			std::cerr<<"Invalid utf chars in server name"<<std::endl;
		}


#include "config.inc"

#undef VH
#undef SH

		return true;
	} else {
		std::cerr << "Can not open config file for writing " << S::path::config_file << std::endl;
	}
	return false;
}
