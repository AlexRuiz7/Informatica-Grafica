/*____________________________________________________________ */
//               Fichero object3d.cpp
/*____________________________________________________________ */

#include <GL/glut.h>
#include "../include/object3d.h"

//-----------------------------------------------------------------------//

Object3d::Object3d(){}

//-----------------------------------------------------------------------//

void Object3d::drawObject(){
  glBegin(GL_TRIANGLES);
  for(int i=0; i<triangles.size(); i++)
    for(int j=0; j<3; j++){
      glNormal3fv((GLfloat *) &normals[i][0]);
      glVertex3fv((GLfloat *) &vertices[triangles[i][j]]);
    }
  glEnd();
}

//-----------------------------------------------------------------------//

void Object3d::drawPoints(){
  glColor3f(0.5,0,1);
  glPointSize(6);
  glBegin(GL_POINTS);
  for(int i=0; i<vertices.size(); i++)
    glVertex3fv((GLfloat *) &vertices[i]);
  glEnd();
}

//-----------------------------------------------------------------------//

void Object3d::drawEdges(){
  glColor3f(0,1,0);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  drawObject();
}

//-----------------------------------------------------------------------//

void Object3d::drawSolid(){
  glColor3f(1,0,0);
  glPolygonMode(GL_FRONT, GL_FILL);
  drawObject();
}

//-----------------------------------------------------------------------//

void Object3d::drawSolidChess(){
  glPolygonMode(GL_FRONT, GL_FILL);
  glBegin(GL_TRIANGLES);
  for(int i=0; i<triangles.size(); i+=2){
    glColor3f(0,0,0);               // Negro
    for(int j=0; j<3; j++)
      glVertex3fv((GLfloat *) &vertices[triangles[i][j]]);

    glColor3f(1,0,0);               // Rojo
    for(int j=0; j<3; j++)
      glVertex3fv((GLfloat *) &vertices[triangles[i+1][j]]);
  }
  glEnd();
}

// MÉTODOS PROPIOS

//-----------------------------------------------------------------------//

void Object3d::scalate(float x, float y, float z){
  glScalef(x,z,y);
}

//-----------------------------------------------------------------------//

void Object3d::move(float x, float y, float z){
  glTranslatef(x,y,z);
}

//-----------------------------------------------------------------------//

void Object3d::rotate(float alpha, float x, float y, float z){
  glRotatef(alpha,x,y,z);
}

//-----------------------------------------------------------------------//

void Object3d::generateNormals(){
  _vertex3f a, b, n;
  normals.resize(triangles.size());

  for(int i=0; i<triangles.size(); i++){
    a = vertices[triangles[i][1]] - vertices[triangles[i][0]];
    b = vertices[triangles[i][2]] - vertices[triangles[i][0]];

    n = a.cross_product(b);
    n.normalize();
    normals[i] = n;
  }
}

//-----------------------------------------------------------------------//

 // TODO Work In Progress
void Object3d::applyMaterial(){
  // Material cromado http://devernay.free.fr/cours/opengl/materials.html
  GLfloat ambient[]={0.25, 0.25, 0.25, 1.0},
          diffuse[]={0.4, 0.4, 0.4, 1.0},
          specular[]={0.774597, 0.774597, 0.774597, 1.0},
          shininess= 0.6*128;

  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}

//-----------------------------------------------------------------------//

void Object3d::draw(bool dots, bool edges, bool solid, bool chess){
  if(dots)	 drawPoints();
	if(chess)	 drawSolidChess();
  if(edges)	 drawEdges();
  if(solid)	 drawSolid();
}
