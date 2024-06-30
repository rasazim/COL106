#pragma once
#include <iostream>
#include <fstream>
#include "Node.h"
#include "dict.h"
#include "search.h"

using namespace std;
/*
part2
*/
struct stopnode{
    public:
    stopnode** children;
    bool end;

    stopnode(){
        children = new stopnode*[26];
        for(int i=0;i<26;i++)children[i]=NULL;
        end=false;
    }

    ~stopnode(){
        for(int i=0;i<26;i++)if(children[i])delete children[i];
        delete[] children;
        children=NULL;
    }
};

class Stop{
    public:
    stopnode* root;

    void insert(string word){
        stopnode* at=root;
        for(char c:word){
            if(at->children[c-'a'])at=at->children[c-'a'];
            else{
                at->children[c-'a']=new stopnode();
                at = at->children[c-'a'];
            }
        }
        at->end=true;
    }

    bool operator()(string word){
        stopnode* at=root;
        for(char c:word){
            if(at->children[c-'a'])at=at->children[c-'a'];
            else return false;
        }
        return at->end;
    }

    Stop(){
        vector<string> stops = {"a","able","about","above","abst","accordance","according","accordingly","across","act","actually","added","adj","affected","affecting","affects","after","afterwards","again","against","ah","all","almost","alone","along","already","also","although","always","am","among","amongst","an","and","announce","another","any","anybody","anyhow","anymore","anyone","anything","anyway","anyways","anywhere","apparently","approximately","are","aren","arent","arise","around","as","aside","ask","asking","at","auth","available","away","awfully","b","back","be","became","because","become","becomes","becoming","been","before","beforehand","begin","beginning","beginnings","begins","behind","being","believe","below","beside","besides","between","beyond","biol","both","brief","briefly","but","by","c","ca","came","can","cannot","cant","cause","causes","certain","certainly","co","com","come","comes","contain","containing","contains","could","couldnt","d","date","did","didnt","different","do","does","doesnt","doing","done","dont","down","downwards","due","during","e","each","ed","edu","effect","eg","eight","eighty","either","else","elsewhere","end","ending","enough","especially","et","et-al","etc","even","ever","every","everybody","everyone","everything","everywhere","ex","except","f","far","few","ff","fifth","first","five","fix","followed","following","follows","for","former","formerly","forth","found","four","from","further","furthermore","g","gave","get","gets","getting","give","given","gives","giving","go","goes","gone","got","gotten","h","had","happens","hardly","has","hasnt","have","havent","having","he","hed","hence","her","here","hereafter","hereby","herein","heres","hereupon","hers","herself","hes","hi","hid","him","himself","his","hither","home","how","howbeit","however","hundred","i","id","ie","if","ill","im","immediate","immediately","importance","important","in","inc","indeed","index","information","instead","into","invention","inward","is","isnt","it","itd","itll","its","itself","ive","j","just","k","keep","keeps","kept","kg","km","know","known","knows","l","largely","last","lately","later","latter","latterly","least","less","lest","let","lets","like","liked","likely","line","little","ll","look","looking","looks","ltd","m","made","mainly","make","makes","many","may","maybe","me","mean","means","meantime","meanwhile","merely","mg","might","million","miss","ml","more","moreover","most","mostly","mr","mrs","much","mug","must","my","myself","n","na","name","namely","nay","nd","near","nearly","necessarily","necessary","need","needs","neither","never","nevertheless","new","next","nine","ninety","no","nobody","non","none","nonetheless","noone","nor","normally","nos","not","noted","nothing","now","nowhere","o","obtain","obtained","obviously","of","off","often","oh","ok","okay","old","omitted","on","once","one","ones","only","onto","or","ord","other","others","otherwise","ought","our","ours","ourselves","out","outside","over","overall","owing","own","p","page","pages","part","particular","particularly","past","per","perhaps","placed","please","plus","poorly","possible","possibly","potentially","pp","predominantly","present","previously","primarily","probably","promptly","proud","provides","put","q","que","quickly","quite","qv","r","ran","rather","rd","re","readily","really","recent","recently","ref","refs","regarding","regardless","regards","related","relatively","research","respectively","resulted","resulting","results","right","run","s","said","same","saw","say","saying","says","sec","section","see","seeing","seem","seemed","seeming","seems","seen","self","selves","sent","seven","several","shall","she","shed","shell","shes","should","shouldnt","show","showed","shown","showns","shows","significant","significantly","similar","similarly","since","six","slightly","so","some","somebody","somehow","someone","somethan","something","sometime","sometimes","somewhat","somewhere","soon","sorry","specifically","specified","specify","specifying","still","stop","strongly","sub","substantially","successfully","such","sufficiently","suggest","sup","sure","t","take","taken","taking","tell","tends","th","than","thank","thanks","thanx","that","thatll","thats","thatve","the","their","theirs","them","themselves","then","thence","there","thereafter","thereby","thered","therefore","therein","therell","thereof","therere","theres","thereto","thereupon","thereve","these","they","theyd","theyll","theyre","theyve","think","this","those","thou","though","thoughh","thousand","throug","through","throughout","thru","thus","til","tip","to","together","too","took","toward","towards","tried","tries","truly","try","trying","ts","twice","two","u","un","under","unfortunately","unless","unlike","unlikely","until","unto","up","upon","ups","us","use","used","useful","usefully","usefulness","uses","using","usually","v","value","various","ve","very","via","viz","vol","vols","vs","w","want","wants","was","wasnt","way","we","wed","welcome","well","went","were","werent","weve","what","whatever","whatll","whats","when","whence","whenever","where","whereafter","whereas","whereby","wherein","wheres","whereupon","wherever","whether","which","while","whim","whither","who","whod","whoever","whole","wholl","whom","whomever","whos","whose","why","widely","willing","wish","with","within","without","wont","words","world","would","wouldnt","www","x","y","yes","yet","you","youd","youll","your","youre","yours","yourself","yourselves","youve","z","zer"};
        root=new stopnode();
        for(string word: stops)insert(word);
        stops.clear();
    }

    ~Stop(){
        delete root;
    }
};
/*
end part2
*/


class topK {
public:
    vector<Para*> heap;
    int size = 0;
    int k = 0;

    topK(vector<Para*> v, int num) {
        k = num;
        for (int i = 0;i < k;i++) heap.push_back(v[i]);
        size = k;
        for (int i = size/2 - 1;i >= 0;i--) heapifyDown(i);
        for (size_t i = k;i < v.size();i++) push(v[i]);
    }

    void heapifyDown(int i) {
        int l = 2*i + 1;
        if (l >= size) return;
        int m = i;
        if (heap[l]->ct < heap[m]->ct) m = l;
        int r = 2*i + 2;
        if (r < size) {
            if (heap[r]->ct < heap[m]->ct) m = r;
        }
        if (i != m) {
            swap(heap[m], heap[i]);
            heapifyDown(m);
        }
    }

    void heapifyUp(int i) {
        if (i <= 0) return;
        int p = (i - 1) / 2;
        if (heap[i]->ct < heap[p]->ct) {
            swap(heap[i], heap[p]);
            heapifyUp(p);
        }
    }
    
    void push(Para* p) {
        if (size < k) {
            heap.push_back(p);
            size++;
            heapifyUp(size-1);
        } else if (heap[0]->ct < p->ct) {
            // cout << heap[0]->ct  << " " << p->ct << "\n";
            heap[0] = p;
            heapifyDown(0);
        }
    }
    Node* getTopK() {
        Node* curr = nullptr;
        for (int i = 0;i < k;i++) {
            Node* tmp = new Node(heap[0]->book_code, heap[0]->page_no, heap[0]->para, -1, 100000*heap[0]->ct);
            tmp->right = curr;
            if (curr) curr->left = tmp;
            curr = tmp;
            size--;
            heap[0] = heap[size];
            heapifyDown(0);
        }
        return curr;
    }
};

class QNA_tool {

private:

    // You are free to change the implementation of this function
    void query_llm(string filename, Node* root, int k, string email, string passwd, string question);
    // filename is the python file which will call ChatGPT API
    // root is the head of the linked list of paragraphs
    // k is the number of paragraphs (or the number of nodes in linked list)
    // API_KEY is the API key for ChatGPT
    // question is the question asked by the user

    // You can add attributes/helper functions here
    Stop stops;

public:

    Dict word_counts;
    Dict word_freq;
    Table paras = Table(1024);

    /* Please do not touch the attributes and
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    
    QNA_tool(); // Constructor
    ~QNA_tool(); // Destructor

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);
    // This function is similar to the functions in dict and search 
    // The corpus will be provided to you via this function
    // It will be called for each sentence in the corpus

    Node* get_top_k_para(string question, int k);
    // This function takes in a question, preprocess it
    // And returns a list of paragraphs which contain the question
    // In each Node, you must set: book_code, page, paragraph (other parameters won't be checked)

    std::string get_paragraph(int book_code, int page, int paragraph);
    // Given the book_code, page number, and the paragraph number, returns the string paragraph.
    // Searches through the corpus.

    void query(string question, string filename);
    // This function takes in a question and a filename.
    // It should write the final answer to the specified filename.

    /* -----------------------------------------*/
    /* Please do not touch the code above this line */

    // You can add attributes/helper functions here
};