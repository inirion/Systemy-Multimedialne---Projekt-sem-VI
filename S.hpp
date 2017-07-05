/*
 * S.hpp
 *
 *  Created on: 09.03.2017
 *      Author: jakub
 */
/**
 * \file
 * \brief
 * Definicja przestrzeni nazw S która zawiera stałe liteały tekstowe
 *
 * Literały są podzielone na pod przestrzenie: path, text, option, button.
 */
#ifndef S_HPP_
#define S_HPP_

namespace S{
	const char* const version = "0.3alpha";

	namespace path{
		const char* const font_mono = "assets/DroidSansMono.ttf";
		const char* const config_file = "program.conf";
	}
	namespace text{
		const char* const camera_not_found = "Camera not found.\nPlease plug it in.";
		const char* const options_window_name = "Options";
		const char* const on = "ON";
		const char* const off = "OFF";
		const char* const to_defaults_ask = "Do you want restore options to defaults?";
		const char* const player_one = "Player 1";
		const char* const player_two = "Player 2";
	}

	namespace option{
		const char* const exposure = "Exposure";
		const char* const gamma = "Gamma";
		const char* const white_balance = "White balance";
		const char* const detector_h_l = "Detector H low";
		const char* const detector_h_h = "Detector H high";
		const char* const detector_s_l = "Detector S low";
		const char* const detector_s_h = "Detector S high";
		const char* const detector_v_l = "Detector V low";
		const char* const detector_v_h = "Detector V high";
		const char* const move_th = "Move threshold";
		const char* const circle_th_1 = "Circle mask threshold 1";
		const char* const circle_th_2 = "Circle mask threshold 2";
		const char* const hue_shift = "Hue shift";
		const char* const min_size = "Minimum size";
		const char* const points_limit = "Points limit";
	}

	namespace button{
		const char* const pong = "Air Hockey game";
		const char* const paint = "Paint test";
		const char* const options = "Options";
		const char* const back = "Back";
		const char* const options_first = "Page 1";
		const char* const options_second = "Page 2";
		const char* const defaults = "Defaults";
		const char* const yes = "Yes";
		const char* const no = "No";
		const char* const clear = "Clear";
		const char* const singleplayer = "Singleplayer";
		const char* const multiplayer = "Multiplayer";
		const char* const sidebyside = "Side by side";
		const char* const create_lan_server = "Create LAN server";
		const char* const connect_lan_server = "Connect LAN server";
		const char* const connect = "Connect";
		const char* const create = "Create";
		const char* const video_background = "Video background ";
		const char* const pointer_in_game = "Pointer in game ";
		const char* const pointer_click_circle = "Pointer click circle ";
		const char* const show_ai_game = "Show AI game";
		const char* const hockey_win_info = "Win info button";
		const char* const hockey_player_won = "Winner is player ";
		const char* const hockey_return_menu = "Return to menu";
		const char* const hockey_play_again = "Play Again";
		const char* const lobby_refresh = "Refresh";
		const char* const connection_buttons = "conn_btns";
		const char* const play_btn = "Play";
	}
}
#endif /* S_HPP_ */
