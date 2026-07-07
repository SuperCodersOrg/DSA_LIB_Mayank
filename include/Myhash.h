#pragma once

#include <string>

template<typename T>
class MyHash;

template<>
class MyHash<int>
{
public:
    size_t operator()(const int& key) const
    {
        return key;
    }
};

template<>
class MyHash<long>
{
public:
    size_t operator()(const long& key) const
    {
        return key;
    }
};


template<>
class MyHash<char>
{
public:
    size_t operator()(const char& key) const
    {
        return key;
    }
};

template<>
class MyHash<float>
{
public:
    size_t operator()(const float& key) const
    {
        return static_cast<size_t>(key * 1000);
    }
};

template<>
class MyHash<double>
{
public:
    size_t operator()(const double& key) const
    {
        return static_cast<size_t>(key * 1000000);
    }
};

template<>
class MyHash<std::string>
{
public:
    size_t operator()(const std::string& key) const
    {
        size_t h = 0;

        for(char c : key)
            h = h * 31 + c;

        return h;
    }
};