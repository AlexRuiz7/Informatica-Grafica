//**************************************************************************
//	Práctica 3
//
//	Alejandro Ruiz Becerra -- 2017
//
//	Informática Gráfica
//
//**************************************************************************

#include <GL/glut.h>
#include <ctype.h>
#include "include/regulador.h"

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

void change_projection(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
	// Front_plane>0  Back_plane>PlanoDelantero)
	glFrustum(-Window_width, Window_width, -Window_height, Window_height, Front_plane, Back_plane);
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

// Regulador de Watt
Regulador watt;
// Variables de control para la animación del regulador de Watt.
float vel=0, i=0;
// Indice que indica la pos en el vector del objecto a dibujar.
unsigned short object = 0;
// Variables de estado del modo de dibujo
bool dots  = true, edges = false, solid = false, chess = false;
// Variables para implementar la rotación sobre los ejes
float alpha = 0.0f;
bool rotX = false, rotY = false, rotZ = false;
// Variables para implementar el desplazamiento del objeto.
float tX = 0.0f, tY = 0.0f, tZ = 0.0f;
// Variables para implementar el escalado del objeto.
float sX = 1.0f, sY = 1.0f, sZ = 1.0f;
// Variable para el control de la luz.
bool luz = true;

//***************************************************************************
// Función que dibuja los objetos
//***************************************************************************

void draw_objects(){
	// MÉTODOS PROPIOS
	// Desplazamiento
	if(tX!=0 || tY!=0 || tZ!=0)		watt.move(tX,tY,tZ);

	// Escalado
	if(sX!=1)											watt.scalate(sX, sY, sZ);

	// Rotación
	if(rotX)											watt.rotate(alpha,1,0,0);
	if(rotY)											watt.rotate(alpha,0,1,0);
	if(rotZ)											watt.rotate(alpha,0,0,1);
	// FIN MÉTODOS PROPIOS

	// Dibujado
	watt.draw(dots, edges, solid, chess, vel, i);

	glutPostRedisplay();
}

//***************************************************************************
// Función de incialización de las luces  // TODO Work In Progress
//***************************************************************************

void enableLighting(){
	glShadeModel(GL_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	/*
	GLfloat	ambient[]={0.1, 0.1, 0.1, 0.01},
					diffuse[]={0.5, 0.5, 0.5, 1.0},
					specular[]={0.8, 0.8, 0.8, 1},
					position[]={0, 5, 10, 1},
					direction[]={1, 1, 1, 0},
					dirVector[]={1, 0, 0, 0};

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHT0);
	*/

	// Add ambient light
	//GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f};		// Color (0.2, 0.2, 0.2)
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	// Add positioned light
	GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f};			// Color (0.5, 0.5, 0.5)
	GLfloat lightPos0[] = {4.0f, 0.0f, 8.0f, 1.0f};				// Positioned at (4, 0, 8)
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

	// Add directed light
	GLfloat lightColor1[] = {0.5f, 0.2f, 0.2f, 1.0f};			// Color (0.5, 0.2, 0.2)
	// Coming from the direction (-1, 0.5, 0.5)
	GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f};
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	luz=true;
	glClearColor(0,0,0,1);
}

//***************************************************************************
// Función para desactivar la iluminación  // TODO Work In Progress
//***************************************************************************

void disableLighting(){
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	luz=false;
	glClearColor(1,1,1,1);
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
		case 'P':	dots 	= !dots;		break;
		case 'A':	edges = !edges;		break;
		case 'S':	solid = !solid;		break;
		case 'C':	chess =	!chess;		break;
		case 27:	exit(0);

		// Métodos propios

		// Desplazamiento
		case '1':	tX-=1; 					tZ+=1;	break;
		case '2':									tZ+=1;	break;
		case '3':	tX+=1; 					tZ+=1;	break;
		case '4':	tX-=1;									break;
		case '5':					tY+=1;					break;
		case '6':	tX+=1;									break;
		case '7':	tX-=1; 					tZ-=1;	break;
		case '8':									tZ-=1;	break;
		case '9':	tX+=1; 					tZ-=1;	break;
		case '0': 				tY-=1;					break;

		// Cambiar tamaño
		case '+':	sX=sY=sZ+=0.5;							break;
		case '-':	if(sX>0.5)	sX=sY=sZ-=0.5;	break;

		// Rotación
		case 'R':	rotX = !rotX;						break;
		case 'T':	rotY = !rotY;						break;
		case 'Y':	rotZ = !rotZ;						break;

		// Luz
		case 'L':	(luz) ? disableLighting() : enableLighting(); break;
		case 'O': if(luz)	glDisable(GL_LIGHT0);	else	glEnable(GL_LIGHT0); luz=!luz; break;

		// Animación ~ Práctica 3 ~
		case 'J':	if(i+0.1<=20)		i+=0.1;		break;
		case 'K':	if(i-0.1>=0)		i-=0.1;		break;
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
		case GLUT_KEY_LEFT:				Observer_angle_y++;				break;
		case GLUT_KEY_RIGHT:			Observer_angle_y--;				break;
		case GLUT_KEY_UP:					Observer_angle_x++;				break;
		case GLUT_KEY_DOWN:				Observer_angle_x--;				break;
		case GLUT_KEY_PAGE_UP:		Observer_distance/=1.2;		break;
		case GLUT_KEY_PAGE_DOWN:	Observer_distance*=1.2;		break;
	}
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

	//createObjects();

	change_projection();
	glViewport(0, 0, UI_window_width, UI_window_height);
}


//***************************************************************************
// Función idle. Utilizada para implementar la rotacion automática
//***************************************************************************

void idle(){	alpha+=0.5f;	vel+=i;		}

//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv){
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
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	// Posicion de la esquina inferior izquierdad de la ventana
	glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);
	// Tamaño de la ventana (ancho y alto)
	glutInitWindowSize(UI_window_width,UI_window_height);
	// Llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
	// al bucle de eventos)
	glutCreateWindow("Practica 3: Modelos Jerarquicos");
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
	// Función de inicialización
	initialize();
	// Inicio del bucle de eventos
	glutMainLoop();
	return 0;
}
