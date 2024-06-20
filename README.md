# The Cellular Automata Engine

[![Conway's Game of Life on the Plane](https://github.com/LewisN3142/CellularAutomataEngine/blob/main/GoL_Thumbnail.png)](https://www.youtube.com/watch?v=9tncKbkjvZs)

Click the image to watch a video of the engine in action (Opens Youtube in the current window)!

The video shows The Cellular Automata Engine simulating Conway's Game of Life on a 50x80 grid of square tiles with fixed (Dirichlet) boundary conditions. The board starts with no living cells and is randomised three times, generating a tiling where roughly 37% of the tiles are alive. Board and initial population sizes are both configurable in engine. This demonstration is running in real time and is being captured simultaneously via OBS Studio.

## About Me

Hi, I'm Lewis Napper, a mathematics Ph.D. student from The University of Surrey in the UK [(See my Faculty Webpage)](https://www.surrey.ac.uk/people/lewis-napper). My research interests include geometry, relativity, and fluid dynamics, however more recently I have taken an interest in the behaviour of cellular automata on irregular tilings of the plane and on graphs. I have a moderate amount of experience in programming languages such as MATLAB, C++, and Python [(See my Github Profile)](https://github.com/LewisN3142) from personal projects such as this one, as well as through providing teaching support to undergraduate courses in numerical methods. For more information, please visit my [Personal Website](https://lewisn3142.github.io/).    

## About the Project

The Cellular Automata (CA) Engine is a program for simulating cellular automata such as Conway's Game of Life or Langton's Turmites on a range of regular and irregular tilings of the plane, as well as arbitrary graphs. It does so by interpreting Cellular Automata as alorithms on sparse matrices, namely the weighted adjacency matrices of the tilings/graphs, given in a modified Compressed Sparse Row representation where we exploit additional patterns in the adjacency matrices. The output of these algorithms is then a vector containing the state of each cell at each iteration. More information on this can be found below (Link TBA). Independently of this, the SFML-based visual component can then be used to render the output of the algorithm to the screen.

This project was born of the desire to simulate Conway's Game of Life on tilings of the plane by aperiodic monotiles, such as the Penrose and Einstein tiles, in a flexible and efficient manner. However, since many of the features and methods were initially tested on regular tilings of the plane, where our results were more easily verified, The Cellular Automata 

An executable version of The CA Engine can be found in the root folder of this repository, if you would like to run the code without compiling it yourself. Please ensure that you
 - Have a 64-bit compatible computer.
 - Have downloaded the SFML ``.dll`` files from the root folder of this repository and placed them in the same folder as the ``.exe`` file
before running the executable.

(Note: Once this project moves to a release build we aim to move to static SFML so that the second point is moot. This readme will be updated when this changeover happens.)

## Build Instructions
This project was originally built using Visual C++20 in Visual Studio 2022 and uses the Visual C++17 64-bit version of SFML 2.6.1. Please ensure you have a 64-bit compatible system before attempting to compile and run this application.
In order to compile the code locally and run it using Visual Studio, you should follow the instructions below, ensuring that software versions match where possible to avoid any unwanted errors.

 - Download [Visual Studio 2022](https://visualstudio.microsoft.com/vs/) and Install it.
 - Clone or Download and Extract this repository to an appropriate directory on your local machine. You should end up with a folder called ``CellularAutomataEngine``.
   - Note: If you Download this project rather than Cloning it, you may find that after extracting the files from the ``.zip`` folder, there is a second folder called ``CellularAutomataEngine`` within the first one. It is this inner folder you want -- move the inner folder to your desired directory and delete the (now empty) outer folder.
 - Download [SFML](https://www.sfml-dev.org/download/sfml/2.6.1/). You will need the Visual C++17 (2022) 64-bit version of SFML 2.6.1.
 - Extract the SFML files from the ``.zip`` folder you just downloaded.
 - Inside the ``SFML-2.6.1-windows-vc17-64-bit`` folder you will find a folder named ``SFML-2.6.1``. Move this ``SFML-2.6.1`` folder to the same directory as the ``CellularAutomataEngine`` folder you obtained earlier, but NOT inside the ``CellularAutomataEngine`` folder itself.
 - Rename ``SFML-2.6.1`` to ``SFML_x64.``

Your final folder hierarchy should look like

 - CHOSEN_DIRECTORY
   - ``CellularAutomataEngine``
     - PROJECT_FILES
   - ``SFML_x64``
     - FILES FROM ``SFML-2.6.1``

If so then that's it, you're good to go! Now simply open the ``SFML_Einstein_GoL.sln`` file, which can be found in the ``CellularAutomataEngine`` folder, in Visual Studio 2022 and have fun!

The build options you will need to use are ``x64`` and ``Debug`` in order for the code to compile correctly. Also ensure that your C++ Language Standard (found under ``Project > Project Properties > Configuration Properties > General > General Properties`` in Visual Studio) is set to ``ISO C++20 Standard (/std:c++20)``.
The linker and compiler, along with the above build options and standards, should be set up appropriately by default due to the .vcxproj file included in this repository, however if Visual Studio fails to read this file for any reason, you may have to alter these settings manually. 
If you need to change the linker and compiler settings manually, I recommend following the ``Setting up SFML`` chapter of John Horton's book [Beginning C++ Game Programming](https://subscription.packtpub.com/search?query=beginning%20c%2020%20game%20programming).

To reiterate the note in the introduction, once this project reaches a release build, we aim to move to static SFML so that the end user does not have to download the files separately. This readme will be updated with new instructions once this changeover happens.

(Note that the ``.exe`` file at the root of the project folder does not update when you compile the code yourself. A new executable will be generated in ``x64 > Debug`` and you will need to copy the sfml ``.dll`` files into the same folder in order to run the executable.

## Functionality

The CA Engine is still a work in progress. Should you experience any problems or have any suggestions please [Contact Us](https://lewisn3142.github.io/contact_page/contact.html).

Currently, the Debug version of The CA Engine (Release version TBC) includes the following functionality:

 - Sparse Matrix Game of Life Algorithm
   - Variable starting population
   - Random initial population
   - Variable neighbourhood types (Moore, Newman)
     
 - Square Tiling Generator
   - Variable grid size
   - Variable boundary conditions (Plane, Cylinder, Torus, Real Projective Space, Klein Bottle, Moebius Strip)

More information on proposed functionality can be found on the relevant project page (link TBC). As a brief overview, here are some features that are currently in development:

 - New regular tilings (Hexagons, Triangles).
 - Irregular/Aperiodic tilings (Penrose, Einstein).
 - Import graphs as matrices.
 - Save import settings and export results.

## Settings

### Using Existing Functionality
TBC

### Implementing Your Own Tilings
TBC

### Implementing Your Own Algorithms
TBC

## License and Terms

The material contained within this repository (including but not limited to code, program files, and their documentation) is distributed under a CC-BY-NC-SA license. The material contained within this repository is believed to be safe, true, and accurate. We accept no responsibility for losses incurred, whether directly or indirectly, resulting from incorrect use of this material. Should you wish to license this material under any other terms, claim copyright to any material presented herein, or have any issue with the material herein, please [Contact Us](https://lewisn3142.github.io/contact_page/contact.html).

## Acknowledgements

This project was undertaken under the kind supervision of [Dr. Jamie Gabbay](https://gabbay.org.uk/) of Heriot-Watt University. I am very thankful for him being so amenable to the idea of collaboration when I initially reached out, as well as for his help and advice thereafter.

## References
TBC
