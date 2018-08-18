#include <iostream>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>

using json = nlohmann::json;
using std::cout;
using std::cerr;
using std::endl;

int main(int argc, char** argv)
{
	const std::string prefix = "../run/";

	std::ifstream infile(prefix + "config.json");
	if (!infile) {
		cerr << "Failed to open config file!" << endl;
		return 1;
	}

	json j;
	infile >> j;
	int s_width =  j["screen"]["width"];
	int s_height =  j["screen"]["height"];

	sf::Font font;
	if (!font.loadFromFile(prefix + "fonts/Roboto/Roboto-Regular.ttf")) {
		cerr << "Failed to open font file!" << endl;
		return 1;
	}

	sf::RenderWindow window(sf::VideoMode(s_width, s_height), "7 Days of Doom");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	sf::Text text;
	text.setFont(font);
	text.setString("7 Days of Doom");
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	text.setPosition(200.f, 200.f);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.draw(text);
		window.display();
	}

	return 0;
}
