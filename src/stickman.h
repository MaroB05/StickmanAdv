class stickman{
private:
  int x,y;
  int state;
  static const int width = 3;
  static const int height = 4;
  static const int sprite_size = width * height;
  char sprites[2][12] = {{' ', 'o', ' ', '/', '|', '\\', ' ', '|', ' ', '/', ' ', '\\'}
  , {' ', 'o', ' ', '\\', '|', '/', ' ', '|', ' ', '/', ' ', '\\'}};
  // int positions[2*COMP_NUM] = {0};

public:
  stickman(int a, int b){
    x = a;
    y = b;
    state = 0;
  }

  void print_sprite(int c){
    for (int i = 0; i < width * height; i++)
      cout << sprites[c][i];
  }

  int get_width(){
    return width;
  }

  int get_height(){
    return height;
  }

  int px(){
    return x;
  }

  int py(){
    return y;
  }

  char* get_sprite(){
    state = (state+1)%2;
    return sprites[state];
  }

  void move(int a, int b){
    x += a;
    y += b;
  }
};
