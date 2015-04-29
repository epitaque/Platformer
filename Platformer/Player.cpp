#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include "Object.h"
#include "Player.h"
#include "Level.h"
#include "Block.h"

using namespace sf;
using namespace std;

// Line Intersection code from cplusplus.com user Disch. Works pretty perfectly
typedef Vector2<double> Point; 

inline double Dot(const Point& a, const Point& b)                        { return (a.x*b.x) + (a.y*b.y); }
inline double PerpDot(const Point& a, const Point& b)                    { return (a.y*b.x) - (a.x*b.y); }

bool LineCollision(const Point& A1, const Point& A2, const Point& B1, const Point& B2, double* out = 0)
{
	Point a(A2 - A1);
	Point b(B2 - B1);

	double f = PerpDot(a, b);
	if (!f)      // lines are parallel
	{
		return false;
	}
		

	Point c(B2 - A2);
	double aa = PerpDot(a, c);
	double bb = PerpDot(b, c);

	if (f < 0)
	{
		if (aa > 0)     return false;
		if (bb > 0)     return false;
		if (aa < f)     return false;
		if (bb < f)     return false;
	}
	else
	{
		if (aa < 0)     return false;
		if (bb < 0)     return false;
		if (aa > f)     return false;
		if (bb > f)     return false;
	}

	if (out)
		*out = 1.0 - (aa / f);
	return true;
}

float MaxVelocityOf(float Velocity, float Speed)
{
	if (abs(Velocity) <= Speed)
	{
		return Velocity;
	}
	else
	{
		if (Velocity > 0)
		{
			return Speed;
		}
		else
		{
			return Speed * (-1); 
		}
			
	}
} 

Player::Player(Level* LevelZ)
{
	rect.setPosition(0, 0);
	rect.setSize(sf::Vector2f(64, 64));
	rect.setFillColor(Color::Red);
	Speed = 8;
	Jump = 40;
	Acceleration = 1.01;
	CB = NULL;
	PastBlock = NULL;
	LevelA = LevelZ;
	Gravity = 2.0;

}

Player::Player(Vector2f position, Vector2f size, Color color, Level *LevelZ) 
{
	rect.setPosition(position);
	rect.setSize(size);
	rect.setFillColor(color);   
	Speed = 20;
	Jump = 40;
	Acceleration = 1.002;
	CB = NULL;
	PastBlock = NULL;
	LevelA = LevelZ;
	Gravity = 2.0;
}

bool Player::HandleCollision() // [0]
{
	for (int x = -2; x <= 2; x++) //Loop from -2 to 2
	{
		for (int y = -2; y <= 2; y++) //Loop from -2 to 2
		{							  //so this loops in total 25 times
									  //I could improve performance by only checking the blocks that are where the player will be next. Another day...
			
			// Check if the block is out of bounds
			if ( ( (int(rect.getPosition().x)/64) + x) >= 0 && ( (int(rect.getPosition().y)/64) + y) >= 0) 
			{
				// Check if the block at that position isn't null
				if (LevelA->ptr[(int(rect.getPosition().x) / 64) + x][(int(rect.getPosition().y) / 64) + y] != NULL) 
				{
						CB = LevelA->ptr[(int(rect.getPosition().x) / 64) + x][(int(rect.getPosition().y) / 64) + y];
					
						// DETECT collision
						if (!((right + Velocity.x) < CB->left + 1 || (left + Velocity.x) > CB->right - 1 || (top + Velocity.y) > CB->bottom - 1 || (bottom + Velocity.y) < CB->top + 1))
						{
							if (PastBlock != NULL)
								PastBlock->rect.setFillColor(Color::White);
							CB->rect.setFillColor(Color::Red);
							PastBlock = CB;


							// HANDLE collision
							// See which two sides the cube could be handled on, then see which axis to snap it to
							// Note: for some reason in sfml the y values are always inverted, super annoying but all you do is multiply it by -1
						
							if (Velocity.y < 0) //Bottom of CB.
							{
								if (Velocity.x > 0) //Left of CB ->^
								{
									if ( (right + Velocity.x ) - CB->left > -1 * ( (top + Velocity.y ) - CB->bottom))
									{
										if (!CB->Bot.Phasable)
										{
											rect.setPosition(Vector2f(rect.getPosition().x, CB->bottom));
											Velocity.y = 0;
										}
									} 
									else 
									{	
										if (!CB->Left.Phasable)
										{
											rect.setPosition(Vector2f(CB->left - rect.getSize().x, rect.getPosition().y));
											Velocity.x = 0;
										}
									}
								}
								else if (Velocity.x == 0) //Only bottom of CB
								{
									if (!CB->Bot.Phasable)
									{
										rect.setPosition(Vector2f(rect.getPosition().x, CB->bottom));
										Velocity.y = 0;
									}
								}
								else //Right of CB <-^
								{
									if (CB->right - (left + Velocity.x) >  -1 * ( (top + Velocity.y ) - CB->bottom))
									{
										if (!CB->Bot.Phasable)
										{
											rect.setPosition(Vector2f(rect.getPosition().x, CB->bottom));
											Velocity.y = 0;
										}
									}
									else
									{
										if (!CB->Right.Phasable)
										{
											rect.setPosition(Vector2f(CB->right, rect.getPosition().y));
											Velocity.x = 0;
										}	
									}
								}
							}
							else if (Velocity.y > 0) //Top of CB
							{
								if (Velocity.x > 0) //Left of CB ->\/
								{
									if ((right + Velocity.x) - CB->left > -1 * (CB->rect.getPosition().y - (bottom + Velocity.y))) //X Axis
									{
										if (!CB->Top.Phasable)
										{
											onSurface = true;
											rect.setPosition(Vector2f(rect.getPosition().x, CB->rect.getPosition().y - rect.getSize().y));
											Velocity.y = 0;
										}
									}
									else //Y Axis
									{
										if (!CB->Left.Phasable)
										{
											rect.setPosition(Vector2f(CB->left - rect.getSize().x, rect.getPosition().y));
											Velocity.x = 0;
										}
									}
								}
								else if (Velocity.x == 0) //Only top of CB
								{
									if (!CB->Top.Phasable)
									{
										onSurface = true;
										rect.setPosition(Vector2f(rect.getPosition().x, CB->rect.getPosition().y - rect.getSize().y));
										Velocity.y = 0;
									}
								}
								else //Right of CB \/<- 
								{
									if (CB->right - (left + Velocity.x) > -1 * (CB->rect.getPosition().y - (bottom + Velocity.y)))
									{
										if (!CB->Top.Phasable)
										{
											onSurface = true;
											rect.setPosition(Vector2f(rect.getPosition().x, CB->top - rect.getSize().y));
											Velocity.y = 0;
										}
									}
									else
									{
										if (!CB->Right.Phasable)
										{
											rect.setPosition(Vector2f(CB->right, rect.getPosition().y));
											Velocity.x = 0;
										}
									}
								}
							}
							else if (Velocity.y == 0)
							{
								if (Velocity.x > 0) //Left of CB <-
								{
									if (!CB->Left.Phasable)
									{
										rect.setPosition(Vector2f(CB->left - rect.getSize().x, rect.getPosition().y));
										Velocity.x = 0;
									}
								}
								else //Right of CB ->
								{
									if (!CB->Right.Phasable)
									{
										rect.setPosition(Vector2f(CB->right, rect.getPosition().y));
										Velocity.x = 0;
									}
									
								}
							}
						}
				}
			}
		}
	}
	return false;
}

void Player::Move(View* View)
{
	// Input
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		Velocity.x = MaxVelocityOf((Velocity.x + (1 - (Velocity.x / Speed))) * Acceleration, Speed);
	}

	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		Velocity.x = MaxVelocityOf((Velocity.x - ((1 - (Velocity.x / Speed))) * Acceleration), Speed);
	}

	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		//Velocity.y = MaxVelocityOf((Velocity.y - (1 - (Velocity.y / Speed))) * Acceleration, Speed);
		{		if (onSurface)

			Velocity.y = -1 * Jump;
			onSurface = false;
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		Velocity.y = MaxVelocityOf((Velocity.y + (1 - (Velocity.y / Speed))) * Acceleration, Speed);
	}

	HandleCollision();

	rect.move(Velocity);

	// Friction
	// Decay axes without input
	if(!Keyboard::isKeyPressed(Keyboard::Left) && !Keyboard::isKeyPressed(Keyboard::Right))
	{
		Velocity = Vector2f(Velocity.x / 1.1, Velocity.y);
	}
	/*if (!Keyboard::isKeyPressed(Keyboard::Up) && !Keyboard::isKeyPressed(Keyboard::Down))
	{
		//Velocity = Vector2f(Velocity.x, Velocity.y / 1.1);
		Velocity.y += Gravity;
	} */
	Velocity.y += Gravity;

	if (rect.getPosition().y > 2000)
	{
		cout << "Attempting to return player to spawn.\n";
		rect.setPosition(LevelA->PlayerSpawn->rect.getPosition());
		
	}

	if (!Keyboard::isKeyPressed(Keyboard::Left) && !Keyboard::isKeyPressed(Keyboard::Right) && !Keyboard::isKeyPressed(Keyboard::Up) && !Keyboard::isKeyPressed(Keyboard::Down))
	{
		if (Velocity.x < 0.1 && Velocity.x > -0.1)
		{
			Velocity.x = 0;
		}

		if (Velocity.y < 0.1 && Velocity.y > -0.1)
		{
			Velocity.y = 0;
		}
	}
		
	

	// Output Velocity for debugging
	if (TempIterator > 100 && Velocity != Vector2f(0, 0))
	{
		cout << "Velocity.x = '" << Velocity.x << "', Velocity.y = '" << Velocity.y << "'.\n";
		TempIterator = 0;
	}
	TempIterator = TempIterator + 1;
}
