# Milestone 1: read the GGUF header

Goal: `aether::read_gguf_header` (in `include/aether/gguf.hpp`, stub in `src/gguf.cpp`) reads and validates the first
24 bytes of a GGUF model file. This is the first step of the "model loader" stage in the architecture. Tests are in
`tests/test_gguf.cpp`; they fail until you implement the function.

## The format (version 2 and 3)

Little-endian, no padding:

| Offset | Size | Field |
|---|---|---|
| 0 | 4 bytes | magic: the ASCII bytes `GGUF` |
| 4 | uint32 | version (2 or 3) |
| 8 | uint64 | tensor_count |
| 16 | uint64 | metadata_kv_count |

Reference: the GGUF section of the [ggml repository](https://github.com/ggml-org/ggml/blob/master/docs/gguf.md).
Check it yourself rather than trusting this table. Version 1 used 32-bit counts and is out of scope.

## Steps

1. Read 4 bytes and compare them to `GGUF`; throw `std::runtime_error` if they differ or the stream ends early.
2. Read the version as a little-endian `uint32` and reject anything other than 2 or 3.
3. Read the two `uint64` counts the same way.
4. Write a small helper for "read N bytes as a little-endian integer" and use it for every field. Do not
   `reinterpret_cast` the struct: that breaks on big-endian machines and on padding.
5. Run the tests until they pass:

```bash
cmake -S . -B build -DAETHER_BUILD_TESTS=ON -DAETHER_BUILD_GGUF_TESTS=ON
cmake --build build
ctest --test-dir build --output-on-failure
```

6. Once they pass, remove the `AETHER_BUILD_GGUF_TESTS` option in `CMakeLists.txt` so the test runs in CI by default.

## Then (milestone 2)

Parse the metadata key/value entries that follow the header: a string key (`uint64` length + bytes), a `uint32`
value type, then the value. Start with the scalar types, then strings and arrays. Add a test with a hand-built
byte buffer for each type, the same way `tests/test_gguf.cpp` builds headers.

## Why this milestone

It is small enough to finish in a sitting, touches binary parsing, endianness and error handling, and gives you
something real to explain in an interview: what the format is, why you wrote a safe reader, and how you tested it.
