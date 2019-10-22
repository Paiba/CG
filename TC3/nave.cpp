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

void Nave::setAtt(float x, float y, int iD, float raio, string fill){
    pos_x = x;
    pos_y = y;
    radius = raio;
    id = iD; 
    cor = fill;
}

void Nave::desenhaCirculoEli(float raio, float r, float g, float b, float elip){
	glColor3f(r, g, b);	
	glBegin(GL_POLYGON);
	for(int i = 0; i < 1000; i++) {
    		float angle = (2*3.14*i)/1000;
			glVertex2f(pos_x+radius*cos(angle),pos_y+elip*radius*sin(angle));	
	}		
	glEnd();
}

void Nave::desenhaNave(){
	
	if(cor == "green"){
		desenhaCirculoEli(radius,1,1,1,1);
		desenhaCirculoEli(radius,0,1,0,0.3);
	}
	if(cor == "red"){
		desenhaCirculoEli(radius,1,0,0,1);
	}
	if(cor =="orange"){
		desenhaCirculoEli(radius,1,0.5,0,1);
	}
	
}
