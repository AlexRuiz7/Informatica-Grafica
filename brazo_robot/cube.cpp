
/*____________________________________________________________ */
//               Fichero cube.cpp
/*____________________________________________________________ */


#include "cube.h"

//-----------------------------------------------------------------------//

Cube::Cube(float l){

  // Vértices del cubo en sentido antihorario

	vertices={
		{-l,l,l},		// 0
		{l,l,l},		// 1
		{l,l,-l},		// 2
		{-l,l,-l},	// 3
		{-l,-l,l},	// 4
		{l,-l,l},		// 5
		{l,-l,-l},	// 6
		{-l,-l,-l}	// 7
	};

	// Vértices de los triángulos que representa el cuadrado.

	triangles={
		{0,1,2},
		{0,2,3},
		{1,5,6},
		{1,6,2},
		{3,2,6},
		{3,6,7},
		{0,4,1},
		{1,4,5},
		{0,3,4},
		{4,3,7},
		{4,7,6},
		{4,6,5}
	};
}

//-----------------------------------------------------------------------//

void Cube::draw(short mode){
	switch(mode){
		case 0:
			drawPoints();
			break;
		case 1:
			drawEdges();
			break;
		case 2:
			drawSolid();
			break;
		case 3:
			drawSolidChess();
			break;
		case 4:
			drawAll();
			break;
	}
}

//-----------------------------------------------------------------------//

void Cube::drawPoints(){
  glColor3f(0,0,0);
  glPointSize(6);
  glBegin(GL_POINTS);
  for(int i=0; i<vertices.size(); i++)
    glVertex3fv((GLfloat *) &vertices[i]);
  glEnd();
}

//-----------------------------------------------------------------------//

void Cube::draw(){
  //glColor3f(0,1,0);
  glPointSize(6);
  glBegin(GL_TRIANGLES);
  for(int i=0; i<triangles.size(); i++)
    for(int j=0; j<3; j++)
      glVertex3fv((GLfloat *) &vertices[triangles[i][j]]);
  glEnd();
}

//-----------------------------------------------------------------------//

void Cube::drawEdges(){
  glColor3f(1,0,0);
  draw();
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

//-----------------------------------------------------------------------//

void Cube::drawSolid(){
  draw();
  glPolygonMode(GL_FRONT, GL_FILL);
}

//-----------------------------------------------------------------------//

void Cube::drawSolidChess(){
  bool negro;
  glBegin(GL_TRIANGLES);
  for(int i=0; i<triangles.size(); i++){
    if(!negro){
      glColor3f(0,0,0); // Negro
      negro = true;
    }
    else{
      glColor3f(1,0,0); // Rojo
      negro = false;
    }
    for(int j=0; j<3; j++)
      glVertex3fv((GLfloat *) &vertices[triangles[i][j]]);
  }

  glEnd();
}

//-----------------------------------------------------------------------//

void Cube::drawAll(){
  drawPoints();
  drawSolid();
  drawEdges();
}
