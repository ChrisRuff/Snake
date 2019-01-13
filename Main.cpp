#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <conio.h>

using namespace std;


int const screenSizeX  = 48;
int const screenSizeY = 24;
int oldPlayer[screenSizeX * screenSizeY][2];
int tailSize = 0;
int fruit[2];
int player[2];
int counter = 0;


enum dir{ UP, DOWN, LEFT, RIGHT, STOP };
dir moving;

void draw()
{
	system("CLS");
	for (int i = 0; i <= screenSizeY; i++)
	{
		for (int j = 0; j <= screenSizeX; j++)
		{
			if (i == player[0] && j == player[1])
			{
				cout << "P";
			}
			else if (i == fruit[0] && j == fruit[1])
			{
				cout << "F";
			}
			else if(j == screenSizeX || j == 0)
			{
				cout << "#";
			}
			else if (i == screenSizeY || i == 0)
			{
				cout << "#";
			}
			else
			{
				bool reached = false;
				for (int k = 0; k < tailSize; k++)
				{
					if (oldPlayer[k][0] == i && oldPlayer[k][1] == j) 
					{
						reached = true;
						cout << "o";
						break;
					}
				}
				if (!reached)
				{
					cout << " ";
				}
				
			}
		}
		cout << endl;
	}
	
}

void input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
			if(moving != DOWN)
				moving = UP;
			break;
		case 's':
			if (moving != UP)
				moving = DOWN;
			break;
		case 'a':
			if (moving != RIGHT)
				moving = LEFT;
			break;
		case 'd':
			if (moving != LEFT)
				moving = RIGHT;
			break;
		}
	}
	
}

void logic()
{
	for (int i = tailSize - 1; i >= 1; i--)
	{
		oldPlayer[i][0] = oldPlayer[i - 1][0];
		oldPlayer[i][1] = oldPlayer[i - 1][1];
	}
	oldPlayer[0][0] = player[0];
	oldPlayer[0][1] = player[1];

	if (player[0] == 0 || player[0] == screenSizeY || player[1] == 0 || player[1] == screenSizeX)
	{
		exit(0);
	}
	for (int i = 1; i < tailSize; i++)
	{
		if (oldPlayer[i][0] == player[0] && oldPlayer[i][1] == player[1])
		{
			exit(0);
		}
	}
	

	if (moving == UP)
	{
		player[0] -= 1;
	}
	if (moving == DOWN)
	{
		player[0] += 1;
	}
	if (moving == LEFT)
	{
		player[1] -= 1;
	}
	if (moving == RIGHT)
	{
		player[1] += 1;
	}
	if (player[0] == fruit[0] && player[1] == fruit[1])
	{
		tailSize+=2;
		fruit[0] = rand() % (screenSizeY - 1) + 1;
		fruit[1] = rand() % (screenSizeX - 1) + 1;
	}

	
	
	Sleep(10);
}

int main()
{
	srand(time(NULL));
	fruit[0] = rand() % (screenSizeY - 1) + 1;
	fruit[1] = rand() % (screenSizeX - 1) + 1;
	player[0] = screenSizeY / 2;
	player[1] = screenSizeX / 2;
	moving = STOP;
	while (1)
	{
		draw();
		input();
		logic();
	}
	return 0;
}

