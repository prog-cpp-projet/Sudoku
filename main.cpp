#include "SudokuGame.h"

void playSudoku(sf::RenderWindow& window) {
	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) {
		std::cout << "Error while loading font, please check font path" << std::endl;
		assert(true == false);
	}
	SudokuGame sudoku("Map4x4v1.txt", font);
	sudoku.play(window);
	
}
int main() {
	sf::RenderWindow window;
	window.create(sf::VideoMode(1000, 480), "Sudoku");
	//SudokuGame sudoku("Map1.txt",font);
	//sudoku.play(window);
	playSudoku(window);
	return 0;
}
