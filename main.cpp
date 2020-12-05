#include <iostream>

#define LIST_CAPACITY_SEGMENT 4

using namespace std;

class Item {
  private:
    int value;

  public:
    // KONSTRUKTOR DOMYŚLNY
    Item(){
      this->value = 0;
    }
    // KONSTRUKTOR z przypisaniem wartości
    Item(int value) {
      this->value = value;
    }

    void print(){
      cout << value << endl;
    }
};



class List {
  private:
    int capacity;
    int count;

    Item *elements;
    void extend(){
      Item *newElements = new Item[this->capacity + LIST_CAPACITY_SEGMENT];

      copy(this->elements, this->elements + this->count, newElements);
      delete[] this->elements;

      this->elements = newElements;
      this->capacity += LIST_CAPACITY_SEGMENT;
    }

  public:
    ~List()
    {
      delete[] this->elements;
    }
    // KONSTRUKTOR DOMYŚLNY
    List() {
      this->capacity = LIST_CAPACITY_SEGMENT;
      this->count = 0;

      this->elements = new Item[this->capacity];
    }
    // KONSTRUKTOR z możliwością wyznaczenia wielkosći
    List(int capacity){
      this->capacity = capacity;
      this->count = 0;

      this->elements = new Item[this->capacity];
    }
    Item *add(Item *item);
    Item *add(int value); 

    // WYŚWIETLANIE WSZYSTKIE ELE
    void printAll() {
      cout << "List elements:" << endl;

      for (size_t i = 0; i < this->count; i++){
        this->elements[i].print();
      }
    }
};


Item *List::add(Item *item)
{
  if (this->count + 1 >= this->capacity)
  {
    this->extend();
  }

  this->elements[this->count++] = *item;

  return item;
}

Item *List::add(int value)
{
  Item *item = new Item(value);
  this->add(item);

  return item;
}

// ||||||||||||||||||||||||||||||||||||||
// ||||||||||   MAIN   ||||||||||||||||||
// ||||||||||||||||||||||||||||||||||||||



int main(){
  

  List *list = new List();

  Item *item1 = new Item(10);
  list->add(item1);
  list->add(229);
  list->add(229);
  list->add(229);
  list->add(229);
  list->add(229);
  list->add(229);
  list->add(229);
  list->add(229);

  list->printAll();
  return 0;
}