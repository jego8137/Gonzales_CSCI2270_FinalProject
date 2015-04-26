#include <iostream>
#include <string>
#include <cstdlib>
#include "hashTable.h"

using namespace std;

int main()
{
    HashTable table(10);
    string input;

    while(input != "y" && input != "n"){
        cout<<"Read from file? (y/n): ";
        getline(cin,input);
    }
    if(input == "y"){
        bool checker = false;
        while(checker == false){
            cout<<"Enter name of file: ";
            getline(cin,input);
            checker = table.readFileIntoTable(input);
        }
    }


    int command = 0;

    while(command != 11){
        cout<<"======Main Menu======"<<endl;
        cout<<"1.   Insert Movie"<<endl;
        cout<<"2.  Find Movie"<<endl;
        cout<<"3.   Print Table Contents"<<endl;
        cout<<"4.  Delete Movie"<<endl;
        cout<<"5.   Remove All Movies"<<endl;
        cout<<"6.  Guessing Game"<<endl;
        cout<<"7.   Table Size"<<endl;
        cout<<"8.  Total Index"<<endl;
        cout<<"9.   Find Movie (Using Hash Sum)"<<endl;
        cout<<"10. Read File Into Table"<<endl;
        cout<<"11.  Quit"<<endl;
        cout<<"Input: ";
        getline(cin,input);
        command = atoi(input.c_str());
        if(command == 1){
            string inputMovie;
            string inputYear;
            string inputChar;
            int year;
            cout<<"Name of Movie: ";
            getline(cin,inputMovie);
            cout<<"Index of Movie: "<<table.hashSum(inputMovie,10)<<endl;
            cout<<"Year of Movie: ";
            getline(cin,inputYear);
            year = atoi(inputYear.c_str());
            table.insertMovie(inputMovie,year);

        }if(command == 2){
            string inputMovie;
            cout<<"Name of Movie: ";
            getline(cin,inputMovie);
            table.findMovie(inputMovie);
        }if(command == 3){
            cout<<"Printing Inventory..."<<endl;
            table.printInventory();
        }if(command == 4){
            string inputMovie;
            cout<<"Name of Movie: ";
            getline(cin,inputMovie);
            table.deleteMovie(inputMovie);
        }if(command == 5){
            while(input != "y" && input != "n"){
                cout<<"Are you sure? (y/n): ";
                getline(cin,input);
            }
            if(input == "y"){
                cout<<"Deleting Table..."<<endl;
                table.removeAll();
            }
        }if(command == 6){
            table.guessingGame();
        }if(command == 7){
            table.tableSize();
        }if(command == 8){
            table.totalIndex();
        }if(command == 9){
            string inputMovie;
            cout<<"Name of Movie: ";
            getline(cin,inputMovie);
            table.hashFind(inputMovie);
        }if(command == 10){
            cout<<"This will remove the current table."<<endl;
            while(input != "y" && input != "n"){
                cout<<"Are you sure? (y/n): ";
                getline(cin,input);
            }
            if(input == "y"){
                bool checker = false;
                while(checker == false){
                    cout<<"Enter name of file: ";
                    getline(cin,input);
                    table.removeAll();
                    checker = table.readFileIntoTable(input);
                }
            }
        }
    }

    table.~HashTable();
    cout<<"Goodbye!"<<endl;

    return 0;
}
