/*____________________________________________________________ */
//               Fichero object3d.h
/*____________________________________________________________ */

/**
 * @author Alejandro Ruiz Becerra
 * @date   2017
 * @brief Clase raíz de la jerarquía de objetos 3D. Contiene las primitivas y
 *        métodos generales para representar objetos 3D mediante OpenGL.
 */

#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <vector>
#include "vertex.h"
#include <math.h>
#include <GL/glu.h>

class Object3d{
protected:
  /**
   * Vector de vértices que define al objeto. Cada vértice contiene las coordenadas
   * x,y,z que componen un punto en el espacio.
   */
  vector<_vertex3f> vertices;
  /**
   * Vector de triángulos que define las fonteras del objeto. Cada triángulo está
   * compuesto por 3 vértices, en orden antihorario.
   */
  vector<_vertex3ui> triangles;

  /**
   * Vector que contiene los valores del vector normal de cada triángulo del objeto.
   */
  vector<_vertex3f> f_normals;

  /**
  * Vector que contiene los valores del vector normal de cada vértice. Además,
  * tiene un cuarto componente que almacena el número de triángulos que contienen
  * a dicho vértice.
  */
  vector<_vertex4f> v_normals;

  /**
   * Vector que contiene las coordenadas de texturas del objeto.
   */
  vector<_vertex2f> tex_coords;
  GLuint textura_id;

  float tX, tY, tZ;
  float sX, sY, sZ;
  bool rotX, rotY, rotZ;
  float alpha, beta;


private:
  /**
   * @brief Dibuja el objeto en según el modo de visualización activo.
   * Esta función es invocada por las funciones siguientes:
   *
   * @see drawPoints
   * @see drawEdges
   * @see drawSolid
   * @see drawSolidChess
   */
  void drawObject();

  /**
   * @brief Dibuja el objeto en modo puntos
   */
  void drawPoints();

  /**
   * @brief Dibuja el objeto en modo aristas.
   */
  void drawEdges();

  /**
   * @brief Dibuja el objeto en modo sólido.
   */
  void drawSolid();

  /**
   * @brief Dibuja el objeto en modo ajedrez.
   */
  void drawSolidChess();

public:
  /**
  * @brief Constructor de los objetos Object3d
  */
  Object3d();

  /**
   * @brief Genera el vector normal correspondiente a cada triángulo y cada vértice.
   *
   * El vector normal es utilizado para la iluminación y el suavizado de la
   * superficie del objeto. OpenGL utiliza este vector para calcular como incide
   * la luz sobre la superficie del objeto, dependiendo del ángulo que forman
   * este y la dirección desde la que proviene la luz.
   *
   * El cálculo de las normales es algo que debe hacerse manualmente, y se ha
   * procedido de la forma que se especifíca en el siguiente enlace:
   *
   * https://en.wikibooks.org/wiki/OpenGL_Programming/Intermediate/Normals
   *
   * Editado: añadido generación de normales de cada vértice
   *
   * para cada vertice
   *  vertice.normal = 0, 0, 0
   *
   * para cada cara
   *  calcular normal
   *  para cada vertice en cara
   *  vertice.normal += normal de cara
   *
   * para cada vertice
   *   vertice.normaliza normal
   *
   * fuente: http://www.stratos-ad.com/forums/index.php?topic=1099.0
   */
  void generateNormals();

  /**
   * @brief Aplica el material definido al objeto.
   */
  void applyChromeMaterial();

  /**
   * @brief Aplica el material definido al objeto.
   */
  void applyJadeMaterial();

  /**
   * @brief Aplica el material definido al objeto.
   */
  void applyGoldMaterial();

  /**
   * @brief Selector del modo de dibujado
   * @param dots  Modo puntos
   * @param edges Modo alambre
   * @param solid Modo sólido
   * @param chess Modo sólido ajedrez
   */
  void draw(bool dots, bool edges, bool solid, bool chess);

//############################################################################//
//      Métodos propios
//############################################################################//

  /**
   * @brief Devuelve la cantidad de puntos del modelo.
   * @return [description]
   */
  int getVertexSize();

  /**
   * @brief Devuelve la cantidad de triángulos del modelo.
   * @return [description]
   */
  int getTrianglesSize();

  /**
   * @brief Redimensiona el objeto.
   *
   * En este método se redimensiona el objeto haciendo uso de las tranformaciones
   * de OpenGL, concretamente la funcionalidad glScalatef.
   * El escalado se realiza de manera uniforme para mantener las propociones del
   * objeto, y por simplicidad.
   *
   * @param x Factor de redimensión en el eje X.
   * @param y Factor de redimensión en el eje Y.
   * @param z Factor de redimensión en el eje Z.
   */
  void scalate(float x, float y, float z);

  /**
   * @brief Mueve el objeto en el espacio.
   *
   * Mediante este método parametrizado se permite mover el objeto por el espacio
   * virtual. El objeto se puede mover en 10 direcciones diferentes, de forma
   * horizontal en los ejes X y Z, verticalmente en el eje Y, y diagonalmente en
   * las composiciones del eje XZ. Los únicos movimientos no implementados son
   * aquellos relativos al desplazamiento diagonal con el eje Y.
   *
   * En principio, el objeto se mueve por el espacio desplazándose una unidad
   * entera cada vez, en cualquiera de los ejes y movimientos permitidos
   * mencionados anteriormente. Esto se puede modificar indicando distintos
   * parametros para los ejes X Y Z en la llamada al método.
   *
   * @param x Posiciones x a mover.
   * @param y Posiciones y a mover.
   * @param z Posiciones z a mover.
   */
  void move(float x, float y, float z);

  /**
   * @brief Rota el objeto sobre los ejes X, Y, Z.
   *
   * @param alpha Especifíca los grados sobre los que se va a realizar la rotación.
   * @param x     Indica si se va a rotar sobre el eje X. [0-1] -> False -> True
   * @param y     Indica si se va a rotar sobre el eje Y. [0-1] -> False -> True
   * @param z     Indica si se va a rotar sobre el eje Z. [0-1] -> False -> True
   */
  void rotate(float alpha, bool x, bool y, bool z);

};

#endif
