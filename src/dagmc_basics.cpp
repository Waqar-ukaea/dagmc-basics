#include <fstream>


#include "DagMC.hpp"
#include "moab/Core.hpp"
#include "moab/Interface.hpp"


int main() {
  // ---------------------- Geometry Preparation ----------------------
  std::unique_ptr<moab::DagMC> DAG;
  DAG = std::make_unique<moab::DagMC>(); 
  moab::Range Surfs, Vols, Facets, Facet_vertices;
  DAG->load_file("torus.h5m"); // open test dag file
  DAG->init_OBBTree(); // initialise OBBTree
  DAG->setup_geometry(Surfs, Vols); // store surface and volume entity sets

  // return moab instance for more flexible geometry query
  DAG->moab_instance()->get_entities_by_type(0, moab::MBTRI, Facets);
  
  std::cout << "-------------------------------------------" << std::endl;
  std::cout << "Number of Volumes = " << Vols.size() <<  std::endl;
  std::cout << "Number of Surfaces = " << Surfs.size() << std::endl;
  std::cout << "Number of Triangles = " << Facets.size() << std::endl; 
  std::cout << "-------------------------------------------" << std::endl;
  // ---------------------- Performing a ray trace ----------------------

  moab::EntityHandle VolID = DAG->entity_by_index(3,1); // volume to fire ray at
  double origin[3] = {0,0,0}; // origin of ray
  double direction[3] = {-1,0,0}; // direction of ray 
  moab::EntityHandle nextSurfaceHandle; // EntityHandle of surface hit
  moab::EntityHandle facetIntersected; // EntityHandle of triangular facet hit
  moab::DagMC::RayHistory rayHistory;
  double nextSurfaceDistance; // distance travelled before surface hit
  double rayDistanceLimit = 10.0; // optional distance limit of of ray
  int rayOrientation = -1; // If provided determines intersections along the normal provided, 
                           // e.g. if -1 allows intersections back along the the ray direction, 
                           // Default is 1, i.e. exit intersections

  std::ofstream rayPoints("ray_pts.txt");
  double ray_pt[3];
  double finalPosition[3];

  DAG->ray_fire(VolID, origin, direction, nextSurfaceHandle, nextSurfaceDistance, &rayHistory, rayDistanceLimit, rayOrientation);

  // ---------------------- Second ray trace ----------------------
  if (nextSurfaceHandle != 0) // if surface hit
  {
    rayHistory.get_last_intersection(facetIntersected); 
    std::cout << "Surface hit! EntityHandle of surface - " << nextSurfaceHandle << std::endl;
    std::cout << "EntityHandle of Facet hit - " << facetIntersected << std::endl; 
    std::cout << "-------------------------------------------" << std::endl;

    finalPosition[0] = origin[0] + (direction[0] * nextSurfaceDistance);
    finalPosition[1] = origin[1] + (direction[1] * nextSurfaceDistance);
    finalPosition[2] = origin[2] + (direction[2] * nextSurfaceDistance);
  }

  double distanceTravelled = nextSurfaceDistance / 1000;
  for (int i=0; i<1000; ++i)
  {
    ray_pt[0] = origin[0] + (direction[0] * (i*distanceTravelled));
    ray_pt[1] = origin[1] + (direction[1] * (i*distanceTravelled));
    ray_pt[2] = origin[2] + (direction[2] * (i*distanceTravelled));
    rayPoints << ray_pt[0] << " " << ray_pt[1] << " " << ray_pt[2] << std::endl;
  }

  origin[0] = -7.0;
  origin[1] = 2.5;
  direction[0] = 1.0;;
  DAG->ray_fire(VolID, origin, direction, nextSurfaceHandle, nextSurfaceDistance, &rayHistory, rayDistanceLimit, rayOrientation);

  if (nextSurfaceHandle != 0) // if surface hit
  {
    rayHistory.get_last_intersection(facetIntersected); 
    std::cout << "Surface hit! EntityHandle of surface - " << nextSurfaceHandle << std::endl;
    std::cout << "EntityHandle of Facet hit - " << facetIntersected << std::endl; 
    std::cout << "-------------------------------------------" << std::endl;

    finalPosition[0] = origin[0] + (direction[0] * nextSurfaceDistance);
    finalPosition[1] = origin[1] + (direction[1] * nextSurfaceDistance);
    finalPosition[2] = origin[2] + (direction[2] * nextSurfaceDistance);
  }

  distanceTravelled = nextSurfaceDistance / 1000;
  for (int i=0; i<1000; ++i)
  {
    ray_pt[0] = origin[0] + (direction[0] * (i*distanceTravelled));
    ray_pt[1] = origin[1] + (direction[1] * (i*distanceTravelled));
    ray_pt[2] = origin[2] + (direction[2] * (i*distanceTravelled));
    rayPoints << ray_pt[0] << " " << ray_pt[1] << " " << ray_pt[2] << std::endl;
  }

  DAG->write_mesh("out.vtk", 1);



  return 0;
}





