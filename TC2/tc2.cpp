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
    Circulo(int x, int y, int iD, int raio, string fill);
};

Circulo::Circulo(int x, int y, int iD, int raio, string fill){
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
        if(fill == "green"){
                printf("Player!");
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
}
