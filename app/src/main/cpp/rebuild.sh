#!/bin/bash

cmake -Bbuild && \
cmake --build build -j8 && \
if [ ! -f compile_commands.json ]; then
    rm compile_commands.json 2>/dev/null
    ln -s build/compile_commands.json . 
fi
