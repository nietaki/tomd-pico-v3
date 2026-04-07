# AGENTS.md - Development Guidelines for AI Agents

This document provides essential information for AI coding agents working in this repository.

## Project Overview

This is a C++17 project targeting the PicoSystem handheld gaming device (Raspberry Pi RP2040). It uses:
- PicoSystem SDK: https://github.com/pimoroni/picosystem
- Pico SDK: https://github.com/raspberrypi/pico-sdk
- API documentation: https://wiki.picosystem.com/en/c++/cheatsheet

## Build Commands

### Full Build
```bash
make build
```
This will:
1. Generate build files using CMake (if needed)
2. Compile the project with `-j8` parallel jobs
3. Output `tomd.uf2` file in `build/` directory

### Clean Build
```bash
make clean
```
Removes all build artifacts.

### Deploy to Device
```bash
make copy
```
Copies the compiled `.uf2` file to the mounted PicoSystem device at `/Volumes/RPI-RP2/`.

### Manual Build (Alternative)
```bash
cd build && cmake .. && make -j8
```

## Testing

**No test suite currently exists.** This is an embedded systems project without unit tests. Testing is done by:
1. Building and deploying to hardware
2. Manual visual/gameplay verification
3. Visual inspection via LED/screen output

## Linting and Formatting

**No automated linter or formatter is configured.** Follow these guidelines manually:
- Use C++17 features
- No tabs, use 2 spaces for indentation
- Maximum line length: 100 characters
- No trailing whitespace

## Code Style Guidelines

### File Structure

Main source file must be in `CMakeLists.txt`:
```cmake
set(PROJECT_SOURCES
    main.cpp
)
```

### Entry Points

Every PicoSystem game must implement these three functions:

```cpp
void init() {
    // Called once at startup - initialize game state
}

void update(uint32_t tick) {
    // Called 60 times per second - process input, update game logic
}

void draw(uint32_t tick) {
    // Called 60 times per second - render the frame
}
```

### Headers

Always include the PicoSystem header first:
```cpp
#include "picosystem.hpp"

using namespace picosystem;
```

### Naming Conventions

- **Types/Structs/Enums**: `snake_case_t` suffix
  ```cpp
  enum state_t { PLAYING, GAME_OVER };
  struct vec_t { int32_t x, y; };
  ```

- **Variables**: `snake_case`
  ```cpp
  vec_t apple;
  uint32_t score = 0;
  ```

- **Constants**: `UPPER_CASE` or `constexpr`
  ```cpp
  constexpr vec_t bounds{.x = 18, .y = 16};
  constexpr int scale = 6;
  ```

- **Functions**: `snake_case()`
  ```cpp
  void place_apple() { /* ... */ }
  vec_t transform(vec_t v) { /* ... */ }
  ```

- **Struct members**: `snake_case`
  ```cpp
  struct {
    vec_t dir;
    uint32_t length;
    std::vector<vec_t> body;
  } snake;
  ```

### Types

- Use `uint32_t`, `int32_t` etc. instead of `unsigned int`, `int`
- Use `std::vector` for dynamic arrays
- Use structs for data grouping

### Formatting

- **Braces**: Opening brace on same line (K&R style)
  ```cpp
  if(condition) {
      do_thing();
  } else {
      other_thing();
  }
  ```

- **Functions**: Keep them small and focused (ideally <30 lines)
- **Indentation**: 2 spaces per level
- **Blank lines**: Use to separate logical sections of code

### Comments

- Add comments for:
  - Non-obvious logic
  - Algorithm explanations
  - Game state transitions
  - Coordinate transformations

```cpp
// place the apple in a new random location which is not the snake location
// or part of the snakes tail
void place_apple() { /* ... */ }

// convert a map coordinate into its position on the screen
vec_t transform(vec_t v) {
    return {.x = (v.x * scale) + 6, .y = (v.y * scale) + 18};
}
```

## PicoSystem API Quick Reference

### Input
```cpp
button(UP)      // check if button is currently pressed
button(DOWN)
button(LEFT)
button(RIGHT)
button(A)
button(B)
button(X)
button(Y)

pressed(A)      // check if button was just pressed this frame
```

### Graphics
```cpp
pen(r, g, b, a = 0)    // set drawing color (0-15 for each component)
clear()                 // clear screen
text(str, x, y)         // draw text
rect(x, y, w, h)        // draw rectangle outline
frect(x, y, w, h)       // filled rectangle
hline(x, y, l)          // horizontal line
fcircle(x, y, r)        // filled circle
```

### Timing
```cpp
uint32_t tick     // frame counter (60fps)
time()            // milliseconds since startup
```

### Strings
```cpp
str(value)        // convert number to string
```

## Project-Specific Patterns

### State Machine
Use enum for game states:
```cpp
enum state_t {PLAYING, GAME_OVER};
state_t state = PLAYING;
```

### Tick-Based Updates
Update game logic on specific tick intervals:
```cpp
if(tick % 10 == 0) {
    // Update 6 times per second (60fps / 10)
}
```

### Structured Data
Use structs with designated initializers:
```cpp
constexpr vec_t bounds{.x = 18, .y = 16};
vec_t position = {.x = 9, .y = 8};
```

## CMakeLists.txt Configuration

Key build options (uncomment to enable):
```cmake
# pixel_double(${PROJECT_NAME})          # 120x120 resolution, pixel-doubled to 240x240
# disable_startup_logo(${PROJECT_NAME})  # Skip PicoSystem splash (recommended for games)
# no_font(${PROJECT_NAME})               # Omit default font
# no_spritesheet(${PROJECT_NAME})        # Omit default spritesheet (recommended)
# no_overclock(${PROJECT_NAME})          # Don't overclock
```

## Common Tasks

### Adding New Source Files
1. Create `.cpp` file following style guidelines
2. Add to `PROJECT_SOURCES` in `CMakeLists.txt`:
   ```cmake
   set(PROJECT_SOURCES
       main.cpp
       new_file.cpp
   )
   ```

### Adding Constants
Place game constants at top of file after includes:
```cpp
constexpr int PLAYER_SPEED = 3;
constexpr int SCREEN_WIDTH = 120;
constexpr int SCREEN_HEIGHT = 120;
```

### Adding Game States
1. Add state to enum
2. Handle in `update()` with switch/if
3. Handle rendering in `draw()` if needed

## Debugging

Since this is embedded hardware:
- No console output available
- Debug by visual output on screen
- Use `text()` to display debug values
- Check hardware connections
- Verify `.uf2` file is being copied correctly

## Memory Considerations

- PicoSystem has limited RAM (264KB total, shared with PicoSystem framebuffer)
- Prefer `constexpr` over runtime constants
- Use stack allocation when possible
- Keep `std::vector` sizes bounded
- No dynamic memory allocation during gameplay if possible

## Platform-Specific Notes

- Target: Raspberry Pi RP2040 (ARM Cortex-M0+)
- Screen: 240x240 pixels
- Compile with `-O2` or `-O3` for release builds
- Hardware runs at ~133MHz (can overclock)
- Framebuffer uses ~58KB of RAM

## Important Files

- `main.cpp` - Main game entry point
- `CMakeLists.txt` - Build configuration
- `Makefile` - Build commands
- `README.md` - Project documentation
- `.github/workflows/cmake.yml` - CI/CD pipeline

## Documentation Links

These should be used to obtain better information on the picosystem API

- PicoSystem API Cheatsheet: https://wiki.picosystem.com/en/c++/cheatsheet
- PicoSystem Graphics API: https://wiki.picosystem.com/en/about/graphics
- PicoSystem GitHub: https://github.com/pimoroni/picosystem
- Pico SDK: https://github.com/raspberrypi/pico-sdk/
