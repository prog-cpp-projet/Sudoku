#pragma once
#include<SFML/Graphics.hpp>
#include<string>
#include<iostream>

class Cell {
private:
    float size;  // Taille de la cellule
    std::string number;  // Numéro affiché dans la cellule
    sf::Vector2f position;  // Position de la cellule
    sf::RectangleShape border;  // Bordure de la cellule
    sf::Text text;
    sf::Color BGColor;  // Couleur de fond
    sf::Font font;
    bool updatable;

public:
    
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


    // Constructeur par copie
    Cell(const Cell& other) : size(other.size), number(other.number), position(other.position), border(other.border), BGColor(other.BGColor), font(other.font),updatable(other.updatable) {
        text = other.text;
        text.setFont(font);  // S'assurer que la police est réassignée correctement
        text.setPosition(other.text.getPosition());
    }

    // Constructeur par déplacement
    Cell(Cell&& other) noexcept : size(other.size), number(std::move(other.number)), position(other.position), border(std::move(other.border)), BGColor(other.BGColor), font(other.font),updatable(other.updatable) {
        text = std::move(other.text);
        text.setFont(font);  // S'assurer que la police est réassignée correctement
        other.size = 0.0f;
    }

    // Opérateur d'affectation par copie
    Cell& operator=(const Cell& other) {
        if (this != &other) {
            size = other.size;
            number = other.number;
            position = other.position;
            border = other.border;
            BGColor = other.BGColor;
            text = other.text;
            text.setFont(font);  // S'assurer que la police est réassignée correctement
            text.setPosition(other.text.getPosition());
        }
        return *this;
    }

    // Opérateur d'affectation par déplacement
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

    void draw(sf::RenderWindow& window) {
        float textpositionX = (position.x + position.x + size) / 2 - text.getCharacterSize() / 2;
        float textpositionY = (position.y + position.y + size) / 2 - text.getCharacterSize() / 2;
        //border.setPosition(position);
        text.setPosition(sf::Vector2f(textpositionX, textpositionY));
        window.draw(border);
        window.draw(text);
        std::string num = text.getString();
    }
};
