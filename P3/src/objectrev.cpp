/*____________________________________________________________ */
//               Fichero objectrev.cpp
/*____________________________________________________________ */

#include "../include/objectrev.h"
#include "../include/file_ply_stl.h"

//--------------  DEFENSA PRÁCTICA ----------------------------------------//

ObjectRev::ObjectRev(string file, int perfiles, float angulo_min, float angulo_max){
  ang_min = angulo_min*M_PI/180;
  ang_max = angulo_max*M_PI/180;
  div=0;

  N = perfiles;
  openPLY(file);
  generateModel();
  generateNormals();
  applyMaterial();
}

//-----------------------------------------------------------------------//

void ObjectRev::openPLY(string file){
  _file_ply reader;
  reader.open(file);
  reader.read(V, T);
  reader.close();
}

//-----------------------------------------------------------------------//

void ObjectRev::generateModel(){
  switch(T.size()){
    case 0:   tapa_sup = tapa_inf = false;            break;
    case 1:   tapa_sup = true;    tapa_inf = false;   break;
    case 2:   tapa_sup = false;   tapa_inf = true;    break;
    case 3:   tapa_sup = tapa_inf = true;             break;
  }
  tapas = tapa_sup + tapa_inf;
  cuerpo = (V.size()==3 && tapas==2) ? false : true;

  generateVertex();
  //generateVertexSector();
  generateFaces();
}

//-----------------------------------------------------------------------//

void ObjectRev::generateVertexSector(){
  float angulo = (ang_max-ang_min)/N;   // Radianes de aumento en cada iteración
  int n = V.size();                     // Nº de puntos del perfil
  _vertex3f punto;
  vertices.clear();

  // Inserción de la tapa inferior
  if(tapa_inf)  vertices.push_back(V[0]);

  // Generación e inserción de puntos
  for(int i=0; i<N; i++)
    for(int j=tapa_inf; j<n-tapa_sup; j++){
        punto.x = V[j].x*cos(ang_min + angulo*i);
        punto.y = V[j].y;
        punto.z = V[j].x*sin(ang_min + angulo*i);

        vertices.push_back(punto);
    }

  // Inserción de la tapa inferior
  if(tapa_sup)  vertices.push_back(V[n-1]);

  //std::cout << "Nº de puntos: " << vertices.size() << endl << endl;
}

//-----------------------------------------------------------------------//

void ObjectRev::generateVertex(){
  float angulo = 2*M_PI/N;          // Radianes de aumento en cada iteración
  int n = V.size();                 // Nº de puntos del perfil
  _vertex3f punto;
  vertices.clear();

  // Inserción de la tapa inferior
  if(tapa_inf)  vertices.push_back(V[0]);

  // Generación e inserción de puntos
  for(int i=0; i<N; i++)
    if( (i*angulo>=ang_min) && (i*angulo<=ang_max) ){
      for(int j=tapa_inf; j<n-tapa_sup; j++){
          punto.x = V[j].x*cos(angulo*i);
          punto.y = V[j].y;
          punto.z = V[j].x*sin(angulo*i);

          vertices.push_back(punto);
        }
      div++;
    }

  // Inserción de la tapa inferior
  if(tapa_sup)  vertices.push_back(V[n-1]);

  //std::cout << "Nº de puntos: " << vertices.size() << endl << endl;
}

//-----------------------------------------------------------------------//

void ObjectRev::generateFaces(){
  int n = V.size()-tapas;                 // Nº de puntos del perfil
  _vertex3ui cara;
  triangles.clear();

  //#########################################################################
  // TAPAS
  //
  // Se itera sobre N divisiones uniendo los puntos de las tapas con los puntos
  // colindantes del cuerpo del objeto. Como n almacena el nº de puntos que
  // contiene el perfil del objeto, omitiendo los puntos de las tapas, se itera
  // aumentando las coordenadas n puntos, según convenga.
  // tapas:   tapa_inf -> pos: 0         tapa_sup  ->  pos: último   en vertices

  if(tapa_inf)
    for(int i=0; i<N; i++){
      cara._0 = 0;
      cara._1 = (n*i)%(vertices.size()-tapas)+tapa_inf;
      cara._2 = (n+n*i)%(vertices.size()-tapas)+tapa_inf;
      triangles.push_back(cara);
  }

  if(tapa_sup)
    for(int i=1; i<=N; i++){
      cara._0 = vertices.size()-1;
      cara._1 = (n-1+n*i)%(vertices.size()-tapas)+tapa_inf;
      cara._2 = (n*i-1)%(vertices.size()-tapas)+tapa_inf;
      triangles.push_back(cara);
    }

  //#########################################################################
  // CUERPO
  //
  // Se itera sobre N divisiones, y sobre cada división o sección se itera sobre
  // los n puntos que componen el perfil.
  // La operación % se utiliza para cerrar el objeto, uniendo los útlimos puntos
  // con los primeros.
  // Como el primer punto es el de la tapa inferior(si tiene) se salta(+tapa_inf)
  // En el modulo multiplico se restan las tapas al número total de vértices
  // generados ya que no intervivene en la generación dl cuerpo del modelo.
  // Además las tapas ya han sido generadas justo arriba.

  if(cuerpo)
    for(int i=0; i<N; i++)
      for(int j=0; j<n-1; j++){
      cara._0 = (n*i+j)%(vertices.size()-tapas)+tapa_inf;
      cara._1 = (1+n*i+j)%(vertices.size()-tapas)+tapa_inf;
      cara._2 = (n+n*i+j)%(vertices.size()-tapas)+tapa_inf;
      triangles.push_back(cara);

      cara._0 = (1+n*i+j)%(vertices.size()-tapas)+tapa_inf;
      cara._1 = (n+1+n*i+j)%(vertices.size()-tapas)+tapa_inf;
      cara._2 = (n+n*i+j)%(vertices.size()-tapas)+tapa_inf;
      triangles.push_back(cara);
    }

  std::cout << "Nº de caras: " << triangles.size() << endl << endl;
}
