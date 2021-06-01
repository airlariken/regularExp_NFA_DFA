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
    vector<int>  e_closure_set;         //存储该节点的e集合
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
    
    char suffix_char;
    int suffix_pointer = 0;
    bool start = 0;
    
    
public:
    int begin_state = -1;//用于将nfa初态和终态传给接下来的dfa
    int end_state = -1;//同上
    void read(string& s){regular_exp = s;}//读正则表达式
    void output(){cout<<suffix_exp<<endl;}//输出后缀正则表达式
    void transformToSuffix();//中缀转后缀
    int operatorPriority(const char& t);//运算符优先级函数
    bool getCh();//读取单个字符到结尾返回0
    
    
    
    stack<NFAEdge*> NFA_stk;
    vector<char> terminal_symbol;
    vector<NFANode*> node_set;//所有的NFA节点
    //后缀转NFA
    void createSingleNFA();//遇到符号建立单个NFA
    int NFA_num_cnt = 0;
    void createNFA();//递归的建立起整个NFA
    bool get_suffix_char();//读单个后缀正则表达式字符
    void output_NFA();

};

#endif /* NFAConstructor_hpp */
