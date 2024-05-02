# gdopus

To build, please follow the following instructions:
- follow the opus readme in the `src/opus/` directory to find your dependencies
- use the readme in `src/opus/cmake/` to build libopus
  - you'll want to build with the `DOPUS_BUILD_SHARED_LIBRARY=ON` flag set so you get the libopus file
- once you've built opus, you should have a libopus file in `src/opus/build/`, if that's true then good job!
- now you'll want to go to the project root and simple run `scons` (obviously you can also run scons with arguments to specify platform, architecture, etc.)
- that should be it. it will build the gdextension and place the resulting lib in the test project's bin directory
  - you should be able to find the resulting gdextension in `gdextensiontest/bin/` and it should start with `libgdopusencoder`

please keep in mind this is still under development and will change in the future.
right now this repo simply contains a basic implementation of the opus library so I could use it for learning purposes.
future updates will flesh out the features, stay tuned.

If you're interested in supporting development consider submitting a PR or financailly supporting the [barkvr](https://github.com/zodywoolsey/barkvr) project which this tool is being developed for: 
