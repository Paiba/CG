#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <unistd.h>

#define PI 3.1415926535
//*****FUNÇÕES QUE SERÃO UTILIZADAS*****//

int i, circle_points = 1000;
float angle, raio;
float gx = 0,gy = 0,passo = 0.0005;
float gxm = 0.05, gym = 0.05;
int wzx = 800, wzy = 800;

void display(void);
void init(void);
void mouse(int, int, int, int);
void idle(void);


//****MAIN*****//


int main(int argc, char**argv)
{
	//Modos da janela
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE |GLUT_RGB);
	glutInitWindowSize(wzx, wzy); 
	glutInitWindowPosition(100, 100);
	glutCreateWindow("TC1");
	

	//Callbacks
	glutIdleFunc(idle);
	glutMouseFunc(mouse);
	init();
	glutDisplayFunc(display);
	

	//Main Loop 
	glutMainLoop();

	return 0;
}

void idle(void){
    glutPostRedisplay();
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0,1.0);
	glBegin(GL_POLYGON);
	glColor3f(0.13, 0.55, 40);
	raio = 0.1;
	for(i = 0; i < circle_points; i++) {
		angle = (2*PI*i)/circle_points;
		glVertex2f(gxm+raio*cos(angle),gym+raio*sin(angle));
	}
	glEnd();

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



void mouse(int button, int  state, int x, int y){
	
	y = wzy - y;
    gxm = (float) x / wzx;
    gym = (float) y / wzy;
	glutPostRedisplay();
}



