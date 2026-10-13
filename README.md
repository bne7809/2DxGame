# 2DxGame

A native 2D game / renderer built from scratch on raw Win32 and Direct3D 11 in C++, running **without the C runtime**.

This is a "handmade"-style project: no engine, no framework, and no CRT. The goal was to understand the Windows platform layer and the Direct3D 11 pipeline directly, and to manage memory and resources myself.

## Highlights

- **No C runtime.** Custom `WinMainCRTStartup` entry point, linked with `/NODEFAULTLIB`; exceptions and RTTI disabled (`/EHs- /EHc- /GR- /D_HAS_EXCEPTIONS=0`), stack checks off (`/GS-`), with the few required runtime symbols provided by hand (`src/remcrt.cpp`).
- **Manual memory management.** A custom arena allocator plus a templated object pool (`pool<T>`) using placement `new`, instead of the standard allocator.
- **Direct3D 11 rendering.** Swap chain and render target set up directly against the D3D11 API; HLSL vertex and pixel shaders compiled offline with `fxc`.
- **Animated sprites.** Sprite-sheet rendering with per-frame animation, textures loaded via the Windows Imaging Component (WIC).
- **Input and game loop.** A `PeekMessage` game loop with a small input-command buffer (WASD movement, run), a frame timer, and an entity/animation system.

## Tech

C++ and C, HLSL shaders, Win32 API, Direct3D 11, DirectXMath, WIC. Builds with MSVC (`cl`, `fxc`, `link`).

## Build

Requires Windows, the Windows SDK, and the MSVC toolchain (`cl.exe`, `fxc.exe`, `link.exe`) on the `PATH`. The easiest way is to run from a **Developer Command Prompt for Visual Studio**:

```bat
build.bat
```

This compiles the HLSL shaders to `shader_out\`, builds the sources, and links `dxgame.exe` against the Windows and Direct3D libraries directly (no default libraries).

## Controls

- **W / A / S / D** — move
- **K** — run

## Project structure

```
include/   # headers (arena, pool, entity, shader, sprite_sheet, timer, input_buffer, ...)
src/        # main.cpp (unity build), remcrt.cpp (CRT stubs), and included .cpp units
shader/     # HLSL vertex and pixel shaders
build.bat   # MSVC build script
```

## Notes

The project uses a unity build: `src/main.cpp` includes the other translation units directly, which keeps the build simple and the whole program in one compilation unit.
