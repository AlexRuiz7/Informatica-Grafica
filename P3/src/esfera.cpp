/*____________________________________________________________ */
//               Fichero esfera.cpp
/*____________________________________________________________ */

#include "../include/esfera.h"
#include <fstream>

//-----------------------------------------------------------------------//

void Esfera::generateProfile(){
  float angulo_ini = -0.5*M_PI;           // -90º
  float angulo_fin =  0.5*M_PI;           //  90º
  float angulo = M_PI/revY;               //  angulo_fin - angulo_ini
  _vertex3f punto;

  punto.z = 0;                            //  La coordenada Z siempre es cero

  // Inserción del primer punto
  punto.x = 0;
  punto.y = -radio;
  vertices.push_back(punto);

  // Inserción de los puntos intermedios
  for(int i=1; i<revY; i++){
    punto.x = radio*cos(angulo_ini + angulo*i);
    punto.y = radio*sin(angulo_ini + angulo*i);

    vertices.push_back(punto);
  }

  // Inserción del último punto
  punto.x = 0;
  punto.y = radio;
  vertices.push_back(punto);
}

//-----------------------------------------------------------------------//

void Esfera::generatePLY(){
  ofstream out;
  out.open("ply_rev/esfera.ply");
  out << "ply\n"
      << "format ascii 1.0\n"
      << "element vertex " << vertices.size() << endl
      << "property float x\n"
      << "property float y\n"
      << "property float z\n"
      << "element face 3\n"
      << "property list uchar uint vertex_indices\n"
      << "end_header\n";
  for(int i=0; i<vertices.size(); i++)
    out << vertices[i].x << " " << vertices[i].y << " " << vertices[i].z << endl;

  out.close();
}

//-----------------------------------------------------------------------//

Esfera::Esfera(int rY, float r) {
  radio = r;
  revY = rY;
  generateProfile();
  generatePLY();
  generateNormals();
  applyMaterial();
}
