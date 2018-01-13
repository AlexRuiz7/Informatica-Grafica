/*____________________________________________________________ */
//               Fichero scene.h
/*____________________________________________________________ */

/**
 * @author Alejandro Ruiz Becerra
 * @date   2017
 * @brief Escena 3D compuesta por una matriz i*j de objetos.
 */

 #ifndef SCENE_H
 #define SCENE_H

#include "../include/objectply.h"

class Scene : public Object3d{

private:
  int i, j;
  ObjectPLY *objeto;

public:
  /**
   * @brief Constructor con parámetros
   * @param i Número de filas
   * @param j Número de columnas
   */
  Scene(int i=3, int j=3);

  /**
   * @brief Método que dibuja la escena
   * @param dots  Dibujado modo puntos
   * @param edges Dibujado modo alambre
   * @param solid Dibujado sólido
   * @param chess Dibujado sólido ajedrezz
   */
  void drawScene(bool dots, bool edges, bool solid, bool chess);
};

#endif
