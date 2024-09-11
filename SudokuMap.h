#pragma once
#include "Cell.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include<cassert>

class SudokuMap {

private:
	std::string Map_path;
	std::vector<std::vector<Cell>> Cells;
	sf::Font font;
public:

	void ReadMap() {
		std::ifstream fichier(Map_path);  // Ouvrir le fichier
		if (!fichier.is_open()) {
			std::cout << "Error: Can't open this file." << std::endl;
			assert(fichier.is_open());
			return;
		}

		std::string line;
		while (std::getline(fichier, line)) {  // Lire chaque ligne du fichier
			if (line.size() == 0) { continue; }
			std::vector<Cell> Cells_inter;
			bool mapOK = true;
			if (line.size() == 0 || line.size() > 20) {  // Correction pour une taille de ligne correcte
				std::cout << "This Map:" << Map_path << " cannot be loaded: Error in the map config. Please check the map config" << std::endl;
				mapOK = false;
			}
			for (int i = 0; i < line.size(); i++) {
				std::string current_char(1, line.at(i));

				// Si c'est un "e", ajouter une cellule "vide"
				if (current_char == " ") {
					continue;
				}
				if (current_char == "e") {
					Cells_inter.push_back(Cell(font));  // Cellule vide
				}
				else {
					Cells_inter.push_back(Cell(font,current_char));  // Cellule avec un chiffre
				}
			}
			Cells.push_back(Cells_inter);
		}
		fichier.close();
	}

		std::vector<std::vector<Cell>>& getCells() {
			return Cells;		
		}

		void LoadMap(sf::RenderWindow& window) {
			// Trouver le nombre maximal de cellules dans une ligne
			size_t maxColumns = 0;
			for (const auto& row : Cells) {
				maxColumns = std::max(maxColumns, row.size());
			}

			// Calculer la taille des cellules en fonction du nombre maximal de colonnes et de lignes
			float cellWidth = window.getSize().x / static_cast<float>(maxColumns);
			float cellHeight = window.getSize().y / static_cast<float>(Cells.size());
			float cellSize = std::min(cellWidth, cellHeight);  // Pour garantir des cellules carrées

			// Calculer la position de départ pour centrer la grille dans la fenêtre
			float firstX = (window.getSize().x - cellSize * maxColumns) / 2.0f;
			float firstY = (window.getSize().y - cellSize * Cells.size()) / 2.0f;

			// Positionner chaque cellule à sa place avec une taille uniforme
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


	// Dessiner la carte
	void draw(sf::RenderWindow& window) {
		for (int i = 0; i < Cells.size(); i++) {
			for (int j = 0; j < Cells[i].size(); j++) {  // Correction ici
				Cells[i][j].draw(window);
			}
		}
	}

	SudokuMap(std::string pwd,sf::Font& ft) :Cells(std::vector<std::vector<Cell>>()), Map_path(pwd),font(ft) {
		ReadMap();
	}
};
