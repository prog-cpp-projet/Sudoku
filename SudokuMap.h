#pragma once
#include "Cell.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include<cassert>

//THIS CLASS CREATES AND POSITIONS CELLS
//THAT IS WHY I CALLED IT THE MAP
class SudokuMap {

private:
	std::string Map_path;               //the path of your .txt file on your computer
	std::vector<std::vector<Cell>> Cells;
	sf::Font font;
public:

	void ReadMap() {
		std::ifstream fichier(Map_path);  // Open the file
		if (!fichier.is_open()) {
			std::cout << "Error: Can't open this file." << std::endl;
			assert(fichier.is_open());
			return;
		}

		std::string line;
		while (std::getline(fichier, line)) {  // Read each line of the file
			if (line.size() == 0) { continue; }
			std::vector<Cell> Cells_inter;
			bool mapOK = true;
			if (line.size() == 0 || line.size() > 20) {  // To make sure the line size is correct
				std::cout << "This Map:" << Map_path << " cannot be loaded: Error in the map config. Please check the map config" << std::endl;
				mapOK = false;
			}
			for (int i = 0; i < line.size(); i++) {
				std::string current_char(1, line.at(i));

				// if it is "e", add an empty cell
				if (current_char == " ") {
					continue;
				}
				if (current_char == "e") {
					Cells_inter.push_back(Cell(font));  // Adding empty cell
				}
				else {
					Cells_inter.push_back(Cell(font,current_char));  // Cell with a number
				}
			}
			Cells.push_back(Cells_inter);
		}
		fichier.close();
	}

	// To get de tab of cells
		std::vector<std::vector<Cell>>& getCells() {
			return Cells;		
		}

		void LoadMap(sf::RenderWindow& window) {

			// Find the max number of cells in each line
			size_t maxColumns = 0;
			for (const auto& row : Cells) {
				maxColumns = std::max(maxColumns, row.size());
			}

			// Compute the cells size according to the maw number of rows and lines
			float cellWidth = window.getSize().x / static_cast<float>(maxColumns);
			float cellHeight = window.getSize().y / static_cast<float>(Cells.size());
			float cellSize = std::min(cellWidth, cellHeight);  // To create Square cell

			// Compute the position of the first cell to center the grid in the window
			float firstX = (window.getSize().x - cellSize * maxColumns) / 2.0f;
			float firstY = (window.getSize().y - cellSize * Cells.size()) / 2.0f;

			// Positionning each cell
			for (size_t i = 0; i < Cells.size(); ++i) {
				for (size_t j = 0; j < Cells[i].size(); ++j) {
					Cells[i][j].setPosition(firstX + j * cellSize, firstY + i * cellSize);
					Cells[i][j].setSize(cellSize);
					if (Cells[i][j].getNumber() != "") {
						Cells[i][j].setType(false);
					}
				}
			}
		}


	// Draw the map
	void draw(sf::RenderWindow& window) {
		for (int i = 0; i < Cells.size(); i++) {
			for (int j = 0; j < Cells[i].size(); j++) {
				Cells[i][j].draw(window);
			}
		}
	}

	SudokuMap(std::string pwd,sf::Font& ft) :Cells(std::vector<std::vector<Cell>>()), Map_path(pwd),font(ft) {
		ReadMap();
	}
};
