#include <iostream>
#include <fstream>
#include <vector>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>
#define FMT_HEADER_ONLY
#include <fmt/format.h>

using json = nlohmann::json;

int main(int argc, char** argv)
{
	std::cout << "\n=======================================\n";
	auto console = spdlog::stdout_logger_mt("console");
	console->info("7 Days of Doom");

	const std::string prefix = "../run/";

	std::ifstream infile(prefix + "config.json");
	if (!infile) {
		console->error("Failed to open config file!");
		return 1;
	}

	json j;
	infile >> j;
	int s_width =  j["screen"]["width"];
	int s_height =  j["screen"]["height"];

	sf::Font font;
	if (!font.loadFromFile(prefix + "fonts/Roboto/Roboto-Regular.ttf")) {
		console->error("Failed to open font file!");
		return 1;
	}

	sf::RenderWindow window(sf::VideoMode(s_width, s_height), "7 Days of Doom");

		sf::Texture texture;
	if (!texture.loadFromFile(prefix + "tiles/grid_w.png")) {
		console->error("Failed to open texture file!");
		return 1;
	}
	
	texture.setSmooth(false);
	texture.setRepeated(true);

	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setTextureRect({0, 0, s_width, s_height});
	sprite.setColor(sf::Color(255, 255, 255, 64));


	sf::RectangleShape button(sf::Vector2f(192, 48));
	button.setFillColor(sf::Color(125, 125, 125));


	sf::View view;
	view.setSize(sf::Vector2f(1280, 720));
	view.setCenter(sf::Vector2f(640, 360));
	view.rotate(25);
	window.setView(view);

	sf::Text text;
	text.setFont(font);

	text.setString(fmt::format("({}, {})", 110, 78));
	text.setCharacterSize(16);
	text.setFillColor(sf::Color::White);
	text.setPosition(16.f, 688.f);


	sf::View defView = window.getDefaultView();

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		// draw world
		window.setView(view);
		window.draw(sprite);

		// draw gui
		window.setView(defView);
		window.draw(button);
		window.draw(text);

		window.display();
	}

	return 0;
}
