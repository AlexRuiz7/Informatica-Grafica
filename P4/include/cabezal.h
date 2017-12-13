/*____________________________________________________________ */
//               Fichero cabezal.h
/*____________________________________________________________ */

#ifndef CABEZAL_H
#define CABEZAL_H

#include "brazo.h"

class Cabezal : public Object3d{

private:
  Brazo brazo;
  ObjectRev cilindro;

public:
  Cabezal();

  void draw(bool dots, bool edges, bool solid, bool chess, float i=0);

};

#endif
