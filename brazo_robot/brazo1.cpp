
/*____________________________________________________________ */
//               Fichero brazo1.cpp
/*____________________________________________________________ */


#include "brazo1.h"

//----------------------------------------------------------------------------//

  Brazo1::Brazo1(){}

//----------------------------------------------------------------------------//

  void Brazo1::draw(short mode){
    glPushMatrix();
    glTranslatef(0,6,0);
    glScalef(3,12,3);
    cubo.draw(mode);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,12,0);
    pinza.draw(mode);
    glPopMatrix();
  }

//----------------------------------------------------------------------------//

  void Brazo1::setPinza(float r){
    pinza.setPinza(r);
  }
