#include "controller.h"

int main() {

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
