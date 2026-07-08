#include<iostream>
#include<sstream>
#include<string.h>
#include"../include/RedisLite.h"
using namespace std;

void RedisLite::handleSet(stringstream& ss){
    string key;
    string value;

    ss >> key;
    getline(ss, value);

    if (!value.empty() && value[0] == ' ')
    {
        value.erase(0, 1);
    }

    if (key.empty() || value.empty())
    {
        cout << "Usage: SET <key> <value>\n";
        return;
    }

    storage.set(key, value);
    stats.incrementSet();
    cout << "OK\n";
}


void RedisLite::handleGet(stringstream& ss){
    string key;

    ss >> key;

    if (key.empty())
    {
        cout<< "Usage: GET <key>\n";
        return;
    }

    string* value = storage.get(key);

    if (value == nullptr)
    {
        cout << "(nil)\n";
        return;
    }

    stats.incrementGet();

    cout << *value<<endl;
}

void RedisLite::handleDelete(stringstream& ss){
    string key;

    ss >> key;

    if (key.empty())
    {
        cout << "Usage: DEL <key>\n";
        return;
    }

    if (storage.del(key))
    {
        stats.incrementDel();
        cout << "Key deleted successfully.\n";
    }
    else
    {
        cout << "Key not found.\n";
    }
}

void RedisLite::handleExists(stringstream& ss){
    string key;

    ss >> key;

    if (key.empty())
    {
        cout << "Usage: EXISTS <key>\n";
        return;
    }

    stats.incrementExists();

    if (storage.exists(key))
    {
        cout << "True\n";
    }
    else
    {
        cout << "False\n";
    }
}


void RedisLite::handlePrint(){
    if (storage.size() == 0)
    {
        cout << "Database is empty.\n";
        return;
    }

    storage.print();
}

void RedisLite::handleClear(){
    storage.clear();

    cout << "Database cleared successfully.\n";
}

void RedisLite::handleStats(){
    cout << "\n========== Redis Stats ==========\n";

    cout << "Current Size     : "<< storage.size() << endl;

    cout << "Current Capacity : "<< storage.capacity() << endl;

    if (storage.capacity() != 0)
    {
        cout << "Load Factor      : "<< (double)storage.size() / storage.capacity()<< endl;
    }

    stats.print();

    cout << "=================================\n";
}

void RedisLite::run(){
    cout << "=========================================\n";
    cout << "         Welcome to Redis Lite\n";
    cout << "=========================================\n";
    cout << "Available Commands:\n";
    cout << "-----------------------------------------\n";
    cout << "SET <key> <value>   : Insert or update\n";
    cout << "GET <key>           : Get value\n";
    cout << "DEL <key>           : Delete key\n";
    cout << "EXISTS <key>        : Check if key exists\n";
    cout << "PRINT               : Print all key-value pairs\n";
    cout << "CLEAR               : Remove all data\n";
    cout << "SIZE                : Show number of keys\n";
    cout << "STATS               : Show database statistics\n";
    cout << "EXIT (ctrl + c)     : Exit Redis Lite\n";
    cout << "-----------------------------------------\n";
    cout << "Type a command and press Enter.\n";
    cout << "Example: SET name Mayank\n\n";
    string line;
    while(true){
        cout<<"RedisLite> ";
        getline(cin,line);
        if(line.empty()){
            continue;
        }
        stringstream ss(line);
        string command;
        ss>>command;
        CommandType type=parser.parse(command);
        switch(type){
            case CommandType::SET:
                handleSet(ss);
                break;

            case CommandType::GET:
                handleGet(ss);
                break;

            case CommandType::DEL:
                handleDelete(ss);
                break;

            case CommandType::EXISTS:
                handleExists(ss);
                break;

            case CommandType::PRINT:
                handlePrint();
                break;

            case CommandType::CLEAR:
                handleClear();
                break;

            case CommandType::STATS:
                handleStats();
                break;

            case CommandType::SIZE:
                cout << "Current Size : " << storage.size() << endl;
                break;

            case CommandType::EXIT:
                cout << "Thank you for using Redis Lite.\n";
                return;

            default:
                cout << "Invalid Command.\n";
        }
    }
}

int main(){
    RedisLite redis;
    redis.run();
    return 0;
}