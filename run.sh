#!/bin/bash

# Check if build directory exists
if [ ! -d "cmake-build-debug" ]; then
    echo "Build directory not found. Creating it..."
    mkdir cmake-build-debug
fi

# Navigate to the build directory
cd cmake-build-debug || exit

# Run CMake configuration
cmake ..
if [ $? -ne 0 ]; then
    echo "CMake configuration failed!"
    exit 1
fi

# Build the project
make
if [ $? -eq 0 ]; then
    echo "Build successful! Running the project..."
    .main.cpp # Replace 'intro_lab' with your actual executable name if different
else
    echo "Build failed!"
    exit 1
fi
