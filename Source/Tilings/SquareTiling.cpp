#include "SquareTiling.h"
#include "SquareTileCell.h"
#include "../Engine/variables.h"

#include <SFML/Graphics.hpp>
#include <iostream>

SquareTiling::SquareTiling(int numRows, int numColumns, e_Surface surfaceType, bool isMoore) // Change input to e_surface
{
	// Boundary conditions
	m_surfaceType = surfaceType;

	// Moore or Von Neumann neighbourhood definition
	m_isMoore = isMoore; 

	m_numRowsInTiling = numRows;
	m_numColumnsInTiling = numColumns;
	m_numCells = m_numRowsInTiling * m_numColumnsInTiling; 

	generateAdjacencyMatrix();	
}

void SquareTiling::generateAdjacencyMatrix()
{
	// Total number of neighbours in tiling / edges in graph / non-zero entries in adjacency matrix (this value is for Sphere, Projective plane, Torus which have no Dirichlet BCs)
	m_numTotalNeighbours = 4 * m_numCells * (1 + m_isMoore);

	switch (m_surfaceType)
	{
	case PLANE:
		m_numTotalNeighbours = m_numTotalNeighbours - m_numRowsInTiling * (2 + 4 * m_isMoore) + 4 * m_isMoore; // Adjust for Dirichlet boundaries on left and right for 1 case
		[[fallthrough]]; // Also has Dirichlet top and bottom

	case CYLINDER: 
		[[fallthrough]]; // Also has Dirichlet top and bottom

	case MOEBIUS:
		m_numTotalNeighbours = m_numTotalNeighbours - m_numColumnsInTiling * (2 + 4 * m_isMoore); // Adjust for Dirichlet boundaries on top and bottom for 3 cases
		break;

	default: break;
	}

	// Set the number of neighbours each cell has / adjacent edges each node in graph has / non-zero entries each row of the adjacency matrix has
	setNumCellNeighbours();

	// Set up Compressed Sparse Representation of adjacency matrix
	setFirstNeighbourListIndex();
	setListCellNeighbours();
}

void SquareTiling::generateVisualTiling(int blockSize)
{
	m_visualCells = std::vector<SquareTileCell>(m_numCells, SquareTileCell(sf::Color::Red, blockSize));
	int lineWidth = 1 + blockSize/10; // How far apart tiles will be depends on their size

	for (int i = 0; i < m_numRowsInTiling; i++) // Set the positions of each of the tiles
	{
		for (int j = 0; j < m_numColumnsInTiling; j++)
		{
			m_visualCells[i * m_numColumnsInTiling + j].setPosition((blockSize + lineWidth) * ((float)j + 1), (blockSize + lineWidth) * ((float)i + 1));
		}
	}
}

// Setter Methods

// Note that corner tiles for the topological sphere have themselves as three of their neighbours
void SquareTiling::setNumCellNeighbours()
{
	m_numCellNeighbours = std::vector<int>(m_numCells, 4 * (1 + m_isMoore)); // By default, all cells have 4 or 8 neighbours
	int edgeAdjustment = 1 + 2 * m_isMoore; // How many fewer neighbours an edge with Dirichlet conditions has
	std::vector<int> cornerCells = std::vector<int>{ 0, m_numColumnsInTiling - 1, m_numCells - 1, m_numCells - m_numColumnsInTiling }; // Which cells are situated on the corners


	switch (m_surfaceType)
	{
	case PLANE:
		// Plane has Dirichlet BCs on left and right, so cells on these edges have fewer neighbours
		for (int i = 0; i < m_numRowsInTiling; i++)
		{
			m_numCellNeighbours[i * m_numColumnsInTiling] -= edgeAdjustment;
			m_numCellNeighbours[m_numColumnsInTiling * (i + 1) - 1] -= edgeAdjustment;
		}
		// Account for overcounting on corners which are subject to horizontal and vertical Dirichlet BCs
		for (auto v : cornerCells)
		{
			m_numCellNeighbours[v] += m_isMoore;
		}
		[[fallthrough]]; // Also has Dirichlet top and bottom

	case CYLINDER:
		[[fallthrough]]; // Also has Dirichlet top and bottom

	case MOEBIUS:
		// Cylinder, Moebius strip, and Plane are given fixed top and bottom boundary so tiles on these edges have fewer neighbours
		for (int i = 0; i < m_numColumnsInTiling; i++)
		{
			m_numCellNeighbours[i] -= edgeAdjustment;
			m_numCellNeighbours[m_numCells - (i + 1)] -= edgeAdjustment;
		}
		break;

	default: break;
	}
} 

void SquareTiling::setFirstNeighbourListIndex()
{
	m_firstNeighbourListIndex = std::vector<int>(m_numCells + 1, 0);

	for (int i = 1; i <= m_numCells; i++)
	{
		m_firstNeighbourListIndex[i] = m_firstNeighbourListIndex[i - 1] + m_numCellNeighbours[i - 1];
	}
}

void SquareTiling::setListCellNeighbours() 
{
	m_listCellNeighbours = std::vector<int>(m_numTotalNeighbours, 0);

	std::vector<int> cellNeighbourhood = std::vector<int>{ -1 - m_numColumnsInTiling, -m_numColumnsInTiling, 1 - m_numColumnsInTiling, -1, 1, -1 + m_numColumnsInTiling, m_numColumnsInTiling, 1 + m_numColumnsInTiling }; // Default distance to candidate Moore neighbours
	const std::vector<int> m_neumannModification{ 1,2,2,3, 0,1,1,2 }; // Modification to only check Neumann neighbours from cellNeighbourhood

	// Itertate over all of the cells and store the indices of their neighbours in m_listCellNeighbours
	for (int cellNumber = 0; cellNumber < m_numCells; cellNumber++)
	{
		int candidateNeighbourNumber = 0;

		// Iterate through a cell's candidate neighbours and stop when all of the cell's neighbours have been found
		for (int numberNeighboursFound = 0; numberNeighboursFound < m_numCellNeighbours[cellNumber]; candidateNeighbourNumber++) 
		{
			int candidateNeighbourTilingIndex = cellNumber + cellNeighbourhood[candidateNeighbourNumber + (1 - m_isMoore) * m_neumannModification[candidateNeighbourNumber]]; // Index of the neighbour in the tiling

			// Check if original cell is on right edge and candidate neighbour is on the left edge -- modify neighbour position based on BCs
			if ((candidateNeighbourTilingIndex % m_numColumnsInTiling == 0) && ((cellNumber + 1) % m_numColumnsInTiling == 0)) 
			{
				switch (m_surfaceType)
				{
				// Reject neighbour due to Dirichlet BCs
				case PLANE:
					continue; 

				// Move neighbour down by 1 row to correct position.
				case CYLINDER: 
					[[fallthrough]];
				case TORUS: 
					[[fallthrough]];
				case KLEIN:
					candidateNeighbourTilingIndex -= m_numColumnsInTiling; 
					break;

				// Move neighbour down by 1 row and flip left edge to account for twisted boundary
				case MOEBIUS:
					[[fallthrough]];
				case PROJECTIVE:
					candidateNeighbourTilingIndex = m_numCells - candidateNeighbourTilingIndex;
					break;

				// Move neighbour from left column to top row (for our sphere top right and bottom left corners of representative square are poles)
				case SPHERE:
					candidateNeighbourTilingIndex = m_numColumnsInTiling - (candidateNeighbourTilingIndex / m_numColumnsInTiling);

					// Make bottom right corner its own neighbour one time (one neighbour ends up off the top of the grid)
					if (candidateNeighbourTilingIndex < 0)
					{
						candidateNeighbourTilingIndex += m_numCells;
					}

					// Make top right corner its own neighbour three times (one neighbour stays in the left column)
					if (candidateNeighbourTilingIndex % m_numColumnsInTiling == 0)
					{
						candidateNeighbourTilingIndex = m_numColumnsInTiling - (candidateNeighbourTilingIndex / m_numColumnsInTiling);
					}

					break;

				default: break;
				}
			}

			// Check if original cell is on left edge and candidate neighbour is on the right edge -- modify neighbour position based on BCs
			if (((candidateNeighbourTilingIndex + 1) % m_numColumnsInTiling == 0) && (cellNumber % m_numColumnsInTiling == 0)) 
			{
				switch (m_surfaceType)
				{
				// Reject neighbour due to Dirichlet BCs
				case PLANE:
					continue; 

				// Move neighbour up by 1 row to correct position
				case CYLINDER:
					[[fallthrough]];
				case TORUS:
				case KLEIN:
					candidateNeighbourTilingIndex += m_numColumnsInTiling; 
					break;

				// Move neighbour up by 1 row and flip right edge to account for twisted boundary
				case MOEBIUS:
				case PROJECTIVE:
					candidateNeighbourTilingIndex = m_numCells - candidateNeighbourTilingIndex - 2; 
					break;

				case SPHERE:
					candidateNeighbourTilingIndex = (m_numCells - 1 - (candidateNeighbourTilingIndex / m_numColumnsInTiling)) % m_numCells;

					// Make bottom left corner its own neighbour three times (one neighbour stays in the right column)
					if ((candidateNeighbourTilingIndex+1) % m_numColumnsInTiling == 0)
					{
						candidateNeighbourTilingIndex = (m_numCells - 1 - (candidateNeighbourTilingIndex / m_numColumnsInTiling)) % m_numCells;
					}
					break;

				default: break;
				}
			}

			// Check if candidate neighbour is off the top edge of the tiling and apply BCs
			if (candidateNeighbourTilingIndex < 0)
			{
				switch (m_surfaceType)
				{
				case PLANE:
					continue;
				case CYLINDER:
					continue;
				case MOEBIUS:
					continue;
					
				case TORUS:
					candidateNeighbourTilingIndex += m_numCells;
					break;

				case KLEIN:
					[[fallthrough]];
				case PROJECTIVE:
					candidateNeighbourTilingIndex = m_numCells - m_numColumnsInTiling - 1 - candidateNeighbourTilingIndex; // This will always be strictly less than m_numCells (for size 1 neighbourhoods, think about larger later)
					break;

				case SPHERE:
					candidateNeighbourTilingIndex = -1 - candidateNeighbourTilingIndex * m_numColumnsInTiling;
					break;
				default: break;
				}
			}

			if (candidateNeighbourTilingIndex >= m_numCells)
			{
				
				switch (m_surfaceType)
				{
				case PLANE:
					continue;
				case CYLINDER:
					continue;
				case MOEBIUS:
					continue;
				
				case TORUS:
					candidateNeighbourTilingIndex = candidateNeighbourTilingIndex % m_numCells; 
					break;

				case KLEIN:
					[[fallthrough]];
				case PROJECTIVE:
					candidateNeighbourTilingIndex = m_numColumnsInTiling - 1 - (candidateNeighbourTilingIndex % m_numCells); // This will always be greater than or equal zero (for size 1 neighbourhoods, think about larger later)
					break;

				case SPHERE:
					candidateNeighbourTilingIndex = m_numCells - m_numRowsInTiling * (1 + (candidateNeighbourTilingIndex % m_numCells));
					break;
				default: break;
				}
			}

			// If candidate neighbour is valid add its index to listCellNeighbours and update the number of neighbours that have been processed
			m_listCellNeighbours[m_firstNeighbourListIndex[cellNumber] + numberNeighboursFound] = candidateNeighbourTilingIndex; 
			numberNeighboursFound++;
		}
	}

}

void SquareTiling::resetNeighbourhoodOptions(e_Surface newSurfaceType, bool isNowMoore) 
{
	m_surfaceType = newSurfaceType;
	m_isMoore = isNowMoore;

	generateAdjacencyMatrix();
}


// Getter Methods
std::vector<int> SquareTiling::getFirstNeighbourListIndex()
{
	return m_firstNeighbourListIndex;
}

std::vector<int> SquareTiling::getNumCellNeighbours()
{
	return m_numCellNeighbours;
}

std::vector<int> SquareTiling::getListCellNeighbours()
{
	return m_listCellNeighbours;
}

int SquareTiling::getNumCells()
{
	return m_numCells;
}

std::vector<SquareTileCell> SquareTiling::getVisualTiling()
{
	return m_visualCells;
}



// Do modelling for sphere...
// Add in function to change range of neighbourhood -- would need to change listCellNeighbours computer for different BCs

// if do langton's ants or similar, each tile needs to know who are its neighbours 
// tiles are own class that tiling generator constructs, each tile knows its neighbours' indices and its shape (given unique index number when created)
// resetter for grid size also needs to reset tiling states from SimulationEngine so do that there

