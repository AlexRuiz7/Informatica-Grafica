/*____________________________________________________________ */
//               Fichero loader.h
/*____________________________________________________________ */

/**
 * @author Alejandro Ruiz Becerra
 * @date   2017
 * @brief  Esta clase ofrece la funcionalidad de leer un directorio y crear los
 *         caminos relativos a os ficheros PLY que contiene de forma que puedan
 *         ser usados posteriormente para ser leídos y construir el objeto que
 *         representan.
 */

#ifndef LOADER_H
#define LOADER_H

#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<dirent.h>
#include<fcntl.h>
#include<string.h>
#include<vector>
#include<iostream>

using namespace std;

class Loader{

private:
  /**
   *  Directorio sobre el que se van a realizar las operaciones. Se abrirá y leerá
   *  su contenido, buscando ficheros PLY.
   */
  DIR *d;
  /**
   *  Puntero que iterará sobre cada elemento dentro del directorio. A partir de
   *  este struct se podrá acceder a las propiedades del archivo, en nuestro caso
   *  sólo nos interesa el nombre [ds->name]
   */
  struct dirent *ds;
  /**
   *  Cadenas de caracteres para gestionar los nombres y los caminos relativos
   *  de los ficheros PLY encontrados.
   *
   *  fichero: contendrá el nombre de cada fichero del directorio leído.
   *  ext:     extensión del fichero. Se obtiene a partir de la cadena anterior.
   *  dir:     directorio sobre el que se va a leer.
   */
  char *fichero, *ext, *dir;
  /**
   *  Cadena de tipo sting, contenedora del camino relativo a un fichero PLY
   *  encontrado. Será almacenado en el vector ply.
   */
  string destino;
  /**
   *  Vector que contiene el camino relativo a cada elemento PLY encontrado en
   *  el directorio d .
   */
  std::vector<string> ply;

  /**
   * Abre el directorio destino haciendo uso de utilidades del sistema.
   * Se gestionan casos de error que puedan producirse en la apertura (EXIT_FAILURE).
   */
  void open_dir();

  /**
   * Lee el directorio elemento a elemento, obteniendo sus nombres, identificando
   * ficheros PLY y almacenando sus caminos relativos en el vector ply.
   */
  void read_dir();

public:
  /**
   * @brief Constructor
   * En el constructor se lee el directorio por defecto que contiene los ficheros
   * PLY. Para ello se hace uso de librerías y funcionalidades del sistema para
   * acceso al sistema de ficheros.
   */
  Loader(string path);

  /**
   * @brief Devuelve el tamaño del vector ply, es decir, el número de ficheros
   * que se han leído en el directorio objetivo.
   *
   * @return Valor entero con el tamaño del vector ply.
   */
  int getSize();

  /**
   * @brief Consultor de un elemnto de la lista de nombres a los ficheros PLY.
   *
   * Este método devuelve el elemento i de vector que contiene los nombres de los
   * ficheros PLY que se han leído con anterioridad.
   * De este modo, este string puede usarse para construir el objeto a partir de
   * dicho archivo, que será leído por la clase file_ply_stl y construido por la
   * clase objectply.
   *
   * @param  i Posición del elemento a consultar.
   * @return   String que contiene el camino relativo al fichero PLY que ocupa
   *           la posición i en el vector
   */
  string getElement(int i);
};

#endif
