/*____________________________________________________________ */
//               Fichero objectply.h
/*____________________________________________________________ */

/**
 * @author Alejandro Ruiz Becerra
 * @date   2017
 * @brief Clase para representar gráficamente objetos descritos en un fichero PLY.
 */

#ifndef OBJECTPLY_H
#define OBJECTPLY_H

#include "object3d.h"

class ObjectPLY : public Object3d {

public:
  /**
   * @brief Constructor
   *
   * Recibe como parámetro una cadena de caracteres, que representa el camino
   * relativo al fichero PLY desde el que se va a leer y generar el objeto.
   * Para ello hace uso de la clase auxiliar "file_ply_stl"
   *
   * @param file Path relativo al fichero PLY a leer.
   */
  ObjectPLY(string file);
};

#endif
