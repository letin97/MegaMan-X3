#pragma once
#include<string>
#include "TinyXML\tinyxml.h"
using namespace std;

class MapObject
{
public:
	string name;
	float x, y, width, height;
	int id;

	MapObject(TiXmlElement *node, string name);
	~MapObject();
	void ReadXML(TiXmlElement *node, string name);
};
