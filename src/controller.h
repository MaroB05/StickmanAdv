#include "config.h"
#include "screen.h"

class Controller{
private:
  Scene* scene = nullptr;
  int obj_num;
  const int gravity = 2;
  Stickman* objects = nullptr;

public:
  Controller(){
    obj_num = 0;
    terminal_config();
  }

  // TODO: To implement a dynamic array for handling new stickmen
  void add_stickman(int x, int y){
    obj_num++;
    objects = new Stickman(x, y);
    cout << "Stickman added\n";
  }

  Stickman* get_object(int index){
    if (index+1 <= obj_num)
      return objects + index;
    else 
      return nullptr;
  }

  int on_floor(Stickman* object){
    return (object->py() + object->get_height() >= scene->get_height());
  }

  void draw_object(Stickman& stick){
    char* sprite = stick.get_sprite();
    const int s_width = stick.get_width();
    const int s_height = stick.get_height();
    const int px = stick.px();
    const int py = stick.py();

    for (int y = 0; y < s_height; y++){
      for (int x = 0; x < s_width; x++){
        scene->draw_char(x + px, y + py, sprite[x + y * s_width]);
      }
    }
  }

  void draw_objects(){
    for (int i = 0; i < obj_num; i++){
      draw_object(objects[i]);
    }
  }

  void run(int w, int h){
    scene = new Scene(w, h);
    
    int key_pressed = ' ';
    add_stickman(10, 10);
    Stickman* player = get_object(0);

    while (key_pressed != 'q'){
      scene->clear_screen();
      scene->init();
      draw_objects();
      scene->render();
      key_pressed = getchar();
      if (key_pressed == EOF) 
        clearerr(stdin); 

      if (!on_floor(player))
        player->move(0,1);
      else{
        player->set_y(scene->get_height() - player->get_height());
      }

      if (key_pressed == 'w' && on_floor(player)){
        player->move(0,-10);
        player->next_state();
      }
      else if (key_pressed == 's' && !on_floor(player)){
        player->move(0,1);
        player->next_state();
      }
      else if (key_pressed == 'a'){
        player->move(-1,0);
        player->next_state();
      }
      else if (key_pressed == 'd'){
        player->move(1,0);
        player->next_state();
      }
    }
    cout << "Game Ended!\n";

  }

};
