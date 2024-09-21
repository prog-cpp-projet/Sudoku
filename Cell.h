#pragma once
#include<SFML/Graphics.hpp>
#include<string>
#include<iostream>

class Cell {
private:
    float size;  // Cell size
    std::string number;  // Number displayed by the cell
    sf::Vector2f position;  // cell position
    sf::RectangleShape border;  // cell border
    sf::Text text;  //number displayer
    sf::Color BGColor;  // Back ground color
    sf::Font font;
    bool updatable;   //Type of the cell

public:
    //Constructor taking a font reference as argument
    Cell(const sf::Font& ft) : size(0.0f), number(""), position(0.0f, 0.0f), border(sf::Vector2f(size, size)), BGColor(sf::Color::Blue), font(ft), updatable(true){
        text.setFont(font);
        text.setString(number);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::Black);
        text.setStyle(sf::Text::Bold);
        text.setPosition(position);

        border.setFillColor(BGColor);
        border.setOutlineColor(sf::Color::Black);
        border.setOutlineThickness(5.f);
        border.setPosition(position);
    }

    //Constructor taking a font reference and a string as argument
    Cell(const sf::Font& ft,std::string num) : size(0.0f), number(num), position(0.0f, 0.0f), border(sf::Vector2f(size, size)), BGColor(sf::Color::Blue), font(ft), updatable(true) {
        text.setFont(font);
        text.setString(number);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::Black);
        text.setStyle(sf::Text::Bold);
        text.setPosition(position);

        border.setFillColor(BGColor);
        border.setOutlineColor(sf::Color::Black);
        border.setOutlineThickness(5.f);
        border.setPosition(position);
    }


    // Copy constructor
    Cell(const Cell& other) : size(other.size), number(other.number), position(other.position), border(other.border), BGColor(other.BGColor), font(other.font),updatable(other.updatable) {
        text = other.text;
        text.setFont(font);  // S'assurer que la police est réassignée correctement
        text.setPosition(other.text.getPosition());
    }

    // Move constructor
    Cell(Cell&& other) noexcept : size(other.size), number(std::move(other.number)), position(other.position), border(std::move(other.border)), BGColor(other.BGColor), font(other.font),updatable(other.updatable) {
        text = std::move(other.text);
        text.setFont(font);  // S'assurer que la police est réassignée correctement
        other.size = 0.0f;
    }

    // Copy assignment operator
    Cell& operator=(const Cell& other) {
        if (this != &other) {
            size = other.size;
            number = other.number;
            position = other.position;
            border = other.border;
            BGColor = other.BGColor;
            text = other.text;
            text.setFont(font);  // Make sure the font is correctly assigned
            text.setPosition(other.text.getPosition());
        }
        return *this;
    }

    // Move assignment operator
    Cell& operator=(Cell&& other) noexcept {
        if (this != &other) {
            size = other.size;
            number = std::move(other.number);
            position = other.position;
            border = std::move(other.border);
            BGColor = other.BGColor;
            text = std::move(other.text);
            text.setFont(font);  // S'assurer que la police est réassignée correctement
            other.size = 0.0f;
        }
        return *this;
    }

    ~Cell() {}

    // Getters
    std::string getNumber() {
        return number;
    }

    sf::Vector2f getPosition() {
        return position;
    }

    bool getType() {
        return updatable;
    }

    sf::RectangleShape& getRect() {
        return border;
    }

    sf::Color getBGColor() {
        return BGColor;
    }

    // Setters
    void setPosition(float x, float y) {
        position = sf::Vector2f(x, y);
        float textpositionX = (position.x + position.x + size) / 2 - text.getCharacterSize() / 2;
        float textpositionY = (position.y + position.y + size) / 2 - text.getCharacterSize() / 2;
        border.setPosition(position);
        text.setPosition(sf::Vector2f(textpositionX, textpositionY));
    }

    void setNumber(std::string s) {
        if (updatable) {
            number = s;
            text.setString(s);
        }
    }

    void setBGColor(sf::Color color) {
        if (updatable) {
            BGColor = color;
            border.setFillColor(BGColor);
        }
    }

    void setType(bool type) {
        if (type == false) {
            BGColor = sf::Color::Red;
            border.setFillColor(BGColor);
        }
        updatable = type;
    }

    void setSize(float size) {
        this->size = size;
        border.setSize(sf::Vector2f(size, size));
        float textpositionX = (position.x + position.x + size) / 2 - text.getCharacterSize() / 2;
        float textpositionY = (position.y + position.y + size) / 2 - text.getCharacterSize() / 2;
        text.setPosition(sf::Vector2f(textpositionX, textpositionY));
    }

    //THIS FUNCTION TAKE A REFERENCE TO THE TARGETED WINDOW AS ARGUMENT
    void draw(sf::RenderWindow& window) {
        //compute text position
        float textpositionX = (position.x + position.x + size) / 2 - text.getCharacterSize() / 2;
        float textpositionY = (position.y + position.y + size) / 2 - text.getCharacterSize() / 2;
        text.setPosition(sf::Vector2f(textpositionX, textpositionY));

        //draw the text after drawing the cell
        window.draw(border);
        window.draw(text);
        std::string num = text.getString();
    }
};
