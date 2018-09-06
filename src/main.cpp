#include <iostream>
#include <fstream>
#include <vector>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>
#define FMT_HEADER_ONLY
#include <fmt/format.h>

#include "tilemap.h"

using json = nlohmann::json;

int main(int argc, char **argv)
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
	int s_width = j["screen"]["width"];
	int s_height = j["screen"]["height"];

	sf::Font font;
	if (!font.loadFromFile(prefix + "fonts/Roboto/Roboto-Regular.ttf")) {
		console->error("Failed to open font file!");
		return 1;
	}

	sf::RenderWindow window(sf::VideoMode(s_width, s_height),
				"7 Days of Doom");

	sf::Texture texture;
	if (!texture.loadFromFile(prefix + "tiles/grass3.png")) {
		console->error("Failed to open texture file!");
		return 1;
	}

	sf::Texture tset;
	if (!tset.loadFromFile(prefix + "tileset.png")) {
		console->error("Failed to open texture file!");
		return 1;
	}

	texture.setSmooth(false);
	texture.setRepeated(true);

	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setTextureRect({ 0, 0, s_width, s_height });
	sprite.setColor(sf::Color(255, 255, 255, 255));

	sf::View view;
	view.setSize(sf::Vector2f(1280, 720));
	view.setCenter(sf::Vector2f(640, 360));
	window.setView(view);

	sf::Text text;
	text.setFont(font);

	text.setString(fmt::format("({}, {})", 110, 78));
	text.setCharacterSize(16);
	text.setFillColor(sf::Color::White);
	text.setPosition(16.f, 688.f);

	sf::View defView = window.getDefaultView();

	sf::Clock clock;
	sf::Time delta;
	float delta_m;
	const float spd = 5.f;

	// Loading tilemap
	//
	int level[8 * 12];
	for (int i = 0; i < 8 * 12; i++) {
		level[i] = i;
	}

	TileMap mapa;
	mapa.build(tset, 12, 8, sf::Vector2f(16, 16), level);

	while (window.isOpen()) {
		delta = clock.restart();
		delta_m = delta.asMilliseconds();
		text.setString(fmt::format("({:.2f}, {:.2f}) | {}ms",
					   view.getCenter().x,
					   view.getCenter().y, delta_m));

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
			view.rotate(360.f * (delta_m / 5000.f));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			view.move(spd * 16.f * (delta_m / 500.f), 0.f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			view.move(-spd * 16.f * (delta_m / 500.f), 0.f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			view.move(0.f, -spd * 16.f * (delta_m / 500.f));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			view.move(0.f, spd * 16.f * (delta_m / 500.f));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			//view.move(0.f, spd * 16.f * (delta_m / 500.f));
			view.zoom(0.25f * (delta_m / 1000.f));
		}

		window.clear();

		// draw world
		window.setView(view);
		window.draw(sprite);
		window.draw(mapa);

		// draw gui
		window.setView(defView);
		window.draw(text);

		window.display();
		sf::sleep(sf::milliseconds(5));
	}

	return 0;
}
