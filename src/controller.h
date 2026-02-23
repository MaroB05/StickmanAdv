#include "config.h"
#include "point.h"
#include "screen.h"
#include "object.h"
#include "stickman.h"
#include "platform.h"

class Controller{
private:
  Scene* scene = nullptr;
  const int gravity = 2;
  Objects_array objects;
  Objects_array platforms;

public:
  Controller(){
    terminal_config();
    objects = Objects_array(1);
  }

  void add_stickman(int x, int y){
    objects.add_object(new Stickman(x, y));
  }

  Object* get_object(int index){
      return objects[index];
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
      draw_object(objects[i]);
      draw_object(platforms[i]);
    }
  }

  inline void apply_gravity(){
    Object* temp;
    for (int i = 0; i < objects.get_num_elements(); i++){
      temp = objects[i];
      if (!temp->is_gravitational())
        continue;

      if (!on_floor(temp))
        temp->move(0,1);
      else
        temp->set_y(scene->get_height() - temp->get_height());
    }
  }

  void run(int w, int h){
    scene = new Scene(w, h);
    
    int key_pressed = ' ';
    add_stickman(10, 10);
    Platform* ground = new Platform(10, 15, 5, 2);
    platforms.add_object(ground);
    platforms.add_object(new Platform(0, h, w, h));

    Stickman* player = static_cast<Stickman*>(get_object(0));
    int counter = 0;
    int collided = 0;
    while (key_pressed != 'q'){
      scene->clear_screen();
      scene->init();
      draw_objects();
      scene->render();

      key_pressed = getchar();
      if (key_pressed == EOF) // clear err from stdin to read new characters
        clearerr(stdin); 

      apply_gravity();

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
