#include "nave.hpp"
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

Nave::Nave(){}

void Nave::setAtt(float x, float y, int iD, float raio, string fill, float tangente){
    pos_x = x;
    pos_y = y;
    radius = raio;
    id = iD; 
    cor = fill;
	tan_now = tangente;
	desl_can = 0;
	velocidade = 0;
}
//CORPO DA NAVE
void Nave::desenhaCirculoEli(float raio, float r, float g, float b, float elip){
	if(cor == "green"){	
		glTranslatef(pos_x, pos_y, 0);
		glRotatef(tan_now*180/PI,0,0,1);
	}	
	glColor3f(r, g, b);	
	glBegin(GL_POLYGON);
	for(int i = 0; i < 1000; i++) {
    		float angle = (2*3.14*i)/1000;
			glVertex2f(radius*cos(angle),elip*radius*sin(angle));	
	}		
	glEnd();
}

//CANHÃO
void Nave::desenhaCanhao(float a, float b){
		glTranslatef(a, b, 0);
		glRotatef((tan_now+desl_can)*180/PI,0,0,1);
		glLineWidth(3);
		glBegin(GL_LINES);
			glVertex2f(radius, 0);
			glVertex2f(radius+(radius/1.5),0);
		glEnd();
}
//DETALHES
void Nave::desenhaDet(float a, float b){
		glTranslatef(a, b, 0);
		glRotatef(tan_now*180/PI,0,0,1);
		//Desenho da janela da nave
		glColor3f(0, 0, 0);	
		glBegin(GL_POLYGON);
		for(int i = 0; i < 1000; i++) {
    		float angle = (2*3.14*i)/1000;
			glVertex2f(radius/2+radius/2.5*cos(angle),0.3*radius/2.5*sin(angle));	
		}		
		glEnd();
		//Desenho do detalhe do rabo da nave
		glLineWidth(3);
		glBegin(GL_LINES);
			glVertex2f(-radius, 0);
			glVertex2f(-radius/2, 0);
		glEnd();
}
//ASA
void Nave:: desenhaAsa(float a, float b){
		glTranslatef(a, b, 0);
		glRotatef(tan_now*180/PI,0,0,1);
		glColor3f(0, 0, 0);	
		glBegin(GL_POLYGON);
			glVertex2f(radius/4,0);
			glVertex2f(-radius/4,0);
			glVertex2f(-radius/2,-0.9*radius);
			glVertex2f(0,-0.9*radius);		
		glEnd();
		glBegin(GL_POLYGON);
			glVertex2f(radius/4,0);
			glVertex2f(-radius/4,0);
			glVertex2f(-radius/2,0.9*radius);
			glVertex2f(0,0.9*radius);		
		glEnd();
}

//HÉLICE
void Nave::desenhaHelix(float a, float b){
		glTranslatef(a, b, 0);
		glRotatef(tan_now*180/PI,0,0,1);
		glRotatef(180/PI*velocidade,0,1,0);
		glColor3f(1, 1, 0);	
		glBegin(GL_POLYGON);
			glVertex2f(radius/2,radius/2);
			glVertex2f(radius/2+radius/4,radius/2+radius/4);
			glVertex2f(radius/2+radius/4,radius/2-radius/4);
			glVertex2f(radius/2-radius/4,radius/2+radius/4);
			glVertex2f(radius/2-radius/4,radius/2-radius/4);			
		glEnd();
		glBegin(GL_POLYGON);
			glVertex2f(radius/2,-radius/2);
			glVertex2f(radius/2+radius/4,-radius/2+radius/4);
			glVertex2f(radius/2+radius/4,-radius/2-radius/4);
			glVertex2f(radius/2-radius/4,-radius/2+radius/4);
			glVertex2f(radius/2-radius/4,-radius/2-radius/4);			
		glEnd();
}

//DESENHO DA NAVE INTEIRA
void Nave::desenhaNave(){
	
	if(cor == "green"){
		//-- Hitbox
		/*glPushMatrix();	
			desenhaCirculoEli(radius,1,1,1,1);	
		glPopMatrix();*/
		 //-- Asas da nave
		glPushMatrix();
			desenhaAsa(pos_x,pos_y);
		glPopMatrix();
		// --Corpo da Nave 
		glPushMatrix();
			desenhaCirculoEli(radius,0,1,0,0.3); 
		glPopMatrix();
		// --Detalhes da nave
		glPushMatrix();
			desenhaDet(pos_x,pos_y); 
		glPopMatrix();
		//--Canhão da nave
		glPushMatrix();
			desenhaCanhao(pos_x,pos_y); 
		glPopMatrix();
		//
		glPushMatrix();
			desenhaHelix(pos_x, pos_y); 
		glPopMatrix();
		
	}
	if(cor == "red"){
		glTranslatef(pos_x, pos_y, 0);
		desenhaCirculoEli(radius,1,0,0,1);
	}
	if(cor =="orange"){		
		glTranslatef(pos_x, pos_y, 0);
		desenhaCirculoEli(radius,1,0.5,0,1);
	}
	
}
