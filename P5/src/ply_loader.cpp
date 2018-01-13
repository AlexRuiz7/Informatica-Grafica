/*____________________________________________________________ */
//               Fichero loader.cpp
/*____________________________________________________________ */

#include "../include/ply_loader.h"

Loader::Loader(string path){
  // Pasa la cadena string a char
  dir = new char[path.length()+1];
  strcpy(dir, path.c_str());

  open_dir();     // Abre el directorio
  read_dir();     // Lee las entradas del directorio
  closedir(d);    // Cierra el directorio
  delete[] dir;   // Libera memoria
}

//-----------------------------------------------------------------------//

void Loader::open_dir(){
  d = opendir(dir);
  if(d == NULL){
    printf("Error: No se puede abrir el directorio\n");
    exit(EXIT_FAILURE);
  }
}

//-----------------------------------------------------------------------//

void Loader::read_dir(){
  while((ds = readdir(d)) != NULL){
    fichero = ds->d_name;
    ext = strrchr(fichero, '.');            // Extraemos la extensión del archivo
    if(strcmp(ext, ".ply") == 0){           // Comprobamos con la extensión PLY
      destino = dir;
      destino += fichero;
      cout << destino << endl;
      ply.push_back(destino);
    }
  }
  cout << endl << ply.size() << " ficheros leídos\n";
}

//-----------------------------------------------------------------------//

int Loader::getSize(){   return ply.size();  }

//-----------------------------------------------------------------------//

string Loader::getElement(int i){   return ply[i]; }
