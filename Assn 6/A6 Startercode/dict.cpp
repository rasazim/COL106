// Do NOT add any other includes
#include "dict.h"

TrieNode::TrieNode(){
    cnt = 0;
    word = NULL;
    children = new TrieNode[101];
    for (int i=0;i<101;i++){
        children[i] = NULL;
    }
}
TrieNode::~TrieNode(){
for (int i=0;i<101;i++){
    if(children[i]){
        delete children[i];
    }
}
delete [] children;
if(word){delete word;}
}
void TrieNode::insert(string w){
int place;
TrieNode* at = this;
for (char &ch : w){
    place = (int)ch;
    if('A'<=place&& 'Z'>=place){
        place+=32;
        ch+=32;
    }
    if(place>'Z'){
        place-=26;
    }
    if(at->children[place]){
        at = at->children[place];
    }
    else{
        at->children[place] = new TrieNode();
        at = at->children[place];
    }
}
at->cnt++;
at->word= new string(w);

}
Dict::Dict(){
    root = new TrieNode*();
}

Dict::~Dict(){
       delete root;
}
string seperators = " .,-:!\"\'()?[];@";
void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
     string w = "";
     bool sep;
     for (char c: sentence){
        sep = false;
        for(int i=0;i<16;i++){
            if(seperators[i]==c){
                sep = true;
                break;
            }
        }
        if(sep){
            if(w!=""){
                root->insert(w);
                w="";
            }
        }
        else{
            w+=c;
        }
     }
    return;
}

int Dict::get_word_count(string w){
    int place;
    TrieNode* at = root;
    for (char ch : w){
        place = (int)ch;
        if('A'<=place&& 'Z'>=place){
            place+=32;
        }
        if(place>'Z'){
            place-=26;
        }
        if(at->children[place]){
            at = at->children[place];
        }
        else{
            return 0;
        }
    }
    return at->cnt;
}

void print(TrieNode* root,ofstream& fout){
    if(root->word)fout<<(*(root->word))<<","<<root->cnt<<endl;
    for(int i=0;i<101;i++){
        if(root->children[i]){
            print(root->children[i],fout);
        }
    }
}

void Dict::dump_dictionary(string filename){
    ofstream fout;
    fout.open(filename,ios::out);
    print(root,fout);
    fout.close();
}