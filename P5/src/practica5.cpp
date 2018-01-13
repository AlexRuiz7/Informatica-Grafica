//**************************************************************************
//	Práctica 5
//
//	Alejandro Ruiz Becerra -- 2017
//
//	Informática Gráfica
//
//**************************************************************************

#include <GL/glut.h>
#include <ctype.h>
#include "include/CImg.h"
#include "include/scene.h"

// Tamaño de los ejes
const int AXIS_SIZE=5000;
// Variables que definen la posición de la cámara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;
// Variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width, Window_height, Front_plane, Back_plane;
// Variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50, UI_window_pos_y=50, UI_window_width=500, UI_window_height=500;

//***************************************************************************
//
//***************************************************************************

void clear_window(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

//***************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

bool paralela=false;
GLfloat zoom = 1.0f;

void change_projection(){
	float aspect=(float)Window_width/(float)Window_height;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_trasero)
	// Front_plane>0  Back_plane>PlanoDelantero)
	if(paralela)
		glOrtho(-Window_width*zoom, Window_width*zoom, -Window_height*zoom, Window_height*zoom, Front_plane, Back_plane);
	else
		glFrustum(-Window_width*aspect, Window_width*aspect, -Window_height*aspect, Window_height*aspect, Front_plane, Back_plane);
}

//***************************************************************************
// Función para definir la transformación de vista (posicionar la cámara)
//***************************************************************************

void change_observer(){
	// Posición del observador
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0,0,-Observer_distance);
	glRotatef(Observer_angle_x,1,0,0);
	glRotatef(Observer_angle_y,0,1,0);
}

//***************************************************************************
// Función que dibuja los ejes utilizando la primitiva gráfica de lineas
//***************************************************************************

void draw_axis(){
	glBegin(GL_LINES);
	// Eje X, color rojo
	glColor3f(1,0,0);
	glVertex3f(-AXIS_SIZE,0,0);
	glVertex3f(AXIS_SIZE,0,0);
	// Eje Y, color verde
	glColor3f(0,1,0);
	glVertex3f(0,-AXIS_SIZE,0);
	glVertex3f(0,AXIS_SIZE,0);
	// Eje Z, color azul
	glColor3f(0,0,1);
	glVertex3f(0,0,-AXIS_SIZE);
	glVertex3f(0,0,AXIS_SIZE);
	glEnd();
}


//***************************************************************************
// Objetos
//***************************************************************************

Scene escena;
vector<Object3d> _objects = {escena};

// Variables de control para la animación del regulador de Watt.
float vel=0, i=0;
// Indice que indica la pos en el vector del objecto a dibujar.
unsigned short object = 0;
// Variables de estado del modo de dibujo
bool dots  = true, edges = false, solid = false, chess = false;
// Variables para implementar la rotación sobre los ejes
float alpha = 0.0f, beta, epsilon, delta;
bool rotX = false, rotY = false, rotZ = false;
// Variables para implementar el desplazamiento del objeto.
float tX = 0.0f, tY = 0.0f, tZ = 0.0f;
// Variables para implementar el escalado del objeto.
float sX = 1.0f, sY = 1.0f, sZ = 1.0f;
// Variables para el control de la luz.
bool lighting= false, amb_light= true, spot_light= true, dir_light= true;
// Variables de control para la rotación de la luz posicional y direccional.
bool rsl = false, rdl= false;
// Variables que controlan el radio de rotación de la luz posicional y direccional.
float msl=0, mdl= 0;
// Variables para alternar entre rotación vertical u horizontal en las luces.
bool vertical= false, vertical_dir= false;
// Identificador de textura
GLuint textura_id;
// Variables para el control de la cámara mediante ratón
bool left_mouse_button, right_mouse_button;
int init_mouse_x, init_mouse_y;


//***************************************************************************
// Función de incialización de las luces
//***************************************************************************

void initLighting(){
	glEnable(GL_NORMALIZE);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	// Luz ambiental
	GLfloat global_ambient[] =		{0.4, 0.4, 0.4, 1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

	// Luz direccional roja. Implementada rotación.
	GLfloat light_ambient[] =		{0.0, 0.0, 0.0, 1.0};
	GLfloat light_diffuse[] =		{0.9, 0.5, 0.5, 1.0};
	GLfloat light_specular[] =	{1.0, 1.0, 1.0, 1.0};
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	// Luz posicional (Spot Light). Implementada rotación.
	GLfloat lightColor1[] = {0.7, 0.5, 0.0, 1.0};
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightColor1);
	//glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 60.0);

	// Luz direccional blanca. Fija.
	GLfloat lightColor2[] = {0.7, 0.7, 0.7, 1.0};
	// Posicionada a la izquierda del objeto
	GLfloat lightPos2[] = {-10, 0.5, 0.5, 0};
	glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, lightColor2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, lightColor2);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);
}

//***************************************************************************
// Función para alternar la iluminación
//***************************************************************************

void lightingSwitch(){
	if(lighting){
		glDisable(GL_LIGHT0);		glDisable(GL_LIGHT1);		glDisable(GL_LIGHT2);
		glDisable(GL_LIGHTING);	lighting=false;					glClearColor(1,1,1,1);
	}
	else{
		glClearColor(1,1,1,1);	lighting=true;					glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);		glEnable(GL_LIGHT1);		glEnable(GL_LIGHT2);
	}
}

//***************************************************************************
// Función para activar/desactivar las luces
//***************************************************************************

void lightOnOff(bool signal, int l){
	if(signal)
		switch(l){
			case 0:		glEnable(GL_LIGHT0);		amb_light=true;			break;
			case 1:		glEnable(GL_LIGHT1);		spot_light=true;		break;
			case 2:		glEnable(GL_LIGHT2);		dir_light=true;			break;
		}
	else
		switch(l){
			case 0:		glDisable(GL_LIGHT0);		amb_light=false;		break;
			case 1:		glDisable(GL_LIGHT1);		spot_light=false;		break;
			case 2:		glDisable(GL_LIGHT2);		dir_light=false;		break;
		}
}

//***************************************************************************
// Función para altenar entre sombreado plano o Gouraud
//***************************************************************************

void switchShadowType(){
	static bool gouraud = true;

	gouraud	?	glShadeModel(GL_FLAT) : glShadeModel(GL_SMOOTH);
	gouraud = !gouraud;
}

//***************************************************************************
// Función que implementa la rotación de la luz posicional
//***************************************************************************

void moveSpotLight(){
	GLfloat position[] = { 40.0f+msl, 0.0, 0, 1.0 };
	GLfloat position_v[] = {0.0, 40.0f+msl, 0.0, 1.0 };
	if(vertical){
		glPushMatrix();
		if(rsl){
			glRotatef (alpha, -1.0, 0.0, 0.0);
			beta = alpha;
		}
		else	glRotatef (beta, -1.0, 0.0, 0.0);
	  glLightfv(GL_LIGHT1, GL_POSITION, position_v);
	  glTranslated(0.0, 10.0+msl, 0.0);
	  glDisable(GL_LIGHTING);
	  glColor3f(0.0, 1.0, 1.0);
	  glutWireCube(0.3);
	  glEnable(GL_LIGHTING);
	  glPopMatrix();
	}
	else{
		glPushMatrix();
		if(rsl){
			glRotatef (alpha, 0.0, -1.0, 0.0);
			beta = alpha;
		}
		else	glRotatef (beta, 0.0, -1.0, 0.0);
		glLightfv(GL_LIGHT1, GL_POSITION, position);
		glTranslated(10.0+msl, 0.0, 0.0);
		glDisable(GL_LIGHTING);
		glColor3f(0.0, 1.0, 1.0);
		glutWireCube(0.3);
		glEnable(GL_LIGHTING);
		glPopMatrix();
	}
}

//***************************************************************************
// Función que implementa la rotación de la luz direccional
//***************************************************************************

void moveDirectionalLight(){
	GLfloat position[] = { 45.0f+mdl, 1.0, 0, 1.0 };
	GLfloat position_v[] = {1.0, 45.0f+mdl, 0.0, 1.0 };
	if(vertical_dir){
		glPushMatrix();
		if(rdl){
			glRotatef (epsilon, 1.0, 0.0, 0.0);
			delta = epsilon;
		}
		else glRotatef(delta, 1.0, 0.0, 0.0);
	  glLightfv(GL_LIGHT0, GL_POSITION, position_v);
	  glTranslated(1.0, 5.0+mdl, 0.0);
	  glDisable(GL_LIGHTING);
	  glColor3f(1.0, 1.0, 0.0);
	  glutWireCube(0.3);
	  glEnable(GL_LIGHTING);
	  glPopMatrix();
	}
	else{
		glPushMatrix();
		if(rdl){
			glRotatef (epsilon, 0.0, 1.0, 0.0);
			delta = epsilon;
		}
		else glRotatef(delta, 0.0, 1.0, 0.0);
		glLightfv(GL_LIGHT0, GL_POSITION, position);
		glTranslated(5.0+mdl, 1.0, 0.0);
		glDisable(GL_LIGHTING);
		glColor3f(1.0, 1.0, 0.0);
		glutWireCube(0.3);
		glEnable(GL_LIGHTING);
		glPopMatrix();
	}
}

//***************************************************************************
// Función para activar o desactivar el modo textura.
//***************************************************************************

void enableTexture(){
	static bool tex = false;

	tex ? glDisable(GL_TEXTURE_2D) : glEnable(GL_TEXTURE_2D);
	tex = !tex;
}

//***************************************************************************
// Función llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// código de la tecla
// posición x del raton
// posición y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1, int x, int y){

	Tecla1 = toupper(Tecla1);
	switch(Tecla1){
		case 'P': 	dots 	= !dots;		break;
		case 'A':		edges = !edges;		break;
		case 'S':		solid = !solid;		break;
		case 'C':		chess =	!chess;		break;
		case 27:		exit(0);

		// Métodos propios

		// Desplazamiento
		case '1':		tX-=1; 					tZ+=1;					break;
		case '2':										tZ+=1;					break;
		case '3':		tX+=1; 					tZ+=1;					break;
		case '4':		tX-=1;													break;
		case '5':						tY+=1;									break;
		case '6':		tX+=1;													break;
		case '7':		tX-=1; 					tZ-=1;					break;
		case '8':										tZ-=1;					break;
		case '9':		tX+=1; 					tZ-=1;					break;
		case '0': 					tY-=1;									break;

		// Cambiar tamaño
		case '+':		sX=sY=sZ+=0.5;									break;
		case '-':	if(sX>0.5)	sX=sY=sZ-=0.5;				break;

		// Rotación
		case 'R':		rotX = !rotX;										break;
		case 'T':		rotY = !rotY;										break;
		case 'Y':		rotZ = !rotZ;										break;

		// Luz
		case 'L':		lightingSwitch(); 							break;
		case 'M': 	switchShadowType();		 					break;
		case 'X':		enableTexture();								break;
		case 'G': 	alpha = beta; 	rsl = !rsl;			break;
		case 'B': 	msl-=0.05;											break;
		case 'N': 	msl+=0.05;											break;
		case 'H':		vertical = !vertical;						break;
		case 'F': 	epsilon = delta; 	rdl = !rdl;		break;
		case 'V':		vertical_dir = !vertical_dir;		break;
		case 'U': 	mdl-=0.05;											break;
		case 'I':		mdl+=0.05;											break;
		// Animación ~ Práctica 3 ~
		case 'J':		if(i+0.1<=20)		i+=0.1;					break;
		case 'K':		if(i-0.1>=0)		i-=0.1;					break;
	}
	glutPostRedisplay();
}

//***************************************************************************
// Función llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la función:
// código de la tecla
// posición x del ratón
// posición y del ratón
//***************************************************************************

void special_keys(int Tecla1, int x, int y){

	switch (Tecla1){
		// Cambiar objetos
		case GLUT_KEY_F1:	object=(object+_objects.size()-1)%_objects.size();			break;
		case GLUT_KEY_F2:	object=(object+1)%_objects.size();											break;
		// Activar/desactivar luces
		case GLUT_KEY_F3:	amb_light  ? lightOnOff(false,0) : lightOnOff(true,0); break;
		case GLUT_KEY_F4:	spot_light ? lightOnOff(false,1) : lightOnOff(true,1); break;
		case GLUT_KEY_F5:	dir_light  ? lightOnOff(false,2) : lightOnOff(true,2); break;
		// Aplicación de materiales
		case GLUT_KEY_F6:					_objects[object].applyChromeMaterial();		break;
		case GLUT_KEY_F7:					_objects[object].applyJadeMaterial();			break;
		case GLUT_KEY_F8:					_objects[object].applyGoldMaterial();			break;
		// Control de la cámara
		case GLUT_KEY_LEFT:				Observer_angle_y++;												break;
		case GLUT_KEY_RIGHT:			Observer_angle_y--;												break;
		case GLUT_KEY_UP:					Observer_angle_x++;												break;
		case GLUT_KEY_DOWN:				Observer_angle_x--;												break;
		case GLUT_KEY_PAGE_UP:		Observer_distance/=1.2;										break;
		case GLUT_KEY_PAGE_DOWN:	Observer_distance*=1.2;										break;
	}
	glutPostRedisplay();
}

//***************************************************************************
// Función que dibuja los objetos
//***************************************************************************

void draw_objects(){
	// MÉTODOS PROPIOS
	_objects[object].move(tX,tY,tZ);										// Desplazamiento
	_objects[object].scalate(sX, sY, sZ);								// Escalado
	_objects[object].rotate(alpha,rotX,rotY,rotZ);			// Rotación	del objeto
	if(lighting) {
		moveSpotLight();										// Rotación de la luz posicional
		moveDirectionalLight();							// Rotación de la luz direccional
	}
	// FIN MÉTODOS PROPIOS
	// _objects[object].draw(dots, edges, solid, chess);		// Dibujado
	escena.drawScene(dots, edges, solid, chess);

	glutPostRedisplay();
}

//***************************************************************************
//
//***************************************************************************

void draw_scene(void){
	clear_window();
	change_observer();
	draw_axis();
	draw_objects();
	glutSwapBuffers();
}

//***************************************************************************
//
//***************************************************************************

// void pickScene(){
// 	for(int i=0; i<3; i++){
// 		for(int j=0; j<3; j++){
// 			glPushMatrix();
// 			glTranslatef(5-5*j,0,5-5*i);
// 			glLoadName(i*3+j+1);
// 			cubo.draw(dots,edges,solid,chess);
// 			glPopMatrix();
// 		}
// 	}
// }
//
// void pickHits(GLint hits, GLuint *buffer){
// 	cout << "\nHits: " << hits << endl;
//
// 	cout << "Numero: " << buffer[4] << endl;
// 	for (int i = 0; i < hits; i++){
//
// 		cout << "Min Z: " << buffer[i*4 + 1] << endl;
// 		cout << "Max Z: " << buffer[i*4 + 2] << endl;
// 		cout << "Nombre en la pila: " << buffer[i*4 + 3] << endl;
// 	}
// }
//
// void pick(unsigned int x, unsigned int y)  {
// 	int BUFFER_SIZE = 100;
// 	GLuint Selection_buffer[BUFFER_SIZE];
//   GLint hits, Viewport[4];
//
//   glGetIntegerv (GL_VIEWPORT, Viewport);
//   glSelectBuffer (BUFFER_SIZE, Selection_buffer);
//   glRenderMode (GL_SELECT);
//   glInitNames();
//   glPushName(0);
// 	pickScene();
//   glMatrixMode (GL_PROJECTION);
//   glLoadIdentity ();
//   gluPickMatrix ( x, Viewport[3]-y, 1, 1, Viewport);
// 	glFrustum(-Window_width, Window_width, -Window_height, Window_height, Front_plane, Back_plane);
//
// 	clear_window();
// 	change_projection();	// PROJECTION
// 	change_observer(); 		// MODELVIEW
// 	draw_scene();
//
//   hits = glRenderMode (GL_RENDER);
// 	// Obtener información de la selección y marcar el objeto seleccionado
//   if (hits>0)
//   	pickHits(hits, Selection_buffer);
//   // volver a dibujar la escena pero teniendo en cuenta si hay algún objeto seleccionado
// 	clear_window();
//   change_projection(); 	// PROJECTION
//   change_observer(); 		// MODELVIEW
//   draw_scene();
// }


//***************************************************************************
// Función que implementa el movimiento de la cámara mediante el ratón
//***************************************************************************

void mouseMotion(int x, int y){
	if(left_mouse_button){
		// Movimiento horizontal
		if(init_mouse_x < x)
			Observer_angle_y--;
		else if(init_mouse_x > x)
			Observer_angle_y++;
    // Movimiento vertical
		if(init_mouse_y < y)
			Observer_angle_x++;
		else if(init_mouse_y > y)
			Observer_angle_x--;

		// Actualizar estado del ratón
		init_mouse_x = x;
		init_mouse_y = y;
	}
	glutPostRedisplay();
}


//***************************************************************************
// Función que captura eventos del ratón
//***************************************************************************
// 	MOUSE_LEFT_BUTTON 	= 0,
// 	MOUSE_MIDDLE_BUTTON = 1,
// 	MOUSE_RIGHT_BUTTON 	= 2,
// 	MOUSE_SCROLL_UP 		= 3,
// 	MOUSE_SCROLL_DOWN 	= 4
void mouseButtons(int button, int state, int x, int y){

	switch (button) {
		case 0:
			right_mouse_button = (state == GLUT_UP);
			// pick(x,y);
			break;
		case 1:
			if(state == GLUT_DOWN)
				paralela = !paralela;

			change_projection();
			break;
		case 2:
    // * Capturo las coordenadas del ratón al hacer cick derecho
    // * Si el botón derecho es matenido y se mueve, comparar las coordenadas
    // iniciales con las actuales:
    // 	si (y_ini < y) --> el ratón se ha movido hacia abajo, camara va hacia arriba
    // 	else
    // 	si (x_ini < x) --> el ratón se ha movio hacia la derecha, camara va hacia la izquierda
    // 	* Actualizas información
			left_mouse_button = (state == GLUT_DOWN);
			init_mouse_x = x;		// Coordenada inical vertical
			init_mouse_y = y;		// Coordenada inical horizontal
			break;
		case 3:				// (Zoom in)
			if(paralela){
				zoom /= 1.02;
				if(zoom < 1)
					zoom = 1.0f;
				change_projection();
			}
			else
				Observer_distance /= 1.02;
			break;
		case 4:				// (Zoom out)
			if(paralela){
				zoom *= 1.02;
				change_projection();
			}
			else
				Observer_distance *= 1.02;
			break;
	}
}


//***************************************************************************
// Función llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1, int Alto1){
	glViewport(0, 0, Ancho1, Alto1);
	change_projection();
	glutPostRedisplay();
}

//***************************************************************************
// Función de incialización
//***************************************************************************

void initialize(void){
	// Se inicalizan la ventana y los planos de corte
	Window_width=5;
	Window_height=5;
	Front_plane=10;
	Back_plane=1000;
	// Se inicia la posicion del observador, en el eje z
	Observer_distance=2*Front_plane;
	Observer_angle_x=0;
	Observer_angle_y=0;
	// Se indica cual sera el color para limpiar la ventana	(r,v,a,al)
	// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
	glClearColor(1,1,1,1);
	// Se habilita el z-bufer
	glEnable(GL_DEPTH_TEST);
	change_projection();
	glViewport(0, 0, UI_window_width, UI_window_height);
}

//***************************************************************************
// Función de incialización de las texturas
//***************************************************************************

void initTexture(){
  std::vector<unsigned char> data;

  cimg_library::CImg<unsigned char> img;
	img.load("graffiti.jpg");
	// img.load("logo.jpg");

  // Extraer los datos
  for (long y = 0; y < img.height(); y ++)
     for (long x = 0; x < img.width(); x ++){
        unsigned char *r = img.data(x, y, 0, 0);
        unsigned char *g = img.data(x, y, 0, 1);
        unsigned char *b = img.data(x, y, 0, 2);
        data.push_back(*r);
        data.push_back(*g);
        data.push_back(*b);
     }

  // Se crea la textura
  glGenTextures(1, &textura_id);
  // Se asocia la textura
  glBindTexture(GL_TEXTURE_2D, textura_id);
  // Activar textura 0
  glActiveTexture(GL_TEXTURE0);
  // Repetir componente S(U) de la textura hasta rellenar el modelo.
  // GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP...
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  // Repetir componente T(V) de la textura hasta rellenar el modelo
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // Asigna el tipo de filtrado píxel-coordenada {GL_NEAREST, GL_LINEAR}
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  // Enviar los datos a la GPU
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,img.width(),img.height(),0,GL_RGB,GL_UNSIGNED_BYTE,&data[0]);
}

//***************************************************************************
// Función idle. Utilizada para implementar la rotacion automática
//***************************************************************************

void idle(){	alpha+=0.75f;	vel+=i;	epsilon+=0.75f;	}

//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv){
	if (argc > 1) {
        paralela = true;
    }
	// Se llama a la inicialización de glut
	glutInit(&argc, argv);
	// Se indica las caracteristicas que se desean para la visualización con OpenGL
	// Las posibilidades son:
	// GLUT_SIMPLE -> memoria de imagen simple
	// GLUT_DOUBLE -> memoria de imagen doble
	// GLUT_INDEX -> memoria de imagen con color indizado
	// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
	// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
	// GLUT_DEPTH -> memoria de profundidad o z-bufer
	// GLUT_STENCIL -> memoria de estarcido
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	// Posicion de la esquina inferior izquierdad de la ventana
	glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);
	// Tamaño de la ventana (ancho y alto)
	glutInitWindowSize(UI_window_width,UI_window_height);
	// Llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
	// al bucle de eventos)
	glutCreateWindow("Practica 5: Seleccion y Eventos de Raton");
	// Asignación de la funcion llamada "dibujar" al evento de dibujo
	glutDisplayFunc(draw_scene);
	// Asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
	glutReshapeFunc(change_window_size);
	// Asignación de la funcion llamada "tecla_normal" al evento correspondiente
	glutKeyboardFunc(normal_keys);
	// Asignación de la funcion llamada "tecla_Especial" al evento correspondiente
	glutSpecialFunc(special_keys);
	// Asignación de la función idle.
	glutIdleFunc(idle);
	// Asignación de función que lee eventos del scroll del ratón
	glutMouseFunc(mouseButtons);
  // Asignación de la función de que detecta el movimiento del ratón
	glutMotionFunc(mouseMotion);
	// Función de inicialización
	initialize();
	// Inicializar las luces
	initLighting();
	// Inicializar las texturas
	initTexture();
	// Inicio del bucle de eventos
	glutMainLoop();
	// Liberar memoria usada por la textura
	glDeleteTextures(1, &textura_id);
	return 0;
}
