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
#include <cmath>
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;
#define PI 3.1415926535

void display(void);
void init(void);
void idle(void);
void keyPressDown(unsigned char, int, int);
void keyPressUp(unsigned char,int,int);


float angle;
int i, circle_points = 1000;
float t0, t1, t2;

bool distanciaAereo(float, float);
bool distanciaArena(float, float);
bool decolado = false;
bool keyStatus[255];
bool ready = false;


float velocidade;
string nom;
string tip;
string caminh;
string caminhoInteiro;

class Circulo{
public:
    float pos_x;
    float pos_y;
    float radius;
    int id;
    string cor;

    Circulo();
    void setAtt(float x, float y, int iD, float raio, string fill);
};

Circulo::Circulo(){}

void Circulo::setAtt(float x, float y, int iD, float raio, string fill){
    pos_x = x;
    pos_y = y;
    radius = raio;
    id = iD; 
    cor = fill;
}


struct pista{
    float pos1_x;
    float pos1_y;
    float pos2_x;
    float pos2_y;
	float distx;
	float disty;
    int id;
};

pista pistaDeVoo1;

float accelx, accely;

Circulo JOGADOR;
Circulo ARENA;
vector<Circulo> INIMIGO_T;
vector<Circulo> INIMIGO_A;


void read_xml(char* FileName){
	XMLDocument doc;
	doc.LoadFile(strcat(FileName, "config.xml"));
	XMLNode* pRoot = doc.FirstChild();
	XMLElement* pElement = pRoot->FirstChildElement("arquivoDaArena");
	pElement = pRoot->FirstChildElement("arquivoDaArena");
	pElement = pElement->FirstChildElement("nome");
	nom = pElement->GetText();    
    pElement = pRoot->FirstChildElement("arquivoDaArena");
    pElement = pElement->FirstChildElement("tipo");
    tip = pElement->GetText();    
    pElement = pRoot->FirstChildElement("arquivoDaArena");
    pElement = pElement->FirstChildElement("caminho");
	caminh = pElement->GetText();    
    pElement = pRoot->FirstChildElement("jogador");
    velocidade = pElement->FloatAttribute("vel");
    caminhoInteiro = caminh +  nom + "." + tip;
    XMLDocument doc1;
	doc1.LoadFile(caminhoInteiro.c_str());
    XMLElement * svgElement = doc1.FirstChildElement("svg");
    XMLElement * svgCirc = svgElement->FirstChildElement("circle");    
    XMLElement * svgLin = svgElement->FirstChildElement("line");
    while(svgCirc){
        string fill;
        fill = svgCirc->Attribute("fill");
        if(fill == "green"){//JOGADOR
            //printf("JOGADOR!\n");
            JOGADOR.setAtt(svgCirc->FloatAttribute("cx"),svgCirc->FloatAttribute("cy"),svgCirc->IntAttribute("id"),svgCirc->FloatAttribute("r"),svgCirc->Attribute("fill"));
            
        }
        if (fill == "blue"){//Arena 
            //printf("Arena!\n");
			ARENA.setAtt(svgCirc->FloatAttribute("cx"),svgCirc->FloatAttribute("cy"),svgCirc->IntAttribute("id"),svgCirc->FloatAttribute("r"),svgCirc->Attribute("fill"));
        }
        if (fill == "red"){//Inimigo Aéreo
            //printf("Aereo!\n");
			Circulo a;
			a.setAtt(svgCirc->FloatAttribute("cx"),svgCirc->FloatAttribute("cy"),svgCirc->IntAttribute("id"),svgCirc->FloatAttribute("r"),svgCirc->Attribute("fill"));
			INIMIGO_A.push_back(a);
        }
        if (fill == "orange"){//Inimigo Terrestre
            //printf("Terrestre!\n");
			Circulo a;
			a.setAtt(svgCirc->FloatAttribute("cx"),svgCirc->FloatAttribute("cy"),svgCirc->IntAttribute("id"),svgCirc->FloatAttribute("r"),svgCirc->Attribute("fill"));
			INIMIGO_T.push_back(a);
        }
        svgCirc = svgCirc->NextSiblingElement("circle");
            
    }
    if(svgLin){
        svgLin->QueryFloatAttribute("x1",&pistaDeVoo1.pos1_x);
        svgLin->QueryFloatAttribute("x2",&pistaDeVoo1.pos2_x);
        svgLin->QueryFloatAttribute("y1",&pistaDeVoo1.pos1_y);
        svgLin->QueryFloatAttribute("y2",&pistaDeVoo1.pos2_y);
		
		pistaDeVoo1.distx = pistaDeVoo1.pos2_x-pistaDeVoo1.pos1_x;
		pistaDeVoo1.disty = pistaDeVoo1.pos2_y-pistaDeVoo1.pos1_y;
		accelx = 2*pistaDeVoo1.distx/pow(4000,2.0);
		accely = 2*pistaDeVoo1.disty/pow(4000,2.0);

    }
    
}



int main(int argc, char**argv)
{
    read_xml(argv[1]);   
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE |GLUT_RGB);
	glutInitWindowSize(2*ARENA.radius, 2*ARENA.radius);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Trabalho2");

	//Callbacks	
	init();
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyPressDown);
  	glutKeyboardUpFunc(keyPressUp);
   
    //Main Loop 
	glutMainLoop();
	return 0;
}

void init (void)
{
	glClearColor(255,255,255, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(ARENA.pos_x - ARENA.radius, ARENA.pos_x + ARENA.radius, ARENA.pos_y + ARENA.radius, ARENA.pos_y - ARENA.radius, 0.0f, 1.0f);
}

void keyPressUp(unsigned char key, int x, int y)
{
  keyStatus[key] = false;
  if (key =='u' || key =='U' && !ready){		
		t0 = glutGet(GLUT_ELAPSED_TIME);
		ready = true;	
	}
}

void keyPressDown(unsigned char key, int x, int y)
{
  keyStatus[key] = true;
}

void idle(void){
	float VelFin = 200*sqrt(pow(4000*accely,2.0)+pow(4000*accelx,2.0))*velocidade;
	float TamFin = 2*JOGADOR.radius;
	if(ready && !decolado){
		if(glutGet(GLUT_ELAPSED_TIME)-t0<=4000){
			t1 = (glutGet(GLUT_ELAPSED_TIME)-t0);			
			JOGADOR.pos_x = pistaDeVoo1.pos1_x + accelx*pow(t1,2)/2;
			JOGADOR.pos_y = pistaDeVoo1.pos1_y + accely*pow(t1,2)/2;			
			//if(JOGADOR.radius<=TamFin)			
				//JOGADOR.radius += 0.08; 
		}
		else {decolado = true;}
	}
	if((keyStatus['w'] || keyStatus['W']) && decolado 
		&& distanciaAereo(JOGADOR.pos_x,JOGADOR.pos_y-VelFin) 
		&& distanciaArena(JOGADOR.pos_x,JOGADOR.pos_y-VelFin))
    	JOGADOR.pos_y-= VelFin;

  	if((keyStatus['a'] || keyStatus['A']) && decolado 
		&& distanciaAereo(JOGADOR.pos_x - VelFin,JOGADOR.pos_y) 
		&& distanciaArena(JOGADOR.pos_x - VelFin,JOGADOR.pos_y))
    	JOGADOR.pos_x-= VelFin;

  	if((keyStatus['s'] || keyStatus['S']) && decolado 
		&& distanciaAereo(JOGADOR.pos_x, JOGADOR.pos_y+VelFin) 
		&& distanciaArena(JOGADOR.pos_x, JOGADOR.pos_y+VelFin))
    	JOGADOR.pos_y += VelFin;

  	if((keyStatus['d'] || keyStatus['D']) && decolado 
		&& distanciaAereo(JOGADOR.pos_x+ VelFin,JOGADOR.pos_y) 
		&& distanciaArena(JOGADOR.pos_x+ VelFin,JOGADOR.pos_y))
    	JOGADOR.pos_x += VelFin;


  glutPostRedisplay();
}


void display(void){
    
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,1,1);
	
	//ARENA
	glBegin(GL_POLYGON);
    glColor3f(0, 0, 1);
	for(i = 0; i < circle_points; i++) {
    	angle = (2*PI*i)/circle_points;
		glVertex2f(ARENA.pos_x+ARENA.radius*cos(angle),ARENA.pos_y+ARENA.radius*sin(angle));	
	}
	glEnd();

	//PISTA_DE_VOO
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
    glVertex2f(pistaDeVoo1.pos1_x, pistaDeVoo1.pos1_y);
    glVertex2f(pistaDeVoo1.pos2_x, pistaDeVoo1.pos2_y);
	glEnd();
	

	//INIMIGO_A
	for(int j=0; j<(INIMIGO_A.size()); j++){                
    	glBegin(GL_POLYGON);
        glColor3f(1, 0, 0);
        for(i = 0; i < circle_points; i++) {
        	angle = (2*PI*i)/circle_points;
        	glVertex2f(INIMIGO_A[j].pos_x+INIMIGO_A[j].radius*cos(angle),INIMIGO_A[j].pos_y+INIMIGO_A[j].radius*sin(angle));
        }
        glEnd();
    }
	//INIMIGO_T
	for(int j=0; j<(INIMIGO_T.size()); j++){                
    	glBegin(GL_POLYGON);
        glColor3f(1, 0.5, 0);
        for(i = 0; i < circle_points; i++) {
        	angle = (2*PI*i)/circle_points;
        	glVertex2f(INIMIGO_T[j].pos_x+INIMIGO_T[j].radius*cos(angle),INIMIGO_T[j].pos_y+INIMIGO_T[j].radius*sin(angle));
        }
        glEnd();
    }

	//JOGADOR
    glBegin(GL_POLYGON);
    glColor3f(0, 1, 0);
	for(i = 0; i < circle_points; i++) {
    	angle = (2*PI*i)/circle_points;
		glVertex2f(JOGADOR.pos_x+JOGADOR.radius*cos(angle),JOGADOR.pos_y+JOGADOR.radius*sin(angle));	
	}	
	glEnd();

	
 	
	glutPostRedisplay();
	glFlush();
}

bool distanciaArena(float x, float y){
	if(sqrt(pow((x-ARENA.pos_x),2.0) + pow((y-ARENA.pos_y),2.0)) > ARENA.radius - JOGADOR.radius){
            return false;
    }
    return true;
    
}

bool distanciaAereo(float x, float y){
    
    for(int j=0; j<(INIMIGO_A.size()); j++){
        
        if(sqrt(pow((x-INIMIGO_A[j].pos_x),2.0) + pow((y-INIMIGO_A[j].pos_y),2.0)) < JOGADOR.radius+INIMIGO_A[j].radius){
            return false;
        }
    }
    return true;
    
}


