#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <unistd.h>
#include <list>
using namespace std;
#define PI 3.1415926535
//*****FUNÇÕES QUE SERÃO UTILIZADAS*****//

int i, circle_points = 1000;
float angle, raio;
float gx = 0,gy = 0;
float gxm = 0.05, gym = 0.05;
float gxmf = 0.05, gymf = 0.05;
int wzx = 500, wzy = 500;

//vetor dos circulos
list<float> pos_x;
list<float> pos_y;
list<float>::iterator itex = pos_x.begin();
list<float>::iterator itey = pos_y.begin();

void display(void);
void init(void);
void mouse(int, int, int, int);
void cursorFormat(int, int);
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

//******IDLE*********//

void idle(void){
    glutPassiveMotionFunc(cursorFormat);
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
        glVertex2f(gxmf+raio*cos(angle),gymf+raio*sin(angle));
    }
    glEnd();
    advance(itex,1);
    advance(itey,1);
    glBegin(GL_LINE_LOOP);
	glColor3f(0.13, 0.55, 40);
	raio = 0.1;
	for(i = 0; i < circle_points; i++) {
		angle = (2*PI*i)/circle_points;
		glVertex2f(gxm+raio*cos(angle),gym+raio*sin(angle));
	}
    glEnd();
	
	glFlush();
}

void cursorFormat(int x, int y){
    y = wzy - y;
    gxm = (float) x/ wzx;
    gym = (float) y/ wzy;
	glutPostRedisplay();
    
}

void init (void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0,-1.0, 1.0);
}



void mouse(int button, int  state, int x, int y){
       
        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
            y = wzy - y;
            gxmf = (float) x/ wzx;
            gymf = (float) y/ wzy;    
            pos_x.push_back(x);
            pos_y.push_back(y);
        }
        else{
            
        }
        glutPostRedisplay();
}



