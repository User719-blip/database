# This script compiles the C++ source files and runs the resulting executable.
g++ src/main.cpp src/read.cpp src/schema.cpp src/core.cpp src/save.cpp -o out/main.exe
if ($?) {
    ./out/main.exe
} else {
    Write-Host "Build failed."
}