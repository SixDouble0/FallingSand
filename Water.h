//#include <SFML/Window.hpp>
//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <vector>
//#include <stdio.h>
//#include <cstdlib>
//#include <ctime>
//#include "Sand.h"
//
//class Water : public Sand{
//public:
//
//	void WaterColoring(int x, int y) {
//		int gridX = x / cellSize;
//		int gridY = y / cellSize;
//		if (grid[gridX][gridY] == 0) {
//			grid[gridX][gridY] = 2;
//			sf::RectangleShape water(sf::Vector2f(cellSize, cellSize));
//			water.setFillColor(sf::Color::Blue);
//			water.setPosition(gridX * cellSize, gridY * cellSize);
//			water.push_back(water);
//		}
//	}
//	void WaterFalling() {
//		if (fallClock.getElapsedTime().asMilliseconds() > 10) { // Opoznienie 40 ms
//			for (size_t i = 0; i < sands.size(); ++i) {
//				sf::Vector2f position = water[i].getPosition();
//				int gridX = position.x / cellSize;
//				int gridY = position.y / cellSize;
//				if (gridY + 1 < 160 && grid[gridX][gridY + 1] == 0) {
//					grid[gridX][gridY] = 0; // Ustawienie poprzedniej pozycji jako przezroczystej
//					grid[gridX][gridY + 1] = 1; // Ustawienie nowej pozycji jako zajêtej
//					sands[i].setPosition(gridX * cellSize, (gridY + 1) * cellSize);
//
//
//				}
//			fallClock.restart(); // Zresetuj zegar
//		}
//	}
//protected:
//	std::vector<sf::RectangleShape> water; // wektor przechowuj¹cy ziarna piasku
//	sf::Clock fallClock;
//};