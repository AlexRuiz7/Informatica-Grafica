/*____________________________________________________________ */
//               Fichero cabezal.cpp
/*____________________________________________________________ */

#include "../include/cabezal.h"

//-----------------------------------------------------------------------//

Cabezal::Cabezal() : cilindro("ply_rev/cilindro.ply", 20) {}

//-----------------------------------------------------------------------//

void Cabezal::draw(bool dots, bool edges, bool solid, bool chess, float i){
  // Cilindro central
  glPushMatrix();
  glScalef(8,5,5);
  glTranslatef(0,0.5,0);
  glRotatef(90,0,0,1);
  cilindro.draw(dots, edges, solid, chess);
  glPopMatrix();

  // Brazo izquierdo
  glPushMatrix();
  glTranslatef(-3.25,2.5,0);
  glRotatef(135,0,0,1);
  glRotatef(-i*1.8,0,0,1);
  glRotatef(180,0,1,0);   // Defensa práctica. Rota el brazo 180º (Beethoven aparecía boca abajo.)
  brazo.draw(dots, edges, solid, chess);
  glPopMatrix();

  // Brazo derecho
  glPushMatrix();
  glTranslatef(3.25,2.5,0);
  glRotatef(-135,0,0,1);
  glRotatef(i*1.8,0,0,1);
  brazo.draw(dots, edges, solid, chess);
  glPopMatrix();

/*
  // DEFENSA PRÁCTICA (1) ~ 2 brazos adicionales //

  // Brazo trasero
  glPushMatrix();
  glTranslatef(0,2.5,1);
  glRotatef(45,1,0,0);
  glRotatef(90,1,0,0);
  glRotatef(-90,0,1,0);
  glRotatef(i*1.8,0,0,1);
  brazo.draw(dots, edges, solid, chess);
  glPopMatrix();

  // Brazo frontal
  glPushMatrix();
  glTranslatef(0,2.5,-1);
  glRotatef(-45,1,0,0);
  glRotatef(-90,1,0,0);
  glRotatef(90,0,1,0);
  glRotatef(i*1.8,0,0,1);
  brazo.draw(dots, edges, solid, chess);
  glPopMatrix();

  // DEFENSA PRÁCTICA (2) ~ Invertir brazo //
  float y = 7.5*sin((45-1.5*i)*M_PI/180);
  float x = 7.5-7.5*cos((45-1.5*i)*M_PI/180);

  // Brazo derecho
  glPushMatrix();
  glTranslatef(11-x,-y+2,0);
  glRotatef(45+i*1.8,0,0,1);
  //glRotatef(i*1.8,0,0,1);
  glScalef(1,16,1);
  cilindro.draw(dots, edges, solid, chess);
  glPopMatrix();
  */
}
