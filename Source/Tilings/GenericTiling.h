#pragma once

#include <SFML/Graphics.hpp>
#include "../Engine/variables.h"
#include "GenericTileCell.h"

class GenericTiling
{
private:
	// Tiling options
	bool isTilingRegular; // Make two subclasses for regular and irregular then subclass further from there
	int m_numCells;
	int m_numTotalNeighbours; // Total number of links in graph corresponding to tiling
	std::vector<int> m_numCellNeighbours; // List of how many neighbours each cell has

	// Adjacency matrix in compressed sparse row representation (also need tile states)
	std::vector<int> m_firstNeighbourListIndex; // lists the index in m_listCellNeighbours of each cell's first neighbour -- equivalent to row start vector in CSR
	std::vector<int> m_listCellNeighbours; // lists each cell's neighbours in turn -- equivalent to column index vector in CSR 

	// Store the visual tiling 
	std::vector<GenericTileCell> m_visualCells;


public:
	GenericTiling(); // Custom constructor with input variables...

	std::vector<int> getFirstNeighbourListIndex();
	std::vector<int> getListCellNeighbours();
	std::vector<int> getNumCellNeighbours();
	int getNumCells();
	std::vector<GenericTileCell> getVisualTiling();

	void generateAdjacencyMatrix();
	void generateVisualTiling(int size);

	void setNumCellNeighbours();
	void setFirstNeighbourListIndex();
	void setListCellNeighbours();
};


// number of rows, columns, neighbourhood type, BCs only make sense for regular