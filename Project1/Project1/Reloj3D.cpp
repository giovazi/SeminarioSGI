#define PROYECTO "ISGI::P5::Reloj3D"

#include <iostream>
#include <Utilidades.h>

using namespace std;
GLuint estrella,triangle;

// Variables dependientes del tiempo
static float alfa = 0;

void init() {
	//Configurar ek motor de render
	glClearColor(1.0, 1.0, 1.0, 1);
	estrella = glGenLists(2);
	glNewList(estrella, GL_COMPILE);
	glBegin(GL_TRIANGLE_STRIP);
	for (auto i = 0;i < 3;i++) {
		glVertex3f(0.5*cos(i * 2 * PI / 3 + PI / 2), 0.5 * sin(i * 2 * PI / 3 + PI / 2), 0);
		glVertex3f(0.3 * cos(i * 2 * PI / 3 + PI / 2), 0.3 * sin(i * 2 * PI / 3 + PI / 2), 0);
	}
	glVertex3f(0.5 *cos(0 * 2 * PI / 3 + PI / 2), 0.5 * sin(0 * 2 * PI / 3 + PI / 2), 0);
	glVertex3f(0.3 * cos(0 * 2 * PI / 3 + PI / 2), 0.3 * sin(0 * 2 * PI / 3 + PI / 2), 0);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	for (auto i = 0;i < 3;i++) {
		glVertex3f(-0.5*cos(i * 2 * PI / 3 + PI / 2), -0.5 * sin(i * 2 * PI / 3 + PI / 2), 0);
		glVertex3f(-0.3 * cos(i * 2 * PI / 3 + PI / 2), -0.3 * sin(i * 2 * PI / 3 + PI / 2), 0);
	}
	glVertex3f(-0.5*cos(0 * 2 * PI / 3 + PI / 2), -0.5 * sin(0 * 2 * PI / 3 + PI / 2), 0);
	glVertex3f(-0.3 * cos(0 * 2 * PI / 3 + PI / 2), -0.3 * sin(0 * 2 * PI / 3 + PI / 2), 0);
	glEnd();
	glEndList();
	triangle = estrella + 1;
	glNewList(triangle, GL_COMPILE);
	glBegin(GL_TRIANGLE_STRIP);
	for (auto i = 0;i < 3;i++) {
		glVertex3f(1*cos(i * 2 * PI / 3 + PI / 2), 1 * sin(i * 2 * PI / 3 + PI / 2), 0);
		glVertex3f(0.8 * cos(i * 2 * PI / 3 + PI / 2), 0.8 * sin(i * 2 * PI / 3 + PI / 2), 0);
	}
	glVertex3f(1 *cos(0 * 2 * PI / 3 + PI / 2), 1 * sin(0 * 2 * PI / 3 + PI / 2), 0);
	glVertex3f(0.8 * cos(0 * 2 * PI / 3 + PI / 2), 0.8 * sin(0 * 2 * PI / 3 + PI / 2), 0);
	glEnd();
	glEndList();
	glEnable(GL_DEPTH_TEST);
}

void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Situar la Camara
	gluLookAt(0, 0, 8, 0, 0, 0, 0, 1, 0);

	glPushMatrix();
	glColor3f(0.0, 0.0, 0.3);
	glScalef(0.8,0.8,0.8);
	glRotatef(alfa/2, 1, 1, 0);
	glCallList(estrella);
	int ra = 0;
	float r = 1.0;
	float g = 1.0;
	float b = 0.0;
	for (auto i = 0;i < 5;i++) {
		ra += 30;
		r -= 0.1;
		g -= 0.1;
		b += 0.1;
		glColor3f(r, g, b);
		glPushMatrix();
		glRotatef(ra, 0, 1, 0);
		glCallList(estrella);
		glPopMatrix();
	}
	glPopMatrix();

	for (auto i = 0; i <= 360; i += 30)
	{
		glBegin(GL_LINES);
		glColor3f(0.2, 0.2, 0.2);
		glVertex3f(0.0 + cos(i * PI / 180.0f)* (1.3 - 0.15), 0.0 + sin(i * PI / 180.0f) * (1.3 - 0.15), 0.0);
		glVertex3f(0.0 + cos(i * PI / 180.0f)* 1.3, 0.0 + sin(i * PI / 180.0f) * 1.3, 0.0);
		glEnd();
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, 0, 0);
	glRotatef(90, 0, 1, 1);
	glutWireCone(0.15, 0.3, 5, 5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, 0.2, 0);
	glRotatef(90, 0, 1, 1);
	glutWireCone(0.05,0.5, 5, 5);
	glPopMatrix();


	glutSwapBuffers();
}
void reshape(GLint w, GLint h) {
	glViewport(0, 0, w, h);
	float ra = float(w) / float(h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Defino la camera

	gluPerspective(20, ra, 0.2, 10);
}

void update() {
	// Fase de actualization
	// Sin control del tiempo
	//alfa += 0.1;
	// Con control del tiempo
	static const float omega = 1;	// Vueltas por segundo
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
	glutInitWindowSize(800, 800);
	// Tamanyo inicial de la ventana
	glutCreateWindow(PROYECTO);
	init();
	// Creacion de la ventana con su titulo
	glutDisplayFunc(display);
	// Alta de la funcion de atencion a display
	glutReshapeFunc(reshape);
	// Alta de la funcion de atencion a reshape
	glutTimerFunc(1000 / 60, onTimer, 1000 / 60);
	// Alta de la funcion de atencion a onTimer
	glutMainLoop();
	// Puesta en marcha del programa
}