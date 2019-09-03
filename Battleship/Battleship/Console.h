#pragma once

#include <Windows.h>
#include <string>

class Console
{
public:
	Console(int width, int height, const std::string& title);
	~Console();

	void Render();
	void ClearScreen();

	void DrawPoint(int x, int y, CHAR_INFO pixel);

private:
	bool bInitialised;
	HANDLE hConsole;
	CHAR_INFO* screenBuffer;
	COORD screenSize;
	CONSOLE_FONT_INFOEX font;
	std::string title;

private:
	//bool InitConsole(int width, int height);
	bool InitFont(int fontWidth, int fontHeight);
	bool InitWindow(int width, int height);
};

