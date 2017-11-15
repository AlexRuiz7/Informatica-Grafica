/*____________________________________________________________ */
//               Fichero cube.h
/*____________________________________________________________ */

/**
 * @author Alejandro Ruiz Becerra
 * @date   2017
 * @brief Clase para representar gráficamente un cubo mediante OpenGL.
 */

#ifndef CUBE_H
#define CUBE_H

#include "object3d.h"

class Cube : public Object3d {
public:
  /**
   * @brief Constructor de la clase Cube.
   * Construye el objeto inicializando los vectores vertices y triangles.
   *
   * @param l Lado de las aristas del objeto. Por defecto l=1.
   * @see vertices
   * @see triangles
   */
  Cube(float l=1.0);
};

#endif
