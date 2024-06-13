# A Cellular Automata Engine

## Description

The Cellular Automata (CA) Engine is a program for simulating cellular automata such as Conway's Game of Life or Langton's Turmites on a range of regular and irregular tilings of the plane, as well as arbitrary graphs. 
It does so by interpreting Cellular Automata algorithms as algorithms acting on sparse matrices, namely the adjacency matrices for the cells, given in a modified Compressed Sparse Row representation (more information on this below -- link TBC) and computing a vector containing the state of each cell at each iteration.
Independently of this, an SFML-based visual component can be used to render the output of the algorithm to the screen.

An executable version of The CA Engine can be found in the root folder of this repository, if you would like to run the code without compiling it yourself. Please ensure that you
 - Have a 64-bit compatible computer.
 - Have downloaded the SFML ``.dll`` files from the root folder of this repository and placed them in the same folder as the ``.exe`` file
before running the executable.

(Note: Once this project moves to a release build we aim to move to static SFML so that the second point is moot. This readme will be updated when this changeover happens.)

## Build Instructions
This project was originally built using Visual C++20 in Visual Studio 2022 and uses the Visual C++17 64-bit version of SFML 2.6.1. Please ensure you have a 64-bit compatible system before attempting to compile and run this application.
In order to compile the code locally and run it using Visual Studio, you should follow the instructions below, ensuring that software versions match where possible to avoid any unwanted errors.

 - [Download](https://visualstudio.microsoft.com/vs/) and Install Visual Studio 2022.
 - Clone or Download and Extract this repository to an appropriate directory on your local machine. You should end up with a folder called ``CellularAutomataEngine``.
   - Note: If you Download this project rather than Cloning it, you may find that after extracting the files from the ``.zip`` folder, there is a second folder called ``CellularAutomataEngine`` within the first one. It is this inner folder you want -- move the inner folder to your desired directory and delete the (now empty) outer folder.
 - [Download SFML](https://www.sfml-dev.org/download/sfml/2.6.1/). You will need the Visual C++17 (2022) 64-bit version of SFML 2.6.1.
 - Extract the SFML files from the ``.zip`` folder you just downloaded.
 - Inside the ``SFML-2.6.1-windows-vc17-64-bit`` folder you will find a folder named ``SFML-2.6.1.`` Move this ``SFML-2.6.1`` folder to the same directory as the "CellularAutomataEngine" folder you obtained earlier, but NOT inside the ``CellularAutomataEngine`` folder.
 - Rename "SFML-2.6.1" to "SFML_x64."

Your final file hierarchy should look like

 - CHOSEN_DIRECTORY
   - ``CellularAutomataEngine``
     - PROJECT_FILES
   - ``SFML_x64``
     - FILES FROM ``SFML-2.6.1``

If so then that's it, you're good to go! Now simply open the ``SFML_Einstein_GoL.sln`` file, which can be found in the ``CellularAutomataEngine`` folder, in Visual Studio 2022 and have fun!

The build options you will need to use are ``x64`` and ``Debug`` in order for the code to compile correctly. Also ensure that your C++ Language Standard (found under ``Project > Project Properties > Configuration Properties > General > General Properties`` in Visual Studio) should be set to ``ISO C++20 Standard (/std:c++20)``.
The linker and compiler, along with the above build options and standards, should be set up appropriately by default due to the .vcxproj file included in this repository, however if Visual Studio fails to read this file for any reason, you may have to alter these settings manually. 
If you need to change the linker and compiler settings manually, I recommend following the ``Setting up SFML`` chapter of John Horton's book [Beginning C++ Game Programming](https://subscription.packtpub.com/search?query=beginning%20c%2020%20game%20programming).

To reiterate the note in the introduction, once this project reaches a release build, we aim to move to static SFML so that the end user does not have to download the files separately. This readme will be updated with new instructions once this changeover happens.

(Note that the ``.exe`` file at the root of the project folder does not update when you compile the code yourself. A new executable will be generated in ``x64 > Debug`` and you will need to copy the sfml ``.dll`` files into the same folder in order to run the executable.


## Functionality

### Current Functionality

### Proposed Functionality
More information on proposed functions of The CA Engine can be found in the relevant project page (link TBC). As a brief overview, here are some functions that are currently in the works:

## Implementing Your Own Algorithms
TBC

## Implementing Your Own Tilings
TBC

## References
TBC
