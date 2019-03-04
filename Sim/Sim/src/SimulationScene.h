#pragma once
#include "EC3D/Core/Scene.h"
#include "EC3D/Core/Keyboard.h"
#include "EC3D/Core/Mouse.h"
#include "EC3D/Core/Camera.h"

#include "PhysicInterfaces/PhysicsEngineWrapper.h"
#include "SimulationWindow.h"

#include <memory>

namespace ec
{
	class SceneRenderer;
}

/**
 * Abstract class for scenes with physic simulation.
 */
class SimulationScene : public ec::Scene
{
public:
	explicit SimulationScene(const std::string& name, SimulationWindow* window);
	virtual ~SimulationScene();

	void tick(float timeDelta) override;

	ec::SceneRenderer* getSceneRenderer() const;
	ec::Camera* getCamera() const;

	void setViewportSize(const glm::vec2& size) const;

	virtual void reset();

	static const glm::vec2& getViewportPosition();
	static const glm::vec2& getViewportSize();

protected:

	SimulationWindow* m_window;
	PhysicsEngineWrapper m_physicsEngine;

	std::unique_ptr<ec::SceneRenderer> m_sceneRenderer;
	std::unique_ptr<ec::Camera> m_camera;

	ec::Keyboard* m_keyboard;
	ec::Mouse* m_mouse;

private:
	void initSimulationScene();

	static glm::vec2 s_viewportSize;
	static glm::vec2 s_viewportPosition;
};