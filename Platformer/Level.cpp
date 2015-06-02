#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include "Block.h"
#include "Level.h"
 
using namespace sf;
using namespace std;

Level::Level(std::string LevelFileNamePass) //Default map size (256x256)
{
	height = 256;
	width = 256;
	LevelFileName = LevelFileNamePass;
}

Level::Level(std::string LevelFileNamePass, int h, int w) //Custom map size
{
	height = h;
	width = w;
	LevelFileName = LevelFileNamePass;
}

Level::~Level() 
{
	cout << "Destroying " << LevelFileName << "... \n";
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			if (ptr[x][y] != NULL)
			{
				delete ptr[x][y];
			}
		}
		delete[] ptr[x];
	} 
	delete[] ptr;
	delete[] LevelData;
}

int Level::GetBlockNumberFromLetter(char Letter)
{
	for (int i = 0; i < BlockTemplates.size(); i++)
	{
		if (BlockTemplates.at(i)->letter == Letter)
		{
			return i;
		}
	}
	cout << "Bad Block!\n";
	return 0;
}

void Level::ParseBlocks()
{
	ifstream BlockFile;
	string line, variable, value, side = "";
	BlockFile.open("Levels/" + LevelFileName + "/Blocks/blocks.txt", ios::in);
	std::cout << "Parsing block file in Levels/" << LevelFileName << "/Blocks/blocks.txt\n";
	// parse BlockFile
	if (BlockFile.good()) {
		while (getline(BlockFile, line)) {
			variable.erase();
			value.erase();
			side.erase();
			if (line.empty() || (line.at(0) && line.at(1) == '/'))
				continue;
			if (line.at(0) == '~') { // parse ~<name>, after this is the block info	
				line.erase(0, 1);
				BlockTemplates.push_back(new Block);
				BlockTemplates.back()->name = line;
				cout << "Starting creation of a block...\n";
				continue;
			}

			// parse <variable>=<value> for the line
			else {
				for (int w = 0; line.at(w) != '=' && w < line.length(); w++) {
					variable = variable + line.at(w);
				}
				for (int v = variable.length() + 1; v < line.length(); v++) {
					value = value + line.at(v);
				}
				cout << "Variable: '" << variable << "' Value: '" << value << "'\n";
			}

			// Letter
			if (variable == "letter") {
				BlockTemplates.back()->letter = value.at(0);
			}

			//PhasableSides 
			else if (variable == "PhasableSides")
			{
				if (value == "none") {
					BlockTemplates.back()->Top.Phasable = false;
					BlockTemplates.back()->Bot.Phasable = false;
					BlockTemplates.back()->Left.Phasable = false;
					BlockTemplates.back()->Right.Phasable = false;
				}
				else {
					value = value + ' ';
					for (int x = 0; x < value.length(); x++) {
						if (value.at(x) == ',' || x + 1 >= value.length()) {
							if (side == "left")
								BlockTemplates.back()->Left.Phasable = true;
							else if (side == "right")
								BlockTemplates.back()->Right.Phasable = true;
							else if (side == "top")
								BlockTemplates.back()->Top.Phasable = true;
							else if (side == "bot")
								BlockTemplates.back()->Bot.Phasable = true;
							else
								std::cout << "WARNING: Invalid side in PhasableSides in blocks.txt\n";
							cout << "Side " << side << " is phasable.\n";
							side = "";
						}
						else
							side = side + value.at(x);
					}
				}
			}

			// Texture
			else if (variable == "texture") {
				BlockTemplates.back()->TextureA = new Texture();
				BlockTemplates.back()->TextureA->loadFromFile("Levels/" + LevelFileName + "/Blocks/" + value);
			}

			// Spawn Point
			else if (variable == "spawn") {
				if (value == "true")
				{
					BlockTemplates.back()->PlayerSpawn = true;
				}
			}
		}

	}
	else
		std::cout << "ERROR: Block file does not exist or is invalid!\n"; 
			
	BlockFile.close();
}

void Level::Create() // Create a non-fixed datastructure of Blocks 
{
	cout << "Creating Blocks...\n";

	ptr = new Block **[width];
	for (int x = 0; x < width; x++) //This part sets up the 2d block array of pointers
	{
		ptr[x] = new Block *[height];
	}
	for (int x = 0; x < width; x++) //This part sets the pointers equal to new block addresses.
	{
		for (int y = 0; y < height; y++)
		{
			if (LevelData[x][y] == '0')
			{
				ptr[x][y] = NULL;
			}
			else
			{
				ptr[x][y] = new Block();
				*ptr[x][y] = *BlockTemplates.at(GetBlockNumberFromLetter(LevelData[x][y]));
				ptr[x][y]->rect.setPosition(Vector2f(x*64,y*64));
				ptr[x][y]->rect.setTexture(ptr[x][y]->TextureA);
				ptr[x][y]->Update();
				if (ptr[x][y]->PlayerSpawn == true)
				{
					PlayerSpawn = ptr[x][y];
					ptr[x][y]->OutInfo();
				}
				//cout << "Created a red block at (" << x << ", " << y << "). Value in memory: " << ptr[x][y] << ".\n";
				//
			}
		}
	}

}

void Level::Load()
{
	cout << "Loading LevelData from file '" << LevelFileName << "' to an array...\n"; //Creates an array with data from the textfile

	LevelData = new char*[width];

	ifstream LevelFile;
	LevelFile.open("Levels/" + LevelFileName + "/level.txt", ios::in);

	for (int x = 0; x < width; x++)
	{
		LevelData[x] = new char[height];
	}
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y <= height; y++)
		{
			if (LevelFile.good())
			{
				LevelData[x][y] = (char)LevelFile.get();
			}
			else
			{
				cout << "\nThe level '" << LevelFileName << "' has a bad format.\n";
			}
		}
	}
	LevelFile.close();
	ParseBlocks();
	Create();
}

void Level::Draw(RenderWindow *window)
{
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			if (ptr[x][y] != NULL)
			{
				ptr[x][y]->Update();
				if (window != NULL)
				{
					window->draw(ptr[x][y]->rect);
				}
				else
				{
					cout << "ERROR: RenderWindow at location " << window << " was NULL.\n";
				}
			}
		}
	}
}

void Level::Save()
{
	cout << "Saving " << LevelFileName << "... \n";
	ofstream SaveFile;
	SaveFile.open("level2.txt");
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			SaveFile << LevelData[x][y];
		}
		if (x <= width - 2)
		{
			SaveFile << endl;
		}

	}
	SaveFile.close();
}


