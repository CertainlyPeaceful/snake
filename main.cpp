#include <iostream>
#include <chrono>
#include <thread>
#include "Header.h"

extern bool gameOver;
extern int score;

int main()
{
	initialization();
	while (!gameOver)
	{
		draw_console();
		input_key();
		logic();
		std::this_thread::sleep_for(std::chrono::milliseconds(25));
	}
	system("cls");
	std::cout << "GAME OVER!\n" << "[SCORE]: " << score << std::endl;
}