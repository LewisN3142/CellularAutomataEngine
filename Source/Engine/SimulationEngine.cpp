#include "SimulationEngine.h"
#include "../Automata/MatrixAutomata.h"
#include "../Tilings/SquareTiling.h"
#include "../Tilings/SquareTileCell.h"
#include "variables.h"


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
	e_Surface surfaceType = PLANE;
	bool isMoore = 1;
	std::pair<int, int> proportionDeadAlive(5, 3); // Add in check to make sure these are both positive, set a default value...

	// Eventually replace SquareTiling in this script with generic tiling that may be square penrose einstein etc
	SquareTiling newTiling = generateSquareTiling(rows, columns, surfaceType, isMoore, blockSize, proportionDeadAlive); 

	while (m_Window.isOpen()) 
	{
		handleInput();

		// Eventually enclose below into boardstate manager and updater
		if (m_isSimulationRunning) 
		{
			m_boardStates = MatrixGoL(m_boardStates, newTiling.getFirstNeighbourListIndex(), newTiling.getListCellNeighbours(), newTiling.getNumCellNeighbours());
			m_stepCounter += 1;
			std::cout << m_stepCounter << std::endl;
		}
		renderTiling(newTiling);
	}
}

void SimulationEngine::renderTiling(SquareTiling tiling) // Change function name to renderScreen
{
	m_Window.clear(sf::Color::Black);

	// Line between simulation and control panel (update to two viewports)
	RectangleShape menu_Line(sf::Vector2f(0.005f * m_Resolution.x, m_Resolution.y));
	menu_Line.setPosition(Vector2f(0.8f * m_Resolution.x, 0));
	menu_Line.setFillColor(Color(128, 128, 128));
	m_Window.draw(menu_Line);

	drawVisualCells(tiling.getVisualTiling());
	m_Window.display();
}

void SimulationEngine::drawVisualCells(std::vector<SquareTileCell> visualCells) 
{
	for (int i = 0; i < m_boardStates.size(); i++)
	{
		if (m_boardStates[i] == -1)
		{
			visualCells[i].changeColour(sf::Color::Blue);
		}
		m_Window.draw(visualCells[i].getShape());
	}
}

SquareTiling SimulationEngine::generateSquareTiling(int rows, int columns, e_Surface surfaceType, bool isMoore, int blockSize, std::pair<int,int> proportionDeadAlive)
{
	SquareTiling newTiling = SquareTiling(rows, columns, surfaceType, isMoore);
	newTiling.generateVisualTiling(blockSize);
	m_boardStates = std::vector<int>(newTiling.getNumCells(), 1);
	m_proportionDeadAlive = proportionDeadAlive;
	return newTiling;
}

void SimulationEngine::handleInput()
{
	// to edit -- add temporary reroll function to re-randomise board without re-launching script
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
					m_boardStates = randomBoardState(m_boardStates, m_proportionDeadAlive);
					break;
				}

			// case Keyboard::S: // Eventual pause and save simulation -- get start state (board, tiling, input variables), number of iterations, maybe end state
			}
			break;
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		m_Window.close();
	}
}

std::vector<int> SimulationEngine::randomBoardState(std::vector<int> boardStates, std::pair<int, int> proportionDeadAlive) 
{
	srand((int)time(0));
	for (int i = 0; i < boardStates.size(); i++)
	{
		int number = (int)(rand() % (proportionDeadAlive.first + proportionDeadAlive.second)); // There is a first:second ratio of Dead:Alive
		bool isGoingToLive = (number < proportionDeadAlive.second);

		switch (isGoingToLive)
		{
		case 1:
			boardStates[i] = -1;
			break;
		case 0:
			boardStates[i] = 1;
			break;
		}
	}

	m_stepCounter = 0;
	return boardStates;
}




// Two separate viewports, one for controls, other for simulation
// Implement pass as reference where possible
// Not sure if random board state/board state updater will end up somewhere else... want to make tiles clickable so that will probably need board state manager
// Do we make tiling a member variable ??
