#define WIDTH 3
#define HEIGHT 4
#define STATE_NUM 3

class Stickman : public Object{
public:
  Stickman(int a, int b): Object(a, b, WIDTH, HEIGHT, STATE_NUM){
    state = 0;
    char sprites_temp[state_num][sprite_size] = {{' ', 'o', ' ', '/', '|', '\\', ' ', '|', ' ', '/', ' ', '\\'}
    , {' ', 'o', ' ', '\\', '|', '/', ' ', '|', ' ', '/', '|', ' '}
    , {' ', 'o', ' ', '\\', '|', '/', ' ', '|', ' ', ' ', '|', '\\'}};
    sprites = new char*[state_num];
    for (int i = 0; i < state_num; i++){
      sprites[i] = new char[sprite_size];
      for (int j = 0; j < sprite_size; j++)
        sprites[i][j] = sprites_temp[i][j];
    }
  }
};
