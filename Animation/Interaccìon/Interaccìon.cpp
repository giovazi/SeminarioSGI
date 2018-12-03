#define PROYECTO "ISGI::S6::Interaccìon"

#include <iostream>
#include <sstream>
#include <Utilidades.h>

using namespace std;

static enum {ALAMBRICO,SOLIDO,DOBLE} modo;
static float giroxTR = 0, giroyTR = 0, giroxTV = 0, giroyTV = 0;
static int xanterior, yanterior;
static bool dragging = false;
static GLubyte esroja, esverde;

// Variables dependientes del tiempo
static float alfa = 0;

void onMenu(int valor) {
	// Callback de atencion al menu de contexto

	if (valor == 0) modo = ALAMBRICO;
	else if(valor == 1) modo = SOLIDO;
	else modo = DOBLE;
}

void init() {
	//Configurar ek motor de render
	glClearColor(0, 0, 0.3, 1);
	glEnable(GL_DEPTH_TEST);

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

	//Situar la Camara
	gluLookAt(3, 3, 4, 0, 0, 0, 0, 1, 0);

	ejes();

	glPushMatrix();
	glTranslatef(0, 0, 0.5);
	glColor3f(1, 0, 0);
	glRotatef(giroxTR, 1, 0, 0);
	glRotatef(giroyTR, 0, 1, 0);
	if(modo == ALAMBRICO){
		glutWireTeapot(0.5);
	}
	else if (modo == SOLIDO) {
		glutSolidTeapot(0.5);
	}
	else {
		glutSolidTeapot(0.5);
		glColor3f(1, 1, 1);
		glutWireTeapot(0.5);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -0.2);
	glColor3f(0, 1, 0);
	glRotatef(giroyTV, 0, 1, 0);
	glRotatef(giroxTV, 1, 0, 0);
	if (modo == ALAMBRICO) {
		glutWireTeapot(0.5);
	}
	else if (modo == SOLIDO) {
		glutSolidTeapot(0.5);
	}
	else {
		glutSolidTeapot(0.5);
		glColor3f(1, 1, 1);
		glutWireTeapot(0.5);
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

	switch (tecla){
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

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Situar la Camara
	gluLookAt(3, 3, 4, 0, 0, 0, 0, 1, 0);

	// Tetera roja
	glPushMatrix();
	glTranslatef(0, 0, 0.5);
	glColor3f(1, 0, 0);
	glRotatef(giroxTR, 1, 0, 0);
	glRotatef(giroyTR, 0, 1, 0);
	glutSolidTeapot(0.5);
	glPopMatrix();
	
	// Tetera verde
	glPushMatrix();
	glTranslatef(0, 0, -0.2);
	glColor3f(0, 1, 0);
	glRotatef(giroyTV, 0, 1, 0);
	glRotatef(giroxTV, 1, 0, 0);
	glutSolidTeapot(0.5);
	glPopMatrix();

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

	if (esroja == 0xFF){
		giroxTR += (x - xanterior)*pixel2grados;
		giroyTR += (y - yanterior)*pixel2grados;
	}
	else if (esverde==0xFF) {
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
	float t_tras = (float)(ahora - antes) / 1000.0;

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

void main(int argc, char ** argv)
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