#include "Console.h"


Console::Console(int width, int height, const std::string& title) :
	bInitialised(false),
	screenBuffer(nullptr),
	title(title)
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (!InitFont(8, 16))
		return;

	if (!InitWindow(width, height))
		return;

	screenBuffer = new CHAR_INFO[screenSize.X * screenSize.Y];
	ClearScreen();

	SetConsoleActiveScreenBuffer(hConsole);

	bInitialised = true;
}

Console::~Console()
{
	if (screenBuffer != nullptr)
		delete[] screenBuffer;
}

void Console::Render()
{
	COORD start = { 0, 0 };
	SMALL_RECT writeRegion = { 0, 0, screenSize.X - 1, screenSize.Y };

	WriteConsoleOutput(hConsole, screenBuffer, screenSize, start, &writeRegion);
}

void Console::ClearScreen()
{
	unsigned int length = screenSize.X * screenSize.Y;

	for (int i = 0; i < length; i++)
	{
		screenBuffer[i].Char.AsciiChar = 0;
		screenBuffer[i].Attributes = 0;
	}
}

void Console::DrawPoint(int x, int y, CHAR_INFO pixel)
{
	if (x >= 0 && x < screenSize.X && y >= 0 && y < screenSize.Y)
		screenBuffer[x + (y * screenSize.X)] = pixel;
}

bool Console::InitFont(int fontWidth, int fontHeight)
{
	font.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	font.dwFontSize.X = fontWidth;
	font.dwFontSize.Y = fontHeight;
	font.nFont = 0;
	font.FontFamily = FF_DONTCARE;
	font.FontWeight = FW_NORMAL;
	wcscpy_s(font.FaceName, L"Consolas");
	
	return SetCurrentConsoleFontEx(hConsole, false, &font);
}

bool Console::InitWindow(int width, int height)
{
	COORD maxWindowSize = GetLargestConsoleWindowSize(hConsole);

	screenSize.X = (width < maxWindowSize.X) ? width : maxWindowSize.X;
	screenSize.Y = (height < maxWindowSize.Y) ? height : maxWindowSize.Y;

	SMALL_RECT screenRegion = { 0, 0, screenSize.X - 1, screenSize.Y - 1 };

	bool result = true;

	result = SetConsoleScreenBufferSize(hConsole, screenSize);
	result = SetConsoleWindowInfo(hConsole, true, &screenRegion);
	return result;
}
