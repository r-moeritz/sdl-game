#include "SDL2/SDL.h"
#include "playstate.hh"
#include "game.hh"
#include "player.hh"
#include "enemy.hh"
#include "inputhandler.hh"
#include "gamestatemachine.hh"
#include "pausestate.hh"
#include "gameoverstate.hh"

My::PlayState::PlayState()
  : _pTextureManager(TextureManager::Instance()) {
}

void My::PlayState::update() {
  if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
    std::shared_ptr<GameState> pPauseState(new PauseState());
    GameStateMachine::Instance()->pushState(pPauseState);
  }

  for (auto i = 0; i != _gameObjects.size(); ++i) {
    _gameObjects[i]->update();
  }

  // TODO This feels very hacky!
  auto p1 = std::dynamic_pointer_cast<SDLGameObject>(_gameObjects[0]);
  auto p2 = std::dynamic_pointer_cast<SDLGameObject>(_gameObjects[1]);

  if (collision(p1, p2)) {
    std::shared_ptr<GameState> pGameOverState(new GameOverState());
    GameStateMachine::Instance()->pushState(pGameOverState);
  }
}

void My::PlayState::render() {
  for (auto i = 0; i != _gameObjects.size(); ++i) {
    _gameObjects[i]->draw();
  }
}

bool My::PlayState::onEnter() {
  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Entering PLAY state...");

  if (!_pTextureManager->load("assets/helicopter.png", "helicopter",
                              Game::Instance()->renderer())) {
    return false;
  }

  if (!_pTextureManager->load("assets/helicopter2.png", "helicopter2",
                              Game::Instance()->renderer())) {
    return false;
  }

  std::shared_ptr<GameObject> player(new Player(new LoaderParams(500, 100, 128, 55,
                                                                 "helicopter"), 6));
  std::shared_ptr<GameObject> enemy(new Enemy(new LoaderParams(100, 100, 128, 55,
                                                               "helicopter2"), 6));

  _gameObjects.push_back(player);
  _gameObjects.push_back(enemy);

  return true;
}

bool My::PlayState::onExit() {
  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Exiting PLAY state...");

  for (auto i = 0; i != _gameObjects.size(); ++i) {
    _gameObjects[i]->clean();
  }

  _pTextureManager->clearFromTextureMap("helicopter");

  return true;
}

bool My::PlayState::collision(std::shared_ptr<SDLGameObject> pA, std::shared_ptr<SDLGameObject> pB) {
  // Sides of rect A
  auto leftA = pA->position().x();
  auto rightA = pA->position().x() + pA->width();
  auto topA = pA->position().y();
  auto bottomA = pA->position().y() + pA->height();

  // Sides of rect B
  auto leftB = pB->position().x();
  auto rightB = pB->position().x() + pB->width();
  auto topB = pB->position().y();
  auto bottomB = pB->position().y() + pB->height();

  // Are all of the sides of rect A inside of rect B?
  return (bottomA > topB && topA < bottomB
          && rightA > leftB && leftA < rightB);
}
