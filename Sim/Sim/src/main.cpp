#include "SimulationWindow.h"

#include "EC3D/Gui/MiniAgui.h"
#include "EC3D/Core/Application.h"

int main(int argc, char** argv)
{
	// Create a new application. This is the main class of every
	// program.
	ec::Application app;

	// Create a new window.
	// The new window should be an instance of the class "SimulationWindow".
	// In this window we will create all of our physics simulation scenes and
	// initialize resources we need to visualize the simulation (materials,
	// geometry, shaders, etc.)
	const unsigned int width = 1024;
	const unsigned int height = 1024;
	const auto title = "EyeCandy Example Project";

	app.createWindow<SimulationWindow>(width, height, "Game Physik Simulation", "simulation");

	// Initialize the gui.
	ec::MiniAgui::init();

	// Start the application.
	app.startMainLoop();
}