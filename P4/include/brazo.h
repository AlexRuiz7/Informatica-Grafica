/*____________________________________________________________ */
//               Fichero brazo.h
/*____________________________________________________________ */

#ifndef BRAZO_H
#define BRAZO_H

#include <GL/gl.h>
#include <math.h>
#include "esfera.h"
#include "objectrev.h"
#include "objectply.h"

class Brazo : public Object3d{
private:
  Esfera p;
  ObjectRev esfera;
  ObjectRev cilindro;
  ObjectPLY b;

public:
  Brazo();

  void draw(bool dots, bool edges, bool solid, bool chess);

};

#endif
