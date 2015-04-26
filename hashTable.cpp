#include "hashTable.h"

HashTable::HashTable(int n)
{
    for(int i = 0;i < n;i++){
        hashTable[i] = NULL;
    }
    //ctor
}

int HashTable::hashSum(string x,int s){    //x is string to hash, s is size of array
    int sum = 0;
    for(int i = 0;i < x.length();i++){
        sum = sum + x[i];
    }
    sum = sum % s;
    return sum;
}

int HashTable::sum(string x){
    int sum = 0;
    for(int i = 0;i < x.length();i++){
        sum = sum + x[i];
    }
    return sum;
}

void HashTable::insertMovie(string title,int year){
    int index = hashSum(title,10);
    bool firstSearch = true;
    if(hashTable[index] == NULL){
        hashTable[index] = new Movie(title,year,index);
    }else{
        Movie * Previous = hashTable[index];
        Movie * Iterator = hashTable[index];
        Movie * Insert = new Movie(title,year,index);
        while(Iterator->next != NULL){
            if(title.compare(Iterator->title) >= 0){
                Previous = Iterator;
                Iterator = Iterator->next;
            }else{
                Insert->next = Iterator->next;
                break;
            }
            firstSearch = false;
        }

        if(firstSearch == true){
            if(title.compare(hashTable[index]->title)<0){
                Insert->next = hashTable[index];
                hashTable[index] = Insert;
                return;
            }else{
                hashTable[index]->next = Insert;
                return;
            }
        }

        if(title.compare(Iterator->title) < 0){
            Insert->next = Iterator;
            Previous->next = Insert;
        }else{
            Iterator->next = Insert;
        }
    }
}

void HashTable::printInventory(){
    for(int i = 0; i < 10; i++){
        if(hashTable[i] != NULL){
            //cout<<"Index: "<<hashTable[i]->index<<", Movie: "<<hashTable[i]->title<<endl;
            Movie * Iterator = hashTable[i];
            while(Iterator != NULL){
                cout<<" Index: "<<Iterator->index<<", Movie: "<<Iterator->title<<endl;
                Iterator = Iterator->next;
            }
        }
    }
}

void HashTable::deleteMovie(string title){

    Movie * Previous;
    for(int i = 0; i < 10; i++){
        if(hashTable[i] != NULL){
            Previous = hashTable[i];

            Movie * Iterator = hashTable[i];

            if(Iterator->title == title && Iterator->next == NULL){
                delete Iterator;
                hashTable[i] = NULL;

                return;
            }
            if(Iterator->title == title && Iterator->next != NULL){
                hashTable[i] = Iterator->next;
                delete Iterator;

                return;
            }

            while(Iterator->next != NULL){

                if(Iterator->title == title){
                    if(Iterator->next != NULL && Previous != Iterator){
                        Movie * temp = Iterator->next;
                        Previous->next = temp;
                        delete Iterator;
                        return;
                    }
                }
                Previous = Iterator;
                Iterator = Iterator->next;
            }

            if(Iterator->title == title){
                delete Iterator;
                Previous->next = NULL;
                return;
            }
        }
    }
    cout<<"Movie does not exist."<<endl;
}

Movie * HashTable::findMovie(string title){
    bool found;
    for(int i = 0; i < 10; i++){
        if(hashTable[i] != NULL){

            Movie * Iterator = hashTable[i];
            if(Iterator->title == title){
                cout<<"Movie Found!"<<endl;
                cout<<"Index: "<<Iterator->index<<", Movie: "<<Iterator->title<<", Year: "<<Iterator->year<<endl;
                found = true;
                break;
            }

            while(Iterator->next != NULL){
                if(Iterator->title == title){
                    cout<<"Movie Found!"<<endl;
                    cout<<"Index: "<<Iterator->index<<", Movie: "<<Iterator->title<<", Year: "<<Iterator->year<<endl;
                    found = true;
                    break;
                }
                Iterator = Iterator->next;
            }
            if(Iterator->title == title){
                cout<<"Movie Found!"<<endl;
                cout<<"Index: "<<Iterator->index<<", Movie: "<<Iterator->title<<", Year: "<<Iterator->year<<endl;
                found = true;
                break;
            }
        }
    }
    if(found == false){
        cout<<"Movie not found."<<endl;
    }
}

bool HashTable::readFileIntoTable(string filename){
    ifstream file;

    file.open(filename.c_str());
    if(!file){
        cout<<"File could not be opened."<<endl;
        return false;
    }
    string line;

    string segment;
    string title;
    string yearString;
    int year;
    while(!file.eof()){
        getline(file,line);
        istringstream ss(line);
        getline(ss,segment,',');
        getline(ss,title,',');
        getline(ss,yearString);
        year = atoi(yearString.c_str());
        insertMovie(title,year);
    }
    return true;
}

void HashTable::removeAll(){
    for(int i = 0;i < 10;i++){
        while(hashTable[i] != NULL){
            deleteMovie(hashTable[i]->title);
        }
    }
}

void HashTable::guessingGame(){
    string input;
    bool correct = true;
    int points = 0;

    for(int i = 0; i < 10; i++){
        if(hashTable[i] != NULL){

            Movie * Iterator = hashTable[i];
            //print hint
            cout<<"Hint: ";
            for(int j = 0; j < hashTable[i]->title.length(); j++){
                if(j < 3){
                    cout<<hashTable[i]->title[j];
                }else{
                    if(hashTable[i]->title[j] == ' '){
                        cout<<"  ";
                    }else{
                        cout<<"_ ";
                    }
                }
            }cout<<",Year: "<<hashTable[i]->year<<endl;
            cout<<"The name of this movie is: ";
            getline(cin,input);
            if(input == hashTable[i]->title){
                cout<<"Correct! Point added."<<endl;
                points++;
            }else{
                cout<<"Incorrect! Game over."<<endl;
                cout<<"Final score: "<<points<<endl;
                return;
            }

            while(Iterator->next != NULL){
                cout<<"Hint: ";
                for(int j = 0; j < Iterator->next->title.length(); j++){
                    if(j < 3){
                        cout<<Iterator->next->title[j];
                    }else{
                        if(Iterator->next->title[j] == ' '){
                            cout<<"  ";
                        }else{
                            cout<<"_ ";
                        }
                    }
                }cout<<",Year: "<<Iterator->next->year<<endl;
                cout<<"The name of this movie is: ";
                getline(cin,input);
                if(input == Iterator->next->title){
                    cout<<"Correct! Point added."<<endl;
                    points++;
                }else{
                    cout<<"Incorrect! Game over."<<endl;
                    cout<<"Final score: "<<points<<endl;
                    return;
                }
                Iterator = Iterator->next;
            }
        }
    }
    cout<<"Game over! Final score: "<<points<<endl;
}

void HashTable::tableSize(){
    int tableSize;
    for(int i = 0; i < 10; i++){

        if(hashTable[i] != NULL){
            //cout<<"Index: "<<hashTable[i]->index<<", Movie: "<<hashTable[i]->title<<endl;
            Movie * Iterator = hashTable[i];
            while(Iterator != NULL){
                tableSize++;
                Iterator = Iterator->next;
            }
        }
    }
    cout<<"Number of elements in table: "<<tableSize<<endl;
    return;
}

void HashTable::totalIndex(){
    int totalIndex = 0;
    for(int i = 0; i < 10; i++){

        if(hashTable[i] != NULL){
            //cout<<"Index: "<<hashTable[i]->index<<", Movie: "<<hashTable[i]->title<<endl;
            Movie * Iterator = hashTable[i];
            while(Iterator != NULL){
                totalIndex += sum(Iterator->title);
                Iterator = Iterator->next;
            }
        }
    }totalIndex = totalIndex % 10;
    cout<<"Total Index: "<<totalIndex<<endl;
}

//Cuts down number of actions to find movie significantly
void HashTable::hashFind(string title){
    int index = hashSum(title,10);
    for(int i = 0;i < 10;i++){
        if(i == index && hashTable[i] != NULL){
            Movie *Iterator = hashTable[i];
            while(Iterator != NULL){
                if(Iterator->title == title){
                    cout<<"Movie Found!"<<endl;
                    cout<<"Index: "<<Iterator->index<<", Movie: "<<Iterator->title<<", Year: "<<Iterator->year<<endl;
                    return;
                }
                Iterator = Iterator->next;
            }
        }
    }cout<<"Movie not found."<<endl;
}

HashTable::~HashTable()
{
    removeAll();
    //dtor
}
