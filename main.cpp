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

	std::vector<char> buff;
	infile.seekg(0, infile.end);
	size_t len = infile.tellg();
	infile.seekg(0, infile.beg);

	if (len > 0) {
		buff.resize(len);
		infile.read(&buff[0], len);
	} else {
		cerr << "Failed to read config file!" << endl;
		return 1;
	}
	cout << "Read config file; parsing..." << endl;
	json j = json::parse(buff);
	int width =  j["screen"]["width"];
	int height =  j["screen"]["height"];
	cout << "Screen width: " << width << endl;
	cout << "Screen height: " << height << endl;
	cout << "Failing: " << j["hi"] << endl;


	sf::RenderWindow window(sf::VideoMode(200, 200), "7 Days of Doom");
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
