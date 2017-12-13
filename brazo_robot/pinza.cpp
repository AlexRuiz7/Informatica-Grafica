
/*____________________________________________________________ */
//               Fichero pinza.cpp
/*____________________________________________________________ */


#include "pinza.h"

//----------------------------------------------------------------------------//

  Pinza::Pinza(){t=0;}

//----------------------------------------------------------------------------//

  void Pinza::draw(short mode){
    glPushMatrix();
    glTranslatef(0,0.5,0);
    glScalef(5,1,6);
    cubo.draw(mode);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-t,0,0);
    glTranslatef(2,4,0);
    dedo.draw(mode);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(t,0,0);
    glTranslatef(-2,4,0);
    dedo.draw(mode);
    glPopMatrix();
  }

  //----------------------------------------------------------------------------//

  void Pinza::setPinza(float s){
    t = s;
  }
