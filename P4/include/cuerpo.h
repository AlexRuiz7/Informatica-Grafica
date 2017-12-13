/*____________________________________________________________ */
//               Fichero cuerpo.h
/*____________________________________________________________ */

#ifndef CUERPO_H
#define CUERPO_H

#include "mecanismo.h"

class Cuerpo : public Object3d{

private:
  Mecanismo mecanismo;
  ObjectRev cilindro;

public:
  Cuerpo();

  void draw(bool dots, bool edges, bool solid, bool chess, float i);

};

#endif
