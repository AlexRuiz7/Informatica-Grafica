/*____________________________________________________________ */
//               Fichero tetrahedron.h
/*____________________________________________________________ */

/**
 * @author Alejandro Ruiz Becerra
 * @date   2017
 * @brief Clase para representar gráficamente un tetraedro mediante OpenGL.
 */

#ifndef TETRAHEDRON_H
#define TETRAHEDRON_H

#include "object3d.h"

class Tetrahedron : public Object3d {
public:
  /**
   * @brief Constructor de la clase Tetrahedron.
   * Construye el objeto incializando los vectores vertices y triangles.
   *
   * @param l Lado de las aristas del objeto. Por defecto l=1.
   * @see vertices
   * @see triangles
   */
  Tetrahedron(float l=1.0);
};

#endif
