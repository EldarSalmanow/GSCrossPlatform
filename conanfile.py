from conans import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain
from conan.tools.layout import cmake_layout


class GSCrossPlatformConan(ConanFile):
    name = "GSCrossPlatform"
    version = "1.0"
    author = "Eldar eldar.salm@gmail.com"
    url = "https://github.com/conan-io/conan-center-index"
    description = "GSCrossPlatform - library for easy supporting cross platform C++ programming."
    topics = ("C++", "CrossPlatform")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}
    generators = "cmake_find_package"
    exports_sources = "CMakeLists.txt", "include/*"
    requires = "icu/70.1"

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

