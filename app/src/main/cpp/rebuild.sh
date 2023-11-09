#!/bin/bash

# rm -r build/shared_modules

cmake -Bbuild && \
cmake --build build -j8 && \
./build/main

if [ ! -f compile_commands.json ]; then
    rm compile_commands.json 2>/dev/null
    ln -s build/compile_commands.json . 
fi