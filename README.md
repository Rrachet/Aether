# Aether

A local AI inference runtime built from scratch in C++20. It is an early foundation: the CPU tensor core is in place and tested, and model loading and transformer execution are planned, not built.

## Status: v0.1 CPU foundation

Working today:
- Contiguous `float32` tensors with shape validation
- Reference matrix multiplication
- Linear-layer primitive
- Deterministic, seeded temperature sampling
- CMake build with CTest unit tests and a small `aether-run` demo binary

Not built yet: GGUF loading, tokenization, attention, KV cache, quantized weights and transformer execution. This milestone deliberately does not claim model loading or inference.

## Requirements

- A C++20 compiler (tested with GCC 13)
- CMake 3.20 or newer

## Build, test, run

```bash
cmake -S . -B build -DAETHER_BUILD_TESTS=ON
cmake --build build
ctest --test-dir build --output-on-failure
./build/aether-run
```

`aether-run` prints a banner and one sampled token from the runtime.

## Layout

```text
include/aether/   Public headers (tensor.hpp, runtime.hpp)
src/              Tensor, runtime and the aether-run entry point
tests/            Unit tests (CTest)
CMakeLists.txt    Static library `aether`, executable `aether-run`, tests
```

## Architecture (target)

```text
model loader -> tensor storage -> kernels -> transformer -> logits -> sampler -> token stream
```

Today the tensor storage, a reference kernel and the sampler exist. The rest of the pipeline is the roadmap.

## Roadmap

1. GGUF reader and BPE tokenizer
2. Attention and KV cache
3. Q4/Q8 quantized weights
4. Transformer execution and streaming CLI
5. SIMD kernels and benchmarks

## License

[MIT](LICENSE) © Amarnath Mishra
