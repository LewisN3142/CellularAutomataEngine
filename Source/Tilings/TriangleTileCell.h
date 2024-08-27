#pragma once
#include <SFML/Graphics.hpp>

class TriangleTileCell
{
private:
	sf::Vector2f m_Position;
	sf::VertexArray m_Triangle;
	sf::Color m_Color;

public:
	TriangleTileCell(sf::Color cellColour, int sideLength);

	sf::Vector2f getPosition();
	sf::VertexArray getShape();
	sf::Color getColour();

	void setPosition(float nextX, float nextY);
	void changeColour(sf::Color newColor);
	void setSize(int sideLength); // Make sidelength/blocksize a member variable
	void setOrientation(int sideLength, int rotateAmount);
};

