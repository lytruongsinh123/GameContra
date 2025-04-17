#pragma once
#ifndef SDLGAME_SCENEMANAGER_H
#define SDLGAME_SCENEMANAGER_H

#include <SDL.h>
#include <vector>
#include <memory>
#include "Scenes/LevelSelect.h"
#include "Scenes/Scene.h"
#include "Scenes/SceneLevel1.h"
#include "Scenes/SceneLevel2.h"
#include "Scenes/SceneLevel3.h"
#include "Scenes/SceneMainMenu.h"
#include "Scenes/WinScene.h"
#include "Scenes/GameScenes.h"

/**
 * @brief Manager class handling game state using SDL
 */
class SceneManager
{
public:
	SceneManager(SDL_Renderer* rendererRef, const std::shared_ptr<Scene>& scene);
	explicit SceneManager(SDL_Renderer* rendererRef);
	virtual ~SceneManager() = default;

	void addScene(const std::shared_ptr<Scene>& scene);
	void addGameScenes();
	std::shared_ptr<Scene> sceneFactory(const GameScene& gameScene);
	void setCurrentScene(const std::shared_ptr<Scene>& scene);
	[[nodiscard]] GameScene getCurrentScene() const;

	void checkCurrentSceneState();
	[[nodiscard]] bool onExit() const { return exitGame; }

	virtual void handleEvent(const SDL_Event& event);
	virtual void update(float deltaTime);
	virtual void render();

protected:
	SDL_Renderer* renderer;
	std::shared_ptr<Scene> currentScene;
	std::vector<std::shared_ptr<Scene>> scenes;
	SceneStatus currentSceneStatus;
	bool exitGame = false;
};

#endif // SDLGAME_SCENEMANAGER_H