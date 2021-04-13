//
//  NFA_DFA.cpp
//  regularExp_NFA
//
//  Created by 陈梓玮 on 2021/4/13.
//

#include "NFA_DFA.hpp"

set<int> DFAConstructor:: e_closure(set<int> T)     //集合扔进去，返回一个进行eclosure后的集合
{
    queue<int> q;
    set<int> temp_set;
    for (set<int>::iterator it = T.begin(); it != T.end(); ++it) {
        q.push(*it);
        temp_set.insert(*it);
    }
    bool *visited = new bool[NFA_set.size()];
    memset(visited, 0, sizeof(bool)*NFA_set.size());    //ini
    while (!q.empty()) {
        int n = q.front();  q.pop();
        NFANode* cur = NFA_set[n];
        for (int i = 0; i < cur->e_closure_set.size(); ++i) {
            if (visited[i] == false) {
                int s = cur->e_closure_set[i];
                q.push(s);              //应该不会死循环（死循环的情况是出现了e环
                temp_set.insert(s);     //set中重复的不会插入
                visited[i] = true;
            }
        }
    }
    return temp_set;
}

set<int> DFAConstructor::move(char t, set<int> T)
{
    set<int> temp_set;
    for (set<int>::iterator it = T.begin(); it != T.end(); ++it) {      //遍历这个NFA集合所有节点，检查节点的转换char是否为所需的
        int s = *it;
        if(NFA_set[s]->trans_char ==  t)
            temp_set.insert(NFA_set[s]->next_num);
    }
    return temp_set;
}

void DFAConstructor::construction()
{
    if (NFA_set.size() == 0)    return;
    
    set<int> temp;  temp.insert(0);
    set<int> first = e_closure(temp);           //第一个初态做一个e闭包
    set<int> t = first;
    for (int src = 0; src < NFA_set.size(); ++src) {                      //子集法
        t.clear();  t.insert(src);
        for (int j = 0 ; j < terminal_symbol.size(); ++j) {
             set<int>tempt = e_closure(move(terminal_symbol[j], t));
            if (tempt.empty())
                continue;
            
            if (dfa_set.find(tempt) == dfa_set.end()){
                dfa_set.insert(pair<set<int>, int>(tempt,dfa_num++));//将第一个插入集合
                DFAEdge temp(src,terminal_symbol[j],dfa_num);
                dfa.push_back(temp);
            }
            else{
                cout<<"有重复子集"<<endl;
                
            }
    }
        }


}
void DFAConstructor::output()
{
    for (int i = 0; i< dfa.size(); ++i) {
        cout<<dfa[i].src_sta<<dfa[i].trans<<dfa[i].des_sta<<endl;
    }
}
