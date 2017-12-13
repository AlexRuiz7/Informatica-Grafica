
/*____________________________________________________________ */
//               Fichero dedo.h
/*____________________________________________________________ */

#ifndef DEDO_H
#define DEDO_H

#include <GL/glut.h>
#include "cube.h"

class Dedo : public Cube{
private:
  Cube cubo;
public:
    Dedo();

    void draw(short mode);

};

#endif
