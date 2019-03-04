#include "SimulationScene.h"

#include "EC3D/Core/SceneRenderer.h"

#include "R3D/RigidBodyEngine/RigidBody.h"
#include "R3D/RigidBodyEngine/CollisionSphere.h"

SimulationScene::SimulationScene(const std::string& name, SimulationWindow* window)
	: ec::Scene(name),
	m_window{window}
{
	initSimulationScene();
}

SimulationScene::~SimulationScene()
= default;

void SimulationScene::tick(const float timeDelta)
{
	//printf("Timedelta %f, fps %f\n", timeDelta, 1.0f / timeDelta);
	m_physicsEngine.tick(timeDelta);
}

ec::SceneRenderer* SimulationScene::getSceneRenderer() const
{
	return m_sceneRenderer.get();
}

ec::Camera* SimulationScene::getCamera() const
{
	return m_camera.get();
}

void SimulationScene::setViewportSize(const glm::vec2& size) const
{
	s_viewportSize = size;

	const ec::Viewport viewport(glm::vec2(0.0f, 0.0f), s_viewportSize);
	m_camera->setViewport(viewport);
}

void SimulationScene::reset()
{	
}

const glm::vec2& SimulationScene::getViewportPosition()
{
	return s_viewportPosition;
}

const glm::vec2& SimulationScene::getViewportSize()
{
	return s_viewportSize;
}

void SimulationScene::initSimulationScene()
{
	m_sceneRenderer = std::make_unique<ec::SceneRenderer>();
	m_camera = std::make_unique<ec::Camera>(this);
	m_camera->setFov(glm::radians(60.0f));
	m_camera->setTranslation(glm::vec3(0.0f, 0.0f, 10.0f));

	const ec::Viewport viewport(glm::vec2(0.0f, 0.0f), s_viewportSize);
	m_camera->setViewport(viewport);

	ec::Frame frame;
	frame.addCameraBack(m_camera.get());
	m_sceneRenderer->setFrame(frame);

	// Get input devices
	auto& deviceRegistry = m_window->getEventSystem().getDeviceRegistry();
	m_keyboard = deviceRegistry.getKeyboard();
	m_mouse = deviceRegistry.getMouse();
}

glm::vec2 SimulationScene::s_viewportSize = glm::vec2(1.0f, 1.0f);
glm::vec2 SimulationScene::s_viewportPosition = glm::vec2(0.0f, 0.0f);
