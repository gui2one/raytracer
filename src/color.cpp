#include "color.h"


Color::Color():r(1.0), g(1.0), b(1.0), a(1.0)
{
	
}
Color::Color(double _r, double _g, double _b, double _a):r(_r), g(_g), b(_b), a(_a)
{
	
}

void Color::serialize(JSON::Adapter& adapter){
	//~ std::string str;
	JSON::Class root(adapter, "Color");

	JSON_E(adapter, r);

	JSON_E(adapter, g);
;
	JSON_E(adapter, b);

	JSON_T(adapter, a);
	
}


