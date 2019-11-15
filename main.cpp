#include <iostream>
#include "Tries.h"

int main() {
    Trie t;

    t.insert("hola");

    t.insert("he");

    t.insert("alo");

    if(t.search_complete_word("hola")){
        cout << "Found!" << endl;
    }


    if(t.search_by_prefix("ho")){
        cout << "Found!" << endl;
    }
    return 0;
}