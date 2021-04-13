//
//  NFAConstructor.hpp
//  regularExp_NFA
//
//  Created by 陈梓玮 on 2021/4/7.
//

#ifndef NFAConstructor_hpp
#define NFAConstructor_hpp

#include "Header.h"

struct NFANode      //nfa的状态节点
{
    int num;        //节点编号
    char trans_char = '#';    //转移所接受的符号,默认‘#’
    int next_num = -1;      //下一节点， 默认‘-1’即无转移接受符号
    bool isEnd = 0;
    bool isStart = 0;
    vector<int>  e_closure_set;         //存储该节点的e闭包集合
    NFANode(int n, int next_n,char t):num(n),next_num(next_n),trans_char(t){}//有转移接受符号的构造函数
    NFANode(int n):num(n){} //无转移接受符号的构造函数
};
struct NFAEdge      //状态转换边
{
    NFANode* head = nullptr;
    NFANode* next = nullptr;
    NFAEdge(NFANode* h,NFANode* n):head(h),next(n){}
};
class NFAConstrctor
{
private:
    string regular_exp;
    string suffix_exp;
    stack<char> operator_stk;
    char t;
    int stringpointer = 0;
    
    stack<NFAEdge*> NFA_stk;
    char suffix_char;
    int suffix_pointer = 0;
    
    bool start = 0;
public:
    void read(string& s){regular_exp = s;}
    void output(){cout<<suffix_exp<<endl;}
    void transformToSuffix();
    int operatorPriority(const char& t);
    bool getCh();//读到结尾返回0
    
    //后缀转NFA
    
    void createSingleNFA();//遇到符号建立单个NFA
    int NFA_num_cnt = 0;
    void createNFA();//递归的建立起整个NFA
    bool get_suffix_char();
    vector<NFANode*> node_set;
    void output_NFA();
    
    vector<char> terminal_symbol;
};

#endif /* NFAConstructor_hpp */
