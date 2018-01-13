/*____________________________________________________________ */
//               Fichero scene.cpp
/*____________________________________________________________ */

#include "../include/scene.h"

//-----------------------------------------------------------------------//

Scene::Scene(int i, int j){
  this->i = i;
  this->j = j;

  objeto =  new ObjectPLY("modelos_ply/beethoven.ply");
}

//-----------------------------------------------------------------------//

void Scene::drawScene(bool dots, bool edges, bool solid, bool chess){
	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
      glPushMatrix();
			glTranslatef(15-15*j,0,15-15*i);
      objeto->draw(dots,edges,solid,chess);
      glPopMatrix();
		}
	}
}
