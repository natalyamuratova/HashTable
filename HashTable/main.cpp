#include <iostream>
#include <string>
#include "SeparateChainingTable.h"

using namespace std;


int main() {
    HashTable* table = new SeparateChainingTable(10);
   
    table->insert(1, 1);
    table->insert(1, 1);
    table->insert(2, 1);
    table->print();

    return 0;
}