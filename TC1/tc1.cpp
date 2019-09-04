#include <GL/glut.h>

//*****FUNÇÕES QUE SERÃO UTILIZADAS*****//

void display(void);
void init(void);
void reshape(int, int);
void desenhaBola(int, int, int, int);
void arrasta(int int)

float r,g,b, xm, ym;
bool circulo = false;
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
	glutMouseFunc(desenhaBola);
	glutReshapeFunc(reshape);

	//Main Loop 
	glutMainLoop();

	return 0;
}


void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	if(desenha){
		glBegin(GL_POLYGON);
		glVertex2f(xm,ym);
		glVertex2f(xm+100,ym);
		glVertex2f(xm+100,ym+100);
		glVertex2f(xm,ym+100);
		glEnd();
	}

	
	glFlush();
}

void init (void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0,-1.0, 1.0);
}


void reshape(int w, int h){
	
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-10,10,-10,10);
	glMatrixMode(GL_MODELVIEW);
	
}

void desenhaBola(int button, int  state, int x, int y){
	
	if(button ==  GLUT_LEFT_BUTTON && state==GLUT_DOWN){
		circulo = true;
		x_ = x;
		y_ = 480-y;	
		r=0.5;
		g=0.5;
		b=0.0;	
	}
	if(button== GLUT_RIGHT_BUTTON){
	
	}
	glutPostRedisplay();
}

void arrasta(int x, int y){

}

