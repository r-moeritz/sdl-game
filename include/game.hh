#ifndef GAME_HH
#define GAME_HH

#include <memory>

struct SDL_Renderer;

namespace MyGame {

  struct Game {

    ~Game();
    Game(Game&&);
    Game& operator=(Game&&);

    bool init(const char* title, int xpos, int ypos,
              int height, int width, bool fullscreen);
    void render();
    void clean();
    void update();
    void handleEvents();
    void quit();

    bool running() const;
    SDL_Renderer* renderer() const;

    static Game* Instance();

  private:

    struct Impl;
    std::unique_ptr<Impl> _pImpl;

    Game();

    static Game* s_pInstance;
  };
}

#endif
