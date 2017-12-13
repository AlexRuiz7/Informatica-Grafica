
/*____________________________________________________________ */
//               Fichero robot.cpp
/*____________________________________________________________ */


#include "robot.h"

//----------------------------------------------------------------------------//

  Robot::Robot(){};

//----------------------------------------------------------------------------//

  void Robot::draw(short mode){
    setPinza(1);
    glPushMatrix();
    glTranslatef(0,2.5,0);
    glScalef(10,5,10);
    cubo.draw(mode);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,5,0);
    glRotatef(a,0,0,1);
    glRotatef(b,0,1,0);
    brazo2.draw(mode);
    glPopMatrix();
  }

//----------------------------------------------------------------------------//

    void Robot::setPinza(float r){
      brazo2.setPinza(r);
    }

//----------------------------------------------------------------------------//

    void Robot::setBrazo1(float r){
      brazo2.setBrazo1(r);
    }

//----------------------------------------------------------------------------//

    void Robot::setBrazo2(float x, float y){
      a = x;
      b = y;
    }
