#define PROYECTO "ISGI::P5::Reloj3D"

#include <iostream>
#include <Utilidades.h>
#include <ctime>

using namespace std;
GLuint estrella,triangle;
int seconds, minutes, horas;

// Variables dependientes del tiempo
static float alfa = 0;

void defineStar() {
	//Creo una estrella
	estrella = glGenLists(1);
	glNewList(estrella, GL_COMPILE);
	glBegin(GL_TRIANGLE_STRIP);
	for (auto i = 0;i < 3;i++) {
		glVertex3f(0.5f * cos(i * 2 * PI / 3 + PI / 2), 0.5f * sin(i * 2 * PI / 3 + PI / 2), 0);
		glVertex3f(0.3f * cos(i * 2 * PI / 3 + PI / 2), 0.3f * sin(i * 2 * PI / 3 + PI / 2), 0);
	}
	glVertex3f(0.5f * cos(0 * 2 * PI / 3 + PI / 2), 0.5f * sin(0 * 2 * PI / 3 + PI / 2), 0);
	glVertex3f(0.3f * cos(0 * 2 * PI / 3 + PI / 2), 0.3f * sin(0 * 2 * PI / 3 + PI / 2), 0);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	for (auto i = 0;i < 3;i++) {
		glVertex3f(-0.5f * cos(i * 2 * PI / 3 + PI / 2), -0.5f * sin(i * 2 * PI / 3 + PI / 2), 0);
		glVertex3f(-0.3f * cos(i * 2 * PI / 3 + PI / 2), -0.3f * sin(i * 2 * PI / 3 + PI / 2), 0);
	}
	glVertex3f(-0.5f * cos(0 * 2 * PI / 3 + PI / 2), -0.5f * sin(0 * 2 * PI / 3 + PI / 2), 0);
	glVertex3f(-0.3f * cos(0 * 2 * PI / 3 + PI / 2), -0.3f * sin(0 * 2 * PI / 3 + PI / 2), 0);
	glEnd();
	glEndList();
}

void drawCircle(GLfloat x, GLfloat y, GLfloat r) {
	static const double inc = PI / 96;
	static const double max = 2 * PI;
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f,0.8f,0.8f);
	for (float d = 0; d < max; d += inc) {
		glVertex2f(cos(d) * r + x, sin(d) * r + y);
	}
	glEnd();
}

void drawClock() {
	//Clock circle
	drawCircle(0, 0, 1.35f);
	int j = 0;
	//Clock Tick
	for (auto i = 0; i <= 360; i += 30)
	{
		glBegin(GL_LINES);
		glColor3f(0.0f, 0.8f, 0.8f);
		if ((j % 3) == 0) {
			glVertex3f(0 + cos(i * PI / 180)* 1.025f, 0 + sin(i * PI / 180) * 1.025f, 0);
			glVertex3f(0 + cos(i * PI / 180)* 1.325f, 0 + sin(i * PI / 180) * 1.325f, 0);
		}
		else {
			glVertex3f(0 + cos(i * PI / 180)* (1.3f - 0.15f), 0 + sin(i * PI / 180) * (1.3f - 0.15f), 0);
			glVertex3f(0 + cos(i * PI / 180)* 1.3f, 0 + sin(i * PI / 180) * 1.3f, 0);
		}
		glEnd();
		j++;
	}
}

void init() {
	//Configurar el motor de render
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	defineStar();

	glEnable(GL_DEPTH_TEST);
}


void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Situar la Camara
	gluLookAt(0, 0, 8, 0, 0, 0, 0, 1, 0);

	glLineWidth(4);

	drawClock();

	//Horas
	glBegin(GL_LINES);
	glColor3f(1, 1, 0);
	glVertex3f(0 + sin((horas*30) * PI / 180)* 0.25f, 0 + cos((horas*30) * PI / 180) * 0.25f, 0.0);
	glVertex3f(0 + sin((horas*30) * PI / 180)* 0.7f, 0 + cos((horas*30) * PI / 180) * 0.7f, 0.0);
	glEnd();

	//Minutes
	glBegin(GL_LINES);
	glColor3f(0, 1, 0);
	glVertex3f(0 + sin((minutes * 6) * PI / 180)* 0.25f, 0 + cos((minutes * 6) * PI / 180) * 0.25f, 0);
	glVertex3f(0 + sin((minutes * 6) * PI / 180)* 0.85f, 0 + cos((minutes * 6) * PI / 180) * 0.85f, 0);
	glEnd();

	//Seconds
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0 + sin((seconds * 6) * PI / 180)* 0.25f, 0 + cos((seconds * 6) * PI / 180) * 0.25f, 0);
	glVertex3f(0 + sin((seconds * 6) * PI / 180)* 1, 0 + cos((seconds * 6) * PI / 180) * 1, 0);
	glEnd();

	//Estrella3D
	float ra = 0;
	float r = 0.0;
	float g = 1.0;
	float b = 1.0;
	glPushMatrix();
	glScalef(0.45f, 0.45f, 0.45f);
	glRotatef(alfa / 2, 1, 1, 0);
	for (auto i = 0;i < 5;i++) {
		glColor3f(r, g, b);
		glPushMatrix();
		glRotatef(ra, 0, 1, 0);
		glCallList(estrella);
		glPopMatrix();
		ra += 30;
		r += 0.1f;
		g -= 0.2f;
		b -= 0.1f;
	}
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

	static const float omega = 1;	// Vueltas por segundo
	// Hora anterior
	static int antes = glutGet(GLUT_ELAPSED_TIME);
	// Hora actual
	int ahora = glutGet(GLUT_ELAPSED_TIME);

	// Tiempo trascurrido
	float t_tras = (ahora - antes) / 1000.0f;
	alfa += 360 * omega * t_tras;

	time_t myTime = time(NULL);
	struct tm time;
	localtime_s(&time, &myTime);

	seconds = time.tm_sec;
	minutes = time.tm_min;
	horas = time.tm_hour%12;
	
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