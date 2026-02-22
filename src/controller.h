#include "config.h"
#include "screen.h"
#include "stickman.h"

class Controller{
private:
  Scene* scene = nullptr;
  const int gravity = 2;
  Objects_array objects;

public:
  Controller(){
    terminal_config();
    objects = Objects_array(1);
  }

  void add_stickman(int x, int y){
    objects.add_object(new Stickman(x, y));
    cout << "Stickman added\n";
  }

  Object* get_object(int index){
      return objects.get_object(index);
  }

  int on_floor(Object* object){
    return (object->py() + object->get_height() >= scene->get_height());
  }

  void draw_object(Object* stick){
    char* sprite = stick->get_sprite();
    const int s_width = stick->get_width();
    const int s_height = stick->get_height();
    const int px = stick->px();
    const int py = stick->py();

    for (int y = 0; y < s_height; y++){
      for (int x = 0; x < s_width; x++){
        scene->draw_char(x + px, y + py, sprite[x + y * s_width]);
      }
    }
  }

  void draw_objects(){
    for (int i = 0; i < objects.get_num_elements(); i++){
      draw_object(objects.get_object(i));
    }
  }

  void run(int w, int h){
    scene = new Scene(w, h);
    
    int key_pressed = ' ';
    add_stickman(10, 10);
    Stickman* player = static_cast<Stickman*>(get_object(0));

    while (key_pressed != 'q'){
      scene->clear_screen();
      scene->init();
      draw_objects();
      scene->render();

      key_pressed = getchar();
      if (key_pressed == EOF) // clear err from stdin to read new characters
        clearerr(stdin); 

      if (!on_floor(player))
        player->move(0,1);
      else
        player->set_y(scene->get_height() - player->get_height());

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
