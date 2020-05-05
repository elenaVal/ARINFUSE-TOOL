# ARINFUSE

## GUI

The ARINFUSE mockup is made with QT. To this end, please have the following
installed on your PC:

  - Qt creator (4.8.2)
  - Qt kit 5.12.1 (MSVC 2015, 32bit)

After cloning, open the project in `ARInfuseMockUp` with Qt creator and build
it. Afterwards you should be able to run the mockup.

***Notes***

In case of errors while trying to run please try the following:

  - Clean all from the build tab
  - Build all from build tab
  - run qmake from build tab
  - Run the app (ctrl + R, on windows)

## Tools

The ARINFUSE tools are writtern in C++ and built with CMake. To this end,
please have the following installed on your PC:

  - CMake 3.4 (or later)
  - Visual Studio 14 (2015)

You'll also need access to `arbase-extlibs`. Ask a DFKI collegue for help how to
access the folder.

After cloning, open the project in `tools` with CMake GUI and configure it with
`Visual Studio 14 (2015)` and `x64`. If configuring fails, set `OPENCV_DIR` to
`<arbase-extlibs>/org_opencv` and `EIGEN_DIR` to
`<arbase-extlibs>/org_bitbucket_eigen_eigen/lib/cmake/eigen3`. You can ignore
warnings about missing CUDA. Once configuration succeeds, generate the project
in `<cmake-build>`, open the solutions file in Visual Studio, and compile
everything.

Once compiling succeeded, create a new folder `<tools>` (Please avoid spaces in
the path). Now, copy the following files to `<tools>`.

  - `<cmake-build>/arinfuse/camera_calibration/{Debug,Release}/camera_calibration.exe` -> `<tools>/camera_calibration/camera_calibration.exe`
  - `<cmake-build>/arinfuse/pose_estimation/{Debug,Release}/pose_estimation.exe` -> `<tools>/pose_estimation/pose_estimation.exe`
  - `<cmake-build>/arinfuse/xml_preproccessor/{Debug,Release}/xml_preproccessor.exe` -> `<tools>/xml_preproccessor/xml_preproccessor.exe`

Finally, clone `Lara` (at the time of writing, branch `new_command_line_parser`)
and build the Unity project as `<tools>/LARABuild`.

TODO(narek): Document how to get `<tools>/GIS-MODULE`.

Now, you're ready to launch the QT application. Don't forget to update
`Tool path` and `Data path` in the settings tab!

## Data Format

A data set is a folder containing the following files:

  - `camera_mins.txt`
  - `input.jpg`
  - `utilities.xml`
  - `xyz.txt`
