#include "util.hh"
#include <cppcodec/base64_rfc4648.hpp>
#include <algorithm>

std::string MyGame::trim(std::string const& s) {
  auto wsfront = std::find_if_not(s.begin(),
                                  s.end(),
                                  [](int c) { return std::isspace(c); });
  return std::string(wsfront,
                     std::find_if_not(s.rbegin(),
                                      std::string::const_reverse_iterator(wsfront),
                                      [](int c){return std::isspace(c);}).base());
}

std::vector<uint8_t> MyGame::decodeBase64(std::string const& encoded) {
  using base64 = cppcodec::base64_rfc4648;

  return base64::decode<std::vector<uint8_t>>(encoded);
}
