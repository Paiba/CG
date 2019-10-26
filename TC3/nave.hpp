#include <iostream>
using namespace std;

class Nave{
public:
    float pos_x;
    float pos_y;
    float radius;
    int id;
    string cor;
	float tan_now;

    Nave();
    void setAtt(float x, float y, int iD, float raio, string fill, float tangente);
	void desenhaCirculoEli(float raio, float r, float g, float b, float elip);
	void desenhaHelix(float a, float b);	
	void desenhaNave();
};

