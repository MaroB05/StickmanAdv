class Creature : public Object{
protected:
  int health;
public:
  Creature(int a, int b, int w, int h, int s, int _health) : Object(a, b, w, h, s){
    health = _health;
  } 

  void decrease_health(){
    health--;
  }

  int get_health(){
    return health;
  }

  Bullet* shoot(Point bullet_direction){
    Point bullet_pos = pos;
    if (bullet_direction.x > 0)
      bullet_pos.x += (width-1) * bullet_direction.x ;
    else
      bullet_pos.x += 2 * bullet_direction.x;
    Bullet* bullet_ptr = new Bullet(bullet_pos.x, bullet_pos.y);
    bullet_ptr->set_velocity(bullet_direction);
    if (bullet_direction.x == 1)
      bullet_ptr->set_state(0);
    else
      bullet_ptr->set_state(1);
    return bullet_ptr;
  }
};

class Creatures_array{
private:
  Creature** array = nullptr;
  Creature** temp = nullptr; // instead of allocating and deallocating temp pointer
  int capacity, elements;
public:
  Creatures_array(){
    capacity = 0;
    elements = 0;
  }

  Creatures_array(int n){
    elements = 0;
    capacity = n;
    array = new Creature*[n];
  }

  int get_num_elements(){
    return elements;
  }

  Creature* get_object(int index){
    if (index < elements)
      return array[index];
    return nullptr;
  }

  void set_element(int index, Creature* obj){
    array[index] = obj;
  }

  int find(Creature* obj){
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
      array = new Creature*[capacity];
      return;
    }
    capacity *= 2;
    temp = array;
    array = new Creature*[capacity];
    move_elements();
    delete[] temp;
    temp = nullptr;
  }

  void shrink(){
    if (capacity <= 1)
      return;

    capacity /= 2;
    temp = array;
    array = new Creature*[capacity];
    move_elements();
    delete[] temp;
    temp = nullptr;
  }

  void add_object(Creature* obj){
    if (is_full())
      grow();
    array[elements] = obj;
    elements++;
  }

  void remove_object(int index){
    delete array[index];
    array[index] = nullptr;
    elements--;
    array[index] = array[elements];
  }

  void remove_object(Creature* obj){
    int index = find(obj);
    if (index == -1)
      return;
    delete array[index];
    elements--;
    array[index] = array[elements];
  }

  Creature* operator[](int i){
    return array[i];
  }

};
