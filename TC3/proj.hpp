#include <iostream>
using namespace std;

class Proj{
public:
    float pos_x;
    float pos_y;
    float radius;
	float tan_now;
	float velocidade;
	char tipo;

    Proj();
    void setAtt(float x, float y, float raio, float tangente, char tip);
	void desenhaProj();
};

