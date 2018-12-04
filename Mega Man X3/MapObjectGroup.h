#pragma once
#include"MapObject.h"
#include<string>
#include <vector>
using namespace std;
#include "TinyXML\tinyxml.h"

class MapObjectGroup
{
public:
	string name;
	vector<MapObject*> objects;
	int numObjects;

	MapObjectGroup(TiXmlElement *node);
	~MapObjectGroup();
	void ReadXML(TiXmlElement *node);
};