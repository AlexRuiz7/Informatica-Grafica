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

class Object3d{
protected:
  /**
   * Vector de vértices que define al objeto. Cada vértice cotiene las coordenadas
   * x,y,z que componen un punto en el espacio.
   */
  vector<_vertex3f> vertices;
  /**
   * Vector de triángulos que define las fonteras del objeto. Cada triángulo está
   * compuesto por 3 vértices, en orden antihorario.
   */
  vector<_vertex3ui> triangles;

  vector<_vertex3f> normals;

public:
  /**
   * @brief
   * Constructor de los objetos Object3d
   */
  Object3d();

  /**
   * @brief
   * Dibuja el objeto en según el modo de visualización activo. Esta función es
   * invocada por las funciones siguientes:
   *
   * @see drawPoints
   * @see drawEdges
   * @see drawSolid
   * @see drawSolidChess
   */
  void drawObject();

  /**
   * @brief
   * Dibuja el objeto en modo puntos
   */
  void drawPoints();

  /**
   * @brief
   * Dibuja el objeto en modo aristas.
   */
  void drawEdges();

  /**
   * @brief
   * Dibuja el objeto en modo sólido.
   */
  void drawSolid();

  /**
   * @brief
   * Dibuja el objeto en modo ajedrez.
   */
  void drawSolidChess();

  // Métodos propios

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
  void rotate(float alpha, float x, float y, float z);

  /**
   * @brief Genera el vector normal correspondiente a cada triángulo.
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
   */
  void generateNormals();

  /**
   * @brief Dibujo puntos que representan los vectores normales de la superficie.
   */
  void drawNormals();
};

#endif
