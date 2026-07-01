#include<iostream>
#include<string.h>
#include "../include/DynamicArray.h"
using namespace std;

class Person {
public:
    string name;
    int age;

    Person(string name, int age){
        this->name=name;
        this->age=age;
    }
    // Person() : name(""), age(0) {}

    // Person(string n, int a) : name(std::move(n)), age(a) {}

    // Person(const Person& other) {
    //     name = other.name;
    //     age = other.age;
    //     cout << "Copied Person\n";
    // }

    // Person(Person&& other) noexcept {
    //     name = std::move(other.name);
    //     age = other.age;
    //     cout << "Moved Person\n";
    // }
    bool operator==(const Person& other) const {
        return name == other.name && age == other.age;
    }   
    friend std::ostream& operator<<(std::ostream& os, const Person& p) {
        os << "{Name: " << p.name << ", Age: " << p.age << "}";
        return os;
    }
};


void test_int() {
    cout << "\n--- TEST INT ---\n";

    DynamicArray<int> arr;

    for (int i = 1; i <= 10; i++) {
        arr.append(i);
    }

    arr.print();

    arr.insert(5, 999);
    arr.print();

    arr.remove(3);
    arr.print();

    cout << "Find 999: " << arr.find(999) << endl;

    arr.reverse();
    arr.print();

    arr.clear();
    cout << "Size after clear: " << arr.get_size() << endl;
}

// ----------------------
// TEST 2: string operations
// ----------------------
void test_string() {
    cout << "\n--- TEST STRING ---\n";

    DynamicArray<string> arr;

    arr.append("hello");
    arr.append("world");
    arr.append("dynamic");
    arr.append("array");

    arr.print();

    arr.insert(2, "INSERTED");
    arr.print();

    arr.remove(1);
    arr.print();

    cout << "Find 'array': " << arr.find("array") << endl;

    arr.reverse();
    arr.print();
}

// ----------------------
// TEST 3: complex object
// ----------------------
void test_person() {
    cout << "\n--- TEST PERSON (Complex Type) ---\n";

    DynamicArray<Person> arr;

    arr.append(Person("Aman", 20));
    arr.append(Person("Jatin", 22));
    arr.append(Person("Amit", 25));

    cout << "\nAfter inserts:\n";
    arr.print(); // NOTE: won't print nicely unless you overload operator<<

    arr.insert(1, Person("Inserted", 99));

    cout << "\nAfter insert:\n";
    arr.print();

    arr.remove(2);

    cout << "\nAfter remove:\n";
    arr.print();

    cout << "Find Amit: " << arr.find(Person("Amit", 25)) << endl;
}

// ----------------------
// TEST 4: stress test (resize check)
// ----------------------
void test_resize() {
    cout << "\n--- TEST RESIZE ---\n";

    DynamicArray<int> arr;

    for (int i = 0; i < 1000; i++) {
        arr.append(i);
    }

    cout << "Size: " << arr.get_size() << endl;
    cout << "Capacity: " << arr.get_capacity() << endl;

    cout << "Last element: " << arr[arr.get_size() - 1] << endl;
}

// ----------------------
// MAIN
// ----------------------
int main() {
    test_int();
    test_string();
    test_person();
    test_resize();

    cout << "\nALL TESTS DONE\n";
    return 0;
}