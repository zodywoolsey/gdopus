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

# append all the external dependencies for opus to the include path
env.Append(LIBPATH=["opus/.libs/","opus/src/.libs/"])
env.Append(LIBS=["libopus","opus"])


# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=["./"])
sources = Glob("*.cpp")

if env["platform"] == "macos":
    library = env.SharedLibrary(
        "gdextensiontest/bin/libgdopusencoder.{}.{}.framework/libgdopusencoder.{}.{}".format(
            env["platform"], env["target"], env["platform"], env["target"]
        ),
        source=sources,
    )
else:
    library = env.SharedLibrary(
        "gdextensiontest/bin/libgdopusencoder{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

Default(library)
