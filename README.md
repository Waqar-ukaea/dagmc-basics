# dagmc-basics
Super basic introduction for getting started with DAGMC for particle tracking. A docker image is avaialble with DAGMC's dependencies pre-built (see below). Instructions for how to build DAGMC and its dependencies locally can be found in the Dockerfile provided. Files included in this repo: 
- `using_dagmc.pdf` --> Slides with introduction and some useful links
- `src/dagmc_basics.cpp` --> .cpp file that sets up a DAGMC instance and performs two simple ray traces
- `torus.h5m` --> Faceted geometry file of a torus created in Coreform Cubit.
- `Dockerfile` --> The Dockerfile used to create the docker image with the DAGMC dependencies. 
- `CMakeLists.txt` basic cmake config to link to DAGMC

If you wish to use a docker container, the image should be pulled with: 

    docker pull waqar1711/dagmc-dependencies

And an interactive container created with: 

    docker run -it waqar1711/dagmc-dependencies bash

Once in the container navigate to the dagmc-basics directory and the project should already be linked and compiled with DAGMC

    cd /opt/dagmc-basics/
