#define PROYECTO "ISGI::S7::Iluminacìon"

#include <iostream>
#include <sstream>
#include <Utilidades.h>

using namespace std;

static enum { ALAMBRICO, SOLIDO, DOBLE } modo;
static float giroxTR = 0, giroyTR = 0, giroxTV = 0, giroyTV = 0;
static int xanterior, yanterior;
static bool dragging = false;
static GLubyte esroja, esverde;

// Variables dependientes del tiempo
static float alfa = 0;

void onMenu(int valor) {
	// Callback de atencion al menu de contexto

	if (valor == 0) modo = ALAMBRICO;
	else if (valor == 1) modo = SOLIDO;
	else modo = DOBLE;
}

void init() {
	//Configurar ek motor de render
	glClearColor(1, 1, 1, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	// Luces
	glLightfv(GL_LIGHT0, GL_DIFFUSE, BLANCO);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, BLANCO);
	glLightfv(GL_LIGHT1, GL_SPECULAR, BLANCO);
	glEnable(GL_LIGHT1);

	//Crear menu
	glutCreateMenu(onMenu);
	glutAddMenuEntry("ALAMBRICO", 0);
	glutAddMenuEntry("SOLIDO", 1);
	glutAddMenuEntry("DOBLE", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Luces solidarias a la camara
	GLfloat pl1[] = { 0,0,0,1 };
	glLightfv(GL_LIGHT1, GL_POSITION, pl1);

	//Situar la Camara
	gluLookAt(3, 3, 7, 0, 0, 0, 0, 1, 0);

	// Positionar luces fijas de la escena
	GLfloat pl0[] = { 0,3,0,1 }; //Luz puntual
	glLightfv(GL_LIGHT0, GL_POSITION, pl0);

	ejes();

	// Donuts
	// Material primer donuts
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ROJO);
	glMaterialfv(GL_FRONT, GL_SPECULAR, NEGRO);
	glPushMatrix();
	glTranslatef(0, 0, 0.5f);
	glColor3f(1, 0, 0);
	glRotatef(giroxTR, 1, 0, 0);
	glRotatef(giroyTR, 0, 1, 0);
	if (modo == ALAMBRICO) {
		glutWireTorus(0.3,0.5,50,50);
	}
	else if (modo == SOLIDO) {
		glutSolidTorus(0.3, 0.5, 50, 50);
	}
	else {
		glutSolidTorus(0.3, 0.5, 50, 50);
		glColor3f(1, 1, 1);
		glutWireTorus(0.3, 0.5, 50, 50);
	}
	glPopMatrix();

	// Otro Donuts
	// Material segundo donuts
	glMaterialfv(GL_FRONT, GL_DIFFUSE, BRONCE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, BLANCO);
	glMaterialf(GL_FRONT, GL_SHININESS, 50);
	glPushMatrix();
	glTranslatef(0, 0, -0.2f);
	glColor3f(0, 1, 0);
	glRotatef(giroyTV, 0, 1, 0);
	glRotatef(giroxTV, 1, 0, 0);
	if (modo == ALAMBRICO) {
		glutWireTorus(0.3, 0.5, 50, 50);
	}
	else if (modo == SOLIDO) {
		glutSolidTorus(0.3, 0.5, 50, 50);
	}
	else {
		glutSolidTorus(0.3, 0.5, 50, 50);
		glColor3f(1, 1, 1);
		glutWireTorus(0.3, 0.5, 50, 50);
	}
	glPopMatrix();

	glutSwapBuffers();
}


void reshape(GLint w, GLint h) {
	glViewport(0, 0, w, h);
	float ra = float(w) / float(h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Defino la camera ortografica

	gluPerspective(20, ra, 0.2, 10);
	//Camara Ortogonale
	//if(ra>1)	glOrtho(-2*ra, 2*ra, -2, 2, -2, 2);
	//else        glOrtho(-2, 2, -2 / ra, 2 / ra, -2, 2);
}

void onKey(unsigned char tecla, int x, int y) {

	switch (tecla) {
	case 'a':
		modo = ALAMBRICO;
		break;
	case 's':
		modo = SOLIDO;
		break;
	case 'd':
		modo = DOBLE;
		break;
	}

	glutPostRedisplay();
}

void select() {
	// Dibuja en el backbuffer la escena con solo los objectos 
	// que interesa seleccionar, cada uno de un color, y sin 
	// intercambiar con el buffer frontal

	// Disabilitar la ilùminacion para que funciona glColor
	glDisable(GL_LIGHTING);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Situar la Camara
	gluLookAt(3, 3, 7, 0, 0, 0, 0, 1, 0);

	// Donuts
	glPushMatrix();
	glTranslatef(0, 0, 0.5);
	glColor3f(1, 0, 0);
	glRotatef(giroxTR, 1, 0, 0);
	glRotatef(giroyTR, 0, 1, 0);
	glutSolidTorus(0.3,0.5,50,50);
	glPopMatrix();

	// Otro Donuts
	glPushMatrix();
	glTranslatef(0, 0, -0.2f);
	glColor3f(0, 1, 0);
	glRotatef(giroyTV, 0, 1, 0);
	glRotatef(giroxTV, 1, 0, 0);
	glutSolidTorus(0.3, 0.5, 50, 50);
	glPopMatrix();

	glEnable(GL_LIGHTING);
}

void onClick(int boton, int estado, int x, int y) {
	// Callback de atencion al click de raton

	if (boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
		xanterior = x;
		yanterior = y;
		dragging = true;

		// Quiero saber el color de x,y en el backbuffer
		// habiendo dibujado con colores solidos diferentes 
		GLint viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);
		int vy = viewport[3] - y;

		select();

		glReadPixels(x, vy, 1, 1, GL_RED, GL_UNSIGNED_BYTE, &esroja);
		glReadPixels(x, vy, 1, 1, GL_GREEN, GL_UNSIGNED_BYTE, &esverde);

	}
	else
		dragging = false;
}

void onDrag(int x, int y) {
	// Callback de arratre del raton

	if (!dragging)	return;

	static const float pixel2grados = 1.0f;

	/*
	// Al mover el raton hacia la derecha la x aumenta y el giro es positivo
	giroy += (x - xanterior) * pixel2grados;

	// Al mover el raton hacia abajo la y aumenta y el giro es positivo
	// alrededor de x
	girox += (y - yanterior) * pixel2grados;
	*/

	if (esroja == 0xFF) {
		giroxTR += (x - xanterior)*pixel2grados;
		giroyTR += (y - yanterior)*pixel2grados;
	}
	else if (esverde == 0xFF) {
		giroxTV += (x - xanterior)*pixel2grados;
		giroyTV += (y - yanterior)*pixel2grados;
	}

	xanterior = x;
	yanterior = y;

	glutPostRedisplay();
}

void update() {
	// Fase de actualization
	// Sin control del tiempo
	//alfa += 0.1;
	// Con control del tiempo
	static const float omega = 2;	// Vueltas por segundo

	// Hora anterior
	static int antes = glutGet(GLUT_ELAPSED_TIME);
	// Hora actual
	int ahora = glutGet(GLUT_ELAPSED_TIME);

	// Tiempo trascurrido
	float t_tras = (float)(ahora - antes) / 1000.0f;

	// Incremento = velocidad*tiempo;
	alfa += 360 * omega*t_tras;

	// Actualizar la hora para la proxima vez
	antes = ahora;

	// Mandar evento de dibujo
	glutPostRedisplay();
}

void onTimer(int tiempo) {
	// CallBack de atencion a la cuenta atras
	update();

	// Una nueva cuenta atras
	glutTimerFunc(tiempo, onTimer, tiempo);
}

int main(int argc, char ** argv)
// Programa principal
{
	glutInit(&argc, argv);
	// Inicializacion de GLUT

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	// Alta de buffers a usar

	glutInitWindowSize(700, 700);
	// Tamanyo inicial de la ventana

	glutCreateWindow(PROYECTO);
	// Creacion de la ventana con su titulo

	init();

	glutDisplayFunc(display);
	// Alta de la funcion de atencion a display

	glutReshapeFunc(reshape);
	// Alta de la funcion de atencion a reshape

	glutTimerFunc(1000 / 50, onTimer, 1000 / 50);
	// Alta de la funcion de atencion a onTimer

	glutKeyboardFunc(onKey);
	// Alta de la funcion de atencion a onKey

	glutMouseFunc(onClick);
	// Alta de la funcion de atencion a onClick

	glutMotionFunc(onDrag);
	// Alta de la funcion de atencion a onDrug

	glutMainLoop();
	// Puesta en marcha del programa
}