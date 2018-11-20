#define PROYECTO "ISGI::S5::Animation"

#include <iostream>
#include <sstream>
#include <Utilidades.h>

using namespace std;


// Variables dependientes del tiempo
static float alfa = 0;

void init() {
	//Configurar ek motor de render
	glClearColor(0, 0, 0.3, 1);
	glEnable(GL_DEPTH_TEST);
}

void FPS() {
	// Cuenta fotogramas hasta qu pasa un segundo
	// Entonces los muestra y reinicia la cuenta

	int ahora, t_tras;
	static int antes = glutGet(GLUT_ELAPSED_TIME);
	static int fps = 0;

	// Cada vez que paso sumo un fotograma
	fps++;

	// Calcular el tiempo
	ahora = glutGet(GLUT_ELAPSED_TIME);
	t_tras = ahora - antes;

	// Si ha trascurrido mas de un segundo muestri y reinicio
	if (t_tras > 1000) {
		stringstream titulo;
		titulo << "FPS = " << fps;
		glutSetWindowTitle(titulo.str().c_str());
		fps = 0;
		antes = ahora;
	}
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
	glRotatef(alfa, 0, 1, 0);
	glutSolidTeapot(0.5);
	glColor3f(1, 1, 1);
	glutWireTeapot(0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -0.2);
	glColor3f(0, 1, 0);
	glRotatef(alfa/2, 0, 1, 0);
	glutSolidTeapot(0.5);
	glColor3f(1, 1, 1);
	glutWireTeapot(0.5);

	FPS();

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

	//glutIdleFunc(update);
	// Alta de la funcion de atencion a idle

	glutTimerFunc(1000 / 50, onTimer, 1000 / 50);
	// Alta de la funcion de atencion a onTimer

	glutMainLoop();
	// Puesta en marcha del programa
}