/*____________________________________________________________ */
//               Fichero cuerpo.cpp
/*____________________________________________________________ */

#include "../include/cuerpo.h"

//-----------------------------------------------------------------------//

Cuerpo::Cuerpo() : cilindro("ply_rev/cilindro.ply", 20){}

//-----------------------------------------------------------------------//

void Cuerpo::draw(bool dots, bool edges, bool solid, bool chess, float i){
  // Barra vertical
  glPushMatrix();
  glTranslatef(0,20,0);
  glScalef(2,40,2);
  cilindro.draw(dots, edges, solid, chess);
  glPopMatrix();

  // Mecanismo del regulador
  glPushMatrix();
  glTranslatef(0,17.5,0);
  mecanismo.draw(dots, edges, solid, chess, i);
  glPopMatrix();
}
