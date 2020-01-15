#include <iostream>
#include <conio.h>

// Global constants (bad practice?)
bool gameOver;
static const int width = 20;
static const int height = 20;
static int x, y, fruit_x, fruit_y;
int score;
static int tail_x[50], tail_y[50];
static int tail_length;

enum class direction {
	stop = 0, left, right, up, down
};
direction dir;

void initialization()
{
	gameOver = false;
	dir = direction::stop;
	x = width / 2;
	y = height / 2;
	fruit_x = rand() % width;
	fruit_y = rand() % height;
	score = 0;
}

void draw_console() {
	// Clear console (for a new frame) and output the top edge of the map
	system("cls");
	for (int i = 0; i < width + 2; i++)
		std::cout << "#";
	std::cout << std::endl;

	for (int row = 0; row < height; ++row) {
		for (int col = 0; col <= width; ++col) {
			// Left edge of map or fruit?
			if (col == 0)
				std::cout << "#";
			else if (row == fruit_y && fruit_x == col)
				std::cout << "F";
			// Head or body of snake?
			else if (row == y && col == x)
				std::cout << "O";
			else {
				bool print = false;
				for (int index = 0; index < tail_length; ++index) {
					if (tail_y[index] == row && tail_x[index] == col) {
						std::cout << "o";
						print = true;
					}
				}
				// If it does not print snake body
				if (!print)
					std::cout << " ";
			}
			// Right edge of map
			if (col == width)
				std::cout << "#";
		}
		std::cout << std::endl;
	}

	// Output bottom edge of map and score
	for (int i = 0; i < width + 2; i++)
		std::cout << "#";
	std::cout << '\n' << '\n' << "[SCORE]: " << score << std::endl;
}

void input_key()
{
	// _kbhit returns non-zero value if (k)ey(b)oard is (hit)
	if (_kbhit()) {
		// _getch has no buffer (i.e. immediately returns character without pressing enter)
		switch (_getch()) {
		case 'a': dir = direction::left;
			  break;
		case 'd': dir = direction::right;
			  break;
		case 'w': dir = direction::up;
			  break;
		case 's': dir = direction::down;
			  break;
		}
	}
}

void logic()
{
	// Tail logic
	for (int index = tail_length; index > 0; --index) {
		tail_x[index] = tail_x[index - 1];
		tail_y[index] = tail_y[index - 1];
	}
	tail_x[0] = x;
	tail_y[0] = y;

	// Move [BLANK] depending on dir (enum)
	switch (dir) {
	case direction::left :  x--;
				break;
	case direction::right : x++;
				break;
	case direction::up :	y--;
				break;
	case direction::down :  y++;
				break;
	}

	// Collsion (wall and tail)
	if (x > width || x < 0 || y > height || y < 0)
		gameOver = true;
	for (int i = 0; i < tail_length; i++)
		if (x == tail_x[i] && y == tail_y[i])
			gameOver = true;

	// Get fruit?
	if (x == fruit_x && y == fruit_y) {
		score += 10;

		fruit_x = rand() % width;
		fruit_y = rand() % height;

		tail_length++;
	}
}
