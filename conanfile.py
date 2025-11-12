from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.scm import Git

import os;

class NiflibConan(ConanFile):
	name = "niflib"
	version = "1.0"
	license = "BSD-3-Clause"
	author = "Niftools"
	url = "https://github.com/roknus/niflib"
	description = "Niftools C++ library for Nif IO"
	settings = "os", "compiler", "build_type", "arch"
	options = {"shared": [True, False], "fPIC": [True, False]}
	default_options = {"shared": False, "fPIC": True}

	exports_sources = [
		"cmake/*",
		"src/*",
		"include/*",
		"NvTriStrip/*",
		"TriStripper/*",
		"qhull/src/*",
		"CMakeLists.txt",
		"CMakePresets.json",
		"license.txt",
		"change_log.txt",
		"VERSION"
	]

	def generate(self):
		tc = CMakeToolchain(self)
		tc.generate()

		deps = CMakeDeps(self)
		deps.generate()

	def layout(self):
		cmake_layout(self)

	def config_options(self):
		if self.settings.os == "Windows":
			del self.options.fPIC

	def build(self):
		cmake = CMake(self)
		cmake.configure()
		cmake.build()
		
		# No test yet
		#if not self.conf.get("tools.build:skip_test", default=False):
		#	cmake.test()

	def export(self):
		git = Git(self)
		git.coordinates_to_conandata()

	def package(self):
		cmake = CMake(self)
		cmake.install()

	def package_info(self):
		self.cpp_info.set_property("cmake_find_mode", "none")
		self.cpp_info.builddirs.append(os.path.join("lib", "cmake", "niflib"))
