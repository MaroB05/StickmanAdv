#include "stickman.h"

class scene{
private:
  int width, height, obj_num;
  char** pixels = NULL;
  stickman* men = NULL;
  
public:
  scene(int w, int h){
    width = w;
    height = h;
    obj_num = 0;
    pixels = new char*[height];
    for (int i = 0; i < height; i++){
      pixels[i] = new char[width];
      fill(pixels[i], pixels[i]+width, ' ');
    }
  }

  void init(){
    for (int i = 0; i < height; i++){
      fill(pixels[i], pixels[i]+width, ' ');
    }
  }

  void clear_screen() {
      // ANSI escape code to clear screen and move cursor to top-left
      cout << "\033[2J\033[1;1H";
  }
  
  // TODO: To implement a dynamic array for handling new stickmen
  void add_stickman(int x, int y){
    obj_num++;
    men = new stickman(x, y);
    cout << "stickman added\n";
  }

  stickman* get_object(int index){
    if (index+1 <= obj_num)
      return men + index;
    else 
      return nullptr;
  }

  inline bool draw_char(int x, int y, char c){
    if (x >= 0 && x < width && y >= 0 && y < height){
      pixels[y][x] = c;
    }
    else
      return false;
    return true;
  }

  void draw_object(stickman& stick){
    char* sprite = stick.get_sprite();
    const int s_width = stick.get_width();
    const int s_height = stick.get_height();
    const int px = stick.px();
    const int py = stick.py();

    for (int y = 0; y < s_height; y++){
      for (int x = 0; x < s_width; x++){
        draw_char(x + px, y + py, sprite[x + y * s_width]);
      }
    }
  }

  void draw_objects(){
    for (int i = 0; i < obj_num; i++){
      draw_object(men[i]);
    }
  }

  void render(){
    for (int i = 0; i < height; i++)
        cout << pixels[i] << endl;
  }

};
