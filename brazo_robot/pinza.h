
/*____________________________________________________________ */
//               Fichero pinza.h
/*____________________________________________________________ */

#ifndef PINZA_H
#define PINZA_H

#include "dedo.h"

class Pinza : public Dedo{
private:
  Cube cubo;
  Dedo dedo;
  float t;
public:
  Pinza();

  void draw(short mode);
  void setPinza(float s);
};

#endif
