#include "../config.h"
#define draw_objects_array(obj_arr) for (int i = 0; i < obj_arr.get_num_elements(); i++) draw_object(obj_arr[i]);

class Controller{
private:
  Scene* scene = nullptr;
  const int gravity = 2;
  Stickman* player;
  Point bullet_direction;
  Objects_array objects;
  Objects_array platforms;
  Creatures_array enemies;
  Objects_array bullets;

public:
  Controller(){
    terminal_config();
    bullet_direction = Point(1,0);
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
    draw_objects_array(enemies);
    draw_objects_array(objects);
    draw_objects_array(bullets);
    for (int i = 0; i < player->get_health(); i++){
      scene->draw_char(i, 0, '+');
    }
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

    for (int i = 0; i < enemies.get_num_elements(); i++){
      temp = enemies[i];
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

  void init_game(int w, int h){
    scene = new Scene(w, h);

    add_stickman(10, 10);
    platforms.add_object(new Platform(5, 15, 5, 2));
    platforms.add_object(new Platform(13, 17, 4, 1));

    player = static_cast<Stickman*>(get_object(0));

    enemies.add_object(new Stickman(14, 10));
  }

  inline void control(int &key_pressed){
    key_pressed = getchar();
    if (key_pressed == EOF) // clear err from stdin to read new characters
      clearerr(stdin); 

    if (key_pressed == 'w' && on_floor(player)){
      player->accelerate(0,-10);
      player->reset_state();
    }
    else if (key_pressed == 's' && !on_floor(player)){
      player->accelerate(0,1);
      player->next_state();
    }
    else if (key_pressed == 'a'){
      bullet_direction.x = -1;
      player->accelerate(-1,0);
      player->next_state();
    }
    else if (key_pressed == 'd'){
      bullet_direction.x = 1;
      player->accelerate(1,0);
      player->next_state();
    }
    else if (key_pressed == ' '){
      Bullet* bullet_ptr = player->shoot(bullet_direction);
      bullets.add_object(bullet_ptr);
      
      bullet_ptr = enemies[0]->shoot(Point(-1,0));
      bullets.add_object(bullet_ptr);
    }
  }

  inline void update(){
    for (int i = 0; i < bullets.get_num_elements(); i++){
      bullets[i]->move();
      if (bullets[i]->px() >= scene->get_width() || bullets[i]->px() + bullets[i]->get_width() <= 0)
        bullets.remove_object(i);
    }
    
    for (int i = 0; i < enemies.get_num_elements(); i++){
      enemies[i]->move();
    }

    player->move();
  }

  void run(int w, int h){
    init_game(w, h);
    
    int key_pressed = ' ';
    int counter = 0;
    int collided = 0;
    while (key_pressed != 'q'){
      scene->clear_screen();
      scene->init();
      draw_objects();
      scene->render();

      player->set_velocity(0, 0);
      if (!on_floor(player))
        apply_gravity();
      
      control(key_pressed);
      
      for (int j = 0; j < bullets.get_num_elements(); j++){
        for (int i = 0; i < enemies.get_num_elements(); i++){
          if (collided = enemies[i]->collided(bullets[j])){
            if ((collided == RIGHT && bullets[i]->get_velocity() != Point(-1,0)) ||
              (collided == LEFT && bullets[i]->get_velocity() != Point(1,0)))
              continue;
            bullets.remove_object(j);
            enemies[i]->decrease_health();

            if (enemies[i]->get_health() == 0)
              enemies.remove_object(i);
          }
        }
      }

      update();
    }
    cout << "Game Ended!\n" << "Collided: " << counter;
    cout << "\nAlive bullets: " << bullets.get_num_elements() << endl;
    if (enemies[0])
      cout << "enemy health: " << enemies[0]->get_health() << endl;
  }
};
