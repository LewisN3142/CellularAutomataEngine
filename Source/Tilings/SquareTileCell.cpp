#include "SquareTileCell.h"
#include <iostream>

SquareTileCell::SquareTileCell(sf::Color cellColour, int blockSize)
{
	m_Rectangle.setSize(sf::Vector2f((float)blockSize, (float)blockSize));
	changeColour(cellColour);
}


sf::Vector2f SquareTileCell::getPosition()
{
	return m_Position;
}

sf::RectangleShape SquareTileCell::getShape()
{
	return m_Rectangle;
}

sf::Color SquareTileCell::getColour()
{
	return m_Color;
}

void SquareTileCell::setPosition(float nextX, float nextY)
{
	m_Position.x = nextX;
	m_Position.y = nextY;
	m_Rectangle.setPosition(m_Position);
}

void SquareTileCell::changeColour(sf::Color newColor)
{
	m_Rectangle.setFillColor(newColor);
	m_Color = newColor;
}