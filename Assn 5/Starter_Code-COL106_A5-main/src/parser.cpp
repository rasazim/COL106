/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

//Write your expression below this line

Parser::Parser(){
    symtable = new SymbolTable();
    expr_trees=  vector<ExprTreeNode*>();
    last_deleted=-1;
}

void Parser::parse(vector<string> expression){
    ExprTreeNode* root = new ExprTreeNode(),*opr;
    int temp2;
    if(expression[0]=="del") root->left = new ExprTreeNode("DEL",0);
    else if(expression[0]=="ret") root->left = new ExprTreeNode("RET",0);
    else{
        root->left = new ExprTreeNode("VAR",0);
        root->left->id=expression[0];
    }
    vector<ExprTreeNode*> stack;
    for(int i=2,l=expression.size();i<l;i++){
        if(expression[i]=="(")stack.push_back(NULL);
        else if(expression[i]=="+"){
            opr=new ExprTreeNode("ADD",0);
            opr->left = stack[stack.size()-1];
            stack.pop_back();
            stack.push_back(opr);
        }
        else if(expression[i]=="-"){
            opr=new ExprTreeNode("SUB",0);
            opr->left = stack[stack.size()-1];
            stack.pop_back();
            stack.push_back(opr);
        }
        else if(expression[i]=="*"){
            opr=new ExprTreeNode("MUL",0);
            opr->left = stack[stack.size()-1];
            stack.pop_back();
            stack.push_back(opr);
        }
        else if(expression[i]=="/"){
            opr=new ExprTreeNode("DIV",0);
            opr->left = stack[stack.size()-1];
            stack.pop_back();
            stack.push_back(opr);
        }
        else if(expression[i]=="%"){
            opr=new ExprTreeNode("MOD",0);
            opr->left = stack[stack.size()-1];
            stack.pop_back();
            stack.push_back(opr);
        }
        else if(expression[i]==")"){
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
        else if(expression[i][0]=='-' || (expression[i][0]>='0' && expression[i][0]<='9')){
            temp2 = stoi(expression[i]);
            stack.push_back(new ExprTreeNode("VAL",temp2));
        }
        else{
            opr = new ExprTreeNode("VAR",0);
            opr->id=expression[i];
            stack.push_back(opr);
        }
    }
    root->right = stack[0];
    expr_trees.push_back(root);
}

Parser::~Parser(){
    // delete symtable;
}
