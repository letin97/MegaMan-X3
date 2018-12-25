#include "Stage.h"

Stage::Stage()
{
}


Stage::~Stage()
{
}

RECT Stage::GetBound()
{
	return bound;
}

void Stage::SetBound(RECT bound)
{
	this->bound = bound;
}

string Stage::GetName()
{
	return name;
}
void Stage::SetName(string name)
{
	this->name = name;
}

