# Bide: BCPL IDE

A modern, fully-independent Integrated Development Environment for BCPL (Basic Combined Programming Language) written in pure C++ with cross-platform support for Windows and Linux.

## Features

- **Syntax Highlighting**: Full BCPL syntax highlighting with keyword recognition, comments, strings, and operators
- **Cross-Platform**: Native support for both Windows and Linux without external GUI dependencies
- **Cintsys Integration**: Direct compilation and execution using Cintsys/Cintpos/Cintcode systems
- **Native GUI**: Built with only standard C++ and platform-native APIs (WinAPI for Windows, X11 for Linux)
- **Code Editor**: Full-featured text editor with line numbers, indentation, and navigation
- **Build System**: Integrated compiler interface with error reporting and diagnostics
- **Project Management**: Support for BCPL projects with file organization
- **Zero External Dependencies**: Fully independent implementation

## Building

### Prerequisites

- C++17 or later compiler (GCC, Clang, or MSVC)
- CMake 3.16+
- Windows: Visual Studio 2019+ or MinGW-w64
- Linux: libX11-dev, libxkbcommon-dev (for native X11 support)
- Cintsys/Cintpos/Cintcode installed and accessible in PATH

### Linux Build

```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
sudo make install
```

### Windows Build

```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release
```

## Usage

```bash
./bide [bcpl_file]
```

## Keyboard Shortcuts

- **Ctrl+S**: Save
- **Ctrl+O**: Open
- **Ctrl+N**: New file
- **Ctrl+B**: Build/Compile
- **Ctrl+R**: Run
- **Ctrl+Z**: Undo
- **Ctrl+Y**: Redo
- **Ctrl+A**: Select All
- **Ctrl+Q**: Quit

## Project Structure

```
src/
├── main.cpp                      # Application entry point
├── editor/
│   ├── editor.cpp               # Text editor implementation
│   └── highlighter.cpp          # BCPL syntax highlighter
├── compiler/
│   ├── compiler.cpp             # BCPL compiler interface
│   └── cintsys.cpp              # Cintsys backend
├── ui/
│   ├── window.cpp               # Main window
│   └── renderer.cpp             # Native GUI renderer
├── platform/
│   ├── platform.cpp             # Platform abstraction
│   ├── platform_windows.cpp     # Windows (WinAPI) implementation
│   └── platform_linux.cpp       # Linux (X11) implementation
└── utils/

include/
├── editor.hpp
├── compiler.hpp
├── platform.hpp
└── ui/
    └── window.hpp

CMakeLists.txt
.gitignore
```

## Architecture

### Platform Independence
Bide uses a platform abstraction layer that interfaces with:
- **Windows**: Direct WinAPI for windowing, text rendering, and input handling
- **Linux**: X11 for windowing with native font rendering

No external GUI frameworks (Qt, GTK, etc.) are used - fully independent.

### Syntax Highlighting
Implements a state machine-based tokenizer for BCPL that recognizes:
- Keywords (let, be, and, or, not, if, then, else, for, while, do, etc.)
- Operators and delimiters
- String and character literals
- Comments (// and /* */)
- Numbers (decimal and hexadecimal)
- Identifiers

### Compiler Integration
Direct interface to Cintsys/Cintpos systems via:
- Process spawning for compilation
- Standard input/output capture
- Error message parsing and reporting
- Real-time compilation feedback with line/column error markers

## License

MIT License
