#include <GL/glut.h>

//*****FUNÇÕES QUE SERÃO UTILIZADAS*****//

void display(void);
void init(void);

//****MAIN*****//


int main(int argc, char**argv)
{
	//Modos da janela
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE |GLUT_RGB);
	glutInitWindowSize(500, 500); 
	glutInitWindowPosition(100, 100);
	glutCreateWindow("TC1");
	

	//Callbacks
	init();
	glutDisplayFunc(display);

	//Main Loop 
	glutMainLoop();

	return 0;
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentidy();

	glColor3f (1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f (0.25, 0.25, 0.0);
	glVertex3f (0.75, 0.25, 0.0);
	glVertex3f (0.75, 0.75, 0.0);
	glVertex3f (0.25, 0.75, 0.0);
	glEnd();

	glFlush();
}

void init (void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0,-1.0, 1.0);
}