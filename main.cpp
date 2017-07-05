#include <iostream>
#include <SFML/Graphics.hpp>

#include "Program.hpp"

int main(){
	sf::RenderWindow window(sf::VideoMode(800, 600), "OpenCV Demo", sf::Style::Default);
	window.setVerticalSyncEnabled(true);
//	window.setFramerateLimit(2);
	Program p(window);
	while (window.isOpen()){
		sf::Event e;
		while (window.pollEvent(e)){
			switch(e.type){
				default: break;
				case e.Closed:{
					cv::destroyAllWindows();
					window.close();
					e.type = e.Count;
				}break;
			}
			if(e.type != e.Count){
				p.events(e);
			}
		}
		p.update();
		window.clear(sf::Color(0,0,64));
		window.draw(p);
		window.display();
	}
	return 0;
}
