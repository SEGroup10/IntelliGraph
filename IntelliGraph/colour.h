#ifndef COLOUR_H
#define COLOUR_H

#include <string>
using namespace std;

class colour
{
	public:
		colour();
		void changeColourRGB(int newR,int newG, int newB);
		int getR();
		int getG();
		int getB();

	private:
		int R, G, B;
};

class position
{
	public:
		position();
		int X;
		int Y;
};

#endif // COLOUR_H
