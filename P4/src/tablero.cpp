/*____________________________________________________________ */
//               Fichero tablero.cpp
/*____________________________________________________________ */

#include "../include/tablero.h"

//-----------------------------------------------------------------------//

void Tablero::generateFaces(){
  _vertex3ui cara;

  // Parte superior
  for(int i=0; i<m; i++){
    for(int j=0; j<m; j++){
      // Triángulos inferiores
      cara._0=i+j*(m+1);
      cara._1=i+(m+1)+j*(m+1);
      cara._2=i+(m+2)+j*(m+1);
      triangles.push_back(cara);

      // Triángulos superiores
      cara._0=i+j*(m+1);
      cara._1=i+(m+2)+j*(m+1);
      cara._2=i+1+j*(m+1);
      triangles.push_back(cara);
    }
  }

  // Parte inferior
  for(int i=0; i<m; i++){
    for(int j=0; j<m; j++){
      cara._0=(m+1)*(m+1)+i+j*(m+1);
      cara._1=(m+1)*(m+1)+i+1+j*(m+1);
      cara._2=(m+1)*(m+1)+i+(m+1)+j*(m+1);
      triangles.push_back(cara);

      cara._0=(m+1)*(m+1)+1+i+j*(m+1);
      cara._1=(m+1)*(m+1)+i+(m+2)+j*(m+1);
      cara._2=(m+1)*(m+1)+i+(m+1)+j*(m+1);
      triangles.push_back(cara);
    }
  }

  // Lado izquierdo
  for(int i=0; i<m; i++){
    cara._0=i*(m+1);
    cara._1=(m+1)*(m+1)+i*(m+1);
    cara._2=(m+1)+i*(m+1);
    triangles.push_back(cara);

    cara._0=cara._2;
    cara._2=cara._1+m+1;
    triangles.push_back(cara);
  }

  // Lado derecho
  for(int i=0; i<m; i++){
    cara._0=m+i*(m+1);
    cara._1=m+m+1+i*(m+1);
    cara._2=(m+1)*(m+1)+m+m+1+i*(m+1);
    triangles.push_back(cara);

    cara._1=cara._2;
    cara._2=(m+1)*(m+1)+m+i*(m+1);
    triangles.push_back(cara);
  }

  // Lado superior
  for(int i=0; i<m; i++){
    cara._0=i;
    cara._1=i+1;
    cara._2=(m+1)*(m+1)+i+1;
    triangles.push_back(cara);

    cara._1=cara._2;
    cara._2=(m+1)*(m+1)+i;
    triangles.push_back(cara);
  }

  // Lado inferior
  for(int i=0; i<m; i++){
    cara._0=i+m*(m+1);
    cara._1=cara._0+(m+1)*(m+1);
    cara._2=cara._1+1;
    triangles.push_back(cara);

    cara._1=cara._2;
    cara._2=cara._0+1;
    triangles.push_back(cara);
  }

}

//-----------------------------------------------------------------------//

void Tablero::generateVertex(){
  _vertex3f coord;
  coord.y=0.15;

  float aumento_x=tam_cuadrado_x;
  float aumento_z=tam_cuadrado_z;

  for(int h=0; h<2;h++){
    if(h==1)  coord.y=-coord.y;
    for(int i=0; i<=m; i++){
      coord.z=z_ini+aumento_z*i;
      for(int j=0; j<=m; j++){
        coord.x=x_ini+aumento_x*j;
        vertices.push_back(coord);

        //////////////////////////////////////////////////
        //  Textura distribuida por todos los cuadrados
        //
        tex_coords.push_back({1.0f/m*j,1.0f/m*i});
        //////////////////////////////////////////////////
        //  Textura aplicada a cada cuadrado
        //
        // if(i%2==0)
        //   (j%2==0) ? tex_coords.push_back({0,0}) : tex_coords.push_back({1,0});
        // else
        //   (j%2==0) ? tex_coords.push_back({0,1}) : tex_coords.push_back({1,1});
        //////////////////////////////////////////////////
      }
    }
  }
}

//-----------------------------------------------------------------------//

Tablero::Tablero(float x_ini, float z_ini, float x_fin, float z_fin, int m){
  if(x_fin<x_ini){
    float temp=x_ini;
    x_ini=x_fin;
    x_fin=temp;
  }
  if(z_fin<z_ini){
    float temp=z_ini;
    z_ini=z_fin;
    z_fin=temp;
  }

  this->x_ini = x_ini;
  this->z_ini = z_ini;
  this->x_fin = x_fin;
  this->z_fin = z_fin;
  this->m = m;
  lado_x = x_fin - x_ini;
  tam_cuadrado_x = lado_x / m;
  lado_z = z_fin - z_ini;
  tam_cuadrado_z = lado_z / m;

  generateVertex();
  generateFaces();
  generateNormals();
}

//-----------------------------------------------------------------------//

Tablero::Tablero() : Tablero(-5, -5, 5, 5, 5) {}
