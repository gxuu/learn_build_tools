#! /bin/bash

rm -rf build *json

conan create .

cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -B build

# cmake --preset conan-debug 

# source ./build/Debug/generators/deactivate_conanbuild.sh


