#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
using namespace std;
struct Movie{
    std::string title;
    int year;
    int index;
    Movie *next = NULL;
    Movie(){};

    Movie(std::string in_title, int in_year,int in_index)
    {
        title = in_title;
        year = in_year;
        index = in_index;
    }

};

class HashTable
{
    public:
        HashTable(int);
        ~HashTable();

        bool readFileIntoTable(std::string);
        void removeAll();
        void guessingGame();
        void tableSize();
        void totalIndex();
        int sum(std::string);
        void hashFind(std::string);
        int hashSum(std::string,int);
        void insertMovie(std::string in_title,int);
        Movie* findMovie(std::string in_title);
        void deleteMovie(std::string in_title);
        void printInventory();

    protected:
    private:
        Movie *hashTable[10];
};

#endif // HASHTABLE_H
