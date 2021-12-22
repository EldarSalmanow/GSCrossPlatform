import os

from conans import ConanFile, tools
from conan.tools.cmake import CMake, CMakeToolchain
from conan.tools.layout import cmake_layout


class GSCrossPlatformTestConan(ConanFile):
    name = "GSCrossPlatformTest"
    version = "1.0"
    author = "Eldar eldar.salm@gmail.com"
    url = "https://github.com/conan-io/conan-center-index"
    description = "GSCrossPlatformTests - package for testing GSCrossPlatform library."
    topics = ("C++", "CrossPlatform", "Tests")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}
    generators = "cmake_find_package"
    exports_sources = "*"
    requires = "gtest/cci.20210126", "GSCrossPlatform/1.0"

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

    def test(self):
        cmd = os.path.join(self.cpp.build.bindirs[0], "GSCrossPlatformStringTests")
        self.run(cmd, env="conanrun")
