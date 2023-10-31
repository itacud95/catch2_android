#!/bin/bash

rm -r build/shared_modules

cmake -Bbuild && \
cmake --build build -j8 && \
if [ ! -f compile_commands.json ]; then
    rm compile_commands.json 2>/dev/null
    ln -s build/compile_commands.json . 
fi

./build/shared_modules/runner --filenames-as-tags
# ./build/shared_modules/runner --filenames-as-tags [#bar]
