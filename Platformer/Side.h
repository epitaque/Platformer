#pragma once
#include <vector>
#include "BlockFunction.h"

using namespace std;

class Side
{
public:
	Side();
	~Side();
	bool Phasable;
	vector<BlockFunction> Functions;
};

