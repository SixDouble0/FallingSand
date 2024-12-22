#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <ctime>

class Sand {
public:

	void SandColoring(int x, int y) {
		int gridX = x / cellSize;
		int gridY = y / cellSize;
		if (grid[gridX][gridY] == 0) {
			grid[gridX][gridY] = 1;
			sf::RectangleShape sand(sf::Vector2f(cellSize, cellSize));
			sand.setFillColor(sf::Color::Yellow);
			sand.setPosition(gridX * cellSize, gridY * cellSize);
			sands.push_back(sand);
		}
	}
	void SandFalling() {
		if (fallClock.getElapsedTime().asMilliseconds() > 10) { // Opoznienie 40 ms
			for (size_t i = 0; i < sands.size(); ++i) {
				sf::Vector2f position = sands[i].getPosition();
				std::srand(std::time(0)); //losowanie czy pojdzie na lewo 
				int gridX = position.x / cellSize;
				int gridY = position.y / cellSize;
				if (gridY + 1 < 160 && grid[gridX][gridY + 1] == 0) {
					grid[gridX][gridY] = 0; // Ustawienie poprzedniej pozycji jako przezroczystej
					grid[gridX][gridY + 1] = 1; // Ustawienie nowej pozycji jako zajêtej
					sands[i].setPosition(gridX * cellSize, (gridY + 1) * cellSize);


				}
				else {

					int random = std::rand() % 2;//randomowe wybieranie gdzie spadnie

					//spadanie na lewo
					if (gridY + 1 < 160 && gridX - 1 > 0 && grid[gridX][gridY + 1] == 1 && grid[gridX - 1][gridY + 1] == 0 && random == 1) {
						grid[gridX][gridY] = 0;
						grid[gridX - 1][gridY + 1] = 1;
						sands[i].setPosition((gridX - 1) * cellSize, (gridY + 1) * cellSize);

					}//spadanie na prawo
					if (gridY + 1 < 160 && gridX + 1 < 160 && grid[gridX][gridY + 1] == 1 && grid[gridX + 1][gridY + 1] == 0 && random == 0) {
						grid[gridX][gridY] = 0;
						grid[gridX + 1][gridY + 1] = 1;
						sands[i].setPosition((gridX + 1) * cellSize, (gridY + 1) * cellSize);

					}
				}
			}
			fallClock.restart(); // Zresetuj zegar
		}
	}
protected:
	std::vector<sf::RectangleShape> sands; // wektor przechowuj¹cy ziarna piasku
	sf::Clock fallClock; // zegar
	const int cellSize = 5; //rozmiar pixela
	int grid[160][160] = { 0 }; //siatka
};

