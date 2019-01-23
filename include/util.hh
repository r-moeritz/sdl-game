#ifndef UTIL_HH
#define UTIL_HH

#include <string>
#include <cstdint>
#include <vector>

namespace MyGame {
  std::string trim(std::string const&);
  std::vector<uint8_t> decodeBase64(std::string const&);
}

#endif // #ifndef UTIL_HH
