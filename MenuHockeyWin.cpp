#include "MenuHockeyWin.hpp"
#include "Program.hpp"

MenuHockeyWin::MenuHockeyWin(Program * p):
	ButtonView(p->getUniPointer())
{
	MenuButton b;
	std::function<void(const MenuButton&)> f;

	b.setFontSize(smallFont);
	b.setName(S::button::hockey_win_info);
	b.setEnabled(false);
	b.setSize(sf::Vector2f(1200.f, 300.f));
	add(b);

	f = std::bind(&Program::returnToMenuEvent, p, std::placeholders::_1);
	b.setAction(f);
	b.setSize(sf::Vector2f(575.f, 300.f));
	b.setEnabled(true);
	b.setName(S::button::hockey_return_menu);
	add(b);

	b.setName(S::button::hockey_play_again);
	f = std::bind(&Program::resetGameEvent, p, std::placeholders::_1);
	b.setAction(f);
	add(b);
}

void MenuHockeyWin::update()
{
	MenuButton *b;
	b = get(S::button::hockey_win_info);
	const float gap = 200.f * Conf::gs;
	sf::Vector2f shift(0, gap);

	if (b != nullptr) {
		b->setPosition(Conf::refPos + shift + sf::Vector2f(Conf::ws.x*0.5 - b->getSizeReal().x*0.5, 0));
		shift.y += gap + b->getSizeReal().y;
	}
	b = get(S::button::hockey_return_menu);
	if (b != nullptr) {
		b->setPosition(Conf::refPos + shift + sf::Vector2f(Conf::ws.x*0.5 - b->getSizeReal().x, 0));
		shift.x += 600.f * Conf::gs;
	}
	b = get(S::button::hockey_play_again);
	if (b != nullptr) {
		b->setPosition(Conf::refPos + shift + sf::Vector2f(Conf::ws.x*0.5 - b->getSizeReal().x, 0));
	}
	updateButtons();
}
