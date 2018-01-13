/*____________________________________________________________ */
//               Fichero deslizador.cpp
/*____________________________________________________________ */

#include "../include/deslizador.h"

//-----------------------------------------------------------------------//

Deslizador::Deslizador() : cilindro("ply_rev/cilindro.ply", 20){
  x=0;
  y=0;
}

//-----------------------------------------------------------------------//

void Deslizador::draw(bool dots, bool edges, bool solid, bool chess, float i){
  y = 7.5*sin((45-1.5*i)*M_PI/180);
  x = 7.5-7.5*cos((45-1.5*i)*M_PI/180);
  // Cilindro central
  glPushMatrix();
  glScalef(8,5,5);
  glTranslatef(0,0.5,0);
  glRotatef(90,0,0,1);
  cilindro.draw(dots, edges, solid, chess);
  glPopMatrix();

  // Brazo izquierdo
  glPushMatrix();
  glTranslatef(-11+x,2.0+y,0);
  glRotatef(45,0,0,1);
  glRotatef(i*2,0,0,1);
  glScalef(1,16,1);
  cilindro.draw(dots, edges, solid, chess);
  glPopMatrix();

  // Brazo derecho
  glPushMatrix();
  glTranslatef(11-x,2.0+y,0);
  glRotatef(-45,0,0,1);
  glRotatef(-i*2,0,0,1);
  glScalef(1,16,1);
  cilindro.draw(dots, edges, solid, chess);
  glPopMatrix();

  // Cubo inferior
  glPushMatrix();
  glTranslatef(2.5,-7.25,0);
  glScalef(1,15,1);
  cubo.draw(dots, edges, solid, chess);
  glPopMatrix();

  // Defensa Práctica (1)
/*
  // Brazo izquierdo
  glPushMatrix();
  glTranslatef(0,2+y,-9+x);
  glRotatef(-45,1,0,0);
  glRotatef(-i*2,1,0,0);
  glScalef(1,16,1);
  cilindro.draw(dots, edges, solid, chess);
  glPopMatrix();

  // Brazo derecho
  glPushMatrix();
  glTranslatef(0,2+y,9-x);
  glRotatef(45,1,0,0);
  glRotatef(i*2,1,0,0);
  glScalef(1,16,1);
  cilindro.draw(dots, edges, solid, chess);
  glPopMatrix();

  // Defensa Práctica (2)
  glPushMatrix();
  glTranslatef(3.5,2.5,0);
  glRotatef(-45,0,0,1);
  glRotatef(-i*2,0,0,1);
  brazo.draw(dots, edges, solid, chess);
  glPopMatrix();
*/
}
