#include <iostream>
#include <string>
#include "../include/HashMap.h"

using namespace std;

int main() {

    cout << "=====================================\n";
    cout << "TEST 1 : Basic Insertion\n";
    cout << "=====================================\n";

    HashMap<int, string> map;

    map.put(1, "One");
    map.put(2, "Two");
    map.put(3, "Three");

    map.print();

    cout << "\nSize : " << map.get_size() << endl;
    cout << "Capacity : " << map.get_capacity() << endl;


    cout << "\n=====================================\n";
    cout << "TEST 2 : Updating Existing Key\n";
    cout << "=====================================\n";

    map.put(2, "Updated Two");

    cout << "Key 2 = " << map.get(2) << endl;


    cout << "\n=====================================\n";
    cout << "TEST 3 : Collision Handling\n";
    cout << "=====================================\n";

    // Initial capacity = 8
    // 1,9,17 all hash to bucket 1

    map.put(9, "Nine");
    map.put(17, "Seventeen");

    map.print();

    cout << "\n9  = " << map.get(9) << endl;
    cout << "17 = " << map.get(17) << endl;


    cout << "\n=====================================\n";
    cout << "TEST 4 : containsKey()\n";
    cout << "=====================================\n";

    cout << boolalpha;

    cout << "containsKey(17) : "
         << map.containsKey(17) << endl;

    cout << "containsKey(100) : "
         << map.containsKey(100) << endl;


    cout << "\n=====================================\n";
    cout << "TEST 5 : get() Reference\n";
    cout << "=====================================\n";

    map.get(1) = "ONE";

    cout << map.get(1) << endl;


    cout << "\n=====================================\n";
    cout << "TEST 6 : Remove Existing Key\n";
    cout << "=====================================\n";

    cout << map.remove(9) << endl;

    map.print();

    cout << "containsKey(9) : "
         << map.containsKey(9) << endl;


    cout << "\n=====================================\n";
    cout << "TEST 7 : Remove Missing Key\n";
    cout << "=====================================\n";

    cout << map.remove(500) << endl;


    cout << "\n=====================================\n";
    cout << "TEST 8 : getKeys()\n";
    cout << "=====================================\n";

    DynamicArray<int> keys = map.getKeys();

    for(auto it = keys.begin(); it != keys.end(); ++it)
    {
        cout << *it << " ";
    }

    cout << endl;


    cout << "\n=====================================\n";
    cout << "TEST 9 : getValues()\n";
    cout << "=====================================\n";

    DynamicArray<string> values = map.getValues();

    for(auto it = values.begin(); it != values.end(); ++it)
    {
        cout << *it << " ";
    }

    cout << endl;


    cout << "\n=====================================\n";
    cout << "TEST 10 : Copy Constructor\n";
    cout << "=====================================\n";

    HashMap<int, string> copy(map);

    copy.print();

    copy.put(100, "Hundred");

    cout << "\nOriginal\n";
    map.print();

    cout << "\nCopy\n";
    copy.print();


    cout << "\n=====================================\n";
    cout << "TEST 11 : Copy Assignment\n";
    cout << "=====================================\n";

    HashMap<int, string> another;

    another.put(500, "Five Hundred");

    another = map;

    another.print();


    cout << "\n=====================================\n";
    cout << "TEST 12 : Self Assignment\n";
    cout << "=====================================\n";

    map = map;

    map.print();


    cout << "\n=====================================\n";
    cout << "TEST 13 : Rehashing\n";
    cout << "=====================================\n";

    HashMap<int, int> numbers;

    for(int i = 0; i < 30; i++)
    {
        numbers.put(i, i * 10);
    }

    cout << "Size : " << numbers.get_size() << endl;
    cout << "Capacity : " << numbers.get_capacity() << endl;

    for(int i = 0; i < 30; i++)
    {
        cout << i << " -> " << numbers.get(i) << endl;
    }


    cout << "\n=====================================\n";
    cout << "TEST 14 : clear()\n";
    cout << "=====================================\n";

    map.clear();

    cout << "Size : " << map.get_size() << endl;
    cout << "isEmpty : " << map.isEmpty() << endl;


    cout << "\n====================================\n";
    cout << "TEST 15 : Exception\n";
    cout << "====================================\n";

    try
    {
        cout << map.get(100) << endl;
    }
    catch(const exception& e)
    {
        cout << e.what() << endl;
    }

    cout << "\n=====================================\n";
    cout << "ALL TESTS FINISHED\n";
    cout << "=====================================\n";

    return 0;
}