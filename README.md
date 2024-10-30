# Parking System

This project is a parking management system developed in C++ using Qt5 and built with CMake and Ninja.

## Requirements

- [CMake](https://cmake.org/download/) 3.5 or higher
- [Ninja](https://ninja-build.org/) build system (optional, but recommended)
- [Qt5](https://doc.qt.io/qt-5/index.html) (Widgets module)

## Build Instructions

### Step 1: Clean previous builds

Before starting a new build, clean the `build` directory (optional, but recommended):

```bash
rm -rf build
```

### Step 2: Configure the build using CMake

Use the following command to configure the project with CMake and Ninja:

```bash
cmake -S . -B build -G Ninja
```

This command specifies the source directory (`-S .`), the build directory (`-B build`), and the Ninja generator (`-G Ninja`).

### Step 3: Build the project using Ninja

```bash
ninja -C build
```

You can also use the following options with Ninja:

- `-v` for verbose output during the build process.
- `-d stats` to display detailed statistics after the build.

Example:

```bash
ninja -C build -v -d stats
```

### Step 4: Run the application

Once the build is complete, run the executable:

```bash
./build/parking_system_client
```

## Build without Ninja

To build the project without using Ninja, use the following command:

```bash
rm -rf build
cmake -S . -B build
make -C build
./build/parking_system_client
```

## Project Structure

- `src/`: Contains the source code files (`.cpp` and `.hpp`) for the different widgets and the main application logic.
- `CMakeLists.txt`: CMake configuration file for the project.

## CMake Configuration

The project is built with C++17 and uses the following CMake settings:

- `CMAKE_AUTOMOC`, `CMAKE_AUTORCC`, `CMAKE_AUTOUIC` are enabled to automate Qt's MOC, RCC, and UIC processes.
- The Qt5 Widgets module is required and linked with the target.

## TroubleShooting

On Ubuntu 22.04 may occure error:

```bash
./build/parking_system_client
./build/parking_system_client: symbol lookup error: /snap/core20/current/lib/x86_64-linux-gnu/libpthread.so.0: undefined symbol: __libc_pthread_init, version GLIBC_PRIVATE
```

just try to unset `GTK_PATH`:

```bash
unset GTK_PATH
```
