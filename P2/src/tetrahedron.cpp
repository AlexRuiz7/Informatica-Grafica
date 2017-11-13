/*____________________________________________________________ */
//               Fichero tetrahedron.cpp
/*____________________________________________________________ */

#include "../include/tetrahedron.h"

//-----------------------------------------------------------------------//

Tetrahedron::Tetrahedron(float l){
  float r, z, m;
  m = l*0.5;
  r = m/sin(60*M_PI/180);					// Radio de la circunferencia circunscrita.
  z = m*sin(30*M_PI/180)/sin(60*M_PI/180);	// Distancia del circuncentro a cada arista.
  //  Para l=10:  r=5.77,  z=2.88

  // Vértices del tetraedro
  vertices={
    {0, r, 0},      // 0
    {-m,-z,z},      // 1
    {m,-z, z},      // 2
    {0,-z,-r}       // 3
  };

  // Vértices de los triángulos que representa el tetraedro en sentido antihorario.
  triangles={
      {0,1,2},
      {2,3,0},
      {3,1,0},
      {1,3,2}
  };

  generateNormals();
}
