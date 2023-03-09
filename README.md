## rtsp_stream_viewer
This project is written in C++ and use OpenCV to read a rtsp stream and display it in a OpenCV window. 

#### Prerequisites
- install c++ compiler
- install opencv

# Build
```shell
# use cmake and give it the path .  It generates a build system for a target platform based on a project's CMakeLists.txt file
cmake .

# use make to build the project by invoking the makefiles generated by cmake 
# this will generate a executable called rtsp_stream_viewer,  run it like:
make

#Alternatively you can run ./build.sh which essentially does the same thing as above
```

# Run
```shell
# to run:
./rtsp_stream_viewer
```

# Helper scripts
There are a couple of helper scripts to clean/build as well
```
./cleanup.sh
./build.sh
```