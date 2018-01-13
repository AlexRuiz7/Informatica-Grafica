/*____________________________________________________________ */
//               Fichero tablero.h
/*____________________________________________________________ */

/**
 * @author Alejandro Ruiz Becerra
 * @date   2017
 * @brief Clase que define y representa gráficamente un tablero cuadrado de
 *        dimensiones mxm en OpenGL.
 */

#include "object3d.h"

#ifndef TABLERO_H
#define TABLERO_H

class Tablero : public Object3d{

private:
  int m;
  float x_ini, z_ini, x_fin, z_fin, lado_x, lado_z, tam_cuadrado_x, tam_cuadrado_z;

public:
  Tablero();

  Tablero(float x_ini, float z_ini, float x_fin, float z_fin, int m);

private:

  void generateVertex();

  void generateFaces();

};

#endif
