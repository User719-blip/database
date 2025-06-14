#!/bin/bash
g++ src/main.cpp src/read.cpp src/schema.cpp src/core.cpp src/save.cpp -o out/main.exe
if [ $? -eq 0 ]; then
    ./out/main.exe
else
    echo "Build failed."
fi