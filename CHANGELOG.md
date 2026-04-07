# Changelog

## 1.3.1

- Added `include/GeosCompat.h` to support differences between GEOS 3.10.7 and newer GEOS C++ APIs.
- Updated geometry creation code to handle both raw-pointer and `std::unique_ptr` factory return styles.
- Updated coordinate access code to support both `Coordinate`- and `CoordinateXY`-based APIs.
- Improved build compatibility on macOS where multiple GEOS installations may coexist.
- Updated README documentation to describe the compatibility changes and build considerations.

## 1.3.0

- Released NetEventSimulator version 1.3.0.
- Provided cross-platform build instructions for Windows, Linux, and macOS.
- Included example datasets, simulator configuration files, and documentation.
