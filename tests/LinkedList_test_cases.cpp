#include <iostream>
#include "../include/LinkedList.h"

using namespace std;

int main() {

    cout << "==============================\n";
    cout << "TEST 1 : Empty List\n";
    cout << "==============================\n";

    LinkedList<int> list;

    cout << "Size : " << list.size() << endl;
    cout << "Empty : " << list.isEmpty() << endl;

    try {
        list.pop_front();
    }
    catch(const exception& e){
        cout << "pop_front(): " << e.what() << endl;
    }

    try {
        list.pop_back();
    }
    catch(const exception& e){
        cout << "pop_back(): " << e.what() << endl;
    }

    try {
        cout << list.front() << endl;
    }
    catch(const exception& e){
        cout << "front(): " << e.what() << endl;
    }

    try {
        cout << list.back() << endl;
    }
    catch(const exception& e){
        cout << "back(): " << e.what() << endl;
    }


    cout << "\n==============================\n";
    cout << "TEST 2 : push_back()\n";
    cout << "==============================\n";

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.print();

    cout << "\nSize : " << list.size() << endl;
    cout << "Front : " << list.front() << endl;
    cout << "Back : " << list.back() << endl;


    cout << "\n==============================\n";
    cout << "TEST 3 : push_front()\n";
    cout << "==============================\n";

    list.push_front(5);
    list.push_front(1);

    list.print();

    cout << "\nFront : " << list.front() << endl;
    cout << "Back : " << list.back() << endl;


    cout << "\n==============================\n";
    cout << "TEST 4 : operator[]\n";
    cout << "==============================\n";

    for(int i=0;i<list.size();i++)
        cout << list[i] << " ";

    cout << endl;

    list[2] = 100;

    cout << "After modification\n";
    list.print();

    cout << endl;

    try{
        cout << list[100];
    }
    catch(const exception& e){
        cout << e.what() << endl;
    }


    cout << "\n==============================\n";
    cout << "TEST 5 : find()\n";
    cout << "==============================\n";

    cout << "Find 100 : " << list.find(100) << endl;
    cout << "Find 999 : " << list.find(999) << endl;


    cout << "\n==============================\n";
    cout << "TEST 6 : insert()\n";
    cout << "==============================\n";

    list.insert(0,111);
    list.insert(list.size(),999);
    list.insert(3,500);

    list.print();

    cout << endl;

    try{
        list.insert(100,0);
    }
    catch(const exception& e){
        cout << e.what() << endl;
    }


    cout << "\n==============================\n";
    cout << "TEST 7 : remove()\n";
    cout << "==============================\n";

    cout << "Removed : " << list.remove(0) << endl;
    cout << "Removed : " << list.remove(list.size()-1) << endl;
    cout << "Removed : " << list.remove(2) << endl;

    list.print();

    cout << endl;

    try{
        list.remove(100);
    }
    catch(const exception& e){
        cout << e.what() << endl;
    }


    cout << "\n==============================\n";
    cout << "TEST 8 : pop_front()\n";
    cout << "==============================\n";

    cout << list.pop_front() << endl;

    list.print();

    cout << endl;


    cout << "\n==============================\n";
    cout << "TEST 9 : pop_back()\n";
    cout << "==============================\n";

    cout << list.pop_back() << endl;

    list.print();

    cout << endl;


    cout << "\n==============================\n";
    cout << "TEST 10 : Copy Constructor\n";
    cout << "==============================\n";

    LinkedList<int> copy(list);

    cout << "Original : ";
    list.print();

    cout << "\nCopy : ";
    copy.print();

    cout << endl;

    copy.push_back(9999);

    cout << "\nAfter modifying copy\n";

    cout << "Original : ";
    list.print();

    cout << "\nCopy : ";
    copy.print();

    cout << endl;


    cout << "\n==============================\n";
    cout << "TEST 11 : clear()\n";
    cout << "==============================\n";

    list.clear();

    cout << "Size : " << list.size() << endl;
    cout << "Empty : " << list.isEmpty() << endl;

    list.print();

    cout << endl;


    cout << "\n==============================\n";
    cout << "TEST 12 : Single Element\n";
    cout << "==============================\n";

    LinkedList<int> one;

    one.push_back(50);

    one.print();

    cout << endl;

    cout << one.pop_front() << endl;

    cout << "Size : " << one.size() << endl;
    cout << "Empty : " << one.isEmpty() << endl;

    one.push_back(100);

    cout << one.pop_back() << endl;

    cout << "Size : " << one.size() << endl;
    cout << "Empty : " << one.isEmpty() << endl;


    cout << "\n==============================\n";
    cout << "ALL TESTS COMPLETED\n";
    cout << "==============================\n";

    return 0;
}