#include "proj.hpp"
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

Proj::Proj(){}

void Proj::setAtt2(float x, float y, float raio,float tangente, char tip){
    pos_x = x;
    pos_y = y;
    radius = raio;
	tan_now = tangente;
	velocidade = 0;
	tipo = tip;
}

void Proj::desenhaProj(){
	glTranslatef(pos_x, pos_y, 0);
	glRotatef((tan_now)*180/PI,0,0,1);
	if( tipo =='b'){
		glColor3f(0, 0, 0);	
		glBegin(GL_POLYGON);
		for(int i = 0; i < 1000; i++) {
    			float angle = (2*3.14*i)/1000;
				glVertex2f(radius*cos(angle),radius*sin(angle));	
		}
		glEnd();
	}
	else if(tipo=='t'){
		
		glColor3f(0, 0, 0);	
		glBegin(GL_POLYGON);
		for(int i = 0; i < 1000; i++) {
    			float angle = (2*3.14*i)/1000;
				glVertex2f(radius*cos(angle),radius*sin(angle));	
		}
		glEnd();
	}		
	
	
}

