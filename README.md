# dagmc-basics
Super basic introduction for getting started with DAGMC for particle tracking. Files included: 
- `using_dagmc.pdf` --> Slides with introduction and some useful links
- `src/dagmc_basics.cpp` --> .cpp file that sets up a DAGMC instance and performs two simple ray traces
- `torus.h5m` --> Faceted geometry file of a torus created in Coreform Cubit.
- `Dockerfile` --> A dockerfile that creates a new container with DAGMC and its required dependencies already installed. This repo is already cloned within that docker container and DAGMC is already linked to the dagmc-basics project within the `/opt/dagmc-basics` directory.
- `CMakeLists.txt` basic cmake config to link to DAGMC

The Docker container can be built using `docker build Dockerfile` 
