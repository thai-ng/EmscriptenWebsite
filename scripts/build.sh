mkdir -p build
cd build
cmake ../ -DCMAKE_TOOLCHAIN_FILE="../emsdk-linux/emscripten/1.37.38/cmake/Modules/Platform/Emscripten.cmake"
make