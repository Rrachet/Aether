#pragma once
#include <cstdint>
#include <iosfwd>

namespace aether {

/// The fixed-size start of a GGUF file (format spec: github.com/ggml-org/ggml, docs/gguf.md).
struct GgufHeader {
  std::uint32_t version = 0;            ///< format version (2 or 3 supported)
  std::uint64_t tensor_count = 0;       ///< number of tensors described after the metadata
  std::uint64_t metadata_kv_count = 0;  ///< number of key/value metadata entries
};

/// Reads the GGUF header from the current position of `in`.
///
/// Layout, all little-endian: 4 bytes magic "GGUF", uint32 version,
/// uint64 tensor_count, uint64 metadata_kv_count.
///
/// Throws std::runtime_error when the magic is wrong, the version is not 2 or 3,
/// or the stream ends early. See docs/GGUF_MILESTONE.md.
GgufHeader read_gguf_header(std::istream& in);

}  // namespace aether
