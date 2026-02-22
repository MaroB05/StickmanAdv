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

  ~Object(){
    delete[] sprites;
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
  Object** array = nullptr;
  Object** temp = nullptr; // instead of allocating and deallocating temp pointer
  int capacity, elements;
public:
  Objects_array(){
    capacity = 0;
    elements = 0;
  }

  Objects_array(int n){
    elements = 0;
    capacity = n;
    array = new Object*[n];
  }

  Object* get_element(int index){
    if (index < elements)
      return array[index];
    return nullptr;
  }

  void* set_element(int index, Object* obj){
    array[index] = obj;
  }

  int find(Object* obj){
    for (int i = 0; i < elements; i++){
      if (array[i] == obj)
        return i;
    }
    return -1;
  }

  // move from one array to a new one
  void move_elements(){
    for (int i = 0; i < elements; i++)
      array[i] = temp[i];
  }

  inline int is_full(){
    return (capacity == elements);
  }

  void grow(){
    if (capacity == 0){
      capacity = 1;
      array = new Object*[capacity];
      return;
    }
    capacity *= 2;
    temp = array;
    array = new Object*[capacity];
    move_elements();
    delete[] temp;
    temp = nullptr;
  }

  void shrink(){
    if (capacity <= 1)
      return;

    capacity /= 2;
    temp = array;
    array = new Object*[capacity];
    move();
    delete[] temp;
    temp = nullptr;
  }

  void add_object(Object* obj){
    if (is_full())
      grow();
    array[elements] = obj;
    elements++;
  }

  void remove_object(int index){
    delete array[index];
    array[index] = nullptr;
    elements--;
  }

  void remove_object(Object* obj){
    int index = find(obj);
    if (index == -1)
      return;
    delete array[index];
    array[index] = array[elements-1];
    elements--;
  }

};
