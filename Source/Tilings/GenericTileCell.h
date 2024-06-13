#pragma once

#pragma once
#include <SFML/Graphics.hpp>

class GenericTileCell
{
private:
	sf::Vector2f m_Position;
	sf::CircleShape m_Circle; // Make generic tiling appear as a graph of (linked?) dots -- will want this to be a generic shape called m_TileShape, which is set to a circle for this class etc... will need a set of shapes for irrgular tiles
	sf::Color m_Color;

public:
	GenericTileCell(sf::Color cellColour, int dotSize);
	// Add in other functions from SquareTileCell as needed
};