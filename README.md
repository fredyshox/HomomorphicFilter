# Homomorphic filter

Implementation of homomorphic filter in C++ using OpenCV library.

## Build

Project is using CMake:

```
mkdir Build/
cd Build
cmake ..
make
```

## Usage

Executables:
* HomomorphicFilterDemo in `bin/demo` - interactive toy with GUI

* * Usage: ./build/HomomorphicFilterDemo [OPTIONS] \<imagefile\>

* HomomorphicFilterCLI in `bin/cli` - CLI with ability to write results to file

* * Usage: ./HomomorphicFilterCLI [OPTIONS] \<imagefile\> \<outputfile\>

Common parameters:
- `-b`: use butterworth high pass filter
- `-g`: use gaussian high pass filter
- `-c`: use constant value as a border (0)
- `-r`: use boundary pixel replication as a border

## Sources

* Digital Image Processing (4th Edition) - Rafael C. Gonzalez, Richard E. Woods
* Part 1 & Part 2: https://blogs.mathworks.com/steve/2013/06/25/homomorphic-filtering-part-1/
