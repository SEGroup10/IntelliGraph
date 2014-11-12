#include "colour.h"
#include <string>
using namespace std;

colour::colour()
{
	changeColourRGB(0,0,0);
}

void colour::changeColourRGB(int newR, int newG, int newB)
{
	newR > 255 ? newR = 255: 1;
	newG > 255 ? newG = 255: 1;
	newB > 255 ? newB = 255: 1;
	newR < 0 ? newR = 0: 1;
	newG < 0 ? newG = 0: 1;
	newB < 0 ? newB = 0: 1;
	R = newR; G = newG; B = newB;
	return;
}

int colour::getR()
{
	return R;
}

int colour::getG()
{
	return G;
}

int colour::getB()
{
	return B;
}

position::position()
{

}
