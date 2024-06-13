#pragma once
#include <SFML/Graphics.hpp>

class SquareTileCell
{
private:
	sf::Vector2f m_Position;
	sf::RectangleShape m_Rectangle;
	sf::Color m_Color;

public:
	SquareTileCell(sf::Color cellColour, int blockSize);

	sf::Vector2f getPosition();
	sf::RectangleShape getShape();
	sf::Color getColour();

	void setPosition(float nextX, float nextY);
	void changeColour(sf::Color newColor);

};