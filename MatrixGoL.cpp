#include "MatrixAutomata.h"
#include "variables.h"


/*
%%%%%%%%%%%%%%%%% Input varaibles %%%%%%%%%%%%%%%%%%%%%%%%%%

tilingStates -- Vector containing the current state of each cell in the tiling 
				Takes the place of weighted adjacency matrix in CSR sparse representation as each non-zero entry in a given column is the same (if cell j is a neighbour of cell i and is alive (i,j) is -1, if dead (i,j) is 1, not neighbour then 0)

columnIndex -- Vector containing the column index of each non-zero entry in the adjacency matrix for our tiling (part of CSR sparse representation)
               Goes through each tile in order and lists the index of each of its neighbours

rowStart -- Vector containing the index of the entry in columnIndex corresponding to the first of the tile's neighbours (part of CSR representation)
			The last entry in rowStart is the total number of non-zero entries (1 + size(columnIndex))

numCellNeighbours -- Number of neighbours each cell has, equivalent to the number of non-zero entries in the rows of the adjacency matrix 
                        Precomputed and passed to function (rather than calculating internally each time) as is static once the tiling is generated 

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/


std::vector<int> MatrixGoL(std::vector<int> tilingStates, std::vector<int> rowStart, std::vector<int> columnIndex, std::vector<int> numCellNeighbours)
{
	int length = (int)tilingStates.size();
	std::vector<int> newStates(length, 0);

	// Iterate through all of the cells in the tiling (equiv. to each row in adjacency matrix)
	for (int cellInTiling = 0; cellInTiling < length; cellInTiling++)
	{
		// Compute (twice the) number of alive neighbours 'k' of each cell (given by the number of neighbours 'n' of the cell minus the rowSum 'n-2k' of the relevant row in weighted adjacency matrix)
		std::vector<int> cellTwiceAliveNeighbours = numCellNeighbours;

		for (int cellNeighboursIter = rowStart[cellInTiling]; cellNeighboursIter < rowStart[cellInTiling + 1]; cellNeighboursIter++)
		{
			cellTwiceAliveNeighbours[cellInTiling] -= tilingStates[columnIndex[cellNeighboursIter]];
		}

		// If cell is currently dead and has 3 neighbours or the cell is currently alive and has (2 or 3) neighbours, then the new state is alive, otherwise the new state is dead.
		bool isCellAlive = (tilingStates[cellInTiling] == DEAD && cellTwiceAliveNeighbours[cellInTiling] == 6) || (tilingStates[cellInTiling] == ALIVE && (cellTwiceAliveNeighbours[cellInTiling] == 4 || cellTwiceAliveNeighbours[cellInTiling] == 6));

		switch (isCellAlive) {
		case 1:
			newStates[cellInTiling] = ALIVE;
			break;
		case 0:
			newStates[cellInTiling] = DEAD;
			break;
		}
	}

	return newStates;
}


// Cannot use vector iterator here since we iterate multiple vectors simultaneously
// Modify if we implement variable size neighbourhoods where closer neighbours are weighted more heavily
// Work out how to pass arguments by reference to save memory -- issue with private member variables of tilings and get methods.

