/*____________________________________________________________ */
//               Fichero regulador.cpp
/*____________________________________________________________ */

#include "../include/regulador.h"

//-----------------------------------------------------------------------//

Regulador::Regulador(){}

//-----------------------------------------------------------------------//

void Regulador::draw(bool dots, bool edges, bool solid, bool chess, float v, float i){
  // Base del regulador
  glPushMatrix();
  glTranslatef(0,0.5,0);
  glScalef(30,1,30);
  cubo.draw(dots, edges, solid, chess);
  glPopMatrix();

  // Regulador
  glPushMatrix();
  glTranslatef(0,1,0);
  glRotatef(v/2,0,1,0);
  cuerpo.draw(dots, edges, solid, chess,i);
  glPopMatrix();
}
