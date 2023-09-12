from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout 


class normalRecipe(ConanFile):
    name = "normal"
    version = "1.0"

    # Must have: Binary Configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {
            "shared" : [True, False],
            "fPIC"   : [True, False],
            }

    default_options = {
            "shared" : False,
            "fPIC"   : True,
            }

    # then you must export source

    exports_sources = "CMakeLists.txt", "src/*", "include/*"

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def layout(self):
        cmake_layout(self)

    def generate(self):
        toolchain = CMakeToolchain(self)
        toolchain.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["normal"]
