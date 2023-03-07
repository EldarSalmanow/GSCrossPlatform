from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout


class GSCrossPlatformConan(ConanFile):
    name = "gs_cross_platform"
    version = "1.0"

    author = "Eldar eldar.salm@gmail.com"
    url = "https://github.com/conan-io/conan-center-index"
    description = "GSCrossPlatform - library for easy supporting cross platform C++ programming."
    topics = ("C++", "CrossPlatform")

    settings = "os", "compiler", "build_type", "arch"
    options = {
        "shared": [True, False],
        "fPIC": [True, False]
    }
    default_options = {"shared": False, "fPIC": True}

    generators = ["CMakeDeps"]
    exports_sources = "CMakeLists.txt", "include/*", "src/*"

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def requirements(self):
        self.requires("icu/72.1")

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
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("cmake_file_name", "GSCrossPlatform")
        self.cpp_info.set_property("cmake_target_name", "GSCrossPlatform::GSCrossPlatform")

        self.cpp_info.libs = ["GSCrossPlatformLibrary"]

