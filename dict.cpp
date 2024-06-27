// Do NOT add any other includes
#include "dict.h"
#include <iostream>
using namespace std;



long long int pow(int p,int i){
    int ans = 1;
    for(int j=0;j<i;j++){
        ans=ans*p;
    }

    return p;
}

int geth(AVLNode* node){
    if(node==NULL){
        return -1;
    }
    else{
        return node->height;
    }
}

int getheight(AVLNode* node){
    if(node==NULL){
        return -1;
    }
    else{
        return node->height;
    }
}

AVLNode* succ(AVLNode* node){
    AVLNode* temp = node->right;
    
    while(temp->left!=NULL){
        
        temp = temp->left;
    }
    return temp;
}

void annihilator(AVLNode* r){
    if(r==NULL){
        return;
    }
    else{
        annihilator(r->right);
        annihilator(r->left);
        delete r;
    }
}

AVLNode::AVLNode(){
    key = "";
    par = NULL;
    left = NULL;
    right = NULL;
    height = 0;
    count=1;
}

AVLNode::AVLNode(string k){
    key = k;
    par = NULL;
    left = NULL;
    right = NULL;
    count=1;
    height = 0;
}


AVLNode::~AVLNode(){
    key = "";
    par = NULL;
    left = NULL;
    right = NULL;
    height = 0;
}

AVLNode* AVLNode::LeftLeftRotation(){
    if(this->left->right!=NULL){                             
        this->left->right->par = this;
    }
    this->left->par = this->par;
    this->par = this->left;
    /*SymNode* temp = new SymNode;
    temp = this->left;*/
    this->left = this->left->right;
    this->par->right = this;
    this->height = max(geth(this->left), geth(this->right)) + 1;
    this->par->height = max(geth(this->par->left), geth(this->par->right)) + 1;
    return this->par;
}

AVLNode* AVLNode::RightRightRotation(){
    if(this->right->left!=NULL){                             
        this->right->left->par = this;
    }
    this->right->par = this->par;
    this->par = this->right;
    /*SymNode* temp = new SymNode;
    temp = this->right;*/
    this->right = this->right->left;
    this->par->left = this;
    this->height = max(geth(this->left), geth(this->right)) + 1;
    this->par->height = max(geth(this->par->left), geth(this->par->right)) + 1;
    return this->par;
}


AVLNode* AVLNode::LeftRightRotation(){
    this->left = this->left->RightRightRotation();
    return this->LeftLeftRotation();
}

AVLNode* AVLNode::RightLeftRotation(){
    this->right =this->right->LeftLeftRotation();
    return this->RightRightRotation();
}

string AVLNode::get_key(){
    return key;
}
AVLTree::AVLTree(){

}

AVLTree::~AVLTree(){
    annihilator(root);
}

AVLNode* AVLTree::search(string k){
    AVLNode* r = root;

    while((r!=NULL)&&(r->key!=k)){
        if(r->key>k){
            r = r->left;
        }
        else{
            r= r->right;
        }
    }

    if(r==NULL){
        return NULL;
    }

    else{
        
        return r;
    }
}

void AVLTree::insert(string k){
    /*cout<<"heights before insert of "<<k<<endl;
    heightprint(root);*/
    
    AVLNode* r = root;
    AVLNode* parent = r;
    //check if root is null
    if(root==NULL){
        
        root = new AVLNode(k);
        root->height=0;
        size=1;
        return;
    }

    //find location
    else{
        while((r!=NULL)){
            
            
            if(r->key>k){
                
                parent = r;
                
                r = r->left;
            }
            else{
            
                parent = r;

                r = r->right;
                
            }
        
        }

    }

    
    r =  new AVLNode(k);
    
    if(parent->key>r->key){
        parent->left = r;
        r->par = parent;
        
    }
    else{
        parent->right = r;
        r->par = parent;
    }

    size++;
    
    
    
    //height_update


    while(parent!=NULL){
        
        
        parent->height = max(getheight(parent->left),getheight(parent->right)) +1;
        
        
        parent = parent->par;
    }
    //cout<<"updated heights after INSERT of "<<k<<endl;
    //heightprint(root);
    //rotations
    AVLNode* temp = r;



    //go up while tree is balanced
    while(  (temp->par->par!=NULL) && ( (  ( getheight(temp->par->par->left) )-(getheight(temp->par->par->right))<=1 )&& (  (getheight(temp->par->par->left))-(getheight(temp->par->par->right))>=-1 ) ) ){
        /*cout<<"balanced at "<<temp->par->par->key<<" for insert of "<<k<<endl;*/
        temp = temp->par;

    }
    

    //reached root and no imblancing present
    if(temp->par->par == NULL){
       
        
        return;
    }

    //balance tree at imbalance and then update height then done.
    else{

        
        //LEFTLEFT
        if((temp->par->par->left!=NULL)&&(temp->par->par->left->left == temp)){
            if(temp->par->par!=root){
                
                
                AVLNode* p = temp->par->par->LeftLeftRotation();
                if(p->par->left==p->right){
                    p->par->left=p;
                }
                else{
                    p->par->right=p;
                }

                //height update
                while(p!=NULL){
                    p->height = max(getheight(p->left),getheight(p->right))+1;
                    p = p->par;
                }
            }
            else{

                /*temp->par->right=temp->par->par;
                temp->par->par=NULL;
                temp->par->right->par=temp->par;
                temp->par->right->left=NULL;
                root = temp->par;
                root->height = max(getheight(root->right),getheight(root->left))+1;*/

                if(temp->par->right!=NULL){
                    temp->par->right->par  = temp->par->par;
                }
                temp->par->par->left=temp->par->right;
                temp->par->right = temp->par->par;
                temp->par->right->par= temp->par;
                temp->par->par = NULL;
                root = temp->par;
                root->right->height = max(getheight(root->right->left),getheight(root->right->right))+1;
                root->height = max(getheight(root->right),getheight(root->left))+1;
                
                
            }
               
                
                
        }

        //RIGHTRIGHT
        else if((temp->par->par->right!=NULL)&&(temp->par->par->right->right == temp)){
            if(temp->par->par==root){
                

                if(temp->par->left!=NULL){
                    temp->par->left->par  = temp->par->par;
                }
                temp->par->par->right=temp->par->left;
                temp->par->left = temp->par->par;
                temp->par->left->par= temp->par;
                temp->par->par = NULL;
                root = temp->par;
                root->left->height = max(getheight(root->left->right),getheight(root->left->left))+1;
                root->height = max(getheight(root->right),getheight(root->left))+1;
                
                
            }
            else{
                AVLNode*p = temp->par->par->RightRightRotation();
                if(p->par->left==p->left){
                    p->par->left=p;
                }
                else{
                    p->par->right = p;
                }
                //height update
                while(p!=NULL){
                    p->height = max(getheight(p->left),getheight(p->right))+1;
                    p = p->par;
                }

                
            }


        }

        //LEFTRIGHT
        else if((temp->par->par->left!=NULL)&&(temp->par->par->left->right==temp)){
            
            if(temp->par->par!=root){
                
                AVLNode* t = temp->par->par->LeftRightRotation();
                if(t->par->left==t->right){
                    t->par->left = t;
                }
                else{
                    t->par->right = t;
                }
                //height update
                while(t!=NULL){
                    t->height = max(getheight(t->left),getheight(t->right))+1;
                    t=t->par;
                }

            }
            else{
                root =temp->par->par->LeftRightRotation();
                root->height = max(getheight(root->right),getheight(root->left))+1;

            }
    
        }

        //RightLeft
        else{
            
            if(temp->par->par!=root){
                
                AVLNode* t = temp->par->par->RightLeftRotation();
                if(t->par->left==t->left){
                    t->par->left = t;
                }
                else{
                    t->par->right = t;
                }
                //height update
                while(t!=NULL){
                    t->height = max(getheight(t->left),getheight(t->right))+1;
                    t=t->par;
                }

            }
            else{
                root = temp->par->par->RightLeftRotation();
                root->height = max(getheight(root->right),getheight(root->left))+1;

            }

            
        }


    }

    /* cout<<"updated height aft ins and rot"<<endl;
    heightprint(root); */


    
        
    
    
} 

void AVLTree::remove(string k){
    /*cout<<" heights bef removal of "<<k<<endl;
    heightprint(root);*/
    
    AVLNode* r = root;
    AVLNode* parent=r->par;
    //find the node
    while((r!=NULL)&&(r->key!=k)){
        parent = r;
        if(r->key>k){
            r = r->left;
        }
        else{
            r= r->right;
        }
    }
    if(r==NULL){
        return;
    }


    //no child
    if((r->left==NULL)&&(r->right==NULL)){
        /*cout<<"no child case"<<endl;*/
        
        size--;
        parent = r->par;
        AVLNode* b = r->par;
        if(r==root){
            
            root=NULL;
            return;
        }

        if(r->par->left==r){
            
            r->par->left = NULL;
            delete r;
        }
        else{
            r->par->right=NULL;
            delete r;
        }
        /*cout<<"root is "<<root->key<<endl;*/
    }

    //two child
    else if((r->left!=NULL)&&(r->right!=NULL)){
        /*cout<<"Two case wala remove"<<endl;*/
        
        parent = r->par;
        AVLNode* s = succ(r);
        string x = s->key;
        
        /*cout<<"removing succ "<<s->key<<endl;*/
        remove(x);

        r->key = x;
      
        /*cout<<"root is "<<root->key<<endl;*/
    }

    //one child
    else {
        
        size--;
        if(r==root){
        
            if(r->left!=NULL){
                AVLNode* child= r->left;
                child->par = NULL;
                delete r;
                root = child;
            }
            else{
                AVLNode* child = r->right;
                child->par = NULL;
                delete r;
                root = child;
            }

        }
        else{
            parent = r->par;

            if((r->par->left==r)&&(r->left!=NULL)){
                r->par->left =r->left;
                r->left->par = r->par;
                delete r;
            }
            else if((r->par->left==r)&&(r->right!=NULL)){
                r->par->left = r->right;
                r->right->par  = r->par;
                delete r;
            }
            else if((r->par->right==r)&&(r->left!=NULL)){
                r->par->right = r->left;
                r->left->par = r->par;
                delete r;
            }
            else{
                r->par->right = r->right;
                r->right->par = r->par;
                delete r;
            }

        }
        

    }

    //update height;

    AVLNode* b = parent;
    while(parent!=NULL){
        parent->height= 1+ max(getheight(parent->left),getheight(parent->right));
        
        /*if((parent->left!=NULL)&&(parent->right!=NULL)){
            parent->height = 1 + max(getheight(parent->left), getheight(parent->right));

        }
        else if((parent->left==NULL)&&(parent->right!=NULL)){
            parent->height = 1 + getheight(parent->right);
        }
        else{
            parent->height = 1 + getheight(parent->left);
        }*/

        parent = parent->par;
    }
    /*cout<<"updated heights after removal of "<<k<<endl;
    heightprint(root);
    cout<<"new root after remove of key "<<k<<endl;
    cout<<root->key<<endl;*/
    //check imbalance

    while(b!=NULL){

        if((getheight(b->right)-getheight(b->left)>=-1)&&(getheight(b->right)-getheight(b->left)<=1)){
            
            b = b->par;

        }

        else{
            
            if(getheight(b->left)>getheight(b->right)){
                
                if(getheight(b->left->left)>getheight(b->left->right)){
            
                    AVLNode* t =b->LeftLeftRotation();
                    if(t->par!=NULL){
                        if(t->par->right ==b){
                            t->par->right =t;
                        }
                        else{
                            t->par->left= t;
                        }
                    }
                    else{
                        root = t;
                    }

                    AVLNode* c = t->par;

                    while(c!=NULL){
                        c->height = max(getheight(c->right),getheight(c->left)) +1;
                        c = c->par;
                    }
                    b=t->par;
                    //tree may be unbalanced so go up



                }
                
                else if(getheight(b->left->left)<getheight(b->left->right)){
                
                    AVLNode* t = b->LeftRightRotation();
                    if(t->par!=NULL){
                        if(t->par->left==b){
                            t->par->left =t;
                        }
                        else{
                            t->par->right = t;
                        }
                    }
                    else{
                        root =t;
                    }
                    AVLNode* c = t->par;
                    while(c!=NULL){
                        c->height = max(getheight(c->right),getheight(c->left)) +1;
                        c = c->par;
                    }
                    b=t->par;
                        //tree may be unbalanced so go up




                }

                else{
                    AVLNode* t=b->LeftLeftRotation();
                    if(t->par!=NULL){
                        if(t->par->right==b){
                            t->par->right = t;
                        }
                        else{
                            t->par->left = t;
                        }
                    }
                    else{
                        root = t;
                    }
                    AVLNode* c= t->par;
                    b=t->par;
                    while(c!=NULL){
                        c->height = max(getheight(c->right),getheight(c->left)) +1;
                        c = c->par;
                    }
                    //after this tree will be balanced



                }
            }
            else{
                
                if(getheight(b->right->right)<getheight(b->right->left)){
                    
                    AVLNode* t = b->RightLeftRotation();

                    if(t->par!=NULL){
                        if(t->par->left==b){
                            t->par->left =t;
                        }
                        else{
                            t->par->right = t;
                        }
                    }
                    else{
                        
                        root = t;
                    }
                    AVLNode* c = t->par;
                    while(c!=NULL){
                        c->height = max(getheight(c->right),getheight(c->left)) +1;
                        c = c->par;
                    }
                    b = t->par;
                    //tree may still be unbalanced so while loop will go up


                }
                
                else if(getheight(b->right->right)>getheight(b->right->left)){
                    
                    AVLNode* t =b->RightRightRotation();
                    if(t->par!=NULL){
                        if(t->par->right ==b){
                            t->par->right =t;
                        }
                        else{
                            t->par->left= t;
                        }
                    }
                    else{
                        root = t;
                    }
                    AVLNode* c = t->par;

                    while(c!=NULL){
                        c->height = max(getheight(c->right),getheight(c->left)) +1;
                        c = c->par;
                    }

                    b = t->par;
                    // after this the tree may be unbalanced so aage jana padega while loop will take care
                }

                else{
                
                    AVLNode* t = b->RightRightRotation();
                    
                    if(t->par!=NULL){
                        if(t->par->right==b){
                            t->par->right = t;
                        }
                        else{
                            t->par->left = t;
                        }
                    }
                    
                    else if(t->par==NULL){
                        root = t;
                    }
                    
                    b= t->par;
                    AVLNode* c = t->par;
                    while(c!=NULL){
                        c->height = max(getheight(c->right),getheight(c->left)) +1;
                        c = c->par;
                    }
                    
                    //after this tree will be balanced

                }
            }
            /*cout<<"after rot : tree is "<<endl;
            deb(root);
            heightprint(root);
            cout<<"next step"<<endl;*/

        }
        
    }

    return;
}

int AVLTree::get_size(){
    return size;
}

AVLNode* AVLTree::get_root(){
    return root;
}

int HashTable::hash(string k){

    int s=0;
    int prime= 3;
    int m = 100003;

    for(int i=0;i<k.size();i++){
    
        s+=((int(k[i])-'0' + 1)*(int((pow(prime,i)))*((i*i)+1)))%m;
    }
    
    return s;

}

HashTable::HashTable(){
    cap=100003;

    table.resize(0);
    //cout<<table.size()<<endl;
    for(int i=0;i<100003;i++){
      

        table.push_back(NULL);
  
        
    }
}
HashTable::~HashTable(){
    while(table.size()!=0){
        AVLTree* n = table.back();
        delete n;
        table.pop_back();
    }
    table.clear();
}



void HashTable::insertword(string word){
   
 
    int hashval =hash(word);
    



    

    if((this->table)[hashval]==NULL){
        
        //AVLTree* tree = new AVLTree();
        //AVLNode* r = new AVLNode(word);
        //tree->root = r;
        AVLTree* tree = new AVLTree();
        tree->insert(word);
        (this->table)[hashval]= tree;
        /*if((this->table)[hashval]==NULL){
            cout<<"Still null"<<endl;
        }
        else{
            cout<<"inserted, hash= "<<hashval<<" word = "<<word<<endl;
        }*/


        //cout<<table[hashval]->get_root()->get_key()<<endl;
        //cout<<hashval<<endl;

    }
    else{
        AVLNode* ans = (this->table)[hashval]->search(word);
        if(ans==NULL){
            (this->table)[hashval]->insert(word);
        }
        else{
            ans->count++;
        }  
    }
    /*cout<<"check vector :"<<endl;
    for(int i=0;i<table.size();i++){
        if((this->table)[i]!=NULL){
            cout<<(this->table)[i]->get_root()->get_key()<<endl;
        }
    }*/


}


void inorder(AVLNode* node, std::ofstream &outFile){
    if(node==NULL){
        return;
    }
    else{
        inorder(node->left, outFile);
        outFile<<node->key<<", "<<node->count<<"\n";
        inorder(node->right,outFile);
        return;
    }
}

Dict::Dict(){

   HashTable hashtable = HashTable();

}

Dict::~Dict(){

}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    // Implement your function here
    int i=0;
    string w = "";
    while(i<sentence.size()){
        
        while((i<sentence.size())&&(sentence[i]!=' ')&&(sentence[i]!='.')&&(sentence[i]!=',')&&(sentence[i]!='-')&&(sentence[i]!=':')&&(sentence[i]!='!')&&(sentence[i]!='\"')&&(sentence[i]!='\'')&&(sentence[i]!='(')&&(sentence[i]!=')')&&(sentence[i]!='?')&&(sentence[i]!='_')&&(sentence[i]!='[')&&(sentence[i]!=']')&&(sentence[i]!=';')&&(sentence[i]!='@')&&(sentence[i]!='{')&&(sentence[i]!='}')){
            w+=(char)tolower(sentence[i]);
            i++;
        }
        

        /*vector<AVLTree*>* t = hashtable->table;

       
        int hashval = hashtable->hash(w);
        if((*t)[hashval]==NULL){
            AVLTree* tree = new AVLTree();
            AVLNode* r = new AVLNode();
            tree->root = r;
            (*t)[hashval]=tree;
        }*/
        hashtable.insertword(w);
        //vector<AVLTree*> t = hashtable.table;

        w="";
        i++;


    } 

    return;
}

int Dict::get_word_count(string word){
    int u = hashtable.hash(word);

    if(hashtable.table[u]==NULL){
        return 0;
    }
    else{
        AVLNode* node = (hashtable.table)[u]->search(word);
        if(node==NULL){
            return 0;
        }
        else{
            return node->count;
        }
    }
    return -1;
}

void Dict::dump_dictionary(string filename){
    // Implement your function here 

    std::ofstream outFile;
    outFile.open(filename);

    for(int i=0;i<100003;i++){
        if(hashtable.table[i]==NULL){

        }
        else{
            inorder(hashtable.table[i]->get_root(), outFile);
        }
    }

    return;
}

