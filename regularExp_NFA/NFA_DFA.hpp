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
    set<int> src_sta;
    char trans = '$';
    set<int> des_sta;
    DFAEdge(set<int> s, char t, set<int> d):src_sta(s), trans(t), des_sta(d){}
};

class DFAConstructor
{
    int dfa_num = 0;
    vector<NFANode*> NFA_set;
    vector<DFAEdge> dfa;
    set<int> DFA_node;  //节点
    map<set<int>, int> dfa_set;  //用于标记DFA，防止集合重复
    vector<char> terminal_symbol;   //终态符
    
    
    vector<vector<int>> dfa_matrix;
    vector<char> dfa_trans;
public:
    //constructor
    DFAConstructor(vector<char>& ter_sym, vector<NFANode*>& NFA_s):terminal_symbol(ter_sym), NFA_set(NFA_s){}
    set<int> e_closure(set<int> T);
    set<int> move(char t, set<int> T);
    void construction();
    void output();
};
#endif /* NFA_DFA_hpp */
