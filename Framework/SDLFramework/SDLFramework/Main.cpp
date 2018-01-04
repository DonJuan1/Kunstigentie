#include <iostream>
#include "Config.h"
#include "FWApplication.h"
#include <SDL_events.h>
#include "SDL_timer.h"
#include <time.h>
#include "SparseGraph.h"
#include "StatusBar.h"
#include <ctime>

int main(int args[])
{
	//auto window = Window::CreateSDLWindow();
	auto application = new FWApplication(50,50, 1680, 720);
	if (!application->GetWindow())
	{
		LOG("Couldn't create window...");
		return EXIT_FAILURE;
	}
	
	application->SetTargetFPS(60);
	application->SetColor(Color(255, 10, 40, 255));
	
	SparseGraph graph{ false };
	graph.Load("graph.txt");

	StatusBar statusBar(1280, 0, 400, 720, Color(245, 245, 255,255));
	statusBar.setMisterJansen(graph.getMisterJansen());
	statusBar.setMissesJansen(graph.getMissesJansen());
	statusBar.setSheep(graph.getSheep());

	//while (true){}
	while (application->IsRunning())
	{
		application->StartTick();

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
				application->Quit();
				break;
			}
		}
		
		graph.update();

		graph.draw();
		statusBar.draw();

		application->SetColor(Color(0, 0, 0, 255));

		application->EndTick();
	}
		
	return EXIT_SUCCESS;
}