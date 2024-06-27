// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class AVLNode{
    public:
        string key;
        AVLNode* left=NULL;
        AVLNode* right=NULL;
        AVLNode* par=NULL;
        int height=0;
        int count=1;
        AVLNode();

        AVLNode(string w);

        ~AVLNode();
        AVLNode* LeftLeftRotation(); // case 1
        AVLNode* RightRightRotation(); // case 2
        AVLNode* LeftRightRotation(); // case 3
        AVLNode* RightLeftRotation(); // case 4
        string get_key();
    };


class AVLTree{
    public:
        AVLNode* root;
        int size=0;

        AVLTree();
        ~AVLTree();

        void insert(string word);

        void remove(string word);

        AVLNode* search(string word);

        int get_size();

        AVLNode* get_root();
    };

class HashTable{
public:
    vector<AVLTree* > table;
    int cap;

    HashTable();
    ~HashTable();

    void insertword(string word);

    int hash(string k);

};

class Dict {
private:
    // You can add attributes/helper functions here

public: 
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */

    HashTable hashtable;

    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    int get_word_count(string word);

    void dump_dictionary(string filename);

    /* -----------------------------------------*/


    //helper functions

    
};