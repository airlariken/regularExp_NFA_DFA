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
        if (visited[n] ==true)
            continue;
        visited[n] = true;
        NFANode* cur = NFA_set[n];
        for (int i = 0; i < cur->e_closure_set.size(); ++i) {
            if (visited[cur->e_closure_set[i]] == false) {
                int s = cur->e_closure_set[i];
                q.push(s);              //应该不会死循环（死循环的情况是出现了e环
                temp_set.insert(s);     //set中重复的不会插入
                
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
    queue<set<int>> q;
    
    set<int> temp;  temp.insert(begin_state);//放入初态
    set<int> first = e_closure(temp);           //第一个初态做一个e闭包
    q.push(first);//扔进队列中
    new_DFA.insert(pair<set<int>, int>(first,dfa_num++));//将第一个插入集合
    set<int> t;
    while (!q.empty()) {
        set<int> t = q.front(); q.pop();
        for (int j = 0 ; j < terminal_symbol.size(); ++j) {
            set<int>tempt = e_closure(move(terminal_symbol[j], t));
           if (tempt.empty())
               continue;
           
           if (new_DFA.find(tempt) == new_DFA.end()){
               new_DFA.insert(pair<set<int>, int>(tempt,dfa_num++));//将第一个插入集合
               DFAEdge temp(t,terminal_symbol[j],tempt);
               dfa.push_back(temp);

               q.push(tempt);
           }
           else{
               map<set<int>, int>::iterator it = new_DFA.find(tempt);
               set<int> x = it->first;
               DFAEdge temp(t,terminal_symbol[j],tempt);
               dfa.push_back(temp);
           }
        }
    }
}
void DFAConstructor::output()//输出NFA集合的转换，也存好了对应DFA的转换
{
    
    DFAmatrix.resize(new_DFA.size(), vector<int>(terminal_symbol.size(), -1));
    for (int i = 0; i < terminal_symbol.size(); ++i){       //给字符转换矩阵横坐标赋值
        trans_to_index.insert(pair<char, int>(terminal_symbol[i], i));
    }
    
    for (int i = 0; i< dfa.size(); ++i) {               //遍历所有dfa边
        auto fi = new_DFA.find(dfa[i].src_sta);
        if( fi == new_DFA.end()) {                      //如果当前集合中没有该DFA则插入
            new_DFA.insert(pair<set<int>, int>(dfa[i].src_sta, new_DFA.size()));
            dfa[i].new_src_num = (int)new_DFA.size()-1;
        }
        else
            dfa[i].new_src_num = fi->second;
        fi = new_DFA.find(dfa[i].des_sta);
        if( fi == new_DFA.end()) {                       //如果当前集合中没有该DFA则插入
            new_DFA.insert(pair<set<int>, int>(dfa[i].des_sta, new_DFA.size()));
            dfa[i].new_des_num = (int)new_DFA.size()-1;
        }
        else
            dfa[i].new_des_num = fi->second;
        
        for(set<int>::iterator it = dfa[i].src_sta.begin(); it != dfa[i].src_sta.end(); ++it){
            if (*it == end_state) {
                dfa[i].is_end_state = 1;//意味着des_state是终态
                auto find2 = new_DFA.find(dfa[i].src_sta);
                terminal_index.insert(find2->second);
            }
        }


        for (set<int>::iterator it = dfa[i].des_sta.begin(); it != dfa[i].des_sta.end(); ++it) {

            if (*it == end_state) {
                dfa[i].is_end_state = 1;//意味着des_state是终态
                auto find2 = new_DFA.find(dfa[i].des_sta);
                terminal_index.insert(find2->second);
            }
        }
        
        cout << dfa[i].new_src_num << "->'" << dfa[i].trans << "'->" << dfa[i].new_des_num<< endl;
        
        auto find1 = trans_to_index.find(dfa[i].trans);
        DFAmatrix[dfa[i].new_src_num][find1->second] = dfa[i].new_des_num;
    }
    
    
    
    for (int i = 0; i < DFAmatrix.size(); ++i) {
        for (int j = 0; j < terminal_symbol.size(); ++j) {
            cout<<i<<"->'"<<terminal_symbol[j]<<"'->"<<DFAmatrix[i][j]<<'\t';
        }
        cout<<endl;
    }
    
    

    cout<<"终态:";
    for (auto it3 = terminal_index.begin(); it3 != terminal_index.end(); ++it3) {
        cout<<*it3<<'\t';
    }
}
