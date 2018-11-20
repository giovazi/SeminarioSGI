
#define TITULO "Estrella de David"

#include <iostream>
#include <Utilidades.h>

using namespace std;

GLuint triangle;

void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	triangle = glGenLists(1);
	glNewList(triangle, GL_COMPILE);
	glColor3f(0.0, 0.0, 0.3);
	glBegin(GL_TRIANGLE_STRIP);
	for (auto i = 0;i < 3;i++) {
		glVertex3f(1.0*cos(i * 2 * PI / 3 + PI / 2), 1 * sin(i * 2 * PI / 3 + PI / 2), 0);
		glVertex3f(0.7 * cos(i * 2 * PI / 3 + PI / 2), 0.7 * sin(i * 2 * PI / 3 + PI / 2), 0);
	}
	glVertex3f(1.0 *cos(0 * 2 * PI / 3 + PI / 2), 1 * sin(0 * 2 * PI / 3 + PI / 2), 0);
	glVertex3f(0.7 * cos(0 * 2 * PI / 3 + PI / 2), 0.7 * sin(0 * 2 * PI / 3 + PI / 2), 0);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	for (auto i = 0;i < 3;i++) {
		glVertex3f(-1.0*cos(i * 2 * PI / 3 + PI / 2), -1.0 * sin(i * 2 * PI / 3 + PI / 2), 0);
		glVertex3f(-0.7 * cos(i * 2 * PI / 3 + PI / 2), -0.7 * sin(i * 2 * PI / 3 + PI / 2), 0);
	}
	glVertex3f(-1.0*cos(0 * 2 * PI / 3 + PI / 2), -1 * sin(0 * 2 * PI / 3 + PI / 2), 0);
	glVertex3f(-0.7 * cos(0 * 2 * PI / 3 + PI / 2), -0.7 * sin(0 * 2 * PI / 3 + PI / 2), 0);
	glEnd();
	glEndList();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glCallList(triangle);
	glFlush();
}
void reshape(GLint w, GLint h)
{
}

void main(int argc, char ** argv)  // Programa principal
{
	glutInit(&argc, argv);
	// Inicializacion de GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	// Alta de buffers a usar
	glutInitWindowSize(400, 400);
	// Tamanyo inicial de la ventana
	glutCreateWindow(TITULO);
	// Creacion de la ventana con su titulo
	std::cout << TITULO <<
		" running"
		<< std::
		endl;
	// Mensaje por consola
	glutDisplayFunc(display);
	// Alta de la funcion de atencion a display
	glutReshapeFunc(reshape);
	// Alta de la funcion de atencion a reshape
	init();
	glutMainLoop();
	// Puesta en marcha del programa
}