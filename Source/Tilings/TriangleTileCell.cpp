#include "TriangleTileCell.h"
#include <iostream>

TriangleTileCell::TriangleTileCell(sf::Color cellColour, int sideLength)
{
	m_Triangle = sf::VertexArray(sf::Triangles, 3);
	changeColour(cellColour);
	setSize(sideLength);
}


sf::Vector2f TriangleTileCell::getPosition()
{
	return m_Position;
}

sf::VertexArray TriangleTileCell::getShape()
{
	return m_Triangle;
}

sf::Color TriangleTileCell::getColour()
{
	return m_Color;
}

void TriangleTileCell::setSize(int sideLength) // If used outside of constructor, need to reposition after as sets up at origin
{
	m_Triangle[0].position = sf::Vector2f((float)sideLength / 2, 0.0f);
	m_Triangle[1].position = sf::Vector2f((float)sideLength, sqrt(3) * (float)sideLength / 2);
	m_Triangle[2].position = sf::Vector2f(0.0f, sqrt(3) * (float)sideLength / 2);
}

void TriangleTileCell::setOrientation(int sideLength, int rotateAmount)
{
	sf::Vector2f centre = (m_Triangle[0].position + m_Triangle[1].position + m_Triangle[2].position)/3.0f;
	sf::Transform rotation;
	rotation.rotate(rotateAmount, centre);

	for (int i = 0; i < 3; i++)
	{
		m_Triangle[i].position = rotation.transformPoint(m_Triangle[i].position);
	}
}

void TriangleTileCell::setPosition(float nextX, float nextY) // Note this positions based on the centre, unlike rectangle shape (which should be replaced with quad or trianglestrip) as we want the method to be orientation independent
{
	sf::Vector2f translation = sf::Vector2f(nextX, nextY) - (m_Triangle[0].position + m_Triangle[1].position + m_Triangle[2].position) / 3.0f;

	for (int i = 0; i < 3; i++)
	{
		m_Triangle[i].position += translation;
	}
}

void TriangleTileCell::changeColour(sf::Color newColor)
{
	for (int i = 0; i < 3; i++)
	{
		m_Triangle[i].color = newColor;
	}
	m_Color = newColor;
}