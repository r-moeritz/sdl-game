#include "menustate.hh"
#include "pausestate.hh"
#include "gamestatemachine.hh"
#include "texturemanager.hh"
#include "menubutton.hh"
#include "SDL2/SDL.h"

using namespace MyGame;

void PauseState::update() {
  for (auto i = 0; i != _gameObjects.size(); ++i) {
    _gameObjects[i]->update();
  }
}

void PauseState::render() {
  for (auto i = 0; i != _gameObjects.size(); ++i) {
    _gameObjects[i]->draw();
  }
}

bool PauseState::onEnter() {
  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Entering PAUSE state...");

  if (!TextureManager::Instance()->load("assets/resume.png",
                                        "resumebutton",
                                        Game::Instance()->renderer())) {
    return false;
  }

  if (!TextureManager::Instance()->load("assets/main.png",
                                        "mainbutton",
                                        Game::Instance()->renderer())) {
    return false;
  }

  std::shared_ptr<GameObject> pauseButton(new MenuButton(new LoaderParams(200, 100, 200, 80,
                                                                          "mainbutton"), s_main));
  std::shared_ptr<GameObject> resumeButton(new MenuButton(new LoaderParams(200, 300, 200, 80,
                                                                           "resumebutton"), s_resume));

  _gameObjects.push_back(pauseButton);
  _gameObjects.push_back(resumeButton);

  return true;
}

bool PauseState::onExit() {
  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Exiting PAUSE state...");

  for (auto i = 0; i != _gameObjects.size(); ++i) {
    _gameObjects[i]->clean();
  }

  TextureManager::Instance()->clearFromTextureMap("mainbutton");
  TextureManager::Instance()->clearFromTextureMap("resumebutton");

  return true;
}

void PauseState::s_main() {
  std::shared_ptr<GameState> pMenuState(new MenuState());
  GameStateMachine::Instance()->changeState(pMenuState);
}

void PauseState::s_resume() {
  GameStateMachine::Instance()->popState();
}
