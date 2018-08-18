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
	std::ifstream infile("../run/config.json");
	if (!infile) {
		cerr << "Failed to open config file!" << endl;
		return 1;
	}

	json j;
	infile >> j;
	int s_width =  j["screen"]["width"];
	int s_height =  j["screen"]["height"];

	sf::RenderWindow window(sf::VideoMode(s_width, s_height), "7 Days of Doom");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}
