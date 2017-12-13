/*____________________________________________________________ */
//               Fichero objectrev.h
/*____________________________________________________________ */

/**
 * @author Alejandro Ruiz Becerra
 * @date   2017
 * @brief Clase para crear objetos gráficos por revolución.
 */

#ifndef OBJECTREV_H
#define OBJECTREV_H

#include "object3d.h"
#include <string>

class ObjectRev : public Object3d {
private:
  bool tapa_sup, tapa_inf, cuerpo;
  int tapas, N;
  vector<_vertex3f> V;
  vector<_vertex3ui> T;


  float ang_min, ang_max;
  int div;

  /**
   * @brief Apertura y lectura de fichero PLY
   * Este método abre y lee la información almacenada en un fichero PLY para
   * crear un objeto gráficamente. Hace uso de las utilidades definidas en la
   * clase auxiliar _file_ply
   *
   * @param file Camino relativo del fichero PLY a leer.
   */
  void openPLY(string file);

  /**
   * @brief Generación del modelo completo
   * Calcula el nº de tapas que tiene el modelo. Los puntos de las tapas están
   * almacenados en el fichero PLY del objeto a construir, en la primera
   * posición está la tapa inferior y en la última posición la tapa superior.
   * Para crear el cuerpo del modelo omitimos estos puntos.
   * Codificamos las tapas mediante el nº de caras(fichero PLY):
   *    si faces=0: sin tapas
   *    si faces=1: tapa sup
   *    si faces=2: tapa inf
   *    si faces=3: dos tapas
   *
   * Una vez definidas qué tapas se deben construir se procede a generar el
   * modelo de vértices y caras.
   * @see generateVertex
   * @see generateFaces
   */
  void generateModel();

  /**
   * @brief Genera los vértices del objeto.
   *
   */
  void generateVertex();

  /**
   * @brief Genera las caras del objeto
   *
   */
  void generateFaces();


  void generateVertexSector();

public:
  /**
   * @brief Constructor
   * @param file     Camino relativo al fichero PLY dónde se encuentra el perfil
   *                 del objeto
   * @param perfiles Número de secciones a ganerar. Utilizar números no divisores
   *                 de 360 puede generar errores en el modelo.
   * @see openPLY
   * @see generateModel
   * @see generateNormals
   * @see applyMaterial
   */
  ObjectRev(string file, int perfiles=20, float angulo_min=0, float angulo_max=360);
  // DEFENSA PRÁCTICA
};

#endif
