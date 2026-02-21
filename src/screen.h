#include "stickman.h"

class Scene{
private:
  int width, height;
  char** pixels = NULL;
  
public:
  Scene(int w, int h){
    width = w;
    height = h;
    pixels = new char*[height];
    for (int i = 0; i < height; i++){
      pixels[i] = new char[width];
      fill(pixels[i], pixels[i]+width, ' ');
    }
  }

  int get_width() const{
    return width;
  }

  int get_height() const{
    return height;
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

  inline bool draw_char(int x, int y, char c){
    if (x >= 0 && x < width && y >= 0 && y < height)
      pixels[y][x] = c;
    else
      return false;
    return true;
  }

  void render(){
    for (int i = 0; i < height; i++)
        cout << pixels[i] << endl;
  }

};
