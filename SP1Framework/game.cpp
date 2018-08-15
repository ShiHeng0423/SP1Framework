// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];
//setting of maze
bool activatetrap = false;
bool eventactivate = false;
bool opentrap = false;
int puzzlelevel = 0;
void renderMapOpenTrap1();
bool clearevent1 = false;
void renderMapEventClear1();
void renderMapOpenTrap2();
bool clearevent2 = false;
void renderMapEventClear2();
void renderMapOpenTrap3();
bool clearevent3 = false;
void renderMapEventClear3();
// Game specific variables here
SGameChar   g_sChar;
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once

// Console object
Console g_Console(80, 25, "SP1 Framework");

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init( void )
{
    // Set precision for floating point output
    g_dElapsedTime = 0.0;
    g_dBounceTime = 0.0;

    // sets the initial state for the game
    g_eGameState = S_SPLASHSCREEN;

    g_sChar.m_cLocation.X = 0;
    g_sChar.m_cLocation.Y = 2;
    g_sChar.m_bActive = true;
    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 16, L"Consolas");
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown( void )
{
    // Reset to white text on black background
    colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    g_Console.clearBuffer();
}

//--------------------------------------------------------------
// Purpose  : Getting all the key press states
//            This function checks if any key had been pressed since the last time we checked
//            If a key is pressed, the value for that particular key will be true
//
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void getInput( void )
{    
    g_abKeyPressed[K_UP]     = isKeyPressed(VK_UP);
    g_abKeyPressed[K_DOWN]   = isKeyPressed(VK_DOWN);
    g_abKeyPressed[K_LEFT]   = isKeyPressed(VK_LEFT);
    g_abKeyPressed[K_RIGHT]  = isKeyPressed(VK_RIGHT);
    g_abKeyPressed[K_SPACE]  = isKeyPressed(VK_SPACE);
    g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	g_abKeyPressed[K_SPECIAL] = isKeyPressed(VK_KEY_B);
}

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// Output   : void
//--------------------------------------------------------------
void update(double dt)
{
    // get the delta time
    g_dElapsedTime += dt;
    g_dDeltaTime = dt;

    switch (g_eGameState)
    {
        case S_SPLASHSCREEN : splashScreenWait(); // game logic for the splash screen
            break;
        case S_GAME: gameplay(); // gameplay logic when we are in the game
            break;
    }
}
//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
//--------------------------------------------------------------
void render()
{
    clearScreen();      // clears the current screen and draw from scratch 
    switch (g_eGameState)
    {
        case S_SPLASHSCREEN: renderSplashScreen();
            break;
        case S_GAME: renderGame();
            break;
    }
    renderFramerate();  // renders debug information, frame rate, elapsed time, etc
    renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}

void splashScreenWait()    // waits for time to pass in splash screen
{
    if (g_dElapsedTime > 0.0) // wait for 3 seconds to switch to game mode, else do nothing
        g_eGameState = S_GAME;
}

void gameplay()            // gameplay logic
{
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
                        // sound can be played here too.
}
char scanMap1(char createwall[20][70])
{
	string line;
	ifstream myfile("MAZE1.txt");
	int i = 0;
	int pos = 0;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			for (int j = 0; j < 70; j++)
			{
				createwall[i][j] = line[j];
			}
			i++;
		}
		myfile.close();
	}
	return createwall[20][70];
}
char scanMap1E(char createwall[20][70])
{
	string line;
	ifstream myfile("MAZE1E.txt");
	int i = 0;
	int pos = 0;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			for (int j = 0; j < 70; j++)
			{
				if (opentrap == true)
				{
					if (line[j] == 'x' || line[j] == 'X')
					{
						line[j] = ' ';
					}
				}
				createwall[i][j] = line[j];
			}
			i++;
		}
		myfile.close();
	}
	return createwall[20][70];
}
char scanMap1D(char createwall[20][70])
{
	string line;
	ifstream myfile("MAZE1D.txt");
	int i = 0;
	int pos = 0;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			for (int j = 0; j < 70; j++)
			{
				createwall[i][j] = line[j];
			}
			i++;
		}
		myfile.close();
	}
	return createwall[20][70];
}
char scanMap2(char createwall[20][70])
{
	string line;
	ifstream myfile("MAZE2.txt");
	int i = 0;
	int pos = 0;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			for (int j = 0; j < 70; j++)
			{
				createwall[i][j] = line[j];
			}
			i++;
		}
		myfile.close();
	}
	return createwall[20][70];
}
char scanMap3(char createwall[20][70])
{
	string line;
	ifstream myfile("MAZE3.txt");
	int i = 0;
	int pos = 0;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			for (int j = 0; j < 70; j++)
			{
				createwall[i][j] = line[j];
			}
			i++;
		}
		myfile.close();
	}
	return createwall[20][70];
}
void moveCharacter()
{
    bool bSomethingHappened = false;
    if (g_dBounceTime > g_dElapsedTime)
        return;
	char createwall[20][70];

	if (puzzlelevel == 0)
	{
		if (eventactivate == true)
		{
			if (clearevent1 == true)
			{
				scanMap1D(createwall);
			}
			else
			{
				scanMap1E(createwall);
			}
		}
		else
		{
			scanMap1(createwall);
		}
	}
	else if(puzzlelevel == 1)
	{
		scanMap2(createwall);
	}
	else if (puzzlelevel == 2)
	{
		scanMap3(createwall);
	}
    // Updating the location of the character based on the key press
    // providing a beep sound whenver we shift the character
	if (g_abKeyPressed[K_UP] && g_sChar.m_cLocation.Y > 2)
	{
		//Beep(1440, 30);
		int characterlocationY = g_sChar.m_cLocation.Y - 1;
		int characterlocationX = g_sChar.m_cLocation.X;
		characterlocationY -= 1;
		if (createwall[characterlocationY][characterlocationX] == ' ' || createwall[characterlocationY][characterlocationX] == '2' ||
			createwall[characterlocationY][characterlocationX] == 'E' || createwall[characterlocationY][characterlocationX] == '3' ||
			createwall[characterlocationY][characterlocationX] == 'T' || createwall[characterlocationY][characterlocationX] == 'X' ||
			createwall[characterlocationY][characterlocationX] == 'S' || createwall[characterlocationY][characterlocationX] == 's')
		{
			g_sChar.m_cLocation.Y--;
			bSomethingHappened = true;
			if (createwall[characterlocationY][characterlocationX] == '2')
			{
				g_sChar.m_cLocation.X = 0;
				g_sChar.m_cLocation.Y = 2;
				puzzlelevel++;
				renderGame();
			}
			if (createwall[characterlocationY][characterlocationX] == '3')
			{
				g_sChar.m_cLocation.X = 0;
				g_sChar.m_cLocation.Y = 2;
				puzzlelevel++;
				renderGame();
			}
			else if (createwall[characterlocationY][characterlocationX] == 'E')
			{
				g_sChar.m_cLocation.X = 0;
				g_sChar.m_cLocation.Y = 2;
				eventactivate = true;
				renderGame();
			}
			else if (createwall[characterlocationY][characterlocationX] == 'T')
			{
				g_sChar.m_cLocation.X = 60;
				g_sChar.m_cLocation.Y = 12;
			}
			else if (createwall[characterlocationY][characterlocationX] == 'X')
			{
				g_sChar.m_cLocation.X = 60;
				g_sChar.m_cLocation.Y = 13;
				opentrap = true;
				renderGame();
			}
			else if (createwall[characterlocationY][characterlocationX] == 's')
			{
				g_sChar.m_cLocation.X = 1;
				g_sChar.m_cLocation.Y = 14;
			}
			else if (characterlocationY == 13 && characterlocationX == 69 && opentrap == true)
			{
				g_sChar.m_cLocation.X = 33;
				g_sChar.m_cLocation.Y = 2;
				clearevent1 = true;
				renderGame();
			}
		}
	}

	if (g_abKeyPressed[K_LEFT] && g_sChar.m_cLocation.X > 0)
	{
		//Beep(1440, 30);

		int characterlocationY = g_sChar.m_cLocation.Y - 1;
		int characterlocationX = g_sChar.m_cLocation.X;
		characterlocationX -= 1;
		if (createwall[characterlocationY][characterlocationX] == ' ' || createwall[characterlocationY][characterlocationX] == '2' ||
			createwall[characterlocationY][characterlocationX] == 'E' || createwall[characterlocationY][characterlocationX] == '3' ||
			createwall[characterlocationY][characterlocationX] == 'T' || createwall[characterlocationY][characterlocationX] == 'X' ||
			createwall[characterlocationY][characterlocationX] == 'S' || createwall[characterlocationY][characterlocationX] == 's')
		{
			g_sChar.m_cLocation.X--;
			bSomethingHappened = true;
			if (createwall[characterlocationY][characterlocationX] == '2')
			{
				g_sChar.m_cLocation.X = 0;
				g_sChar.m_cLocation.Y = 2;
				puzzlelevel++;
				renderGame();
			}
			if (createwall[characterlocationY][characterlocationX] == '3')
			{
				g_sChar.m_cLocation.X = 0;
				g_sChar.m_cLocation.Y = 2;
				puzzlelevel++;
				renderGame();
			}
			else if (createwall[characterlocationY][characterlocationX] == 'E')
			{
				g_sChar.m_cLocation.X = 0;
				g_sChar.m_cLocation.Y = 2;
				eventactivate = true;
				renderGame();
			}
			else if (createwall[characterlocationY][characterlocationX] == 'T')
			{
				g_sChar.m_cLocation.X = 60;
				g_sChar.m_cLocation.Y = 12;
			}
			else if (createwall[characterlocationY][characterlocationX] == 'X')
			{
				g_sChar.m_cLocation.X = 60;
				g_sChar.m_cLocation.Y = 12;
				opentrap = true;
				renderGame();
			}
			else if (createwall[characterlocationY][characterlocationX] == 's')
			{
				g_sChar.m_cLocation.X = 1;
				g_sChar.m_cLocation.Y = 14;
			}
			else if (characterlocationY == 13 && characterlocationX == 69 && opentrap == true)
			{
				g_sChar.m_cLocation.X = 33;
				g_sChar.m_cLocation.Y = 2;
				clearevent1 = true;
				renderGame();
			}
		}
	}
    if (g_abKeyPressed[K_DOWN] && g_sChar.m_cLocation.Y < 19)
    {
        //Beep(1440, 30);
		int characterlocationY = g_sChar.m_cLocation.Y-1;
		int characterlocationX = g_sChar.m_cLocation.X;
		characterlocationY += 1;
		if (createwall[characterlocationY][characterlocationX] == ' ' || createwall[characterlocationY][characterlocationX] == '2' ||
			createwall[characterlocationY][characterlocationX] == 'E' || createwall[characterlocationY][characterlocationX] == '3' ||
			createwall[characterlocationY][characterlocationX] == 'T' || createwall[characterlocationY][characterlocationX] == 'X' ||
			createwall[characterlocationY][characterlocationX] == 'S' || createwall[characterlocationY][characterlocationX] == 's')
		{
			g_sChar.m_cLocation.Y++;
			bSomethingHappened = true;
			if (createwall[characterlocationY][characterlocationX] == '2')
			{
				g_sChar.m_cLocation.X = 0;
				g_sChar.m_cLocation.Y = 2;
				puzzlelevel++;
				renderGame();
			}
			if (createwall[characterlocationY][characterlocationX] == '3')
			{
				g_sChar.m_cLocation.X = 0;
				g_sChar.m_cLocation.Y = 2;
				puzzlelevel++;
				renderGame();
			}
			else if (createwall[characterlocationY][characterlocationX] == 'E')
			{
				g_sChar.m_cLocation.X = 0;
				g_sChar.m_cLocation.Y = 2;
				eventactivate = true;
				renderGame();
			}
			else if (createwall[characterlocationY][characterlocationX] == 'T')
			{
				g_sChar.m_cLocation.X = 60;
				g_sChar.m_cLocation.Y = 12;
			}
			else if (createwall[characterlocationY][characterlocationX] == 'X')
			{
				g_sChar.m_cLocation.X = 60;
				g_sChar.m_cLocation.Y = 12;
				opentrap = true;
				renderGame();
			}
			else if (createwall[characterlocationY][characterlocationX] == 's')
			{
				g_sChar.m_cLocation.X = 1;
				g_sChar.m_cLocation.Y = 14;
			}
			else if (characterlocationY == 13 && characterlocationX == 69 && opentrap == true)
			{
				g_sChar.m_cLocation.X = 33;
				g_sChar.m_cLocation.Y = 2;
				clearevent1 = true;
				renderGame();
			}
		}

    }
	if (g_abKeyPressed[K_RIGHT] && g_sChar.m_cLocation.X < 69)
	{
		//Beep(1440, 30);
		int characterlocationY = g_sChar.m_cLocation.Y - 1;
		int characterlocationX = g_sChar.m_cLocation.X;
		characterlocationX += 1;
		if (createwall[characterlocationY][characterlocationX] == ' ' || createwall[characterlocationY][characterlocationX] == '2' ||
			createwall[characterlocationY][characterlocationX] == 'E' || createwall[characterlocationY][characterlocationX] == '3' ||
			createwall[characterlocationY][characterlocationX] == 'T' || createwall[characterlocationY][characterlocationX] == 'X' ||
			createwall[characterlocationY][characterlocationX] == 'S' || createwall[characterlocationY][characterlocationX] == 's')
		{
			g_sChar.m_cLocation.X++;
			bSomethingHappened = true;
			if (createwall[characterlocationY][characterlocationX] == '2')
			{
				g_sChar.m_cLocation.X = 0;
				g_sChar.m_cLocation.Y = 2;
				puzzlelevel++;
				renderGame();
			}
			if (createwall[characterlocationY][characterlocationX] == '3')
			{
				g_sChar.m_cLocation.X = 0;
				g_sChar.m_cLocation.Y = 2;
				puzzlelevel++;
				renderGame();
			}
			else if (createwall[characterlocationY][characterlocationX] == 'E')
			{
				g_sChar.m_cLocation.X = 0;
				g_sChar.m_cLocation.Y = 2;
				eventactivate = true;
				renderGame();
			}
			else if (createwall[characterlocationY][characterlocationX] == 'T')
			{
				g_sChar.m_cLocation.X = 60;
				g_sChar.m_cLocation.Y = 12;
			}
			else if (createwall[characterlocationY][characterlocationX] == 'X')
			{
				g_sChar.m_cLocation.X = 60;
				g_sChar.m_cLocation.Y = 12;
				opentrap = true;
				renderGame();
			}
			else if (createwall[characterlocationY][characterlocationX] == 's')
			{
				g_sChar.m_cLocation.X = 1;
				g_sChar.m_cLocation.Y = 14;
			}
			else if (g_sChar.m_cLocation.Y == 13 && g_sChar.m_cLocation.X == 69 && opentrap == true)
			{
				g_sChar.m_cLocation.X = 33;
				g_sChar.m_cLocation.Y = 2;
				clearevent1 = true;
				renderGame();
			}
		}
	}
    if (g_abKeyPressed[K_SPACE])
    {
        g_sChar.m_bActive = !g_sChar.m_bActive;
        bSomethingHappened = true;
    }

    if (bSomethingHappened)
    {
        // set the bounce time to some time in the future to prevent accidental triggers
        g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
    }
	
}
void processUserInput()
{
    // quits the game if player hits the escape key
    if (g_abKeyPressed[K_ESCAPE])
        g_bQuitGame = true;    
}

void clearScreen()
{
    // Clears the buffer with this colour attribute
    g_Console.clearBuffer(0x00);
}

void renderSplashScreen()  // renders the splash screen
{
    COORD c = g_Console.getConsoleSize();
    c.Y /= 3;
    c.X = c.X / 2 - 9;
    g_Console.writeToBuffer(c, "A game in 3 seconds", 0x03);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 20;
    g_Console.writeToBuffer(c, "Press <Space> to change character colour", 0x09);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 9;
    g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0x09);
}

void renderGame()
{
	if (opentrap == true && clearevent1 == false)
	{
		renderMapOpenTrap1();
	}
	else if (clearevent1 == true && opentrap == true)
	{
		renderMapEventClear1();
	}
	else
	{
		renderMap();
	}
    renderCharacter();  // renders the character into the buffer
}

void renderMap()
{
	COORD c;
	char createwall[20][70];
	string line;
	int i = 0;
	int pos = 0;
	if (puzzlelevel == 0)
	{
		if (eventactivate == true)
		{
			ifstream myfile("MAZE1E.txt");

			if (myfile.is_open())
			{
				while (getline(myfile, line))
				{
					for (int j = 0; j < 70; j++)
					{
						createwall[i][j] = line[j];
					}
					i++;
				}
				myfile.close();
			}
		}
		else
		{
			ifstream myfile("MAZE1.txt");

			if (myfile.is_open())
			{
				while (getline(myfile, line))
				{
					for (int j = 0; j < 70; j++)
					{
						createwall[i][j] = line[j];
					}
					i++;
				}
				myfile.close();
			}
		}
	}
	else if(puzzlelevel == 1)
	{
		ifstream myfile("MAZE2.txt");

		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				for (int j = 0; j < 70; j++)
				{
					createwall[i][j] = line[j];
				}
				i++;
			}
			myfile.close();
		}
	}
	else if (puzzlelevel == 2)
	{
		ifstream myfile("MAZE3.txt");

		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				for (int j = 0; j < 70; j++)
				{
					createwall[i][j] = line[j];
				}
				i++;
			}
			myfile.close();
		}
	}
	else
	{

	}
	for (int k = 0; k < 20; k++)
	{
		int position = 0;
		c.Y = 1 + pos;
		for (int j = 0; j < 70; j++)
		{
			c.X = position;
			if (createwall[k][j] == ' ' || createwall[k][j] == '2' || createwall[k][j] == 'k' ||
				createwall[k][j] == 'E' || createwall[k][j] == 'S' || createwall[k][j] == 's' ||
				createwall[k][j] == 'X' || createwall[k][j] == 'T' || createwall[k][j] == '3' ||
				createwall[k][j] == 'Y' || createwall[k][j] == 'V' || createwall[k][j] == 'A' ||
				createwall[k][j] == 'O')
			{
				g_Console.writeToBuffer(c, createwall[k][j], 0x0);
			}
			else
			{
				g_Console.writeToBuffer(c, createwall[k][j], 0xFFF);
			}
			position++;
		}
		pos++;
	}
}
void renderMapOpenTrap1()
{
	COORD c;
	char createwall[20][70];
	string line;
	int i = 0;
	int pos = 0;
	if (puzzlelevel == 0)
	{
		if (eventactivate == true)
		{
			ifstream myfile("MAZE1E.txt");

			if (myfile.is_open())
			{
				while (getline(myfile, line))
				{
					for (int j = 0; j < 70; j++)
					{
						if (line[j] == 'x')
						{
							line[j] = ' ';
						}
						createwall[i][j] = line[j];
					}
					i++;
				}
				myfile.close();
			}
		}
		for (int k = 0; k < 20; k++)
		{
			int position = 0;
			c.Y = 1 + pos;
			for (int j = 0; j < 70; j++)
			{
				c.X = position;
				if (createwall[k][j] == ' ' || createwall[k][j] == '2' || createwall[k][j] == 'k' ||
					createwall[k][j] == 'E' || createwall[k][j] == 'S' || createwall[k][j] == 's' ||
					createwall[k][j] == 'X' || createwall[k][j] == 'T')
				{
					g_Console.writeToBuffer(c, createwall[k][j], 0x0);
				}
				else
				{
					g_Console.writeToBuffer(c, createwall[k][j], 0xFFF);
				}
				position++;
			}
			pos++;
		}
	}
}
void renderMapEventClear1() 
{
	COORD c;
	char createwall[20][70];
	string line;
	int i = 0;
	int pos = 0;
	if (puzzlelevel == 0)
	{
		if (eventactivate == true)
		{
			ifstream myfile("MAZE1D.txt");

			if (myfile.is_open())
			{
				while (getline(myfile, line))
				{
					for (int j = 0; j < 70; j++)
					{
						createwall[i][j] = line[j];
					}
					i++;
				}
				myfile.close();
			}
		}
	}
	for (int k = 0; k < 20; k++)
	{
		int position = 0;
		c.Y = 1 + pos;
		for (int j = 0; j < 70; j++)
		{
			c.X = position;
			if (createwall[k][j] == ' ' || createwall[k][j] == '2' || createwall[k][j] =='k'||
				createwall[k][j] == 'E')
			{
				g_Console.writeToBuffer(c, createwall[k][j], 0x0);
			}
			else
			{
				g_Console.writeToBuffer(c, createwall[k][j], 0xFFF);
			}
			position++;
		}
		pos++;
	}
}
void renderMapOpenTrap2()
{
	COORD c;
	char createwall[20][70];
	string line;
	int i = 0;
	int pos = 0;
	if (puzzlelevel == 0)
	{
		if (eventactivate == true)
		{
			ifstream myfile("MAZE2E.txt");

			if (myfile.is_open())
			{
				while (getline(myfile, line))
				{
					for (int j = 0; j < 70; j++)
					{
						if (line[j] == 'x')
						{
							line[j] = ' ';
						}
						createwall[i][j] = line[j];
					}
					i++;
				}
				myfile.close();
			}
		}
		for (int k = 0; k < 20; k++)
		{
			int position = 0;
			c.Y = 1 + pos;
			for (int j = 0; j < 70; j++)
			{
				c.X = position;
				if (createwall[k][j] == ' ' || createwall[k][j] == '2' || createwall[k][j] == 'k' ||
					createwall[k][j] == 'E' || createwall[k][j] == 'S' || createwall[k][j] == 's' ||
					createwall[k][j] == 'X' || createwall[k][j] == 'T')
				{
					g_Console.writeToBuffer(c, createwall[k][j], 0x0);
				}
				else
				{
					g_Console.writeToBuffer(c, createwall[k][j], 0xFFF);
				}
				position++;
			}
			pos++;
		}
	}
}
void renderMapEventClear2()
{
	COORD c;
	char createwall[20][70];
	string line;
	int i = 0;
	int pos = 0;
	if (puzzlelevel == 0)
	{
		if (eventactivate == true)
		{
			ifstream myfile("MAZE2D.txt");

			if (myfile.is_open())
			{
				while (getline(myfile, line))
				{
					for (int j = 0; j < 70; j++)
					{
						createwall[i][j] = line[j];
					}
					i++;
				}
				myfile.close();
			}
		}
	}
	for (int k = 0; k < 20; k++)
	{
		int position = 0;
		c.Y = 1 + pos;
		for (int j = 0; j < 70; j++)
		{
			c.X = position;
			if (createwall[k][j] == ' ' || createwall[k][j] == '2' || createwall[k][j] == 'k' ||
				createwall[k][j] == 'E')
			{
				g_Console.writeToBuffer(c, createwall[k][j], 0x0);
			}
			else
			{
				g_Console.writeToBuffer(c, createwall[k][j], 0xFFF);
			}
			position++;
		}
		pos++;
	}
}
void renderCharacter()
{
    // Draw the location of the character
    WORD charColor = 0x0C;
    if (g_sChar.m_bActive)
    {
        charColor = 0x0A;
    }
    g_Console.writeToBuffer(g_sChar.m_cLocation, (char)1, charColor);
}

void renderFramerate()
{
    COORD c;
    // displays the framerate
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(3);
    ss << 1.0 / g_dDeltaTime << "fps";
    c.X = g_Console.getConsoleSize().X - 9;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str());

    // displays the elapsed time
    ss.str("");
    ss << g_dElapsedTime << "secs";
    c.X = 0;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str(), 0x59);
}
void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}