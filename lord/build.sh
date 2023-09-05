#!/bin/bash

# build source is missing
conan install . -b=missing

cmake --preset conan-release
