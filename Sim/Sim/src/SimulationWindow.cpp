#include "SimulationWindow.h"
#include "SimulationScene.h"

#include "EC3D/Core/CubeGeometry.h"
#include "EC3D/Core/SphereGeometry.h"
#include "EC3D/Core/CylinderGeometry.h"
#include "EC3D/Core/RectangleGeometry.h"

#include "EC3D/Core/Camera.h"
#include "EC3D/Core/Viewport.h"

#include "Examples/FallingCubeScene.h"

SimulationWindow::SimulationWindow(const unsigned width,
                                   const unsigned height,
								   const std::string& title)
	: ec::Window(width, height, title)
{
	initAssets();
	initCameras();
	initScenes();

	m_currentScene = 0;

	m_cooldownSceneChange = 0.2f;
	m_cooldownSceneChangeCurrent = 0.0f;

	// Set a specific start scene
	changeScene(m_scenes["example"]);
}

SimulationWindow::~SimulationWindow()
= default;

void SimulationWindow::tick(const float timeDelta)
{
	m_cameraController->tick(timeDelta);


	m_cooldownSceneChangeCurrent += timeDelta;

	// Get the keyboard
	auto& deviceRegistry = getEventSystem().getDeviceRegistry();
	auto keyboard = deviceRegistry.getKeyboard();

	// Check if scene should be changed
	if(m_cooldownSceneChangeCurrent > m_cooldownSceneChange
	   && !m_scenes.empty())
	{
		// Next scene
		if(keyboard->isKeyDown(ec::Keyboard::RIGHT))
		{
			m_currentScene = (m_currentScene + 1) % m_scenes.size();
			changeScene(getSceneByIndex(m_currentScene));

			m_cooldownSceneChangeCurrent = 0.0f;
		}
		// Previous scene
		else if(keyboard->isKeyDown(ec::Keyboard::LEFT))
		{
			--m_currentScene;
			if(m_currentScene < 0)
			{
				m_currentScene = m_scenes.size() - 1;
			}
			changeScene(getSceneByIndex(m_currentScene));
			m_cooldownSceneChangeCurrent = 0.0f;
		}
	}
	
}

void SimulationWindow::initCameras()
{
	// Viewport contains the whole window
	ec::Viewport viewport(glm::vec2(SimulationScene::getViewportSize().x, 0.0f),
						  glm::vec2(1.0f, 1.0f));
	m_camera = new ec::Camera(nullptr, viewport);

	m_cameraController = std::make_unique<ec::CameraController>();
	m_eventSystem.registerInputListener(m_cameraController.get());
}

void SimulationWindow::initScenes()
{
	// Particle engine scenes
	m_scenes["example"] = new FallingCubeScene("example", this);
	prepareScene(m_scenes["example"]);

	// ADD NEW SCENES HERE
	// ...
}

void SimulationWindow::changeScene(SimulationScene* scene)
{
	if(!scene) return;

	// Deactivate the current scene if necessary
	if(m_activeScene)
	{
		m_lastScene = m_activeScene;
		m_lastScene->disable();	
	}

	// Update the window title and enable the new scene
	setTitle(scene->getName().c_str());
	m_activeScene = scene;
	scene->enable();

	// Control the camera of the new scene
	m_cameraController->setCamera(scene->getCamera());

	// Use the camera of the new scene for rendering
	const auto sceneRenderer = scene->getSceneRenderer();
	m_renderer->changeRenderer(sceneRenderer);
}

void SimulationWindow::changeScene(const std::string& sceneName)
{
	changeScene(m_scenes[sceneName]);
}

const ec::ResourceRegistry<ec::Drawable>& SimulationWindow::getDrawableRegistry() const
{
	return m_drawableRegistry;
}

const ec::ResourceRegistry<ec::Geometry>& SimulationWindow::getGeometryRegistry() const
{
	return m_geometryRegistry;
}

const ec::ResourceRegistry<ec::Material>& SimulationWindow::getMaterialRegistry() const
{
	return m_materialRegistry;
}

void SimulationWindow::initShaders()
{
	const std::string path = s_resourcesPath + "Shaders/";

	m_shaderManager.addShader("basic",
							  path + "basic.vert",
							  path + "basic.frag");

	m_shaderManager.addShader("gui",
							  path + "gui.vert",
							  path + "gui.frag");

	m_shaderManager.addShader("text",
							  path + "text.vert",
							  path + "text.frag");

	m_renderer->init(m_shaderManager.getShader("gui"),
					 m_shaderManager.getShader("text"));
}

void SimulationWindow::initAssets()
{
	initTextures();
	initShaders();
	initMaterials();
	initGeometries();
	initDrawables();
}

void SimulationWindow::initGeometries()
{
	m_geometryRegistry.registerResource(new ec::CubeGeometry(), "cube");
	m_geometryRegistry.registerResource(new ec::SphereGeometry(), "sphere");
	m_geometryRegistry.registerResource(new ec::CylinderGeometry(), "cylinder");
	m_geometryRegistry.registerResource(new ec::RectangleGeometry(), "rectangle");
}

void SimulationWindow::initMaterials()
{
	const std::string path = s_resourcesPath + "Textures/";

	auto matBotWall = new ec::Material();
	matBotWall->addDiffuseTextureFromPath((path + "wood_04.jpg").c_str());
	auto matSideWall = new ec::Material();
	matSideWall->addDiffuseTextureFromPath((path + "wall_01.jpg").c_str());
	auto matBackWall = new ec::Material();
	matBackWall->addDiffuseTextureFromPath((path + "wall_00.jpg").c_str());
	auto matRock = new ec::Material();
	matRock->addDiffuseTextureFromPath((path + "stone_00.jpg").c_str());

	m_materialRegistry.registerResource(matBotWall, "wood");
	m_materialRegistry.registerResource(matSideWall, "side_wall");
	m_materialRegistry.registerResource(matBackWall, "back_wall");
	m_materialRegistry.registerResource(matRock, "matRock");

	// ADD NEW MATERIALS HERE IF YOU WANT TO REUSE THEM
	// ...


	// REGISTER THE NEW MATERIALS HERE
	// ...
}

void SimulationWindow::initTextures()
{
}

void SimulationWindow::initDrawables()
{
	auto cubeGeometry = m_geometryRegistry.getResource("cube");
	auto shader = m_shaderManager.getShader("basic");

	auto botWall = new ec::Drawable(cubeGeometry, 
									m_materialRegistry.getResource("wood"),
									shader);
	auto sideWall = new ec::Drawable(cubeGeometry, 
									 m_materialRegistry.getResource("side_wall"), 
									 shader);
	auto backWall = new ec::Drawable(cubeGeometry, 
									 m_materialRegistry.getResource("back_wall"),
									 shader);
	auto cannon = new ec::Drawable(m_geometryRegistry.getResource("cylinder"), 
								   m_materialRegistry.getResource("matRock"), 
								   shader);
	auto sphere = new ec::Drawable(m_geometryRegistry.getResource("sphere"),
								   m_materialRegistry.getResource("matRock"),
								   shader);

	auto cube = new ec::Drawable(cubeGeometry,
								 m_materialRegistry.getResource("wood"),
								 shader);

	m_drawableRegistry.registerResource(botWall, "bot_wall");
	m_drawableRegistry.registerResource(sideWall, "side_wall");
	m_drawableRegistry.registerResource(backWall, "back_wall");
	m_drawableRegistry.registerResource(cannon, "cannon");
	m_drawableRegistry.registerResource(sphere, "sphere");
	m_drawableRegistry.registerResource(cube, "cube");

	// ADD NEW DRAWABLES HERE IF YOU WANT TO REUSE THEM
	// ...


	// REGISTER THE NEW DRAWABLES HERE
	// ...
}

void SimulationWindow::prepareScene(SimulationScene* scene)
{
	if(scene == nullptr)
	{
		printf("Error: prepareScene(...): Scene is invalid!\n");
		return;
	}

	scene->disable();
	auto& frame = scene->getSceneRenderer()->getFrame();
	frame.addCameraBack(m_camera);
	m_sceneSystem.registerScene(scene);
}

SimulationScene* SimulationWindow::getSceneByIndex(const int index)
{
	if(m_scenes.empty())
	{
		return nullptr;
	}
	if(index >= 0 && index < m_scenes.size())
	{
		int i = 0;
		for(auto& it : m_scenes)
		{
			if(i == index)
			{
				return it.second;
			}
			++i;
		}
	}
	return nullptr;
}

const std::string SimulationWindow::s_resourcesPath = "./../../EyeCandy3D/Resources/";