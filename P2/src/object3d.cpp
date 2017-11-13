/*____________________________________________________________ */
//               Fichero object3d.cpp
/*____________________________________________________________ */

#include <GL/glut.h>
#include "../include/object3d.h"

//-----------------------------------------------------------------------//

Object3d::Object3d(){
  generateNormals();
  applyMaterial();
}

//-----------------------------------------------------------------------//

void Object3d::drawObject(){
  glBegin(GL_TRIANGLES);
  for(int i=0; i<triangles.size(); i++)
    for(int j=0; j<3; j++){
      glNormal3fv((GLfloat *) &normals[i][j]);
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
  for(int i=0; i<triangles.size()-1; i+=2){
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

void Object3d::applyMaterial(){
  /*
    GLfloat ambient[]={0.2125, 0.1275, 0.054, 1.0},
  					diffuse[]={0.714, 0.4284, 0.18144, 1.0},
  					specular[]={0.393548, 0.271906, 0.166721, 1.0},
  					shininess[]= {25.6};
    GLfloat ambient[]={0.24725, 0.2245, 0.0645, 1.0},
  					diffuse[]={0.34615, 0.3143, 0.0903, 1.0},
  					specular[]={0.797357, 0.723991, 0.208006, 1.0},
  					shininess[]= {83.2};

    GLfloat ambient[]={1.0, 1.0, 1.0, 1.0},
  					diffuse[]={1.0, 0.5, 0.5, 1.0},
  					specular[]={0.797357, 0.723991, 0.608006, 1.0},
  					shininess[]= {83.2};
  */

  GLfloat ambient[]={0, 0, 0, 0.01},
          diffuse[]={0.2, 0.2, 0.2, 0.1},
          specular[]={1, 1, 1, 1},
          shininess[]= {128};

  	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
  	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}
