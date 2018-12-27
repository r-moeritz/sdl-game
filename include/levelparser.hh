#ifndef LEVELPARSER_HH
#define LEVELPARSER_HH

#include <memory>

namespace MyGame {

  struct Level;
  using LevelPtr = std::shared_ptr<Level>;

  struct LevelParser {

    LevelParser();
    ~LevelParser();
    LevelParser(LevelParser&&);
    LevelParser& operator=(LevelParser&&);

    LevelPtr parseLevel(const char* levelFile);

  private:

    struct Impl;
    std::unique_ptr<Impl> _pImpl;
  };
}

#endif // #ifndef LEVELPARSER_HH
