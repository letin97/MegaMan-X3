#pragma once
#include <d3dx9.h>
#include <string>
using namespace std;

class Stage
{
protected:
	string name;
	RECT bound;
public:
	Stage();
	~Stage();

	RECT GetBound();
	void SetBound(RECT bound);

	string GetName();
	void SetName(string name);
};

