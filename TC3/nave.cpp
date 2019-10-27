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
}

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

void Nave::desenhaHelix(float a, float b){
		glTranslatef(a, b, 0);
		glRotatef(tan_now*180/PI,0,0,1);
		glColor3f(1, 1, 0);	
		glBegin(GL_POLYGON);
			glVertex2f(a,b);
			glVertex2f(a-radius/10,b+radius/10);
			glVertex2f(a-radius/10,b-radius/10);
			glVertex2f(a+radius/10,b+radius/10);
			glVertex2f(a+radius/10,b-radius/10);
			//glVertex2f(a,b);			
		glEnd();

}

void Nave::desenhaNave(){
	
	if(cor == "green"){  
		glPushMatrix();	
			desenhaCirculoEli(radius,1,1,1,1);	//-- Hitbox
		glPopMatrix();
		glPushMatrix();
			desenhaCirculoEli(radius,0,1,0,0.3); // --Corpo da Nave
		glPopMatrix();
		glPushMatrix();
			desenhaHelix((pos_x),(pos_y));
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
