#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <unistd.h>
#include <list>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;
#define PI 3.1415926535
//*****FUNÇÕES QUE SERÃO UTILIZADAS*****//



bool check = 0;


int i, circle_points = 1000;
//XML CIRCULO
float angle, raio;
float cR, cG,cB;
//XML Modelo
float cnR, cnG, cnB;
float caR, caG, caB;
//XML Tela
string titulo = "TC1";
int wzx = 500, wzy = 500;



float gx = 0,gy = 0;
float gxm = 0.05, gym = 0.05;
float gxmf = 0.0, gymf = 0.0;




//vetor dos circulos
vector<float> pos_x;
vector<float> pos_y;


void display(void);
void init(void);
void mouse(int, int, int, int);
void cursorFormat(int, int);
void arrasta(int, int);
void idle(void);


//****MAIN*****//


int main(int argc, char**argv)
{
	//Modos da janela
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE |GLUT_RGB);
	glutInitWindowSize(wzx, wzy); 
	glutInitWindowPosition(100, 100);
	glutCreateWindow("aiai");
	

	//Callbacks	
	init();
	glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(cursorFormat);
	glutMotionFunc(arrasta);
    //Main Loop 
	glutMainLoop();
	return 0;
}


void display(void){
    
    
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0,1.0);
    
    glBegin(GL_LINE_LOOP);
	glColor3f(0.13, 0.55, 40);
	raio = 0.1;
	for(i = 0; i < circle_points; i++) {
		angle = (2*PI*i)/circle_points;
		glVertex2f(gxm+raio*cos(angle),gym+raio*sin(angle));
	}
    glEnd();
    for(int j=0; j<(pos_x.size()); j++){
            if(check){
                
                    glBegin(GL_POLYGON);
                    glColor3f(0.13, 0.55, 40);
                    raio = 0.1;
                    for(i = 0; i < circle_points; i++) {
                        angle = (2*PI*i)/circle_points;
                        glVertex2f(pos_x[j]+raio*cos(angle),pos_y[j]+raio*sin(angle));
                    }
                    glEnd();
            }}
    
	
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
            check = 1;
            y = wzy - y;
            pos_x.push_back((float)x/ wzx);
            pos_y.push_back((float)y/ wzy);
                        
        }
        else if {button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
            
        }
        glutPostRedisplay();
}

void arrasta(int x, int y){
    
}
