#include "aether/gguf.hpp"

#include <istream>
#include <stdexcept>

namespace aether {

GgufHeader read_gguf_header(std::istream&) {
  // TODO(milestone 1): implement. See docs/GGUF_MILESTONE.md and tests/test_gguf.cpp.
  throw std::logic_error("read_gguf_header is not implemented yet");
}

}  // namespace aether
