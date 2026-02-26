#include <iostream>
using namespace std;
#include "entities/point.h"
#include "entities/object.h"
#include "entities/platform.h"
#include "entities/stickman.h"
#include "entities/bullet.h"
#include "engine/screen.h"

#if defined(__linux__)
#include <unistd.h>
#include <termios.h>
#elif defined(_WIN32)
#include <windows.h>
#endif

void terminal_config(){
  #if defined(__linux__)
    static struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
    newt.c_cc[VMIN] = 0;
    newt.c_cc[VTIME] = 1;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  #elif defined(_WIN32)
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hInput, &mode);

    // Equivalent to disabling ICANON and ECHO
    mode &= ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
    SetConsoleMode(hInput, mode);
  #endif
}
