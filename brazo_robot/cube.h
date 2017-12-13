
/*____________________________________________________________ */
//               Fichero cube.h
/*____________________________________________________________ */

#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include "vertex.h"
#include "GL/glut.h"

class Cube{

private:
  vector<_vertex3f> vertices;
  vector<_vertex3ui> triangles;

public:
  Cube(float l=0.5);

  void draw();
  void draw(short mode);
  void drawPoints();
  void drawEdges();
  void drawSolid();
  void drawSolidChess();
  void drawAll();
};

#endif
