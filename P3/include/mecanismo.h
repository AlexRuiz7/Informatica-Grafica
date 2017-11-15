
/*____________________________________________________________ */
//               Fichero mecanismo.h
/*____________________________________________________________ */

#ifndef MECANISMO_H
#define MECANISMO_H

#include "deslizador.h"
#include "cabezal.h"

class Mecanismo : public Object3d{

private:
  Cabezal cabezal;
  Deslizador deslizador;

public:
  Mecanismo();

  void draw(bool dots, bool edges, bool solid, bool chess, float i);

};

#endif
