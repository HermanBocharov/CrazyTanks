#include "ConsoleApp.h"

ConsoleApp::ConsoleApp()
{
	SMALL_RECT windowSize = { 0, 0, X_WINDOW_SIZE - 1, Y_WINDOW_SIZE - 1 };
	COORD bufferSize = { X_WINDOW_SIZE, Y_WINDOW_SIZE };

	writeHandle_ = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleScreenBufferSize(writeHandle_, bufferSize);

	SetConsoleWindowInfo(writeHandle_, TRUE, &windowSize);

	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(writeHandle_, &cursorInfo);
	cursorInfo.bVisible = FALSE;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(writeHandle_, &cursorInfo);

	consoleBuffer_ = new CHAR_INFO[X_WINDOW_SIZE * Y_WINDOW_SIZE];

	bufferSize_ = bufferSize;
	charPosition_ = { 0, 0 };
	writeArea_ = windowSize;

	for (int x = 0; x < X_WINDOW_SIZE; x++)
	{
		for (int y = 0; y < Y_WINDOW_SIZE; y++)
		{
			setChar(x, y, ' ');
		}
	}
}



ConsoleApp::~ConsoleApp()
{
	delete consoleBuffer_;
}



void ConsoleApp::setChar(int x, int y, char c)
{
	consoleBuffer_[x + X_WINDOW_SIZE * y].Char.AsciiChar = c;
	consoleBuffer_[x + X_WINDOW_SIZE * y].Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN |
												BACKGROUND_RED | BACKGROUND_INTENSITY |
												FOREGROUND_BLUE;
}



char ConsoleApp::getChar(int x, int y)
{
	return consoleBuffer_[x + X_WINDOW_SIZE * y].Char.AsciiChar;
}



void ConsoleApp::render()
{
	WriteConsoleOutputA(writeHandle_, consoleBuffer_, bufferSize_, charPosition_, &writeArea_);
}