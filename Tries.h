#ifndef TRIES_TRIES_H
#define TRIES_TRIES_H
#include <map>
#include <string>
#include <queue>
using namespace std;

struct Node{
    bool is_word = false;
    map<char,Node*> characters;
    Node() = default;
    ~Node() = default;
};


struct Trie{
    Node* root = new Node;

    Trie() = default;

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
                q.pop();

                --nodos;
            }
            cout << endl;
        }
    }


    void insert(string word){
        if(root->characters.size() == 0){
            auto aux = root;
            for(int i=0; i<word.size(); ++i){
                pair aux_pair(word[i], new Node);
                aux->characters.insert(aux_pair);
                aux = aux->characters[word[i]];
            }
            aux->is_word = true;
        }
        else{
            auto aux = root;
            int track = 0;
            for(int i=0; i<word.size(); i++) {
                if(!search_in_node(word[i],aux->characters)){
                    pair aux_pair(word[i], new Node);
                    aux->characters.insert(aux_pair);
                    aux = aux->characters[word[i]];
                }
                else{
                    aux = aux->characters[word[i]];
                }
            }
            aux->is_word = true;
        }
    }

    bool search_complete_word(string word){
        auto aux = root;
        bool fail_case = false;
        for(int i = 0; i<word.size(); ++i){
            for (auto it = aux->characters.begin(); it!= aux->characters.end(); ++it){
                if (word[i] == it->first){
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

    bool search_by_prefix(string word){
        auto aux = root;
        bool fail_case = false;
        for(int i = 0; i<word.size(); ++i){

            for (auto it = aux->characters.begin(); it!= aux->characters.end(); ++it){
                if (word[i] == it->first){
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

    bool search_in_node(char c, map<char,Node*> characters){
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
