#include <iostream>
#include <string>

using namespace std;

class Planet{
private:
    string name;
    int moons;

public:
    Planet();
    Planet(string, int);
    Planet(const Planet&);
    Planet(Planet&&) noexcept;
    Planet& operator=(Planet&);
    Planet& operator=(Planet&&) noexcept;
    bool operator==(const Planet&);
    friend bool List::operator()(Planet& n);
    void show()
    {
        cout << this->name << ": " << this->moons << endl;
    };
};

Planet::Planet() {
    this->name = "";
    this->moons = 0;
};

Planet::Planet(string name, int ns)
{
    this->name = name;
    this->moons = ns;
};

Planet::Planet(const Planet& n)
{
    this->name = string(n.name);
    this->moons = n.moons;
};

Planet::Planet(Planet&& n) noexcept :name(n.name), moons(n.moons) {
    n.moons = NULL;
    n.name = "";
};

Planet& Planet::operator=(Planet&& n) noexcept {
    if (this == &n)
        return *this;
    this->name = n.name;
    this->moons = n.moons;
    n.moons = NULL;
    n.name = "";
    return *this;
};

Planet& Planet::operator=(Planet& n)
{
    this->name = string(n.name);
    this->moons = n.moons;

    return *(this);
};

bool Planet::operator==(const Planet& n) {
    if ((this->name == n.name) && (this->moons == n.moons)) {
        cout << "true" << endl;
        return true;
    }
    else {
        cout << "false" << endl;
        return false;
    }
};
//####################################################################################################################################
class List {
    private:
        int cap;
        int count;
        Planet* el;

        void extend() {
            Planet* newElements = new Planet[this->cap + 1];
            copy(this->el, this->el + this->count, newElements);
            delete[] this->el;
            this->el = newElements;
            this->cap += 1;
        };

    public:
        List();
        List(int size);
        List(const List&);
        List(List&&) noexcept;
        List& operator=(List&);
        List& operator=(List&&) noexcept;
        friend List& operator+(List&, const Planet&);
        friend List& operator+(const Planet&, const List&);
        friend List& operator+(const List&, const List&);
        Planet& operator[](int);
        bool operator()(Planet&);

        ~List();

        void add(Planet& element) {
            if (this->count >= this->cap) {
                this->extend();
                //std::cout << "Extended" << std::endl; //sprawdzenie poprawności rozszerzania tablicy
            }
            this->el[this->count++] = element;

        }
        void add(Planet& element) {
            if (this->count >= this->cap) {
                this->extend();
                //std::cout << "Extended" << std::endl; //sprawdzenie poprawności rozszerzania tablicy
            }
            this->el[this->count++] = element;

        }

        void add(string name, int ns) {
            Planet el = Planet(name, ns);
            this->add(el);
        };

        void showAll() {
            cout << "Elements:" << endl;
            for (int i = 0; i < this->count; i++) {
                this->el[i].show();
            }
            cout << "cap: " << this->cap << endl;
            cout << "count: " << this->count << endl;
        };
};

List::List(const List& n) {
    this->count = n.count;
    this->cap = n.cap;
    this->el = n.el;
};

List::List() {
    this->cap = 2;
    this->count = 0;
    this->el = new Planet[this->cap];
};

List::List(int size) {
    this->cap = size;
    this->count = 0;
    this->el = new Planet[this->cap];
};

List::~List() {
    delete[] this->el;
};

List::List(List&& n) noexcept :count(n.count), cap(n.cap), el(n.el){
    n.cap = NULL;
    n.count = NULL;
    delete n.el;
};

List& List::operator=(List& n) {
    if (this == &n)
        return *this;
    this->count = n.count;
    this->cap = n.cap;
    if (el != NULL)
        delete[] el;
    this->el = new Planet[this->cap];
    copy(n.el, n.el + n.count, this->el);
    return *this;
};

List& List::operator=(List&& n) noexcept{
    if (this == &n)
        return *this;
    this->count = n.count;
    this->cap = n.cap;
    if (el != NULL)
        delete[] el;
    this->el = new Planet[this->cap];
    copy(n.el, n.el + n.count, this->el);
    n.count = 0;
    n.cap = 0;
    delete[] n.el;
    n.el = nullptr;
    return *this;
};
//3.1 powinno działać
List& operator+(const List& lhs, const Planet& rhs) {
    Planet tempp(rhs);
    List templ(lhs);
    templ.add(tempp);
    return templ;
};
//3.2 trzeba zrobić dodawanie na początek, tak aby dodawany element był początkiem listy
List& operator+(const Planet& lhs, const List& rhs) {
    Planet tempp(lhs);
    List templ(rhs);
    //templ.add(tempp);
    //return templ;
};
//3.3 nie ma zrobionej funkcji dodawania listy do listy, wydaje mi się, że trzeba po prostu zrobić taką funkcję i ją tu zastosować
List& operator+(const List& lhs, const List& rhs) {
    List templ1(lhs);
    List templ2(rhs);

};
//3.4 sposób zrobienia tego jest na slajdzie w discordzie u Krystiana. Chodzi niejako o iteracyjne dodawanie np gdy mamy a+b+c+d trzeba realizować to w kolejności a(lhs)+b(rhs) -> (a+b)(lhs)+c(rhs) -> (a+b+c)(lhs)+d(rhs). W praktyce lhs jest iteracyjną sumą wykonywanych dodawań
List& operator+(const List& lhs, const List& rhs) {
    List templ1(lhs);
    List templ2(rhs);

};
//5 moim zdaniem da się to zrobić bez heada, trzeba w jakiś sposób przeskoczyć po tablicy elementów listy i po danych parametru n.name i n.moons sprawdzić czy jest taki element
bool List::operator()(Planet& n) {
    if (count == 0) {
        return false;
    }
    int i;
    //while(this->el[i] != n)
};
//4 działa, ale trzeba zrobić wyjątek, jeśli lista jest pusta
Planet& List::operator[](int i) {
    if (i < count) {
        cout << "Zwrocono " << i << " element" << endl;
        return el[i];
    }
    else {
        cout << "brak elementu pod tym indeksem" << endl;
        return;
    }
};

int main(){
    List l1;
    List l2;
    Planet p1("Merkury", 0);
    Planet p2("Wenus", 0);
    Planet p3("Ziemia", 1);
    Planet p4("Mars", 2);
    p4.show();
    l1.add(p1);
    l1.add(p2);
    l1.add(p3);
    l1.add(p4);
    p4 = l1[2];
    p4.show();
    //l1.showAll();
    //l2.showAll();
    //l1 = move(l2);
    //cout << "PRZENIESIENIE LISTY" << endl;
    //l1.showAll();
    //l2.showAll();
    return 0;
}