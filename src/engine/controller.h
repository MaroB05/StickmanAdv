#include "../config.h"
#define draw_objects_array(obj_arr) for (int i = 0; i < obj_arr.get_num_elements(); i++) draw_object(obj_arr[i]);

class Controller{
private:
  Scene* scene = nullptr;
  const int gravity = 2;
  Objects_array objects;
  Objects_array platforms;
  Objects_array enemies;
  Objects_array bullets;

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
    for (int i = 0; i < platforms.get_num_elements(); i++){
      if (object->collided(platforms[i]) == DOWN)
        return 1;
    }
    return (object->py() + object->get_height() >= scene->get_height());
  }

  void draw_object(Object* object){
    char* sprite = object->get_sprite();
    const int s_width = object->get_width();
    const int s_height = object->get_height();
    const int px = object->px();
    const int py = object->py();

    for (int y = 0; y < s_height; y++)
      for (int x = 0; x < s_width; x++)
        scene->draw_char(x + px, y + py, sprite[x + y * s_width]);
  }

  void draw_objects(){
    draw_objects_array(platforms);
    draw_objects_array(objects);
    draw_objects_array(bullets);
  }

  inline void apply_gravity(){
    Object* temp;
    for (int i = 0; i < objects.get_num_elements(); i++){
      temp = objects[i];
      if (!temp->is_gravitational())
        continue;

      if (!on_floor(temp)){
        temp->accelerate(0,1);
        temp->move();
      }
      else{
        temp->set_velocity(0,0);
      }
    }
  }

  void run(int w, int h){
    scene = new Scene(w, h);
    
    int key_pressed = ' ';
    add_stickman(10, 10);
    platforms.add_object(new Platform(5, 15, 5, 2));
    platforms.add_object(new Platform(13, 17, 4, 1));

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
      
      for (int i = 0; i < objects.get_num_elements(); i++){
        if (collided = player->collided(objects[i])){
        }
      }

      player->set_velocity(0, 0);
      if (!on_floor(player))
        apply_gravity();

      if (key_pressed == 'w' && on_floor(player)){
        player->accelerate(0,-10);
        player->reset_state();
      }
      else if (key_pressed == 's' && !on_floor(player)){
        player->accelerate(0,1);
        player->next_state();
      }
      else if (key_pressed == 'a'){
        player->accelerate(-1,0);
        player->next_state();
      }
      else if (key_pressed == 'd'){
        player->accelerate(1,0);
        player->next_state();
      }

      player->move();
    }
    cout << "Game Ended!\n" << "Collided: " << counter;

  }

};
