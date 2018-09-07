#include <iostream>
#include <fstream>
#include <vector>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>
#define FMT_HEADER_ONLY
#include <fmt/format.h>

#include <jdm/path.h>
#include "map.h"

using json = nlohmann::json;

int main(int argc, char **argv)
{
	std::cout << "\n=======================================\n";
	auto console = spdlog::stdout_logger_mt("console");
	console->info("7 Days of Doom");

	const jdm::path prefix("../run");
	const jdm::path config = prefix / "config.json";

	console->info("Config file is `{}`", config);

	std::ifstream infile(config);
	if (!infile) {
		console->error("Failed to open config file!");
		return 1;
	}

	json j;
	infile >> j;
	int s_width = j["screen"]["width"];
	int s_height = j["screen"]["height"];

	sf::Font font;
	if (!font.loadFromFile(prefix / "fonts/Roboto/Roboto-Regular.ttf")) {
		console->error("Failed to open font file!");
		return 1;
	}

	sf::RenderWindow window(sf::VideoMode(s_width, s_height),
				"7 Days of Doom");

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

	// Load map -- simple raw data
	//
	Map map;
	if (!Map::from_json(&map, prefix / "avalon/better_map.json"))
		return 1;

	// Create graphics representation
	//
	std::vector<sf::VertexArray> varrs;
	Map::build_verts(&map, &varrs);
	console->info("Built {} varrs", varrs.size());
	sf::VertexArray bboxes;
	Map::build_bboxes(&map, &bboxes);

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

		/*
		 * Set world view
		 */
		window.setView(view);

		/*
		 * Draw tilemap
		 */
		for (const auto &varr : varrs) {
			window.draw(varr, &map.tile_set);
		}
		/*
		 * Draw bboxes
		 */
		window.draw(bboxes);

		/*
		 * Draw gui
		 */
		window.setView(defView);
		window.draw(text);

		/*
		 * Flip buffers
		 */
		window.display();
		sf::sleep(sf::milliseconds(5));
	}

	return 0;
}
