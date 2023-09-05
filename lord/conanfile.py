import os
from conan import ConanFile
from conan.tools.cmake import cmake_layout


class lordRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"


    def requirements(self):
        self.requires("normal/1.0")

    # this is not needed as long as we don't care build environment
    def build_requirements(self):
        self.requires("cmake/3.27.0")

    def layout(self):
        cmake_layout(self)
