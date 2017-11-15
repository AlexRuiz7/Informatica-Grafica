/*____________________________________________________________ */
//               Fichero cube.cpp
/*____________________________________________________________ */

#include "../include/cube.h"

//-----------------------------------------------------------------------//

Cube::Cube(float l){

	// Dado el lado, las coordenadas de los puntos del cubo serán la mitad para
	// x, y, z
	l /= 2;
  // Vértices del cubo en sentido antihorario
	vertices={
		{-l,l,l},		// 0
		{l,l,l},		// 1
		{l,l,-l},		// 2
		{-l,l,-l},	// 3
		{-l,-l,l},	// 4
		{l,-l,l},		// 5
		{l,-l,-l},	// 6
		{-l,-l,-l}	// 7
	};

	// Vértices de los triángulos que representa el cuadrado.
	triangles={
		{0,1,2},
		{0,2,3},
		{1,5,6},
		{1,6,2},
		{3,2,6},
		{3,6,7},
		{0,4,1},
		{1,4,5},
		{0,3,4},
		{4,3,7},
		{4,7,6},
		{4,6,5}
	};

	generateNormals();
	applyMaterial();
}
