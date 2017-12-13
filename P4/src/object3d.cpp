/*____________________________________________________________ */
//               Fichero object3d.cpp
/*____________________________________________________________ */

#include <GL/glut.h>
#include "../include/object3d.h"
#include "../cImg/CImg.h"

//-----------------------------------------------------------------------//

Object3d::Object3d(){}

//-----------------------------------------------------------------------//

void Object3d::drawObject(){
  if(!triangles.empty()){
    glBegin(GL_TRIANGLES);
    for(int i=0; i<triangles.size(); i++){
      if(!f_normals.empty())
        glNormal3fv((GLfloat *) &f_normals[i][0]);
      for(int j=0; j<3; j++){
        if(!v_normals.empty())
          glNormal3fv((GLfloat *) &v_normals[triangles[i][j]]);
        if(tex_coords.size())
          glTexCoord2fv((GLfloat *) &tex_coords[triangles[i][j]]);
        glVertex3fv((GLfloat *) &vertices[triangles[i][j]]);
      }
    }
    glEnd();
  }
}

//-----------------------------------------------------------------------//

void Object3d::drawPoints(){
  if(!vertices.empty()){
    glColor3f(0.5,0,1);
    glPointSize(6);
    glBegin(GL_POINTS);
    for(int i=0; i<vertices.size(); i++)
      glVertex3fv((GLfloat *) &vertices[i]);
    glEnd();
  }
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
  if(!triangles.empty()){
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_TRIANGLES);
    for(int i=0; i<triangles.size(); i+=2){
      if(!f_normals.empty())
        glNormal3fv((GLfloat *) &f_normals[i][0]);

      glColor3f(0,0,0);               // Negro
      for(int j=0; j<3; j++){
        if(!v_normals.empty())
          glNormal3fv((GLfloat *) &v_normals[triangles[i][j]]);
        if(!tex_coords.empty())
          glTexCoord2fv((GLfloat *) &tex_coords[triangles[i][j]]);
        glVertex3fv((GLfloat *) &vertices[triangles[i][j]]);
      }
      glColor3f(1,0,0);               // Rojo
      for(int j=0; j<3; j++){
        if(!v_normals.empty())
          glNormal3fv((GLfloat *) &v_normals[triangles[i+1][j]]);
        if(!tex_coords.empty())
          glTexCoord2fv((GLfloat *) &tex_coords[triangles[i+1][j]]);
        glVertex3fv((GLfloat *) &vertices[triangles[i+1][j]]);
      }
    }
    glEnd();
  }
}


//-----------------------------------------------------------------------//

void Object3d::generateNormals(){
  _vertex3f a, b, n;
  f_normals.resize(triangles.size());
  v_normals.resize(vertices.size());
  for(int i=0; i<v_normals.size(); i++){
    v_normals[i].x = 0;  v_normals[i].y = 0;  v_normals[i].z = 0;  v_normals[i].w = 0;
  }

  // Normales de las caras
  for(int i=0; i<triangles.size(); i++){
    a = vertices[triangles[i][1]] - vertices[triangles[i][0]];
    b = vertices[triangles[i][2]] - vertices[triangles[i][0]];

    n = a.cross_product(b);
    n.normalize();
    f_normals[i] = n;

    // Normales de los vértices
    for(int j=0; j<3; j++){
      v_normals[triangles[i][j]] += n;
      v_normals[triangles[i][j]].w += 1;
    }
  }

  for(int i=0; i<v_normals.size(); i++){
    v_normals[i] /= v_normals[i].w;
    v_normals[i].normalize();
  }
}


//-----------------------------------------------------------------------//

void Object3d::applyChromeMaterial(){
  // Material cromado
  GLfloat ambient[]={0.25, 0.25, 0.25, 1.0},
          diffuse[]={0.4, 0.4, 0.4, 1.0},
          specular[]={0.774597, 0.774597, 0.774597, 1.0},
          shininess= 76.8;

  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}

//-----------------------------------------------------------------------//

void Object3d::applyJadeMaterial(){
  // Material Jade
  GLfloat ambient[]={0.135, 0.2225, 0.1575, 0.95},
          diffuse[]={0.54, 0.89, 0.63, 0.95},
          specular[]={0.316228, 0.316228, 0.316228, 0.95},
          shininess= 12.8;

  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}

//-----------------------------------------------------------------------//

void Object3d::applyGoldMaterial(){
  // Material Oro
  GLfloat ambient[]={0.24725, 0.2245, 0.0645, 1.0},
          diffuse[]={0.34615, 0.3143, 0.0903, 1.0},
          specular[]={0.797357, 0.723991, 0.208006, 1.0},
          shininess= 83.2;

  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}


//-----------------------------------------------------------------------//

void Object3d::draw(bool dots, bool edges, bool solid, bool chess){
  glPushMatrix();
  glScalef(sX,sY,sZ);
  glTranslatef(tX,tY,tZ);
  glRotatef(alpha,rotX,rotY,rotZ);

  if(dots)	 drawPoints();
	if(chess)	 drawSolidChess();
  if(edges)	 drawEdges();
  if(solid)	 drawSolid();
  glPopMatrix();
}

//############################################################################//
//      Métodos propios
//############################################################################//

int Object3d::getVertexSize(){ return vertices.size(); }

//-----------------------------------------------------------------------//

int Object3d::getTrianglesSize(){  return triangles.size();  }

//-----------------------------------------------------------------------//

void Object3d::scalate(float x, float y, float z){
  sX = x;   sY = y;   sZ = z;
}

//-----------------------------------------------------------------------//

void Object3d::move(float x, float y, float z){
  tX = x;   tY = y;   tZ = z;
}

//-----------------------------------------------------------------------//

void Object3d::rotate(float alpha, bool x, bool y, bool z){
  this->alpha = alpha; rotX = x; rotY = y;  rotZ = z;
}
