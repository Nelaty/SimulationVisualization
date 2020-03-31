#include "EmptyScene.h"

EmptyScene::EmptyScene(const std::string& name, SimulationWindow* window)
	: SimulationScene(name, window)
{
}

EmptyScene::~EmptyScene()
{
}

void EmptyScene::tick(const float timeDelta)
{
	SimulationScene::tick(timeDelta);
}

void EmptyScene::reset()
{
}
