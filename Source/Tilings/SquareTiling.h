#pragma once
#include <SFML/Graphics.hpp>
#include "SquareTileCell.h"
#include "../Engine/variables.h"

class SquareTiling
{
private:
	// Tiling options
	int m_numRowsInTiling;
	int m_numColumnsInTiling;
	int m_numCells;

	int m_numTotalNeighbours;
	std::vector<int> m_numCellNeighbours;

	// Neighbourhood options
	bool m_isMoore;
	e_Surface m_surfaceType;

	// Adjacency matrix in compressed sparse row representation (also need tile states)
	std::vector<int> m_firstNeighbourListIndex; // lists the index in m_listCellNeighbours of each cell's first neighbour -- equivalent to row start vector in CSR
	std::vector<int> m_listCellNeighbours; // lists each cell's neighbours in turn -- equivalent to column index vector in CSR 

	// Store the visual tiling 
	std::vector<SquareTileCell> m_visualCells;


public:
	SquareTiling(int numRows, int numColumns, e_Surface surfaceType, bool isMoore);

	std::vector<int> getFirstNeighbourListIndex();
	std::vector<int> getListCellNeighbours();
	std::vector<int> getNumCellNeighbours();
	int getNumCells();
	std::vector<SquareTileCell> getVisualTiling();

	void generateAdjacencyMatrix();
	void generateVisualTiling(int blockSize);

	void setNumCellNeighbours();
	void setFirstNeighbourListIndex();
	void setListCellNeighbours();
	void resetNeighbourhoodOptions(e_Surface newSurfaceType, bool isNowMoore);
};