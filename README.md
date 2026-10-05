# Aether

High-performance local AI inference runtime built from scratch in C++.

## v0.1 CPU foundation

Aether now has a real C++20 runtime core:
- contiguous float32 tensors
- shape validation
- reference matrix multiplication
- deterministic seeded temperature sampling
- linear-layer primitive
- CMake + CTest

Build:
cmake -S . -B build -DAETHER_BUILD_TESTS=ON
cmake --build build
ctest --test-dir build --output-on-failure

Architecture:
model loader -> tensor storage -> kernels -> transformer -> logits -> sampler -> token stream

Next: GGUF reader, BPE tokenizer, KV cache, attention, Q4/Q8 weights, transformer execution, SIMD kernels, streaming CLI, benchmarks.

This milestone deliberately does not claim model loading or transformer inference yet.
