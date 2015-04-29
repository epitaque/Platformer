#pragma once
#include <vector>
#include <string>

using namespace std;
class BlockFunction
{
public:
	BlockFunction(string FunctionA, vector<string> ParametersA);
	~BlockFunction();
	string Function;
	vector<string> Parameters;
};

