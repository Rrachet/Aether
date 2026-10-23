// Tests for the GGUF header reader (docs/GGUF_MILESTONE.md). They fail until
// aether::read_gguf_header is implemented, so they are not part of the default build:
//   cmake -S . -B build -DAETHER_BUILD_GGUF_TESTS=ON && cmake --build build
//   ctest --test-dir build --output-on-failure -R gguf
#include "aether/gguf.hpp"

#include <cstdint>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace {

int failures = 0;

#define CHECK(cond)                                                              \
  do {                                                                           \
    if (!(cond)) {                                                               \
      std::cerr << "FAILED " << __FILE__ << ":" << __LINE__ << ": " #cond "\n"; \
      ++failures;                                                                \
    }                                                                            \
  } while (0)

template <typename T>
void put_le(std::string& out, T value) {
  for (std::size_t i = 0; i < sizeof(T); ++i) {
    out.push_back(static_cast<char>((static_cast<std::uint64_t>(value) >> (8 * i)) & 0xFF));
  }
}

std::string header_bytes(const std::string& magic, std::uint32_t version, std::uint64_t tensors,
                         std::uint64_t kvs) {
  std::string bytes = magic;
  put_le(bytes, version);
  put_le(bytes, tensors);
  put_le(bytes, kvs);
  return bytes;
}

template <typename Fn>
bool throws_runtime_error(Fn&& fn) {
  try {
    fn();
  } catch (const std::runtime_error&) {
    return true;
  } catch (...) {
    return false;  // wrong exception type, e.g. the not-implemented std::logic_error
  }
  return false;
}

void reads_a_valid_v3_header() {
  std::istringstream in(header_bytes("GGUF", 3, 291, 25));
  aether::GgufHeader header = aether::read_gguf_header(in);
  CHECK(header.version == 3);
  CHECK(header.tensor_count == 291);
  CHECK(header.metadata_kv_count == 25);
}

void accepts_version_2() {
  std::istringstream in(header_bytes("GGUF", 2, 1, 2));
  CHECK(aether::read_gguf_header(in).version == 2);
}

void reads_values_wider_than_32_bits() {
  std::istringstream in(header_bytes("GGUF", 3, 0x1'0000'0001ULL, 0x2'0000'0002ULL));
  aether::GgufHeader header = aether::read_gguf_header(in);
  CHECK(header.tensor_count == 0x1'0000'0001ULL);
  CHECK(header.metadata_kv_count == 0x2'0000'0002ULL);
}

void leaves_the_stream_after_the_header() {
  std::istringstream in(header_bytes("GGUF", 3, 1, 1) + "NEXT");
  aether::read_gguf_header(in);
  std::string rest;
  in >> rest;
  CHECK(rest == "NEXT");
}

void rejects_a_wrong_magic() {
  std::istringstream in(header_bytes("GGML", 3, 1, 1));
  CHECK(throws_runtime_error([&] { aether::read_gguf_header(in); }));
}

void rejects_unsupported_versions() {
  for (std::uint32_t version : {0u, 1u, 4u, 99u}) {
    std::istringstream in(header_bytes("GGUF", version, 1, 1));
    CHECK(throws_runtime_error([&] { aether::read_gguf_header(in); }));
  }
}

void rejects_a_truncated_file() {
  std::string full = header_bytes("GGUF", 3, 1, 1);
  for (std::size_t length : {std::size_t{0}, std::size_t{3}, std::size_t{4}, std::size_t{10}, full.size() - 1}) {
    std::istringstream in(full.substr(0, length));
    CHECK(throws_runtime_error([&] { aether::read_gguf_header(in); }));
  }
}

}  // namespace

int main() {
  reads_a_valid_v3_header();
  accepts_version_2();
  reads_values_wider_than_32_bits();
  leaves_the_stream_after_the_header();
  rejects_a_wrong_magic();
  rejects_unsupported_versions();
  rejects_a_truncated_file();
  if (failures == 0) std::cout << "GGUF header tests passed\n";
  return failures == 0 ? 0 : 1;
}
