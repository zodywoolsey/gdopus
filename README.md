# gdopus

To build, please follow the following instructions:
- `cd src/opus/` to get into the opus directory
- look at the README to find what dependencies you need to install
- `mkdir build` to create the build folder in `src/opus/`
- run `cmake ..` to setup the cmake build files to build the static library
- run `cmake --build .` to actually build the library file
- once you've built opus, you should have a libopus file in `src/opus/build/`, if that's true then good job!
- now you'll want to go to the project root and simply run `scons` (obviously you can also run scons with arguments, ex: apple silicon macs need to run it like this: `scons platform=macos arch=arm64`)
- that should be it. it will build the gdextension and place the resulting lib in the test project's bin directory
  - you should be able to find the resulting gdextension in `gdextensiontest/bin/` and it should start with `libgdopusencoder`

please keep in mind this is still in early development and will change in the future.
right now this repo simply contains the most basic implementation of the opus library so I could use it for learning purposes and for a quick voip utility.
future updates will flesh out the features, stay tuned.

If you're interested in supporting development consider submitting a PR or financailly supporting the [barkvr](https://github.com/zodywoolsey/barkvr) project which this tool is being developed for: 
