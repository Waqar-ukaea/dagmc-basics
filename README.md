# dagmc-basics
Super basic introduction for getting started with DAGMC for particle tracking. Files included: 
- "Using DAGMC.pdf" --> Slides with introduction and some useful links
- basic.cpp --> .cpp file that sets up a DAGMC instance and performs two simple ray traces
- torus.h5m --> Faceted geometry file of a torus created in Coreform Cubit.
- Dockerfile --> A dockerfile that creates a new container with DAGMC and its required dependencies already installed (you will still need to create your own project that links to DAGMC)

The Docker container can be built using `docker build Dockerfile` 
