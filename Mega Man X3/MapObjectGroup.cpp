#include"MapObjectGroup.h"

MapObjectGroup::MapObjectGroup(TiXmlElement *node)
{
	ReadXML(node);
}
MapObjectGroup::~MapObjectGroup()
{
	for (std::size_t i = 0; i < numObjects; i++)
	{
		MapObject *obj = objects.at(i);
		delete obj;
	}
}
void MapObjectGroup::ReadXML(TiXmlElement *node)
{
	name = (char *)node->Attribute("name");
	TiXmlElement *indexml = NULL;
	numObjects = 0;
	for (indexml = node->FirstChildElement(); indexml != NULL; indexml = indexml->NextSiblingElement())
	{
		numObjects++;
		MapObject *obj = new MapObject(indexml, name);
		objects.push_back(obj);
	}
}