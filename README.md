# pypolypart

Python bindings for CGAL 2D Polygon Partitioning.

## Features

- `optimal_convex_partition_2(...)`
- Returns a list of convex polygons

## Install

```bash
pip install pypolypart
```

Pip will:
1. Download the source package (.tar.gz)
2. Compile the C++ extension using CMake
3. Link against your locally installed CGAL libraries

If dependencies are missing, installation will fail with a compiler or CMake error.

## Important

This package contains compiled C++ extension and is currently distributed as a *source distribution only*.
This means it will be built locally during installation and requires a working C++ toolchain and CGAL installed in your system.

## System Requirements

### Linux (Ubuntu 24.04 recommended)
Install the required system dependencies:

```bash
sudo apt update
sudo apt install -y \
  build-essential \
  python3.12-dev \
  libcgal-dev \
  libboost-dev \
  libgmp-dev \
  libmpfr-dev
```

These provide:
- C++ compiler (g++)
- CGAL headers and libraries
- Required math libraries (GMP, MPFR)
- Boost dependencies

### Other Platforms
- *macOS*: You may be able to install dependencies via brew install cgal, but this is not officially tested.
- *Windows*: Not currently supported (requires manual CGAL + toolchain setup.)

## Example
```Python
from pypolypart import optimal_convex_partition_2

def main() -> None:
    polygon = [
        (391, 374),
        (240, 431),
        (252, 340),
        (374, 320),
        (289, 214),
        (134, 390),
        (68, 186),
        (154, 259),
        (161, 107),
        (435, 108),
        (208, 148),
        (295, 160),
        (421, 212),
        (441, 303),
    ]

    parts = optimal_convex_partition_2(polygon)

    print("Input polygon:")
    print(polygon)
    print()

    print(f"Number of convex pieces: {len(parts)}")
    for idx, poly in enumerate(parts, start=1):
        print(f"Convex part {idx}:")
        for pt in poly:
            print(f"  {pt}")
        print()


if __name__ == "__main__":
    main()
```

## License

This project is licensed under the GNU General Public License v3.0 or later (GPL-3.0-or-later).

This package depends on CGAL's Polygon Partitioning package, which is licensed under the GPL.