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

    exports_sources = "CMakeLists.txt", "include/*", "src/*"

    @property
    def _build_subfolder(self):
        return "build_subfolder"

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def requirements(self):
        self.requires("boost/1.76.0")

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
        self.copy("*.h", dst="include", src="include")
        self.copy("*.lib", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["GSCrossPlatformLibrary"]

