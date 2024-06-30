/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"


//helpers
void eval_node(ExprTreeNode* root,SymbolTable* symtable){
    string type = root->type;
    if(type=="VAL"){
        root->evaluated_value = new UnlimitedRational(root->val->get_p(),root->val->get_q());
    }
    else if(type=="VAR"){
        root->evaluated_value = symtable->search(root->id);
        root->evaluated_value = new UnlimitedRational(root->evaluated_value->get_p(),root->evaluated_value->get_q());
    }
    else if(type=="ADD"){
        eval_node(root->left,symtable);
        eval_node(root->right,symtable);
        root->evaluated_value=UnlimitedRational::add(root->left->evaluated_value,root->right->evaluated_value);
    }
    else if(type=="SUB"){
        eval_node(root->left,symtable);
        eval_node(root->right,symtable);
        root->evaluated_value=UnlimitedRational::sub(root->left->evaluated_value,root->right->evaluated_value);
    }
    else if(type=="MUL"){
        eval_node(root->left,symtable);
        eval_node(root->right,symtable);
        root->evaluated_value=UnlimitedRational::mul(root->left->evaluated_value,root->right->evaluated_value);
    }
    else if(type=="DIV"){
        eval_node(root->left,symtable);
        eval_node(root->right,symtable);
        root->evaluated_value=UnlimitedRational::div(root->left->evaluated_value,root->right->evaluated_value);
    }
    else if(type==":="){
        eval_node(root->right,symtable);
        symtable->insert(root->left->id,new UnlimitedRational(root->right->evaluated_value->get_p(),root->right->evaluated_value->get_q()));
    }
}


Evaluator::Evaluator(){
    expr_trees=vector<ExprTreeNode*>();
    symtable = new SymbolTable();
}

Evaluator::~Evaluator(){
    for(ExprTreeNode* root:expr_trees){
        delete root;
    }
    delete symtable;
}

void Evaluator::parse(vector<string> code){
    ExprTreeNode* root = new ExprTreeNode(),*opr;
    UnlimitedRational *temp=NULL;
    UnlimitedInt *temp2;
    root->left = new ExprTreeNode("VAR",temp);
    root->left->id=code[0];
    vector<ExprTreeNode*> stack;
    for(int i=2,l=code.size();i<l;i++){
        if(code[i]=="(")stack.push_back(NULL);
        else if(code[i]=="+"){
            opr=new ExprTreeNode("ADD",temp);
            opr->left = stack[stack.size()-1];
            stack.pop_back();
            stack.push_back(opr);
        }
        else if(code[i]=="-"){
            opr=new ExprTreeNode("SUB",temp);
            opr->left = stack[stack.size()-1];
            stack.pop_back();
            stack.push_back(opr);
        }
        else if(code[i]=="*"){
            opr=new ExprTreeNode("MUL",temp);
            opr->left = stack[stack.size()-1];
            stack.pop_back();
            stack.push_back(opr);
        }
        else if(code[i]=="/"){
            opr=new ExprTreeNode("DIV",temp);
            opr->left = stack[stack.size()-1];
            stack.pop_back();
            stack.push_back(opr);
        }
        else if(code[i]=="%"){
            opr=new ExprTreeNode("MOD",temp);
            opr->left = stack[stack.size()-1];
            stack.pop_back();
            stack.push_back(opr);
        }
        else if(code[i]==")"){
            if(stack[stack.size()-2]){
                opr = stack[stack.size()-2];
                opr->right=stack[stack.size()-1];
                stack.pop_back();
                stack.pop_back();
                stack.pop_back();
                stack.push_back(opr);
            }
            else{
                opr = stack[stack.size()-1];
                stack.pop_back();
                stack.pop_back();
                stack.push_back(opr);
            }
        }
        else if(code[i][0]>='0' && code[i][0]<='9'){
            temp2 = new UnlimitedInt(code[i]);
            stack.push_back(new ExprTreeNode("VAL",temp2));
            delete temp2;
            temp2=NULL;
        }
        else{
            opr = new ExprTreeNode("VAR",temp);
            opr->id=code[i];
            stack.push_back(opr);
        }
    }
    root->right = stack[0];
    expr_trees.push_back(root);
}

void Evaluator::eval(){
    if(!expr_trees.empty()){
        ExprTreeNode* root = expr_trees[expr_trees.size()-1];
        eval_node(root,symtable);
    }
}




//debug helper


// #include<iostream>


// void print(ExprTreeNode* root){
//     std::cout<<root->type;
//     if(root->val)std::cout<<" "<<root->val->get_frac_str();
//     if(root->evaluated_value)std::cout<<" "<<root->evaluated_value->get_frac_str();
//     cout<<endl;
//     if(root->left)print(root->left);
//     if(root->right)print(root->right);
// }


// int main(){
//     Evaluator A;
//     vector<string> S1 = {"a",":=","5"};
//     vector<string> S = {"v",":=","(","(","a","+","3",")","*","2",")"};
//     A.parse(S1);
//     A.eval();
//     ExprTreeNode* root=A.expr_trees[0];
//     print(root);
//     A.parse(S);
//     cout<<"parsed"<<endl;
//     root=A.expr_trees[1];
//     print(root);
//     A.eval();
//     cout<<"eval"<<endl;
//     root=A.expr_trees[1];
//     print(root);
//     // cout<<A.symtable->get_size()<<endl;
//     // cout<<A.symtable->get_root()->key<<endl;
//     // cout<<A.symtable->search("x")->get_frac_str()<<endl;
// }