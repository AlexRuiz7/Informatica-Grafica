
/*____________________________________________________________ */
//               Fichero deslizador.h
/*____________________________________________________________ */

#ifndef DESLIZADOR_H
#define DESLIZADOR_H

#include <GL/gl.h>
#include "objectrev.h"
#include "cube.h"

//#include "brazo.h"  // Utilizado en la defensa

class Deslizador : public Object3d{

private:
  ObjectRev cilindro;
  Cube cubo;
  float x,y;

  //Brazo brazo;      // Utilizado en la defensa

public:
  Deslizador();

  void draw(bool dots, bool edges, bool solid, bool chess, float i);

};

#endif
