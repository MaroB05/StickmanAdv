#include <iostream>
using namespace std;
#include "screen.h"

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

int main() {
  terminal_config();

  scene window = scene(40, 40);
  
  char key_pressed = ' ';
  window.add_stickman(10, 10);
  stickman* player = window.get_object(0);

  while (key_pressed != 'q'){
    window.init();
    window.draw_objects();
    window.render();
    key_pressed = getchar();
    if (key_pressed == 'w')
      player->move(0,-1);
    else if (key_pressed == 's')
      player->move(0,1);
    else if (key_pressed == 'a')
      player->move(-1,0);
    else if (key_pressed == 'd')
      player->move(1,0);
  }
  cout << "Game Ended!\n";
  return 0;
}
