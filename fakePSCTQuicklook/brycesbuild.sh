#!/bin/bash

# Pre-Step: Check if the build directory exists. If it does, delete it.
if [ -d "build" ]; then
    rm -rf build
fi

# Step 1: Create a new build directory.
mkdir build

# Step 2: Change to the build directory.
cd build

# Step 3: Run CMake to generate the build system.
cmake ..

# Step 4: Compile the code.
make

# Step 5: Execute the program
./fakePSCTQuicklook

# Print a message to let the user know the process has finished.
echo "Build and execution completed."
