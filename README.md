# Prácticas de Informática Gráfica

Prácticas realizadas en la asignatura de Informática Gráfica, cursada en el
tercer curso del grado de Ingeniería Informática de la Universidad de Granada.

## Requisitos y dependencias

  * OpenGL (Open Graphics Library)
  * GLUT (OpenGL Utility Toolkit)
  * GLU (OpenGL Library Utility)

  El comando `apt-get install freeglut3-dev` debería instalar las tres librerías
  mencionadas anteriormente.

## Práctica 1: Modelado y Visualización de objetos 3D sencillos

  En esta etapa se construyen dos objetos simples, un cubo, y un tetraedro.
  Para se ellos crean las estructuras de datos necesarias para definirlos y se
  utilizan las primitivas de dibujo de OpenGL.
  Para la contrucción de los objetos se introducen a mano las coordenadas de sus
  vértices y los vértices que componen cada uno de los triángulos en los que se
  divide el objeto.

## Práctica 2: Modelos PLY y Poligonales

  Esta práctica consiste por una parte, en visualizar objetos almacenados en
  ficheros de texto en formato PLY, los cuales contienen toda la información
  necesaria para generar el objeto que definen, y por otra, generar objetos
  poligonales sencillos como los de la práctica 1 de forma automática, mediante
  la técnica de generación por revolución.

## Práctica 3: Modelos Jerárquicos

  En esta práctica trabajamos con objetos algo más complejos, construidos mediante
  composición de objetos más simples, ya creados en la practica 1 y la practica 2.
  Para ello es necesario hacer uso de las transformaciones que nos proporciona
  OpenGL, lo que también nos permite realizar animaciones sencillas en los objetos.

  En esta práctica se ha construido un regulador de Watt a partir de cilindros,
  esferas y cubos.

## Práctica 4: Iluminación y Texturas

  Aplicación de iluminación y texturas a los modelos para incrementar el realismo.

  Para la iluminación es necesario generar las normales de los objetos, tanto de sus trángulos como de sus vértices. Luego, se definen materiales que se aplicarán a los objetos, así como las luces que intervendrán en las escena.

  En la práctica se han implementado 3 materiales que se pueden aplicar a los objetos en tiempo de ejecución (cromo, jade y oro) y 3 luces, dos móviles (una roja y otra amarilla) y una fija de color blanco. Las luces móviles rotan alrededor del objeto, horizontal o verticalmente. También pueden alejarse y acercarse al origen. Todo en tiempo de ejecución.

  En cuanto a la textura, se ha creado un nuevo objeto denominado Tablero, en el que se puede aplicar una textura (cualquier imagen en formato jpg). Se generan las coordenadas de textura mientras se construye el objeto. La textura puede activarse como cualquier otro modo de visualización. Para una visualización óptima se debe visualizar en modo iluminación, activar el sombreado de Gouraud y, por supuesto, en modo sólido/relleno.


## Práctica 5: Interacción y eventos de ratón

  En esta práctica se implementa el control e interacción con la escena mediante
  el ratón, haciendo uso de los eventos de ratón y las funcionalidades de GLU.

## Mapa de teclas

### Controles generales

  * Modos de visualización:
    * P: activa/desactiva el modo de dibujado por puntos.
    * L: activa/desactiva el modo de dibujado alambre.
    * S: activa/desactiva el modo de dibujado por superficie.
    * C: activa/desactiva el modo de dibujado ajedrez.

  * Cambiar objetos:
    * F1: cambia al objeto anterior.
    * F2: cambia al siguiente objeto.

  * Control de la cámara:
    * RePag: aumenta el zoom.
    * AvPag: reduce el zoom.
    * :arrow_up:: mueve la cámara hacia arriba.
    * :arrow_down:: mueve la cámara hacia abajo.
    * :arrow_left:: mueve la cámara hacia la izquierda.
    * :arrow_right:: mueve la cámara hacia la derecha.

  * Transformaciones:
    * Rotaciones:
      * R: activa/desactiva la rotación en el eje X.
      * T: activa/desactiva la rotación en el eje Y.
      * Y: activa/desactiva la rotación en el eje Z.
    * Escalados:
      * :heavy_plus_sign:: aumenta el objeto.
      * :heavy_minus_sign:: reduce el objeto.
    * Traslaciones:
      * :zero:: mueve el objeto negativamente en el eje Y.  (Y-1)
      * :one:: mueve el objeto en la diagonal XZ.           (X-1, Z+1)
      * :two:: mueve el objeto positivamente en el eje Z.   (Z+1)
      * :three:: mueve el objeto en la diagonal XZ.         (X+1, Z+1)
      * :four:: mueve el objeto negativamente en el eje X.  (X-1)
      * :five:: mueve el objeto positivamente en el eje Y.  (Y+1)
      * :six:: mueve el objeto positivamente en el eje X.   (X+1)
      * :seven:: mueve el objeto en la diagonal XZ.         (X-1, Z-1)
      * :eight:: mueve el objeto negativamente en el eje Z. (Z-1)
      * :nine:: mueve el objeto en la diagonal XZ.          (X+1, Z-1)

  * Iluminación:
    * L: activa/desactiva el modo iluminación.
    * M: alterna entre sombreado plano o sombreado de Gouraud.
    * G: activa/desactiva la rotación de la luz posicional.
    * H: alterna la rotación de la luz posicional entre horizontal o vertical.
    * B: acerca la luz posicional al origen.
    * N: aleja la luz posicional del origen.
    * F: activa/desactiva la rotación de la luz direccional.
    * V: alterna la rotación de la luz direccional entre horizontal o vertical.
    * U: acerca la luz direccional al origen.
    * I: aleja la luz direccional del origen.
    * F3: activa/desactiva la luz direccional móvil (roja).
    * F4: activa/desactiva la luz posicional (amarilla).
    * F5: activa/desactiva la luz direccional fija (blanca).
    * F6: aplica material al objeto (cromo).
    * F7: aplica material al objeto (jade).
    * F8: aplica material al objeto (oro).

  * Textura:
    * X: activa/desactiva la textura. (Solo implementado en tablero)
         (Activar primero modo iluminación, modo sólido y suavizado de Gouraud)

### Controles específicos de la práctica 3

  * J: aumenta la velocidad de rotación del regulador de Watt.
  * k: reduce la velocidad de rotación del regulador de Watt.

### Control de la cámara con el ratón. Práctica 5

  * Rueda del ratón: zoom de la cámara.
  * Botón de la rueda: alterna entre proyección paralela y perspectiva.
  * Botón derecho (mantenido): mueve la cámara siguiendo el movimiento del ratón mientras está mantenido.
  * Botón izquierdo (click): selección de objeto (no implementado).


## Notas adicionales

  * Para cambiar el color de fondo descomentar o editar la línea `glClearColor`
