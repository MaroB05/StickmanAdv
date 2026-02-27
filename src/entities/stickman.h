/* WIDTH 3
 * HEIGHT 4
 * STATE_NUM 3
 * */

class Stickman : public Object{
public:
  Stickman(int a, int b): Object(a, b, 3, 4, 3, 3, 3){
    // health = 3;
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

  Stickman(int a, int b, int h): Stickman(a, b){
    health = h;
  }
};
