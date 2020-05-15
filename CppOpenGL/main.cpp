#include "Game.h"







int main()
{
	Game game("C++ OpenGL", 640, 480, 4, 5, false);

	
	//Material 0

	

	//Lights

	//MAIN LOOP
	while (!game.getWindowShouldClose())
	{
		//Update Input
		game.update();
		game.render();

	}
	//End of program



	//Delete VAO and Buffers


	return 0;
}