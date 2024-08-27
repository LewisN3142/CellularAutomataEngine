#include "SimulationEngine.h"
#include "../Automata/MatrixAutomata.h"
#include "../Tilings/SquareTiling.h"
#include "../Tilings/SquareTileCell.h"
#include "variables.h"

#include <chrono>
#include <thread>


SimulationEngine::SimulationEngine()
{
	m_Resolution.x = 1920.0f;
	m_Resolution.y = 1080.0f;
	m_Window.create(VideoMode((int)(m_Resolution.x), (int)(m_Resolution.y)), "Automata Engine", Style::Default);
}


void SimulationEngine::run()
{
	// Temporary variables for default inputs
	int rows = 50;
	int columns = 50;
	int blockSize = 14;
	e_Surface surfaceType = SPHERE;
	bool isMoore = 1; // Choose between von Neumann neighbourhood (no corners) when isMoore=0, and Moore neighbourhood (with corners) when isMoore=1

	std::pair<int, int> proportionDeadAlive(2, 1); 
	std::vector<int> births = {3};
	std::vector<int> survival = {2,3}; // If values in births/survival are greater than the possible size of the neighbourhood, then this is the same as if the condition was not evaluated.

	bool isLatent = 1; // If true, then make recently born/died cells slightly lighter in colour

	// Check if input variable is valid before tiling generated -- replace with assertion and put into tiling constructor or initial state randomiser. Also set default value.
	if (proportionDeadAlive.first <= 0 || proportionDeadAlive.second <= 0)
	{
		std::cout << "Error: Proportion of initial dead and alive cells should be given as two positive numbers" << std::endl;
		std::cout << ' ' << std::endl;
		return;
	}

	if (rows < 1 || columns < 1)
	{
		std::cout << "Error: Grid must have at least 1 row and column" << std::endl;
		std::cout << ' ' << std::endl;
	}

	// Eventually replace SquareTiling in this script with generic tiling that may be square penrose einstein etc
	SquareTiling newTiling = generateSquareTiling(rows, columns, surfaceType, isMoore, blockSize, proportionDeadAlive); 

	// Ensure that input variables are valid before matrix generated -- replace with assertion and put into the square tiling constructor
	if (surfaceType == SPHERE && columns != rows)
	{
		std::cout << "Error: Sphere must have equal number of columns and rows" << std::endl;
		std::cout << ' ' << std::endl;
		return;
	}

	while (m_Window.isOpen()) 
	{
		handleInput();

		// Eventually enclose below into tiling state manager and updater
		if (m_isSimulationRunning) 
		{
			if (isLatent == 1)
			{
				m_oldTilingStates = m_tilingStates;
			}

			m_tilingStates = MatrixGoL(m_tilingStates, newTiling.getFirstNeighbourListIndex(), newTiling.getListCellNeighbours(), newTiling.getNumCellNeighbours(), births, survival);
			m_stepCounter += 1;
			std::cout << m_stepCounter << std::endl;

			std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Come up with nicer implementation here
		}
		renderTiling(newTiling, isLatent);
	}
}

void SimulationEngine::renderTiling(SquareTiling tiling, bool isLatent) // Change function name to renderScreen, split into two panels, one for buttons and one for tiling
{
	m_Window.clear(sf::Color::Black);

	drawVisualCells(tiling.getVisualTiling(), isLatent);
	m_Window.display();
}

void SimulationEngine::drawVisualCells(std::vector<SquareTileCell> visualCells, bool isLatent) 
{
	for (int i = 0; i < m_tilingStates.size(); i++)
	{
		if (m_tilingStates[i] == ALIVE)
		{
			visualCells[i].changeColour(sf::Color::Blue);
		}
		else if (m_tilingStates[i] == DEAD)
		{
			visualCells[i].changeColour(sf::Color::Red);
		}

		// Change colour slightly if the tile is just born or just died
		if (isLatent == 1 && m_tilingStates[i] == ALIVE && m_oldTilingStates[i] == DEAD)
		{
			visualCells[i].changeColour(sf::Color(100,100,255,255));
		}
		if (isLatent == 1 && m_tilingStates[i] == DEAD && m_oldTilingStates[i] == ALIVE)
		{
			visualCells[i].changeColour(sf::Color(255,100,100,255));
		}

		m_Window.draw(visualCells[i].getShape());
	}
}

SquareTiling SimulationEngine::generateSquareTiling(int rows, int columns, e_Surface surfaceType, bool isMoore, int blockSize, std::pair<int,int> proportionDeadAlive)
{
	SquareTiling newTiling = SquareTiling(rows, columns, surfaceType, isMoore);
	newTiling.generateVisualTiling(blockSize);
	m_tilingStates = std::vector<int>(newTiling.getNumCells(), 1);
	m_oldTilingStates = std::vector<int>(newTiling.getNumCells(), 0);
	m_proportionDeadAlive = proportionDeadAlive;
	return newTiling;
}

void SimulationEngine::handleInput()
{
	Event event;
	while (m_Window.pollEvent(event))
	{
		switch (event.type)
		{
		case Event::Closed:
			m_Window.close();
			break;

		case Event::KeyPressed:
			switch (event.key.code)
			{
			case Keyboard::Space: // Pause and play simulation
				switch (m_isSimulationRunning)
				{
				case 1:
					m_isSimulationRunning = false;
					break;
				case 0:
					m_isSimulationRunning = true;
					break;
				}
				break;

			case Keyboard::R: // Randomize board when simulation stopped
				switch (m_isSimulationRunning)
				{
				case 1:
					break;
				case 0:
					m_tilingStates = randomTilingState(m_tilingStates, m_proportionDeadAlive);
					break;
				}

			// case Keyboard::S: // Eventual pause and save simulation -- get start state (tiling type and state, input variables), number of iterations, maybe end state
			}
			break;
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		m_Window.close();
	}
}

std::vector<int> SimulationEngine::randomTilingState(std::vector<int> tilingStates, std::pair<int, int> proportionDeadAlive) 
{
	// Maybe add in toggles for Perlin or Voronoi

	srand((int)time(0));
	for (int i = 0; i < tilingStates.size(); i++)
	{
		int number = (int)(rand() % (proportionDeadAlive.first + proportionDeadAlive.second)); // There is a first:second ratio of Dead:Alive
		bool isGoingToLive = (number < proportionDeadAlive.second);

		switch (isGoingToLive)
		{
		case 1:
			tilingStates[i] = -1;
			break;
		case 0:
			tilingStates[i] = 1;
			break;
		}

		m_oldTilingStates = std::vector<int>(tilingStates.size(), 0); // Will need to write code to reset old tiling state on random tile generation when move this to tiling manager...
	}

	m_stepCounter = 0;
	return tilingStates;
}




// Two separate viewports, one for controls, other for simulation
// Implement pass as reference where possible
// Not sure if tiling state updater and randomiser will end up somewhere else... want to make tiles clickable so that will probably need tiling state manager
// Do we make tiling a member variable ??
