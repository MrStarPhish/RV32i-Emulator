#pragma once
// Editor's Note: This file contains essential functions related to Console Printing that I've used in my previous projects.
// These are AI-assisted functions that I have written and tested in my previous projects. 
// They are not part of the standard library, but they are useful for console-based applications. 
// You can use them as a starting point for your own projects, or you can modify them to suit your needs.

// Prefer BUFFER method over ITERATIVE method for better performance and less flickering. 
// ITERATIVE method is better for small-scale printing, or for handling minor cases.

// All Console related functions and Buffer/Output related functions are here.
#include<iostream>
#include<Windows.h>
#include<ctime>
#include<sstream> // for stringstream
#include<utility> // for pair<>

const int WIDTH = 120;
const int HEIGHT = 50;

const int X_BOUND = WIDTH;
const int Y_BOUND = HEIGHT-10; // Boundaries Coords

CHAR_INFO buffer[WIDTH * HEIGHT]; // character + color info

enum ColorCode : uint8_t
{
    BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, YELLOW, WHITE, GREY, L_BLUE, L_GREEN, L_CYAN, L_RED, L_MAGENTA, L_YELLOW, L_WHITE, DEFAULT = 7, DEFAULTBG = 0
};

// State variables to remember the last saved coordinates
static int globalSavedX = 0;
static int globalSavedY = 0;

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Function to get current cursor position
void getCursorPosition(int& x, int& y)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        x = csbi.dwCursorPosition.X;
        y = csbi.dwCursorPosition.Y;
    }
    else
    {
        // If for some reason it fails, return (0,0)
        x = 0;
        y = 0;
    }
}


// Saves the current cursor position into the global variables
void saveCoords()
{
    getCursorPosition(globalSavedX, globalSavedY);
}

void saveCoords(int& x, int& y)
{
    getCursorPosition(x, y);
}

void saveCoords(std::pair<int, int>& coords)
{
    getCursorPosition(coords.first, coords.second);
}

// Loads the globally saved coordinates
void loadCoords()
{
    gotoxy(globalSavedX, globalSavedY);
}

// Overload: Loads from specific variables
void loadCoords(int x, int y)
{
    gotoxy(x, y);
}

// Overload: Loads from a std::pair
void loadCoords(std::pair<int, int> coords)
{
    gotoxy(coords.first, coords.second);
}

// =========================================== LEGACY PRINTING: Iterative

void clearLine(int x, int y, int length = 1)
{
    gotoxy(x, y);
    for (int i = 0; i < length; i++)
    {
        std::cout << " ";
    }
}


//void setColor(int textColor = DEFAULT) //// Old function without Background Color considered
//{
//    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), textColor);
//}

void setColor(int textColor = DEFAULT, int backgroundColor = BLACK)
{
    // The background color is shifted left by 4 bits to occupy the higher nibble
    WORD colorAttribute = textColor | (backgroundColor << 4);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorAttribute);
}

// ========================================= ALTERNATE PRINTING: Buffered


void clearBuffer() // to clear screen ; instead of "CLS"
{
    WORD defaultColor = DEFAULT | (BLACK << 4);
    for (int i = 0; i < WIDTH * HEIGHT; i++)
    {
        buffer[i].Char.AsciiChar = ' ';
        buffer[i].Attributes = defaultColor;
    }
}



void bufferChar(int x, int y, char ch, int textColor = DEFAULT, int bgColor = BLACK) // coords, char, RGBA
{
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
    {
        int index = y * WIDTH + x;
        buffer[index].Char.AsciiChar = ch;
        buffer[index].Attributes = textColor | (bgColor << 4);
    }
}

void eraseChar(int x, int y) // the character to be removed ; coords
{
    bufferChar(x, y, ' ');
}

void eraseString(int x, int y, int length) // the string of characters to be removed ; coords , length
{
    for (int i = 0; i < length; i++)
    {
        eraseChar(x + i, y);
    }
}

void bufferString(int x, int y, std::string line, int textColor = DEFAULT, int bgColor = BLACK) // coords, string, RGBA
{
    WORD colorAttribute = textColor | (bgColor << 4);
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
    {
        int index = y * WIDTH + x;
        for (int i = 0; i < line.length(); i++)
        {
            buffer[index + i].Char.AsciiChar = line[i];
            buffer[index + i].Attributes = colorAttribute;
        }
    }
}

// Stamps a 2D Sprite/Grid into Buffer ; x, y, arr, arrSize, Attributes
void bufferObject(int startX, int startY, std::string sprite[], int totalRows, int textColor = DEFAULT, int backgroundColor = BLACK)
{
    for (int i = 0; i < totalRows; i++)
    {
        bufferString(startX, startY + i, sprite[i], textColor, backgroundColor);
    }
}

void renderBuffer() // render the whole buffer[] 
{
    static COORD bufferSize = { WIDTH, HEIGHT };
    static COORD bufferCoord = { 0, 0 }; // starting point
    static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT writeRegion = { 0, 0, WIDTH - 1, HEIGHT - 1 }; // tells Left,Top,Right,Bottom boundary

    WriteConsoleOutputA(hConsole, buffer, bufferSize, bufferCoord, &writeRegion);
}

// ============================================== CONSOLE 

void SetConsoleBufferSize(int width, int height)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD bufferSize; // setting buffer size here
    bufferSize.X = width;
    bufferSize.Y = height;
    SetConsoleScreenBufferSize(hOut, bufferSize);

    SMALL_RECT windowSize; // setting windows size here
    windowSize.Left = 0;
    windowSize.Top = 0;
    windowSize.Right = width - 1;
    windowSize.Bottom = height - 1;
    SetConsoleWindowInfo(hOut, TRUE, &windowSize);
}

void SetConsoleWindowSize(int width, int height)
{
    HWND consoleWindow = GetConsoleWindow();      // Window handle
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);     // Output handle

    CONSOLE_FONT_INFOEX fontInfo = { sizeof(CONSOLE_FONT_INFOEX) }; // getting current font size to calculate pixel dimensions
    GetCurrentConsoleFontEx(hOut, FALSE, &fontInfo);

    int fontWidth = fontInfo.dwFontSize.X;
    int fontHeight = fontInfo.dwFontSize.Y;

    COORD newSize = { (SHORT)width, (SHORT)height }; // Resisizing Buffer first
    SetConsoleScreenBufferSize(hOut, newSize);

    SMALL_RECT windowSize = { 0, 0, (SHORT)(width - 1), (SHORT)(height - 1) }; // Resizing visible window
    SetConsoleWindowInfo(hOut, TRUE, &windowSize);

    MoveWindow(consoleWindow, 100, 100, width * fontWidth, height * fontHeight, TRUE); // Physical resizing 
}

// ============================================= UTILITY

void bufferBoundary()
{
    buffer[0] = { 0x2A, 0x07 };
    buffer[40] = { 0x2A, 0x07 };
    buffer[79] = { 0x2A, 0x07 };
    buffer[80] = { 0x2A, 0x07 };
    buffer[(39*WIDTH) + 0] = { 0x2A, 0x07 };
    buffer[(39 * WIDTH) + 40] = { 0x2A, 0x07 };
    buffer[(39 * WIDTH) + 79] = { 0x2A, 0x07 };
    buffer[(39 * WIDTH) + 90] = { 0x2A, 0x07 };
}
