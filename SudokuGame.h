#pragma once
#include "SudokuMap.h"

//HERE THE GAME LOGICAL IS MANAGED

class SudokuGame {

private:
	SudokuMap map;
	sf::Vector2<int> focus;//it shows the position of MAGENTA cell (the cell we want to modify)
    sf::Text finish;// The text displayed when the game is finish
    bool Gamefinish = false;
public:

	void InitializeSudoKu(sf::RenderWindow& window) {
		map.LoadMap(window);
	}

    //this function check if the input is valid and modify the cell
	bool check_validity(std::string carac) {
		for (int j = 0; j < map.getCells()[0].size(); j++) {
			if (map.getCells()[focus.x][j].getPosition() != map.getCells()[focus.x][focus.y].getPosition() &&
				map.getCells()[focus.x][j].getNumber() == carac) {
				return false;
			}
            if (map.getCells()[j][focus.y].getPosition() != map.getCells()[focus.x][focus.y].getPosition() &&
                map.getCells()[j][focus.y].getNumber() == carac) {
                return false;
            }
		}

		map.getCells()[focus.x][focus.y].setNumber(carac);
		return true;
	}

    //this function check if the map is completed and display the message if it is.
    void mapCompleted(sf::RenderWindow& window) {
        for (int i = 0; i < map.getCells().size(); i++) {
            for (int j = 0; j < map.getCells()[i].size(); j++) {
                if (map.getCells()[i][j].getNumber() == "") {
                    Gamefinish= false;
                    return;
                }
            }
        }
        for (int i = 0; i < map.getCells().size(); i++) {
            for (int j = 0; j < map.getCells()[i].size(); j++) {
                map.getCells()[i][j].setBGColor(sf::Color::Red);
            }
        }
        float posX =window.getSize().x - (window.getSize().x - finish.getLocalBounds().width) / 2;
        float posY = (window.getSize().y - finish.getCharacterSize()) / 2;
        finish.setPosition(sf::Vector2f(posX, posY));
        finish.setString("Map Completed!");
        finish.setCharacterSize(50);
        finish.setFillColor(sf::Color::Black);
        finish.setStyle(sf::Text::Bold);
        Gamefinish= true;
    }


    //Mouse manager
    void MouseClicked(sf::RenderWindow& window, sf::Event& event) {
        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            for (int i = 0; i < map.getCells().size(); i++) {
                for (int j = 0; j < map.getCells()[i].size(); j++) {
                    // Check if the mouse if is in a cell
                    if (map.getCells()[i][j].getRect().getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        // Check if the left button is clicked
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            map.getCells()[focus.x][focus.y].setBGColor(sf::Color::Blue);  // Update the old selected cell color
                            focus.x = i;
                            focus.y = j;
                            map.getCells()[i][j].setBGColor(sf::Color::Magenta);  // To highlight the new selected cell
                        }
                        break;
                    }
                }
            }
        }
    }


    //Keyboard manager
    void writeNumber(sf::Event& event) {
        if (event.type == sf::Event::KeyPressed) {
            sf::Keyboard::Key key = event.key.code;
            switch (key) {
            
            case sf::Keyboard::Numpad0:
            case sf::Keyboard::Num0: check_validity("0"); break;
            case sf::Keyboard::Numpad1:
            case sf::Keyboard::Num1: check_validity("1"); break;
            case sf::Keyboard::Numpad2:
            case sf::Keyboard::Num2: check_validity("2"); break;
            case sf::Keyboard::Numpad3:
            case sf::Keyboard::Num3: check_validity("3"); break;
            case sf::Keyboard::Numpad4:
            case sf::Keyboard::Num4: check_validity("4"); break;
            case sf::Keyboard::Numpad5:
            case sf::Keyboard::Num5: check_validity("5"); break;
            case sf::Keyboard::Numpad6:
            case sf::Keyboard::Num6: check_validity("6"); break;
            case sf::Keyboard::Numpad7:
            case sf::Keyboard::Num7: check_validity("7"); break;
            case sf::Keyboard::Numpad8:
            case sf::Keyboard::Num8: check_validity("8"); break;
            case sf::Keyboard::Numpad9:
            case sf::Keyboard::Num9: check_validity("9"); break;
            case sf::Keyboard::Up:
                if (focus.x > 0) {
                    if ( !map.getCells()[focus.x - 1][focus.y].getType()) {
                        return;
                    }
                    map.getCells()[focus.x - 1][focus.y].setBGColor(sf::Color::Magenta);
                    map.getCells()[focus.x][focus.y].setBGColor(sf::Color::Blue);
                    focus.x = focus.x - 1;
                    break;
                }
                else { break; }
            case sf::Keyboard::Down:
                if (focus.x < map.getCells().size()-1) {
                    if (!map.getCells()[focus.x + 1][focus.y].getType()) {
                        return;
                    }
                    map.getCells()[focus.x + 1][focus.y].setBGColor(sf::Color::Magenta);
                    map.getCells()[focus.x][focus.y].setBGColor(sf::Color::Blue);
                    focus.x = focus.x + 1;
                    break;
                }
                else { break; }
            case sf::Keyboard::Left:
                if (focus.y > 0) {
                    if (!map.getCells()[focus.x][focus.y - 1].getType()) {
                        return;
                    }
                    map.getCells()[focus.x][focus.y - 1].setBGColor(sf::Color::Magenta);
                    map.getCells()[focus.x][focus.y].setBGColor(sf::Color::Blue);
                    focus.y = focus.y - 1;
                    break;
                }
                else { break; }
            case sf::Keyboard::Right:
                if (focus.y < map.getCells()[focus.x].size()-1){
                    if (!map.getCells()[focus.x][focus.y + 1].getType()) {
                        return;
                    }
                    map.getCells()[focus.x][focus.y + 1].setBGColor(sf::Color::Magenta);
                    map.getCells()[focus.x][focus.y].setBGColor(sf::Color::Blue);
                    focus.y = focus.y + 1;
                    break;
                }
                else { break; }
            // To erase a number Backspace
            case sf::Keyboard::BackSpace:
                map.getCells()[focus.x][focus.y].setNumber("");
                break;

                // if the key is not valide
            default:
                std::cout << "Touche non valable" << std::endl;
                break;
            }
        }
    }


    // the function to start the game
    // Take a refence of the the window which will display the game as a parameter
    void play(sf::RenderWindow& window) {
        InitializeSudoKu(window);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (Gamefinish == false) {
                    // Call the mouse manager
                    MouseClicked(window, event);
                    // Call the Keyboard manager
                    writeNumber(event);
                    mapCompleted(window);
                }
            }

            // Draw elements and display the window
            window.clear(sf::Color::White);
            map.draw(window);
            if (Gamefinish) {
                window.draw(finish);
            }
            window.display();
        }
    }
    // Constructor
	SudokuGame(std::string pwd,sf::Font& ft) :map(pwd,ft), focus(sf::Vector2<int>(0, 0)) {
        finish.setFont(ft);
	}
};
