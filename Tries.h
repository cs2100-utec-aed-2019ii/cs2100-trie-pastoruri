#ifndef TRIES_TRIES_H
#define TRIES_TRIES_H
#include <map>
#include <string>
#include <queue>
#include <random>
#include <ctime>
using namespace std;

struct Node{
    bool is_word = false;
    map<string,Node*> characters;
    Node() = default;
    ~Node() = default;
    Node* next = nullptr;
    Node* parent = nullptr;
    Node* previous = nullptr;
    int colisiones = 0;
};


struct Trie{
    Node* root = new Node;
    Node* lastfinal = nullptr;
    int cant_words_totales = 0;
    int cant_words_unique = 0;
    Node* lasttail = nullptr;
    float avg_frequency(){
        return cant_words_totales / float(cant_words_unique);
    }

    Trie() = default;
    vector<string> ejercicio5(string word){
        vector<string> palabras;
        auto  aux = lastfinal;
        auto track = lastfinal;
        while(aux != nullptr){
            bool col = true;
            string pal;
            palabras.push_back(pal);
            int t = palabras.size()-1;
            while(aux != nullptr) {
                auto padre = aux->parent;
                if(padre!=nullptr){
                    for (auto it = padre->characters.begin(); it != padre->characters.end(); ++it) {
                        if (it->second == aux) {
                            palabras[t]+=it->first;
                        }
                    }
                }
                aux = aux->parent;
            }
            aux = track->next;
            track = track->next;
        }

        for(int i=0 ; i< palabras.size(); ++i){
            palabras[i] = reverse(palabras[i]);
        }
        vector<string> matches;

        for(int i=0 ; i < palabras.size(); ++i){
            int count = 0;
            for(int j=0; j < palabras[i].size(); ++j){
                 if(word[count] == palabras[i][j]){
                     ++count;
                    if(count == word.size()){
                        matches.push_back(palabras[i]);
                        cout << palabras[i] << endl;
                        break;
                    }
                }

            }
        }

        return matches;




    }



    void ejercicio2(){
        cout << "Cuantas filas tendra la matriz: " << endl;
        int filas;
        cin >> filas;
        for(int i=0; i < filas; ++i){
           cout << "Ingrese fila " << i << endl;
           string c;
           cin >> c;
           insert(c);
        }
        cout << "Filas que se repiten al menos una vez: " << endl;
        auto  aux = lastfinal;
        auto track = lastfinal;
        while(aux != nullptr){
            bool col = true;
            auto initial_node = aux;
            while(aux != nullptr) {
                if(initial_node->is_word && initial_node->colisiones == 0 ){
                    break;
                }
                else{
                    auto padre = aux->parent;
                    if(aux->is_word == true && col){
                        col = false;
                        cout << "Repetidas: " << aux->colisiones << " veces." << endl;
                    }
                    if(padre!=nullptr){
                        for (auto it = padre->characters.begin(); it != padre->characters.end(); ++it) {
                            if (it->second == aux) {
                                cout << it->first << endl;
                            }
                        }
                    }
                    aux = aux->parent;
                }
            }
            aux = track->next;
            track = track->next;
            cout << endl;
        }


    }


    void ejercicio3(){
        cout << "Palabras con frecuencia mayor que la media: " << endl;

        auto  aux = lastfinal;
        auto track = lastfinal;
        while(aux != nullptr){
            bool col = true;
            auto initial_node = aux;
            while(aux != nullptr) {
                if(initial_node->is_word && initial_node->colisiones+1 < avg_frequency() ){
                    break;
                }
                else{
                    auto padre = aux->parent;
                    if(aux->is_word == true && col){
                        col = false;
                        cout << "Frecuencia: " << aux->colisiones+1 << endl;
                    }
                    if(padre!=nullptr){
                        for (auto it = padre->characters.begin(); it != padre->characters.end(); ++it) {
                            if (it->second == aux) {
                                cout << it->first << endl;
                            }
                        }
                    }
                    aux = aux->parent;
                }
            }
            aux = track->next;
            track = track->next;
            cout << endl;
        }
    }
    string reverse(string const &s)
    {
        string rev;
        for (int i = s.size() - 1; i >= 0; i--) {
            rev = rev.append(1, s[i]);
        };

        return rev;
    }

    void print_all_words(){
        auto  aux = lastfinal;
        auto track = lastfinal;
        while(aux != nullptr){
            bool col = true;
            while(aux != nullptr) {
                auto padre = aux->parent;
                if(aux->is_word == true && col){
                    col = false;
                    cout << "Colisiones: " << aux->colisiones << endl;
                }
                if(padre!=nullptr){
                    for (auto it = padre->characters.begin(); it != padre->characters.end(); ++it) {
                        if (it->second == aux) {
                            cout << it->first << endl;
                        }
                    }
                }
                aux = aux->parent;
            }
            aux = track->next;
            track = track->next;
            cout << endl;
        }
    }
    void print() {
        queue<Node*> q;

        if (root)
            q.push(root);
        else
            return;

        while (!q.empty()) {
            unsigned nodos = q.size();

            while (nodos > 0) {
                Node* n = q.front();

                for (auto& [letter, child] : n->characters) {
                    cout << letter << " ";
                    if (child) {
                        q.push(child);
                    }
                }
                cout << endl;

                q.pop();

                --nodos;
            }
            cout << endl;
        }
    }


    void insert(string word){
        auto aux = root;

        for(int i=0; i<word.size(); i++) {
            string s(1,word[i]);
            if(!search_in_node(s,aux->characters)){
                pair aux_pair(s, new Node);
                auto aux_parent = aux;
                aux->characters.insert(aux_pair);
                aux = aux->characters[s];
                aux->parent = aux_parent;
            }
            else{
                aux = aux->characters[s];
            }
        }
        if( aux->is_word == false){
            aux->is_word = true;
            auto auxf = lastfinal;
            aux->next = auxf;
            lastfinal = aux;
            cant_words_totales++;
            cant_words_unique++;
        }
        else{
            aux->colisiones++;
            cant_words_totales++;
        }
    }

    bool search_complete_word(string word){
        auto aux = root;
        bool fail_case = false;
        for(int i = 0; i<word.size(); ++i){
            for (auto it = aux->characters.begin(); it!= aux->characters.end(); ++it){
                string s(1,word[i]);
                if (s == it->first){
                    aux = aux->characters[it->first];
                    goto Here;
                }
            }
            fail_case = true;
            Here:
            cout << "";
        }
        if(aux->characters.size()==0 && !fail_case){
            return true;
        }
        else{
            return false;
        }
    };


//    Trie patriciafy(Node* node){
//        auto aux = node;
//            for(auto it = aux->characters.begin(); it!=  aux->characters.end(); ++it){
//
//            }
//    }

    void ejercicio1(int cant_ips){
        srand(time(NULL));
    for(int i=0; i <(cant_ips+1); ++i){
        string num = "192.168.";
        int num1 = rand()%255;
        int num2 = rand()%255;
        num += to_string(num1);
        num += ".";
        num += to_string(num2);
        insert(num);
    }
    string ip;
        auto  aux = lastfinal;
        auto track = lastfinal;
        while(aux != nullptr){
            while(aux != nullptr) {
                auto padre = aux->parent;
                if(aux->is_word == true){
                    cout << "Existe esta ip(se lee de abajo hacia arriba): "  << endl;
                }
                if(padre!=nullptr){
                    for (auto it = padre->characters.begin(); it != padre->characters.end(); ++it) {
                        if (it->second == aux) {
                            cout << it->first << endl;
                        }
                    }
                }
                aux = aux->parent;

            }
            aux = track->next;
            track = track->next;
            cout << endl;
            break;
        }

    cout << "Ingrese ip para ser buscada: " ;
    cin >> ip;
        if(search_complete_word(ip)){
            cout << endl << "Ip encontrada." <<endl;
        }
        else{
            cout << endl << "Ip no encontrada." <<endl;
        }

    }

    bool search_by_prefix(string word){
        auto aux = root;
        bool fail_case = false;
        for(int i = 0; i<word.size(); ++i){

            for (auto it = aux->characters.begin(); it!= aux->characters.end(); ++it){
                string s(1,word[i]);
                if (s == it->first){
                    aux = aux->characters[it->first];
                    goto Here;
                }

            }
            fail_case = true;
            Here:
            cout << "";
        }
        if(aux->characters.size()!=0 && !fail_case){
            return true;
        }
        else{
            return false;
        }


    }

    bool search_in_node(string c, map<string,Node*> characters){
        if(characters.size() > 0){
            for(auto it = characters.begin(); it!=characters.end(); ++it){
                if(c == it->first){
                    return true;
                }
            }
            return false;
        }
        else{
            return false;
        }

    }

};





#endif //TRIES_TRIES_H
