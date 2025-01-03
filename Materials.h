#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

class Materials {
public:
	// Tworzenie piasku
	void SandColoring(int x, int y) {
		int gridX = x / cellSize;
		int gridY = y / cellSize;
		if (grid[gridX][gridY] == 0 || grid[gridX][gridY] == 2) {
			grid[gridX][gridY] = 1;
			sf::RectangleShape sand(sf::Vector2f(static_cast<float>(cellSize), static_cast<float>(cellSize)));
			sand.setFillColor(sf::Color::Yellow);
			sand.setPosition(static_cast<float>(gridX * cellSize), static_cast<float>(gridY * cellSize));
			sands.push_back(sand);
		}
	}

	// Tworzenie wody
	void WaterColoring(int x, int y) {
		int gridX = x / cellSize;
		int gridY = y / cellSize;
		if (grid[gridX][gridY] == 0) {
			grid[gridX][gridY] = 2;
			sf::RectangleShape water(sf::Vector2f(static_cast<float>(cellSize), static_cast<float>(cellSize)));
			water.setFillColor(sf::Color::Blue);
			water.setPosition(static_cast<float>(gridX * cellSize), static_cast<float>(gridY * cellSize));
			waters.push_back(water);
		}
	}

	// Sprawdzanie, czy punkt jest w ramce
	bool inFrame(int x, int y) {
		return (x >= 0 && x < 160 && y >= 0 && y < 160);
	}

	


		void SandFizyka() {
			// Aktualizacja pozycji piasku
			for (size_t i = 0; i < sands.size(); ++i) {
				sf::Vector2f position = sands[i].getPosition();
				int gridX = static_cast<int>(position.x) / cellSize;
				int gridY = static_cast<int>(position.y) / cellSize;

				if (inFrame(gridX, gridY + 1)) {
					switch (grid[gridX][gridY + 1]) {
					case 0: // Nothing Under
						grid[gridX][gridY] = 0;
						grid[gridX][gridY + 1] = 1;
						sands[i].setPosition(static_cast<float>(gridX * cellSize), static_cast<float>((gridY + 1) * cellSize));
						break;
					case 1: // Sand Under
						if (inFrame(gridX + 1, gridY + 1) && grid[gridX + 1][gridY + 1] == 0) { // Left Under Open
							grid[gridX][gridY] = 0;
							grid[gridX + 1][gridY + 1] = 1;
							sands[i].setPosition(static_cast<float>((gridX + 1) * cellSize), static_cast<float>((gridY + 1) * cellSize));
						}
						else if (inFrame(gridX - 1, gridY + 1) && grid[gridX - 1][gridY + 1] == 0) { // Right Under Open
							grid[gridX][gridY] = 0;
							grid[gridX - 1][gridY + 1] = 1;
							sands[i].setPosition(static_cast<float>((gridX - 1) * cellSize), static_cast<float>((gridY + 1) * cellSize));
						}
						break;
					case 2: // Water Under
						if (inFrame(gridX + 1, gridY + 1) && grid[gridX + 1][gridY + 1] == 0) { // Left Under Open
							grid[gridX][gridY] = 0;
							grid[gridX + 1][gridY + 1] = 1;
							sands[i].setPosition(static_cast<float>((gridX + 1) * cellSize), static_cast<float>((gridY + 1) * cellSize));
						}
						else if (inFrame(gridX - 1, gridY + 1) && grid[gridX - 1][gridY + 1] == 0) { // Right Under Open
							grid[gridX][gridY] = 0;
							grid[gridX - 1][gridY + 1] = 1;
							sands[i].setPosition(static_cast<float>((gridX - 1) * cellSize), static_cast<float>((gridY + 1) * cellSize));
						}
						else if (inFrame(gridX + 1, gridY + 1) && grid[gridX + 1][gridY + 1] == 2 && grid[gridX][gridY + 1] == 1) { // Left Under Open
							grid[gridX][gridY] = 2;
							grid[gridX + 1][gridY + 1] = 1;
							sands[i].setPosition(static_cast<float>((gridX + 1) * cellSize), static_cast<float>((gridY + 1) * cellSize));
						}
						else if (inFrame(gridX - 1, gridY + 1) && grid[gridX - 1][gridY + 1] == 2 && grid[gridX][gridY + 1] == 1) { // Right Under Open
							grid[gridX][gridY] = 2;
							grid[gridX - 1][gridY + 1] = 1;
							sands[i].setPosition(static_cast<float>((gridX - 1) * cellSize), static_cast<float>((gridY + 1) * cellSize));
						}
						else { // jak ma zachowac sie woda gdy piasek zajmie jej miejsce
							for (auto& water : waters) {
								if (water.getPosition() == sf::Vector2f(static_cast<float>(gridX * cellSize), static_cast<float>((gridY + 1) * cellSize))) {
									water.setPosition(static_cast<float>(gridX * cellSize), static_cast<float>(gridY * cellSize));
									grid[gridX][gridY] = 2;
									break;
								}
							}
							grid[gridX][gridY + 1] = 1;
							sands[i].setPosition(static_cast<float>(gridX * cellSize), static_cast<float>((gridY + 1) * cellSize));
						}
						break;
					}

				}
			}
		}
		void WaterFizyka() {
			// Aktualizacja pozycji wody
			for (size_t i = 0; i < waters.size(); ++i) {
				sf::Vector2f position = waters[i].getPosition();
				int gridX = static_cast<int>(position.x) / cellSize;
				int gridY = static_cast<int>(position.y) / cellSize;

				if (inFrame(gridX, gridY + 1) && grid[gridX][gridY + 1] == 0) { // Nothing Under
					grid[gridX][gridY] = 0;
					grid[gridX][gridY + 1] = 2;
					waters[i].setPosition(static_cast<float>(gridX * cellSize), static_cast<float>((gridY + 1) * cellSize));
				}
				else {
					int random = std::rand() % 2;
					if (inFrame(gridX - 1, gridY) && grid[gridX - 1][gridY] == 0 && random == 0) { // Left Open
						grid[gridX][gridY] = 0;
						grid[gridX - 1][gridY] = 2;
						waters[i].setPosition(static_cast<float>((gridX - 1) * cellSize), static_cast<float>(gridY * cellSize));
					}
					else if (inFrame(gridX + 1, gridY) && grid[gridX + 1][gridY] == 0 && random == 1) { // Right Open
						grid[gridX][gridY] = 0;
						grid[gridX + 1][gridY] = 2;
						waters[i].setPosition(static_cast<float>((gridX + 1) * cellSize), static_cast<float>(gridY * cellSize));
					}
					else if (inFrame(gridX - 1, gridY + 1) && grid[gridX - 1][gridY + 1] == 0) { // Left Under Open
						grid[gridX][gridY] = 0;
						grid[gridX - 1][gridY + 1] = 2;
						waters[i].setPosition(static_cast<float>((gridX - 1) * cellSize), static_cast<float>((gridY + 1) * cellSize));
					}
					else if (inFrame(gridX + 1, gridY + 1) && grid[gridX + 1][gridY + 1] == 0) { // Right Under Open
						grid[gridX][gridY] = 0;
						grid[gridX + 1][gridY + 1] = 2;
						waters[i].setPosition(static_cast<float>((gridX + 1) * cellSize), static_cast<float>((gridY + 1) * cellSize));
					}
				}
			}
		}

		void MaterialFizyka() {
			if (fallClock.getElapsedTime().asMilliseconds() > 10) {
				SandFizyka();
				WaterFizyka();
				fallClock.restart();
			}
		}


protected:
	std::vector<sf::RectangleShape> sands; // wektor przechowuj¹cy ziarna piasku
	std::vector<sf::RectangleShape> waters; // wektor przechowuj¹cy krople wody
	sf::Clock fallClock; // zegar
	const int cellSize = 5; // rozmiar pixela
	int grid[160][160] = { 0 }; // siatka
};










