﻿#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Materials.h"

class Canvas : public Materials
{
public:
	Canvas() : window(sf::VideoMode(800, 800), "Falling Sand", sf::Style::Close), materialChoice(0) { //konstruktor okna
	}

	int roundToNearest5(int num) {
		return std::round(num / 5.0) * 5;
	}

	void run() {
		while (window.isOpen()) {
			sf::Event evnt; //evnt bo event to keyword
			while (window.pollEvent(evnt)) {
				switch (evnt.type) {
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					if (evnt.key.code == sf::Keyboard::Num1) {
						materialChoice = 1;
					}
					if (evnt.key.code == sf::Keyboard::Num2){
						materialChoice = 2;
					}
					break;
				}
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && materialChoice == 1) {
				if (fallClock.getElapsedTime().asMilliseconds() > 5) {
					sf::Vector2i mousePos = sf::Mouse::getPosition(window); //pobieranie do vectora pozycji myszki
					std::cout << "Mouse x: " << roundToNearest5(mousePos.x) << " Mouse y: " << roundToNearest5(mousePos.y) << std::endl;
					if (roundToNearest5(mousePos.x) < 800 && roundToNearest5(mousePos.y) < 800) {
						SandColoring(roundToNearest5(mousePos.x), roundToNearest5(mousePos.y)); //zaokraglanie dla klarownosci by nie bylo pikseli na pol
					}
				}
				
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && materialChoice == 2) {
				if (fallClock.getElapsedTime().asMilliseconds() > 5) {
					sf::Vector2i mousePos = sf::Mouse::getPosition(window); //pobieranie do vectora pozycji myszki
					std::cout << "Mouse x: " << roundToNearest5(mousePos.x) << " Mouse y: " << roundToNearest5(mousePos.y) << std::endl;
					if (roundToNearest5(mousePos.x) < 800 && roundToNearest5(mousePos.y) < 800) {
						WaterColoring(roundToNearest5(mousePos.x), roundToNearest5(mousePos.y)); //zaokraglanie dla klarownosci by nie bylo pikseli na pol
					}
				}
				
			}
			MaterialFizyka();
			draw();
		}
	}

private:
	sf::RenderWindow window; //okno
	int materialChoice; // Przelacznik materiau

	void draw() {
		window.clear(sf::Color::Transparent); // Ustawienie tla jako przezroczyste
		for (const auto& sand : sands) {
			window.draw(sand);
		}
		for (const auto& water : waters) {
			window.draw(water);
		}
		window.display();
	}
};
