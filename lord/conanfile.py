import os
from conan.tools.files import copy
from conan import ConanFile
from conan.tools.cmake import cmake_layout


class lordRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"


    def requirements(self):
        self.requires("normal/1.0")
        self.requires("zlib/1.3")
        self.requires("nlohmann_json/3.11.2")
        self.requires("spdlog/1.12.0")
        # self.requires("ffmpeg/6.0")

    # this is not needed as long as we don't care build environment
    def build_requirements(self):
        self.requires("cmake/3.27.0")

    # def generate(self): 
        # for dep in self.dependencies.values(): 
            # copy(self, "*.h", dep.cpp_info.includedir, "header/");
            # copy(self, "*.so.*", dep.cpp_info.bindir, self.build_folder)
            # copy(self, "*.dll", dep.cpp_info.libdir, self.build_folder)
            # copy(self, "*.lib*", dep.cpp_info.libdir, self.build_folder)

    def layout(self):
        cmake_layout(self)
