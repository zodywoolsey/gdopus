#!/usr/bin/env python
import os
import sys

env = SConscript("godot-cpp/SConstruct")

# For reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

if env["platform"] == "windows":
#    env.Append(LIBPATH=["src/opus/build-win/Release"])
    env.Append(LIBPATH=["src/opus/build-win/"])
elif env["platform"] == "android":
    env.Append(LIBPATH=["src/opus/build-android"])
elif env["platform"] == "macos":
    env.Append(LIBPATH=["src/opus/build-macos"])
else:
    env.Append(LIBPATH=["src/opus/build/"])

env.Append(LIBS=["opus"])

# left over from testing web builds, leaving in case useful in the future
# env.Append(CXXDEFINES=["EMCC_FORCE_STDLIBS=1"])
# env.Append(CPPDEFINES=["EMCC_FORCE_STDLIBS=1"])
# env.Append(CXXFLAGS=['-fstack-protector'])
# env.Append(CXXFLAGS=['-fPIC'])

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=["src/"])
sources = Glob("src/*.cpp")

if env["platform"] == "macos":
    library = env.SharedLibrary(
        "gdextensiontest/addons/gdopus/libgdopusencoder.{}.{}.framework/libgdopusencoder.{}.{}".format(
            env["platform"], env["target"], env["platform"], env["target"]
        ),
        source=sources,
    )
else:
    library = env.SharedLibrary(
        "gdextensiontest/addons/gdopus/libgdopusencoder{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

Default(library)
