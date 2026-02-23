class Object{
protected:
  Point pos, velocity;
  int state, state_num;
  int width, height;
  int sprite_size, gravity; // gravity is a bool
  int pass_through;
  char** sprites = nullptr;

public:
  Object(){
    state_num = 0;
    width = 0;
    height = 0;
    gravity = 1;
    pass_through = 1;
    velocity = Point(0,0);
    sprite_size = width*height;
  }

  Object(int a, int b, int w, int h, int n){
    pos = Point(a,b);
    velocity = Point(0,0);
    state_num = n;
    width = w;
    height = h;
    gravity = 1;
    pass_through = 1;
    sprite_size = width*height;
  }

  Object(int a, int b, int w, int h, int n, int g){
    pos = Point(a,b);
    velocity = Point(0,0);
    state_num = n;
    width = w;
    height = h;
    gravity = g;
    pass_through = 1;
    sprite_size = width*height;
  }

  ~Object(){
    delete[] sprites;
  }

  int is_gravitational(){
    return gravity;
  }

  void toggle_gravity(int g){
    gravity = g;
  }

  int is_penetrable(){ return pass_through; }

  void toggle_penetrable(int p){ pass_through = p; }

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

  Point get_velocity(){
    return velocity;
  }

  void set_velocity(int a, int b){
    velocity.x = a;
    velocity.y = b;
  }

  void accelerate(int a, int b){
    velocity.x = (velocity.x + a);
    velocity.y = (velocity.y + b);
  }

  void decelerate(int a, int b){
    velocity.x = (velocity.x - a)/2;
    velocity.y = (velocity.y - b)/2;
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

  int get_num_elements(){
    return elements;
  }

  Object* get_object(int index){
    if (index < elements)
      return array[index];
    return nullptr;
  }

  void set_element(int index, Object* obj){
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
    move_elements();
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

  Object* operator[](int i){
    return array[i];
  }

};
