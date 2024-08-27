#pragma once
#include <SFML/Graphics.hpp>
#include "../Tilings/SquareTileCell.h"
#include "../Tilings/SquareTiling.h"

using namespace sf;

class SimulationEngine {
private:
	RenderWindow m_Window;
	Vector2f m_Resolution;
	int m_stepCounter = 0;

	std::vector<int> m_tilingStates;
	std::vector<int> m_oldTilingStates;

	std::pair<int,int> m_proportionDeadAlive; 
	bool m_isSimulationRunning = false;

	void handleInput();

	SquareTiling generateSquareTiling(int rows, int columns, e_Surface surfaceType, bool isMoore, int blockSize, std::pair<int,int> proportionDeadAlive);
	void drawVisualCells(std::vector<SquareTileCell> visualTiles, bool isLatent);
	void renderTiling(SquareTiling tiling, bool isLatent);

public:
	SimulationEngine();
	void run();

	std::vector<int> randomTilingState(std::vector<int> boardStates, std::pair<int,int> proportionDeadAlive); // Maybe move into board state manager, or use member variable proportionDeadAlive
};