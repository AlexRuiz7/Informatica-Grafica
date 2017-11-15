
/*____________________________________________________________ */
//               Fichero mecanismo.cpp
/*____________________________________________________________ */

#include "../include/mecanismo.h"

//-----------------------------------------------------------------------//

Mecanismo::Mecanismo(){}

//-----------------------------------------------------------------------//

void Mecanismo::draw(bool dots, bool edges, bool solid, bool chess, float i){
  glPushMatrix();
  glTranslatef(0,i*0.85,0);
  deslizador.draw(dots, edges, solid, chess, i);
  glPopMatrix();

  // Cabezal
  glPushMatrix();
  glTranslatef(0,22,0);
  cabezal.draw(dots, edges, solid, chess, i);
  glPopMatrix();
}
