
/*____________________________________________________________ */
//               Fichero dedo.cpp
/*____________________________________________________________ */


#include "dedo.h"

//----------------------------------------------------------------------------//

  Dedo::Dedo(){};

//----------------------------------------------------------------------------//

  void Dedo::draw(short mode){
    glPushMatrix();
    glScalef(1,6,6);
    cubo.draw(mode);
    glPopMatrix();
  }
