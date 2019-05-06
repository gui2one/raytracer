#ifndef SCENE_FILE_LOADER_H
#define SCENE_FILE_LOADER_H


#include "pch.h"


//-----------------------------------------------------------------------------
// Code support required for serialization.
class JSONExample
{
public:
    // to be JSON'ised
    std::string text;
public:
    // each class requires a public serialize function
    void serialize(JSON::Adapter& adapter)
    {
        // this pattern is required 
        JSON::Class root(adapter,"JSONExample");
        // this is the last member variable we serialize so use the _T variant
        JSON_T(adapter,text);
    }
};

class SceneFileLoader
{
	public:
		SceneFileLoader();
			
	private:
		/* add your private declarations */
};

#endif /* SCENE_FILE_LOADER_H */ 
