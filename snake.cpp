//	Program written and tested in Dev-C++ 5.11

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <conio.h>

using namespace std;


const int board_width = 60;
const int board_height = 20;
const int initial_snake_length = 3;
char MAP[60][20];
int snakeX, snakeY, tailX[1500], tailY[1500], foodX, foodY, x;
int score = 0;
int final_score = 10;
int speed = 500;
string difficulty = "easy";
char direction = 'r';	//	A constant that determines the direction of the snake's movement (r => right, l => left, u => up, d => down); The default value is set to 'r'.;

void MENU();
void INSTRUCTION();
void DIFFICULTY_LEVEL();

void GAME();
void BOARD_VALUES();
void BOARD_CREATE();

void CONTROL();

void YOU_WON();
void YOU_LOST();
void PLAY_AGAIN();



int main()
{
	MENU();

	return 0;
}



void MENU()
{
	system("CLS");

	cout << "Start game - type 1." << endl;
	cout << "Instruction - type 2." << endl;
	cout << "Choose the difficulty level - type 3." << endl;

	int n;

	do
	{
		cin >> n;

		switch (n)
		{
		case 1: GAME();
			break;
		case 2: INSTRUCTION();
			break;
		case 3: DIFFICULTY_LEVEL();
			break;

		}
	} while (n != 0);

}


void INSTRUCTION()
{
	system("CLS");

	cout << "Control:" << endl;
	cout << "Up - type w." << endl;
	cout << "Left - type a." << endl;
	cout << "Right - type d." << endl;
	cout << "Down - type s." << endl;
	cout << endl;
	cout << "Game rules:" << endl;
	cout << endl;
	cout << "You WIN if you eat enough food depending on the chosen difficulty level" << endl;
	cout << "(by default, the level is set to easy - you need to eat 10 food to win)." << endl;
	cout << endl;
	cout << "You LOSE after hitting the board frame or snake tail." << endl;
	cout << endl;
	cout << "Back to MENU - type 1." << endl;

	int n;

	do
	{
		cin >> n;

		switch (n)
		{
		case 1: MENU();
			break;
		}
	} while (n != 0);

}


void DIFFICULTY_LEVEL()
{
	system("CLS");

	cout << "Easy (you need to eat 10 foods to win) - type easy." << endl;
	cout << "Medium (you need to eat 20 foods to win) - type medium." << endl;
	cout << "Hard (you need to eat 40 foods to win) - type hard." << endl;
	cout << endl;
	cout << "Snake's speed increases as you choose a higher difficulty level!" << endl;
	cin >> difficulty;
	cout << endl;
	cout << "Back to MENU - type 1." << endl;
	cout << "Start game - type 2." << endl;

	if (difficulty == "easy")
	{
		final_score = 10;
		speed = 500;
	}

	if (difficulty == "medium")
	{
		final_score = 20;
		speed = 200;
	}

	if (difficulty == "hard")
	{
		final_score = 40;
		speed = 100;
	}

	int n;

	do
	{
		cin >> n;

		switch (n)
		{
		case 1: MENU();
			break;
		case 2: GAME();
			break;
		}
	} while (n != 0);
}


void GAME()
{
	BOARD_VALUES();	// Setting the initial values of the fields.	

	int snake_length;
	snake_length = initial_snake_length;
	score = 0;
	for (; ; )
	{
		//	Snake movement.			
		x++;
		tailX[x] = snakeX;
		tailY[x] = snakeY;
		MAP[tailX[x - snake_length]][tailY[x - snake_length]] = 'e';

		system("CLS");	//	Cleaning the console.

		BOARD_CREATE();	//	Generating the board.	

		CONTROL();	//	Implementation of the snake control by the user.

		Sleep(speed);	//	Delay in refreshing console contents depending on the speed of the snake.

		// Snake control.
		if (direction == 'u') snakeY--;
		if (direction == 'l') snakeX--;
		if (direction == 'r') snakeX++;
		if (direction == 'd') snakeY++;

		//	Extending the snake by another segment when the fruit is eaten.
		// 	Adding a point to the score.
		//	Choosing new, empty field to put the food in there and setting its value to 'f'.
		if (MAP[snakeX][snakeY] == 'f')
		{
			snake_length++;
			score++;
			do
			{
				foodX = rand() % (board_width - 1) + 1;
				foodY = rand() % (board_height - 1) + 1;
			} while (MAP[foodX][foodY] != 'e');
			MAP[foodX][foodY] = 'f';
		}

		//	Ending game when user hit snake's tail.
		if (MAP[snakeX][snakeY] == MAP[tailX[x]][tailY[x]])
		{
			YOU_LOST();
		}

		//	Setting the value of the field where snake is going to move to 's'.
		MAP[snakeX][snakeY] = 's';

		//	Ending game when user hit the board frame.
		if (snakeX == 0 || snakeX == board_width || snakeY == 0 || snakeY == board_height)
		{
			YOU_LOST();
		}

		//	Ending game when user scored the required number of points.
		if (score == final_score)
		{
			YOU_WON();
		}
	}
}


void BOARD_VALUES()
{
	//	Setting empty fields to 'e'
	for (int i = 1; i < board_height - 1; i++)
	{
		for (int j = 1; j < board_width - 1; j++)
		{
			MAP[j][i] = 'e';
		}
	}

	srand(time(NULL));

	//	Choosing random field as snake starting point and setting its value to 's'.	
	snakeX = rand() % (board_width - 10) + 3;
	snakeY = rand() % (board_height - 10) + 3;
	MAP[snakeX][snakeY] = 's';

	//	Choosing random field set as empty one to put the food in there and setting its value to 'f'.
	do
	{
		foodX = rand() % (board_width - 1) + 1;
		foodY = rand() % (board_height - 1) + 1;
	} while (MAP[foodX][foodY] != 'e');
	MAP[foodX][foodY] = 'f';
}


void BOARD_CREATE()
{
	//	Generating the top edge of the board.
	for (int i = 0; i < board_width; i++)
	{
		cout << "*";
	}
	cout << endl;

	//	Generating side edges of the board and its contents.	
	for (int i = 1; i < board_height - 1; i++)
	{
		cout << "*";
		for (int j = 1; j < board_width - 1; j++)
		{
			if (MAP[j][i] == 'e')
				cout << " ";
			if (MAP[j][i] == 's')
				cout << "@";
			if (MAP[j][i] == 'f')
				cout << "$";
		}
		cout << "*" << endl;
	}

	//	Generating the bottom edge of the board.		
	for (int i = 0; i < board_width; i++)
	{
		cout << "*";
	}
	cout << endl;
}


void CONTROL()
{
	int move;

	if (kbhit())
	{
		//	Reading the value of a key pressed by the user.
		move = getch();	

		//	Changing the direction of the snake movement depending on the current orientation and key pressed by user.
		if (move == 119 && (direction == 'r' || direction == 'l'))
			direction = 'u';

		if (move == 100 && (direction == 'u' || direction == 'd'))
			direction = 'r';

		if (move == 97 && (direction == 'u' || direction == 'd'))
			direction = 'l';

		if (move == 115 && (direction == 'r' || direction == 'l'))
			direction = 'd';
	}
}


void YOU_WON()
{
	system("CLS");

	cout << "YOU WON!" << endl;
	cout << endl;

	PLAY_AGAIN();
}


void YOU_LOST()
{
	system("CLS");

	cout << "YOU LOST!" << endl;
	cout << "Your score: " << score << endl;

	PLAY_AGAIN();
}


void PLAY_AGAIN()
{
	cout << "Play again - type 1." << endl;
	cout << "Back to MENU - type 2." << endl;

	int n;

	do
	{
		cin >> n;

		switch (n)
		{
		case 1: GAME();
			break;
		case 2: MENU();
			break;
		}
	} while (n != 0);
}
