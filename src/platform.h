class Platform: public Object{

public:
  Platform(int a, int b, int w, int h): Object(a, b, w, h, 1, 0){
    sprites = new char*[state_num];
    for (int i = 0; i < state_num; i++){
      sprites[i] = new char[sprite_size];
      fill(sprites[i], sprites[i] + sprite_size, '=');
    }
  }
};
