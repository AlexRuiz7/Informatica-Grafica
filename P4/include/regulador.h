/*____________________________________________________________ */
//               Fichero regulador.h
/*____________________________________________________________ */

#ifndef REGULADOR_H
#define REGULADOR_H

#include "cuerpo.h"

class Regulador : public Object3d{

private:
  Cuerpo cuerpo;
  Cube cubo;

public:
  Regulador();

  void draw(bool dots, bool edges, bool solid, bool chess, float v, float i);

};

#endif
