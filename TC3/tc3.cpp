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
#include "nave.hpp"

using namespace std;
using namespace tinyxml2;
#define PI 3.1415926535

void display(void);
void init(void);
void idle(void);
void mouseClick(int button, int  state, int x, int y);
void mouseMove(int x, int y);
void keyPressDown(unsigned char, int, int);
void keyPressUp(unsigned char,int,int);
void reseta();
void transporta();

float TamFin;
float angle;
int i, circle_points = 1000;
float t0, t1, t2;
float oldX;

bool distanciaAereo(float, float);
bool distanciaArena(float, float);
bool decolado = false;
bool keyStatus[255];
bool ready = false;
bool move =  false;

float VelRef;
float velocidade;
string nom;
string tip;
string caminh;
string caminhoInteiro;


struct pista{
    float pos1_x;
    float pos1_y;
    float pos2_x;
    float pos2_y;
	float distx;
	float disty;
	float distAbs;
	float tangente; 
    int id;
};

pista pistaDeVoo1;

float accelx, accely;

Nave JOGADOR;
Nave AUX;
Nave ARENA;
vector<Nave> INIMIGO_T;
vector<Nave> INIMIGO_A;


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
		if (fill == "blue"){//Arena 
        //printf("Arena!\n");
		ARENA.setAtt(svgCirc->FloatAttribute("cx"),svgCirc->FloatAttribute("cy"),svgCirc->IntAttribute("id"),svgCirc->FloatAttribute("r"),svgCirc->Attribute("fill"),0);
        }
        if(fill == "green"){//JOGADOR
            //printf("JOGADOR!\n");
            JOGADOR.setAtt(svgCirc->FloatAttribute("cx"),svgCirc->FloatAttribute("cy"),svgCirc->IntAttribute("id"),svgCirc->FloatAttribute("r"),svgCirc->Attribute("fill"),0);
			TamFin = 2*svgCirc->FloatAttribute("r");
            
        }
        if (fill == "red"){//Inimigo Aéreo
            //printf("Aereo!\n");
			Nave a;
			a.setAtt(svgCirc->FloatAttribute("cx"),svgCirc->FloatAttribute("cy"),svgCirc->IntAttribute("id"),svgCirc->FloatAttribute("r"),svgCirc->Attribute("fill"),0);
			INIMIGO_A.push_back(a);
        }
        if (fill == "orange"){//Inimigo Terrestre
            //printf("Terrestre!\n");
			Nave a;
			a.setAtt(svgCirc->FloatAttribute("cx"),svgCirc->FloatAttribute("cy"),svgCirc->IntAttribute("id"),svgCirc->FloatAttribute("r"),svgCirc->Attribute("fill"),0);
			INIMIGO_T.push_back(a);
        }
        svgCirc = svgCirc->NextSiblingElement("circle");
            
    }
    if(svgLin){
        svgLin->QueryFloatAttribute("x1",&pistaDeVoo1.pos1_x);
        svgLin->QueryFloatAttribute("x2",&pistaDeVoo1.pos2_x);
        svgLin->QueryFloatAttribute("y1",&pistaDeVoo1.pos1_y);
        svgLin->QueryFloatAttribute("y2",&pistaDeVoo1.pos2_y);
		

		pistaDeVoo1.pos1_x =pistaDeVoo1.pos1_x -500;
        pistaDeVoo1.pos2_x =pistaDeVoo1.pos2_x -500;
        pistaDeVoo1.pos1_y =pistaDeVoo1.pos1_y -500;
        pistaDeVoo1.pos2_y =pistaDeVoo1.pos2_y -500;

		pistaDeVoo1.distx = pistaDeVoo1.pos2_x-pistaDeVoo1.pos1_x;
		pistaDeVoo1.disty = pistaDeVoo1.pos2_y-pistaDeVoo1.pos1_y;
		pistaDeVoo1.distAbs = sqrt(pow(pistaDeVoo1.distx,2)+pow(pistaDeVoo1.disty,2));
		accelx = 2*pistaDeVoo1.distx/pow(4000,2.0);
		accely = 2*pistaDeVoo1.disty/pow(4000,2.0);
		
		JOGADOR.tan_now = atan2(pistaDeVoo1.disty,pistaDeVoo1.distx);

    }
	VelRef = velocidade*4000*(pistaDeVoo1.distAbs*2)/pow(4000,2);

    
	JOGADOR.pos_x-= ARENA.pos_x;
	JOGADOR.pos_y-= ARENA.pos_y;
	for(int j=0; j<(INIMIGO_A.size()); j++){                
    	INIMIGO_A[j].pos_x-= ARENA.pos_x;
		INIMIGO_A[j].pos_y-= ARENA.pos_y;

    }
	for(int j=0; j<(INIMIGO_T.size()); j++){
		INIMIGO_T[j].pos_x-= ARENA.pos_x;
		INIMIGO_T[j].pos_y-= ARENA.pos_y;
    }
	ARENA.pos_x-= ARENA.pos_x;
	ARENA.pos_y-= ARENA.pos_y;

	AUX = JOGADOR;
	 
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
	glutMouseFunc(mouseClick);
    glutPassiveMotionFunc(mouseMove);
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
	glOrtho(ARENA.pos_x - ARENA.radius, ARENA.pos_x + ARENA.radius, ARENA.pos_y + ARENA.radius, ARENA.pos_y - ARENA.radius, -1.0f, 1.0f);
}
//----------- TECLADO
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
//------------ MOUSE
void mouseClick(int button, int  state, int x, int y){
	if(decolado){
	
	}
}
void mouseMove(int x, int y){
	if(decolado){
		if(oldX>x){
			if(JOGADOR.tan_now+JOGADOR.desl_can > JOGADOR.tan_now-PI/4)
			JOGADOR.desl_can-=PI/80;
		}
		else if(oldX<x){
			if(JOGADOR.tan_now+JOGADOR.desl_can < JOGADOR.tan_now+PI/4)
			JOGADOR.desl_can+=PI/80;
		}
		oldX=x;
	}
}


void idle(void){
	//printf("x0=%f\ty0=%f\n", JOGADOR.pos_x, JOGADOR.pos_y);
	float meio = pistaDeVoo1.pos1_x + pistaDeVoo1.distx/2;
	if(ready && !decolado){
		if(glutGet(GLUT_ELAPSED_TIME)-t0<=4000){
			t1 = (glutGet(GLUT_ELAPSED_TIME)-t0);			
			JOGADOR.pos_x = pistaDeVoo1.pos1_x + accelx*pow(t1,2)/2;
			JOGADOR.pos_y = pistaDeVoo1.pos1_y + accely*pow(t1,2)/2;
					
			if(JOGADOR.radius<TamFin && JOGADOR.pos_x >= pistaDeVoo1.pos1_x + pistaDeVoo1.distx/2)			
				JOGADOR.radius = (TamFin/2)+(TamFin/2)*(JOGADOR.pos_x-meio)/(pistaDeVoo1.pos2_x - meio);
		}
		else {decolado = true;}
	}
	if( keyStatus['-'] && decolado){
		if(VelRef-velocidade>0){
			VelRef-=velocidade/4;		
		}
	}
	if(keyStatus['r'] || keyStatus['R']){
		reseta();
	}
	if( keyStatus['+'] && decolado ){
		VelRef+=velocidade/4;
	}
  	if((keyStatus['a'] || keyStatus['A']) && decolado )
	{
    	glPushMatrix();
    	glTranslatef(JOGADOR.pos_x, JOGADOR.pos_y,0);
		JOGADOR.tan_now-= PI/48;
		glRotatef(JOGADOR.tan_now*180/PI,0,0,1);
		glPopMatrix();
	}
  	if((keyStatus['d'] || keyStatus['D']) && decolado)
	{
		glPushMatrix();
    	glTranslatef(JOGADOR.pos_x, JOGADOR.pos_y,0);
		JOGADOR.tan_now+= PI/48;
		glRotatef(JOGADOR.tan_now*180/PI,0,0,1);
		glPopMatrix();
	}
	if(decolado && distanciaAereo(JOGADOR.pos_x + cos(JOGADOR.tan_now)*VelRef, JOGADOR.pos_y+sin(JOGADOR.tan_now)*VelRef)){
		if(distanciaArena(JOGADOR.pos_x + cos(JOGADOR.tan_now)*VelRef,JOGADOR.pos_y + sin(JOGADOR.tan_now)*VelRef)){
			JOGADOR.pos_x+= cos(JOGADOR.tan_now)*VelRef;
			JOGADOR.pos_y+= sin(JOGADOR.tan_now)*VelRef;
		}
		else{
			transporta();			
		}
	}
	else if(decolado){		
		reseta();
	}
  	glutPostRedisplay();
}


void display(void){
    
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	//ARENA
	glBegin(GL_POLYGON);
    glColor3f(0, 0, 1);
	for(i = 0; i < circle_points; i++) {
    	angle = (2*PI*i)/circle_points;
		glVertex2f(ARENA.pos_x+ARENA.radius*cos(angle),ARENA.pos_y+ARENA.radius*sin(angle));	
	}
	glEnd();

	//PISTA_DE_VOO
	glLineWidth(1);
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
    glVertex2f(pistaDeVoo1.pos1_x, pistaDeVoo1.pos1_y);
    glVertex2f(pistaDeVoo1.pos2_x, pistaDeVoo1.pos2_y);
	glEnd();
	

	//INIMIGO_A
	for(int j=0; j<(INIMIGO_A.size()); j++){
		glPushMatrix();                
    	INIMIGO_A[j].desenhaNave();
		glPopMatrix();
    }
	//INIMIGO_T
	for(int j=0; j<(INIMIGO_T.size()); j++){                
		glPushMatrix();		
		INIMIGO_T[j].desenhaNave();
		glPopMatrix();
    }
	glColor3f(1,1,1);

	//JOGADOR
	//glPushMatrix();
    JOGADOR.desenhaNave();
	//glPopMatrix();
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

void transporta(){
	float ang = tan(JOGADOR.tan_now*180/PI);
	float x = JOGADOR.pos_x, y= JOGADOR.pos_y, r=ARENA.radius;
	
	float x1= (1/(ang*ang+1))*(sqrt(-x*x+2*x*y*ang-y*y*ang*ang+ang*ang*r*r+r*r)-x*ang+y*ang*ang);
	float y1= (1/(ang*ang+1))*(ang*sqrt(-x*x+2*x*y*ang-y*y*ang*ang+ang*ang*r*r+r*r)+x-y*ang);
	float x2= (1/(ang*ang+1))*(-sqrt(-x*x+2*x*y*ang-y*y*ang*ang+ang*ang*r*r+r*r)-x*ang+y*ang*ang);
	float y2= (1/(ang*ang+1))*(-ang*sqrt(-x*x+2*x*y*ang-y*y*ang*ang+ang*ang*r*r+r*r)+x-y*ang);

	printf("%f\n", JOGADOR.pos_x);
	if( sqrt(pow((x1-JOGADOR.pos_x),2.0) + pow((y1-JOGADOR.pos_y),2.0)) > sqrt(pow((x2-JOGADOR.pos_x),2.0) + pow((y2-JOGADOR.pos_y),2.0))){	
		JOGADOR.pos_x = x1+cos(JOGADOR.tan_now)*VelRef;
		JOGADOR.pos_y = y1+sin(JOGADOR.tan_now)*VelRef;
	}
	else{
		JOGADOR.pos_x = x2+cos(JOGADOR.tan_now)*VelRef;
		JOGADOR.pos_y = y2+sin(JOGADOR.tan_now)*VelRef;
	}
}

void reseta(){
	JOGADOR = AUX;
	decolado = false;
	ready =  false;
	VelRef = velocidade*4000*(pistaDeVoo1.distAbs*2)/pow(4000,2);
}
