/*____________________________________________________________ */
//               Fichero objectply.cpp
/*____________________________________________________________ */

#include "../include/objectply.h"
#include "../include/file_ply_stl.h"

//-----------------------------------------------------------------------//

ObjectPLY::ObjectPLY(string file){
  _file_ply reader;

  reader.open(file);
  reader.read(vertices, triangles);
  reader.close();

  generateNormals();
  applyMaterial();
}
