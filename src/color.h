#ifndef COLOR_H
#define COLOR_H

#include "pch.h"

class Color
{
	public:
		Color();
		Color(double r, double g, double b, double a);
		
		double r;
		double g;
		double b;
		double a;
		
		
		
		void serialize(JSON::Adapter& adapter);
	private:
		/* add your private declarations */
};

#endif /* COLOR_H */ 
