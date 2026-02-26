/* WIDTH 2
 * HEIGHT 1
 * STATE_NUM 1
 * */
class Bullet : public Object{
private:

public:

  Bullet(int a, int b) : Object(a, b, 2, 1, 1){
    char sprites_temp[state_num][sprite_size] = {{'=', '>'}};
    sprites = new char*[state_num];
    for (int i = 0; i < state_num; i++){
      sprites[i] = new char[sprite_size];
      for (int j = 0; j < sprite_size; j++)
        sprites[i][j] = sprites_temp[i][j];
    }
  }
  
};
