#include "Raycast.h"

int main()
{
	RenderWindow window(VideoMode(640, 480), "KOTOK");
	Raycast rc;

	while (window.isOpen()) {

		Event e;
		while (window.pollEvent(e))
			if (e.type == Event::Closed) window.close();


		rc.player_move();

		window.clear();

		rc.raycast(window);

		window.display();
	}

}