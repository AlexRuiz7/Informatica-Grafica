/*____________________________________________________________ */
//               Fichero esfera.h
/*____________________________________________________________ */

/**
 * @author Alejandro Ruiz Becerra
 * @date   2017
 * @brief Clase para generar el perfil de una esfera y ser creada posteriormente
 * por revolución.
 */

#include "object3d.h"

class Esfera : public Object3d{
private:
  float radio, revY;

  /**
   * @brief Genera las coordenadas del perfil de la esfera.
   */
  void generateProfile();

  /**
   * @brief Genera el PLY almacenando el perfil creado.
   */
  void generatePLY();

public:
  /**
   * @brief Constructor de la clase esfera.
   *
   * Genera el perfil de una esfera con las caracteristicas dadas y las almacena
   * en un fichero PLY dentro de la carpeta correspondiente. Este fichero será
   * leído más adelante por la clase ObjectRev, que creará el resto de coordenadas
   * mediante revolución, por lo tanto, esta clase no generá el objeto Esfera,
   * crea la información necesaria para crearla.
   * En el main, se deberá crear un objeto de esta clase para generar el perfil
   * y luego otro objeto de la clase ObjectRev para crearlo.
   *
   * @param r  Radio de la esfera.
   * @param rY Cantidad de puntos en el ejeY
   */
  Esfera(int rY=20, float r=2);
};
