#! /bin/bash

rm -rf build *json

conan install . \
  -b=missing \
  -o=normal/1.0:shared=True \
  -o=ZLIB/*:shared=True \
  -s=build_type=Debug \
  # -o=ffmpeg/6.0:shared=True \
  # -o=ffmpeg/6.0:with_openjpeg=False \
  # -o=ffmpeg/6.0:with_libx264=False \
  # -o=ffmpeg/6.0:with_libx265=False

cmake --preset conan-debug 
