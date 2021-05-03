//
//  NFA_DFA.hpp
//  regularExp_NFA
//
//  Created by 陈梓玮 on 2021/4/13.
//

#ifndef NFA_DFA_hpp
#define NFA_DFA_hpp

#include "Header.h"
#include "NFAConstructor.hpp"
struct DFAEdge{
    set<int> src_sta;//源dfa集合
    char trans = '$';//转换字符
    set<int> des_sta;//源dfa目的集合
    DFAEdge(set<int> s, char t, set<int> d):src_sta(s), trans(t), des_sta(d){}
    int new_src_num;//用于标记新集合名字
    int new_des_num;//用于标记新集合名字通过trans后的集合名字
    bool is_end_state;//标记是否为终态
};

class DFAConstructor
{
    int begin_state;
    int end_state;
    int dfa_num = 0;
    vector<NFANode*> NFA_set;
    vector<DFAEdge> dfa;
    set<int> DFA_node;  //节点
    vector<char> terminal_symbol;   //终态符
    
    map<set<int>, int> new_DFA;//重新命名后的DFA集合,名字为map第二个参数(用于标记DFA，防止集合重复)
    vector<vector<int>> dfa_matrix;
    vector<char> dfa_trans;
public:
    //constructor
    DFAConstructor(vector<char>& ter_sym, vector<NFANode*>& NFA_s, int begin_st, int end_sta):terminal_symbol(ter_sym), NFA_set(NFA_s), begin_state(begin_st), end_state(end_sta){}
    set<int> e_closure(set<int> T);
    set<int> move(char t, set<int> T);
    void construction();
    void output();
    
    
    //MiniDFA接口
    
    map<char, int>trans_to_index;
    vector<vector<int>> DFAmatrix;
};
#endif /* NFA_DFA_hpp */
