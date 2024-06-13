#include "SimulationEngine.h"
#include <iostream>

int main()
{
	SimulationEngine m_SimulationEngine; // Could in theory create and run multiple on different threads to parallelize 
	m_SimulationEngine.run();
	return 0;
}

// Need option for CUDA mode and check for presence of graphics card
