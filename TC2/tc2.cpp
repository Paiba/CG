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


float velocidade;
string nom;
string tip;
string caminh;
string caminhoInteiro;

class Circulo{
private:
    int pos_x;
    int pos_y;
    int radius;
    int id;
    string cor;
public:
    Circulo();
    void setAtt(int x, int y, int iD, int raio, string fill);
};

Circulo::Circulo(){}

void Circulo::setAtt(int x, int y, int iD, int raio, string fill){
    pos_x = x;
    pos_y = y;
    radius = raio;
    id = iD; 
    cor = fill;
}


struct pista{
    int pos1_x;
    int pos1_y;
    int pos2_x;
    int pos2_y;
    int id;
};

Circulo JOGADOR;
Circulo ARENA;

pista pistaDeVoo1;


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
    pElement->QueryFloatAttribute("vel", &velocidade);
    caminhoInteiro = caminh +  nom + "\." + tip;
    XMLDocument doc1;
	doc1.LoadFile(caminhoInteiro.c_str());
    XMLElement * svgElement = doc1.FirstChildElement("svg");
    XMLElement * svgCirc = svgElement->FirstChildElement("circle");    
    XMLElement * svgLin = svgElement->FirstChildElement("line");
    while(svgCirc){
        string fill;
        fill = svgCirc->Attribute("fill");
        if(fill == "green"){//Player
            //printf("Player!\n");
            PLAYER.setAtt(svgCirc->IntAttribute("cx"),svgCirc->IntAttribute("cy"),svgCirc->IntAttribute("id"),svgCirc->IntAttribute("r"),svgCirc->Attribute("fill"),);
            
        }
        if (fill == "blue"){//Arena 
            //printf("Arena!\n");
        }
        if (fill == "red"){//Inimigo Aéreo
            //printf("Aereo!\n");
        }
        if (fill == "orange"){//Inimigo Terrestre
            //printf("Terrestre!\n");
        }
        svgCirc = svgCirc->NextSiblingElement("circle");
            
    }
    if(svgLin){
        svgLin->QueryIntAttribute("x1",&pistaDeVoo1.pos1_x);
        svgLin->QueryIntAttribute("x2",&pistaDeVoo1.pos2_x);
        svgLin->QueryIntAttribute("y1",&pistaDeVoo1.pos1_y);
        svgLin->QueryIntAttribute("y2",&pistaDeVoo1.pos2_y);
    }
    
}



int main(int argc, char**argv)
{
    read_xml(argv[1]);
    
glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE |GLUT_RGB);
	glutInitWindowSize(500, 500); 
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Trabalho2");
	

	//Callbacks	
	init();
	glutDisplayFunc(display);
   
    //Main Loop 
	glutMainLoop();
	return 0;
}

void display(void){
    
    
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,0,0);
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 1, 0);
    angle = (2*PI*i)/1000;
	glVertex2f(PLAYER->pos_x+PLAYER->raio*cos(angle),PLAYER->pos_y+PLAYER->raio*sin(angle));
	
 	
	glFlush();
}
