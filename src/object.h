class Object{
protected:
  Point pos;
  int state, state_num;
  int width, height;
  int sprite_size;
  char** sprites = nullptr;

public:
  Object(){
    state_num = 0;
    width = 0;
    height = 0;
    sprite_size = width*height;
  }

  Object(int w, int h, int n){
    state_num = n;
    width = w;
    height = h;
    sprite_size = width*height;
  }

  int get_width(){
    return width;
  }

  int get_height(){
    return height;
  }

  Point get_pos(){
    return pos;
  }

  void set_pos(int a, int b){
    pos.x = a;
    pos.y = b;
  }

  void set_y(int b){
    pos.y = b;
  }

  void set_x(int a){
    pos.x = a;
  }

  int px(){
    return pos.x;
  }

  int py(){
    return pos.y;
  }

  char* get_sprite(){
    return sprites[state];
  }

  void print_sprite(int c){
    if (c < state_num && c >= 0)
      for (int i = 0; i < width * height; i++)
        cout << sprites[c][i];
  }

  void next_state(){
    if (state_num > 0)
      state = (state+1) % state_num;
  }

  void move(int a, int b){
    pos.x += a;
    pos.y += b;
  }
};

class Objects_array{
private:
  
public:

};
