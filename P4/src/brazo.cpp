/*____________________________________________________________ */
//               Fichero brazo.cpp
/*____________________________________________________________ */

#include "../include/brazo.h"

//-----------------------------------------------------------------------//

Brazo::Brazo() : p(20, 0.5), esfera("ply_rev/esfera.ply", 20), cilindro("ply_rev/cilindro.ply", 20), b("modelos_ply/beethoven.ply"){}

//-----------------------------------------------------------------------//

void Brazo::draw(bool dots, bool edges, bool solid, bool chess){
  // Barra
  glPushMatrix();
  glScalef(1.5,30,1.5);
  glTranslatef(0,0.5,0);
  cilindro.draw(dots, edges, solid, chess);
  glPopMatrix();

  // Esfera
  glPushMatrix();
  glTranslatef(0,31,0);
  glScalef(5,5,5);
  esfera.draw(dots, edges, solid, chess);
  glPopMatrix();
/*
  // DEFENSA PRÁCTICA (1) //
  glPushMatrix();
  glTranslatef(-3.8,15.5,0);
  glRotatef(90,0,0,1);
  glScalef(0.5,0.5,0.5);
  b.draw(dots, edges, solid, chess);
  glPopMatrix();

  // DEFENSA PRÁCTICA (2) //
  glPushMatrix();
  glTranslatef(-5.5,31,0);
  glRotatef(90,0,0,1);
  glScalef(0.5,0.5,0.5);
  b.draw(dots, edges, solid, chess);
  glPopMatrix();
*/
}
