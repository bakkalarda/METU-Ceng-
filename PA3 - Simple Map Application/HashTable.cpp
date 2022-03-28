#include "HashTable.h"

#include <cassert>
#include <iostream>
#include <iomanip>

const int KeyedHashTable::PRIME_LIST[PRIME_TABLE_COUNT] =
{
     2,    3,   5,   7,  11,  13,  17,  19,
     23,  29,  31,  37,  41,  43,  47,  53,
     59,  61,  67,  71,  73,  79,  83,  89,
     97, 101, 103, 107, 109, 113, 127, 131,
    137, 139, 149, 151, 157, 163, 167, 173,
    179, 181, 191, 193, 197, 199, 211, 223,
    227, 229, 233, 239, 241, 251, 257, 263,
    269, 271, 277, 281, 283, 293, 307, 311,
    313, 317, 331, 337, 347, 349, 353, 359,
    367, 373, 379, 383, 389, 397, 401, 409,
    419, 421, 431, 433, 439, 443, 449, 457,
    461, 463, 467, 479, 487, 491, 499, 503,
    509, 521, 523, 541
};

int KeyedHashTable::Hash(const std::string& key) const
{
    int result = 0;
    for(int i=0; i<(int)key.length();i++)
    {
        result = result + key[i]*PRIME_LIST[i];
    }
    return result % tableSize;
}

void KeyedHashTable::ReHash()
{
    int new_table_size = FindNearestLargerPrime(tableSize*2);
    HashData* new_table = new HashData[new_table_size]();
    int ex_table_size = tableSize;
    tableSize = new_table_size;
    for(int i=0; i<ex_table_size; i++)
    {
        if(table[i].key != "")
        {
            int index = Hash(table[i].key);
            new_table[index] = table[i];
        }
    }
    delete[] table;
    table = new_table;
}

int KeyedHashTable::FindNearestLargerPrime(int requestedCapacity)
{
    int result = 2;
    for(int i=0; i<PRIME_TABLE_COUNT; i++)
    {
        if(PRIME_LIST[i] > requestedCapacity)
        {
            result = PRIME_LIST[i];
            break;
        }
    }
    return result;
}

KeyedHashTable::KeyedHashTable()
{
    tableSize = 2;
    occupiedElementCount = 0;
    table = new HashData[2]();
}

KeyedHashTable::KeyedHashTable(int requestedCapacity)
{
    tableSize = FindNearestLargerPrime(requestedCapacity);
    occupiedElementCount = 0;
    table = new HashData[tableSize]();
}

KeyedHashTable::KeyedHashTable(const KeyedHashTable& other)
{
    this->tableSize = other.tableSize;
    this->occupiedElementCount = other.occupiedElementCount;
    this->table = new HashData[other.tableSize]();
    for(int i=0; i<tableSize; i++)
    {
        this->table[i] = other.table[i];
    }
}

KeyedHashTable& KeyedHashTable::operator=(const KeyedHashTable& other)
{
    delete[] table;
    this->tableSize = other.tableSize;
    this->occupiedElementCount = other.occupiedElementCount;
    this->table = new HashData[other.tableSize]();
    for(int i=0; i<tableSize; i++)
    {
        this->table[i] = other.table[i];
    }
    return *this;
}

KeyedHashTable::~KeyedHashTable()
{
    tableSize = 0;
    occupiedElementCount = 0;
    delete[] table;
}

bool KeyedHashTable::Insert(const std::string& key,
                            const std::vector<int>& intArray)
{
    struct HashData new_data;
    new_data.key = key;
    new_data.intArray = intArray;
    int index = 0;
    index = Hash(key);
    if(table[index].key == key)
    {
        return false;
    }
    int i = index;
    int quad = 1;
    while(table[i%tableSize].key != "")
    {
        if(table[i%tableSize].key == key)
        {
            return false;
        }
        quad = quad*quad;
        i = index + quad;
        quad++;
    }
    table[i%tableSize] = new_data;
    occupiedElementCount++;
    if(occupiedElementCount*EXPAND_THRESHOLD >= tableSize)
    {
        ReHash();
    }
    return true;
}

bool KeyedHashTable::Remove(const std::string& key)
{
    int index = 0;
    index = Hash(key);
    if(table[index].key == key)
    {
        table[index].key = "_DELETED_";
        table[index].intArray.resize(0);
        occupiedElementCount--;
        return true;
    }
    int i = index;
    int quad = 1;
    while(table[i%tableSize].key != "")
    {
        if(table[i%tableSize].key == key)
        {
            table[index].key = "_DELETED_";
            table[index].intArray.resize(0);
        }
        quad = quad*quad;
        i = index + quad;
        quad++;
    }
    if(table[i%tableSize].key == "")
    {
        return false;
    }
    occupiedElementCount--;
    return true;
}

void KeyedHashTable::ClearTable()
{
    for(int i=0; i<tableSize; i++)
    {
        table[i].key = "";
        table[i].intArray.resize(0);
    }
    occupiedElementCount = 0;
}

bool KeyedHashTable::Find(std::vector<int>& valueOut,
                          const std::string& key) const
{
    int index = Hash(key);
    if(table[index].key == key)
    {
        valueOut = table[index].intArray;
        return true;
    }
    int i = index;
    int quad = 1;
    while(table[i%tableSize].key != "")
    {
        if(table[i%tableSize].key == key)
        {
            valueOut = table[i%tableSize].intArray;
            break;
        }
        quad = quad*quad;
        i = index + quad;
        quad++;
    }
    if(table[i%tableSize].key == "")
    {
        return false;
    }
    return true;
}

void KeyedHashTable::Print() const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    std::cout << "HT:";
    if(occupiedElementCount == 0)
    {
        std::cout << " Empty";
    }
    std::cout << "\n";
    for(int i = 0; i < tableSize; i++)
    {
        if(table[i].key == "") continue;

        std::cout << "[" << std::setw(3) << i << "] ";
        std::cout << "[" << table[i].key << "] ";
        std::cout << "[";
        for(size_t j = 0; j < table[i].intArray.size(); j++)
        {
            std::cout << table[i].intArray[j];
            if((j + 1) != table[i].intArray.size())
                std::cout << ", ";
        }
        std::cout << "]\n";
    }
    std::cout.flush();
}