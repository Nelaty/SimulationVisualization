#pragma once
#include "EC3D/Core/Window.h"
#include "EC3D/Core/CameraController.h"

#include <string>

namespace ec
{
	class Camera;
	class SceneRenderer;
}

class SimulationScene;

/**
 * This window contains a set of scenes, which we wish to simulate.
 * It has multiple resource registries to manage materials, geometry,
 * drawables and shaders used for visualization.
 */
class SimulationWindow : public ec::Window
{
public:
	explicit SimulationWindow(unsigned int width,
							  unsigned int height,
							  const std::string& title);
	~SimulationWindow();

	void tick(float timeDelta) override;

	void initCameras();
	void initScenes();

	/** Change the currently viewed scene. */
	void changeScene(SimulationScene* scene);
	/** Change the currently viewed scene. */
	void changeScene(const std::string& sceneName);

	/** Get the drawable registry. */
	const ec::ResourceRegistry<ec::Drawable>& getDrawableRegistry() const;
	/** Get the geometry registry. */
	const ec::ResourceRegistry<ec::Geometry>& getGeometryRegistry() const;
	/** Get the material registry. */
	const ec::ResourceRegistry<ec::Material>& getMaterialRegistry() const;

private:
	/** Assets initialization. */
	void initAssets();
	void initShaders();
	void initGeometries();
	void initMaterials();
	void initTextures();
	void initDrawables();

	/** Prepare a new scene. */
	void prepareScene(SimulationScene* scene);

	/** Scenes */
	SimulationScene* m_lastScene;
	SimulationScene* m_activeScene;
	std::map<std::string, SimulationScene*> m_scenes;
	int m_currentScene;
	SimulationScene* getSceneByIndex(int index);

	float m_cooldownSceneChange;
	float m_cooldownSceneChangeCurrent;

	/** Camera */
	ec::Camera* m_camera;
	std::unique_ptr<ec::CameraController> m_cameraController;

	static const std::string s_resourcesPath;
};