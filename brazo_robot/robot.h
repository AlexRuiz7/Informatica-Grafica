
/*____________________________________________________________ */
//               Fichero robot.h
/*____________________________________________________________ */

#ifndef ROBOT_H
#define ROBOT_H

#include "brazo2.h"

class Robot : public Brazo2{
private:
  Cube cubo;
  Brazo2 brazo2;
  float a, b;
public:
  Robot();

  void draw(short);
  void setPinza(float);
  void setBrazo1(float);
  void setBrazo2(float, float);
};

#endif
