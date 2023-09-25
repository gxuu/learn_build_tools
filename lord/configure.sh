#! /bin/bash

rm -rf build *json

conan install . \
  -b=missing \
  -o=normal/1.0:shared=True \
  -o=ZLIB/*:shared=True \
  -o=spdlog/*:shared=False \
  -o=ffmpeg/6.0:shared=True \
  -s=build_type=Debug

# source the following file for building environment
# source ./build/Debug/generators/conanbuild.sh

  # -o=spdlog/*:wchar_support=True \
  # -o=spdlog/*:wchar_filename=True\
  # -o=spdlog/*:no_exceptions=True \
  # -o=ffmpeg/6.0:shared=True \
  # -o=ffmpeg/6.0:with_openjpeg=False \
  # -o=ffmpeg/6.0:with_libx264=False \
  # -o=ffmpeg/6.0:with_libx265=False

cmake --preset conan-debug 

# source ./build/Debug/generators/deactivate_conanbuild.sh

cp build/Debug/compile_commands.json build/compile_commands.json

# source the following file for run environment 
source ./build/Debug/generators/conanrun.sh
