#!/bin/bash

build_folder_path="./build"

# Check if the folder already exists
if [ ! -d "$build_folder_path" ]; then
    # Create the folder
    mkdir -p "$build_folder_path"
    echo "Folder created successfully."
fi

cd ./build

cmake ..
cmake --build .
cmake --install .
cd ..