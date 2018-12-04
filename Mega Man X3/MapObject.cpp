#include"MapObject.h"

MapObject::MapObject(TiXmlElement *node, string name)
{
	this->ReadXML(node, name);
}
MapObject::~MapObject()
{

}
void MapObject::ReadXML(TiXmlElement *node, string name)
{
	this->name = name;
	node->QueryIntAttribute("id", &id);
	node->QueryFloatAttribute("x", &x);
	node->QueryFloatAttribute("y", &y);
	node->QueryFloatAttribute("width", &width);
	node->QueryFloatAttribute("height", &height);
}