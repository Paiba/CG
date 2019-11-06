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
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;
#define PI 3.1415926535
//*****FUNÇÕES E VARIAVEIS QUE SERÃO UTILIZADAS*****//


bool impedido = false;

bool dragCirc = false;
int i, circle_points = 1000;
float angle;
//XML CIRCULO
int raio;
float cR, cG,cB;
//XML CircModelo
float cnR, cnG, cnB;
float caR, caG, caB;
//XML Tela
float telaR, telaG, telaB;
string titulo;
int wzx , wzy;



float gx = 0,gy = 0;
float gxm = 0.0, gym = 0.0;
float gxmf = 0.0, gymf = 0.0;

bool check = 0;


//vetor dos circulos
vector<float> pos_x;
vector<float> pos_y;

void display(void);
void init(void);
void mouse(int, int, int, int);
void cursorFormat(int, int);
void arrasta(int, int);
void idle(void);
bool distancia(int , int);

//Lendo XML

void read_xml(char* FileName){
	XMLDocument doc;
	doc.LoadFile(strcat(FileName, "config.xml"));
	XMLNode* pRoot = doc.FirstChild();
	XMLElement* pElement = pRoot->FirstChildElement("janela");
	pElement = pRoot->FirstChildElement("janela");
	pElement = pElement->FirstChildElement("titulo");
	titulo = pElement->GetText();
    pElement = pRoot->FirstChildElement("janela");
    pElement = pElement->FirstChildElement("dimensao");
    pElement->QueryIntAttribute("largura",&wzx);
	pElement->QueryIntAttribute("altura",&wzy);
    pElement = pRoot->FirstChildElement("janela");
    pElement = pElement->FirstChildElement("fundo");
	pElement->QueryFloatAttribute("corR",&telaR);
	pElement->QueryFloatAttribute("corG",&telaG);
	pElement->QueryFloatAttribute("corB",&telaB);
    pElement = pRoot->FirstChildElement("circulo");
    pElement->QueryFloatAttribute("corR", &cR);
	pElement->QueryFloatAttribute("corG", &cG);
	pElement->QueryFloatAttribute("corB", &cB);
    pElement->QueryIntAttribute("raio", &raio);
    pElement = pRoot->FirstChildElement("circuloModelo");
    pElement->QueryFloatAttribute("corR", &cnR);
	pElement->QueryFloatAttribute("corG", &cnG);
	pElement->QueryFloatAttribute("corB", &cnB);
    
    pElement->QueryFloatAttribute("corSobreposicaoR", &caR);
	pElement->QueryFloatAttribute("corSobreposicaoG", &caG);
	pElement->QueryFloatAttribute("corSobreposicaoB", &caB);
	
    
}


//****MAIN*****//



int main(int argc, char**argv)
{
    read_xml(argv[1]);
	//Modos da janela
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE |GLUT_RGB);
	glutInitWindowSize(wzx, wzy); 
	glutInitWindowPosition(100, 100);
	glutCreateWindow(titulo.c_str());
	
	

	//Callbacks	
	init();
	glutDisplayFunc(display);
   	glutIdleFunc(idle);
	glutMotionFunc(arrasta);
     glutMouseFunc(mouse);
    glutPassiveMotionFunc(cursorFormat);
    //Main Loop 
	glutMainLoop();
	return 0;
}


void display(void){
    
    
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(telaR,telaG,telaB);
    glBegin(GL_LINE_LOOP);
    if (impedido){
        glColor3f(caR, caG, caB);
    }
    else glColor3f(cnR, cnG, cnB);
	for(i = 0; i < circle_points; i++) {
		angle = (2*PI*i)/circle_points;
		glVertex2f(gxm+raio*cos(angle),gym+raio*sin(angle));
	}
    glEnd();
    for(int j=0; j<(pos_x.size()); j++){
            if(check){
                
                    glBegin(GL_POLYGON);
                    glColor3f(cR, cG, cB);
                    for(i = 0; i < circle_points; i++) {
                        angle = (2*PI*i)/circle_points;
                        glVertex2f(pos_x[j]+raio*cos(angle),pos_y[j]+raio*sin(angle));
                    }
                    glEnd();
            }}
    
	
	glFlush();
}

void cursorFormat(int x, int y){
    gxm = (float) x;
    gym = (float) y;
    if(distancia(x,y)){
        impedido = false;
    }
    else impedido = true;
	glutPostRedisplay();
    
}

void init (void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, wzx,  wzy, 0.0f, 0.0f, 1.0f);
}



void mouse(int button, int  state, int x, int y){
       
        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
            dragCirc = false;
            check = 1;
            if(distancia(x,y)){
                pos_x.push_back((float)x);
                pos_y.push_back((float)y);
            }                       
        }
        else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
            dragCirc = true;
        }
        else{
            dragCirc = false;
        }
        glutPostRedisplay();
}

bool distancia(int x, int y){
    
    for(int j=0; j<(pos_x.size()); j++){
        
        if(sqrt( (x-pos_x[j])*(x-pos_x[j]) + (y-pos_y[j])*(y-pos_y[j]) ) < 2*raio){
            
            return false;
        }
    }
    return true;
    
}



void arrasta(int x, int y){
    int circulo;
    float yt = ((float)y);
    float xt = ((float)x);
    
    gxm = (float) x;
    gym = (float) yt;
    
    yt = ((float)yt);
    
    for(int j=0; j<(pos_x.size()); j++){
        
        if(sqrt( (xt-pos_x[j])*(xt-pos_x[j]) + (yt-pos_y[j])*(yt-pos_y[j]) ) <= raio){
            circulo = j;
        }
    }
    if(dragCirc && (circulo < pos_x.size()) && (circulo >= 0)){
            y = y;
            pos_x[circulo] = (float)x;
            pos_y[circulo] = (float)y;
    }

    glutPostRedisplay();
}
