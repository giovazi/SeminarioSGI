#define PROJECTO "SGI-P1"

#include <iostream>
#include <Utilidades.h>

using namespace std;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.3, 0.0);

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
	glutInitWindowSize(500, 400);
	// Tamanyo inicial de la ventana
	glutInitWindowPosition(50, 200);
	glutCreateWindow(PROJECTO);
	// Creacion de la ventana con su titulo
	std::cout << PROJECTO <<
		" running"
		<< std::
		endl;
	// Mensaje por consola
	glutDisplayFunc(display);
	// Alta de la funcion de atencion a display
	glutReshapeFunc(reshape);
	// Alta de la funcion de atencion a reshape
	glutMainLoop();
	// Puesta en marcha del programa
}