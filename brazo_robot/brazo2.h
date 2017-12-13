
/*____________________________________________________________ */
//               Fichero brazo2.h
/*____________________________________________________________ */

#ifndef BRAZO2_H
#define BRAZO2_H

#include "brazo1.h"

class Brazo2 : public Brazo1{
private:
  Cube cubo;
  Brazo1 brazo1;
  float a;
public:
  Brazo2();

  void draw(short mode);
  void setBrazo1(float x);
  void setPinza(float r);
};

#endif
