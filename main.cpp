#include "SudokuGame.h"

//I THINK THIS FUNCTION COULD  BE A MEMBER OF THE SUDOKUGAME CLASS. bUT I PREFER IT THIS WAY
void playSudoku(sf::RenderWindow& window) {
	// you absolutly need to load a font
	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) {
		std::cout << "Error while loading font, please check font path" << std::endl;
		assert(true == false);
	}
	SudokuGame sudoku("Map6x6v1.txt", font);
	sudoku.play(window);
	
}


int main() {
	sf::RenderWindow window;
	window.create(sf::VideoMode(1000, 480), "Sudoku");
	playSudoku(window);
	return 0;
}
