#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include "Block.h"

using namespace sf;
using namespace std;

class Level
{
public:
	int height, width; //Height and width of level
	Block *** ptr; //2d array of pointers to pointers that point to blocks
	Block* PlayerSpawn;
	Level(string LevelFileNamePass);
	Level(string LevelFileNamePass, int h, int w);
	~Level();
	void Load();
	void Draw(RenderWindow *window);
	void Save();
private:
	char** LevelData; //2d character array of the characters in the text file
	int GetBlockNumberFromLetter(char Letter);
	void ParseBlocks();
	vector<Block*> BlockTemplates;
	void Create();
	string LevelFileName; //Text file with leveldata


};
