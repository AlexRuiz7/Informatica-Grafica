
/*____________________________________________________________ */
//               Fichero brazo1.h
/*____________________________________________________________ */


#ifndef BRAZO1_H
#define BRAZO1_H

#include "pinza.h"

class Brazo1 : public Pinza{
private:
  Cube cubo;
  Pinza pinza;

public:
  Brazo1();

  void draw(short mode);
  void setPinza(float r);
};

#endif
