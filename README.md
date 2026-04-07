# NetEventSimulator – A Mobile Network Events Simulator

## Current Version

Current stable release: **1.3.1**

You can check the installed version with:

```bash
Release/simulator -version
```

On Windows, the executable name is `Release/simulator.exe`.

## Overview

NetEventSimulator is a C++ framework for mobile network data micro-simulation. It generates synthetic network event data that can be used to test statistical models for population counts and related indicators derived from mobile network data.

A major advantage of simulation is that it provides a latent ground truth that is unavailable in real mobile network data. This makes it possible to evaluate statistical procedures under controlled conditions before applying them to real-world data.

For background, see:

- Oancea et al. (2019): <https://cros.ec.europa.eu/system/files/2024-04/WPI_Deliverable_I2_Data_Simulator_-_A_simulator_for_network_event_data.pdf>

The code is written in C++ and requires a compiler with **C++17** support. The project has been built with GNU and LLVM toolchains on **Windows**, **Linux**, and **macOS**.

Version **1.3.1** updates the codebase to improve compatibility across GEOS C++ API changes. In particular, the simulator now supports both the older **GEOS 3.10.7** API and newer GEOS releases through a small compatibility layer (`GeosCompat.h`) that abstracts differences in coordinate access and geometry-factory return types.

> **Warning**
> Code revisions may occur without notice.

For questions about the software, contact: [bogdan.oancea@gmail.com](mailto:bogdan.oancea@gmail.com)

---

## Requirements

To build the project you need:

- a C++17-capable compiler
- `make`
- the GEOS C++ library and headers
- `git` to clone the repository

NetEventSimulator officially supports **GEOS 3.10.7** and also includes compatibility updates introduced in version **1.3.1** for newer GEOS C++ API variants. GEOS 3.10.7 remains the reference and newest officially supported version.

On Windows, use a single MSYS2/UCRT64 toolchain consistently. Do **not** mix Cygwin libraries with MinGW/UCRT libraries in the same build.

---

## Building on Windows

The recommended Windows setup uses the **MSYS2 UCRT64** environment distributed with **Rtools**.

### 1. Install Rtools / MSYS2

Download Rtools from CRAN:

<https://cran.r-project.org/bin/windows/Rtools/>

Open the **UCRT64** shell after installation.

### 2. Install the compiler and tools

In the UCRT64 shell, update the package database and install the required tools:

```bash
pacman -Syu
pacman -S mingw-w64-ucrt-x86_64-gcc 
pacman -S mingw-w64-ucrt-x86_64-make
pacman -S mingw-w64-ucrt-x86_64-cmake
pacman -S mingw-w64-ucrt-x86_64-ninja git
```

You may also install editors or other tools, such as `vim`, if desired.

### 3. Build and install GEOS as a static library

On Windows, **GEOS 3.10.7 is the newest supported version**. A tested configuration is a static GEOS 3.10.7 build installed under `C:/local/geos-ucrt64-static`.

Example:

```bash
rm -rf /d/c-projects/geos-3.10.7/_build

SRC=$(cygpath -m /d/c-projects/geos-3.10.7)
BLD=$(cygpath -m /d/c-projects/geos-3.10.7/_build)
INS=C:/local/geos-ucrt64-static

MSYS2_ARG_CONV_EXCL='*' /ucrt64/bin/cmake -G Ninja \
  -S "$SRC" \
  -B "$BLD" \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_INSTALL_PREFIX="$INS" \
  -DBUILD_SHARED_LIBS=OFF \
  -DBUILD_TESTING=OFF \
  -DBUILD_DOCUMENTATION=OFF

MSYS2_ARG_CONV_EXCL='*' /ucrt64/bin/cmake --build "$BLD"
MSYS2_ARG_CONV_EXCL='*' /ucrt64/bin/cmake --install "$BLD"
```

Check that the static libraries were installed:

```bash
ls /c/local/geos-ucrt64-static/lib/libgeos*.a
```

### 4. Clone the repository

```bash
git clone https://github.com/bogdanoancea/neteventsimulator.git
```

### 5. Edit `makefile.inc`

Set the following variables:

- `PROJ_HOME`: simulator project root
- `GEOS_HOME`: GEOS installation prefix

Important: on Windows these paths must be written in **MSYS/UCRT style**, not in native Windows style.

Example:

```make
PROJ_HOME = /d/c-projects/neteventsimulator
GEOS_HOME = /c/local/geos-ucrt64-static
```

`GEOS_HOME` must point to the **installation prefix** that contains both `include` and `lib` subdirectories.

Version **1.3.1** adds a small internal compatibility header (`include/GeosCompat.h`) used by the source code to bridge differences between GEOS 3.10.7 and newer GEOS C++ APIs. No user action is required beyond pointing `GEOS_HOME` to the correct GEOS installation.

### 6. Build and install the simulator

From the project source directory, run:

```bash
make
make install
```

The executable is copied to the `Release` folder.

### 7. Run an example simulation

```bash
Release/simulator.exe \
  -m ./data/dataset1/map.wkt \
  -s ./data/dataset1/simulation.xml \
  -a ./data/dataset1/antennas.xml \
  -p ./data/dataset1/persons.xml \
  -pb ./data/dataset1/probabilities.xml \
  -v
```

---

## Building on Linux or macOS

### 1. Install GEOS

NetEventSimulator officially supports **GEOS 3.10.7** on Linux and macOS, and version **1.3.1** also adds source-level compatibility with newer GEOS C++ API variants. GEOS 3.10.7 remains the reference and newest officially supported version. In either case, identify the installation prefix that contains:

- `include/`
- `lib/`

Typical examples are:

- Linux: `/usr/local` or `/usr`
- macOS: `/usr/local`, `/opt/homebrew/opt/geos`, or another custom prefix

If you build GEOS from source, a standard sequence is:

```bash
./configure
make
make install
```

If needed, run:

```bash
sudo make install
sudo ldconfig
```

### 2. Clone the repository

```bash
git clone https://github.com/bogdanoancea/neteventsimulator.git
```

### 3. Edit `makefile.inc`

Set:

```make
PROJ_HOME = /path/to/neteventsimulator
GEOS_HOME = /path/to/geos/prefix
```

Examples:

```make
PROJ_HOME = /home/user/neteventsimulator
GEOS_HOME = /usr/local
```

or on Apple Silicon:

```make
PROJ_HOME = /Users/user/neteventsimulator
GEOS_HOME = /opt/homebrew/opt/geos
```

If you build against a Homebrew GEOS installation on macOS, make sure the compiler and runtime both resolve the same GEOS installation. Avoid mixing headers or libraries from `/usr/local` and `/opt/homebrew` in the same build.

### 4. Build and install

From the project source directory, run:

```bash
make
make install
```

---

## Running NetEventSimulator

Example:

```bash
Release/simulator \
  -m ./data/dataset1/map.wkt \
  -s ./data/dataset1/simulation.xml \
  -a ./data/dataset1/antennas.xml \
  -p ./data/dataset1/persons.xml \
  -pb ./data/dataset1/probabilities.xml \
  -v
```

### Input files

The main input files are:

- `map.wkt` – simulation map
- `simulation.xml` – main simulation configuration
- `antennas.xml` – antenna configuration
- `persons.xml` – population configuration
- `probabilities.xml` – parameters used to compute location probabilities

Sample input files are provided under `data/dataset1` to `data/dataset7`.

### Notes

- Location probabilities are computed only if the `-pb` option is provided.
- If `-v` is provided, the simulator prints detailed information about persons, operators, antennas, and mobile phones.

---

## Changes in version 1.3.1

The 1.3.1 branch includes source-code updates intended to keep the simulator buildable against both the older GEOS 3.10.7 API and newer GEOS C++ API variants. The main changes are:

- introduction of `include/GeosCompat.h` to centralize GEOS API compatibility handling;
- updates to geometry creation code so that both raw-pointer and `std::unique_ptr` GEOS factory styles are supported;
- updates to coordinate-access code to account for differences between `Coordinate` and `CoordinateXY` views;
- README and build documentation updates reflecting the new compatibility layer.

GEOS **3.10.7** remains the reference build target and the newest officially supported version.

---

## Troubleshooting

- If compilation succeeds but linking fails with unresolved C++ runtime symbols, verify that you are not mixing toolchains.
- On Windows, build both GEOS and the simulator with the same UCRT64 toolchain.
- `GEOS_HOME` should be the installation prefix, not the `include` directory and not the `lib` directory itself.
- If you use a newer GEOS release, note that **GEOS 3.10.7 is the newest officially supported version** of the simulator.
- Version **1.3.1** introduces `include/GeosCompat.h`, which is used internally to handle GEOS API differences such as `Coordinate`/`CoordinateXY` access and raw-pointer versus `std::unique_ptr` returns from geometry factory methods.
- On macOS, do not mix GEOS headers and libraries from different installations (for example `/usr/local` and `/opt/homebrew`) in the same build.
- On macOS, if the simulator fails at runtime because the GEOS shared library cannot be found, run `export DYLD_LIBRARY_PATH=/usr/local/lib:$DYLD_LIBRARY_PATH` before starting the simulator, adjusting `/usr/local/lib` if GEOS is installed in a different location.
- If the compiler command shows a non-existent include directory, enable `-Wmissing-include-dirs` to catch it early.
