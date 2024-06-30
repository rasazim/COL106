/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"
// #include "heapnode.cpp"
// #include "minheap.cpp"
// #include "symnode.cpp"
// #include "symtable.cpp"
// #include "exprtreenode.cpp"
// #include "parser.cpp"

//Write your code below this line

void expr_command(ExprTreeNode* root,vector<string> &targ_expr, Parser &targ){
    if(root->right)expr_command(root->right,targ_expr,targ);
    if(root->left)expr_command(root->left,targ_expr,targ);
    if(root->type == "VAR"){
        int mem_id = targ.symtable->search(root->id);
        if(mem_id!=-2)
        targ_expr.push_back("PUSH mem["+to_string(mem_id)+"]");
    }
    else if(root->type == "VAL"){
        targ_expr.push_back("PUSH "+to_string(root->num));
    }
    else{
        targ_expr.push_back(root->type);
    }
}

EPPCompiler::EPPCompiler(){
    targ = Parser();
    memory_size=0;
    output_file="";
    least_mem_loc=MinHeap();
}

EPPCompiler::EPPCompiler(string out_file,int mem_limit){
    output_file = out_file;
    memory_size = mem_limit;
    targ = Parser();
    least_mem_loc=MinHeap();
    for(int i=0;i<memory_size;i++){
        least_mem_loc.push_heap(i);
    }
}

void EPPCompiler::compile(vector<vector<string>> code){
    vector<string> targ_expr;
    // targ = Parser();
    // least_mem_loc = MinHeap();
    // for(int i=0;i<memory_size;i++){
    //     least_mem_loc.push_heap(i);
    // }
    for(vector<string> expression:code){
        targ.parse(expression);
        targ_expr = generate_targ_commands();
        write_to_file(targ_expr);
    }
}

vector<string> EPPCompiler::generate_targ_commands(){
    ExprTreeNode* root = targ.expr_trees.back();
    vector<string> targ_expr;
    string var_id;
    int mem_id;
    if(root->left->type=="DEL"){
        int mem_id = targ.symtable->search(root->right->id);
        if(mem_id!=-2)
        targ_expr.push_back("DEL = mem["+to_string(mem_id)+"]");
    }
    else{
        expr_command(root->right,targ_expr,targ);
        if(root->left->type=="VAR"){
            int mem_id=targ.symtable->search(root->left->id);
            if(mem_id==-2){
                targ.symtable->insert(root->left->id);
                mem_id = least_mem_loc.get_min();
                targ.symtable->assign_address(root->left->id,mem_id);
                least_mem_loc.pop();
            }
            targ_expr.push_back("mem["+to_string(mem_id)+"] = POP");
        }
        else{
            targ_expr.push_back("RET = POP");
        }
    }
    return targ_expr;
}

void EPPCompiler::write_to_file(vector<string> commands){
    ofstream f;
    f.open(output_file,ios::app);
    for(string command:commands){
        f<<command<<endl;
    }
    f.close();
}

EPPCompiler::~EPPCompiler(){
}

// int main(){
//     EPPCompiler A("test1.txt",10);
//     vector<vector<string>> code;
//     code.push_back({"a",":=","(","5","+","6",")"});
//     code.push_back({"a",":=","(","5","+","6",")"});
//     A.compile(code);
// }
