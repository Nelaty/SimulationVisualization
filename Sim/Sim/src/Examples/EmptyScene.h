#pragma once
#include "SimulationScene.h"
#include "SimulationWindow.h"

#include <string>

class EmptyScene : public SimulationScene
{
public:
	explicit EmptyScene(const std::string& name, SimulationWindow* window);
	~EmptyScene();

	void tick(float timeDelta) override;
	void reset() override;

};