//
//  main.cpp
//  regularExp_NFA
//
//  Created by 陈梓玮 on 2021/4/7.
//

#include <iostream>
#include "NFAConstructor.hpp"
#include "NFA_DFA.hpp"
int main(int argc, const char * argv[]) {
    
    
//    string a = "(a*-(b-c)-d)|(e-f*g)";

//    string a = "a*-b-c";
//    string a = "a*-b*-c*";
//    string a = "(1|2*)-3*";
    string a = "(a|b)*-a-b-b";
    cout<<"原始正则表达式:"<<a<<endl;
    NFAConstrctor myNFAconstructor;
    myNFAconstructor.read(a);
    myNFAconstructor.transformToSuffix();
    cout<<"后缀正则表达式:";
    myNFAconstructor.output();
    myNFAconstructor.createNFA();
    myNFAconstructor.output_NFA();

    cout<<"DFA(终态用<>表示):"<<endl;
    DFAConstructor myDFAconstructor(myNFAconstructor.terminal_symbol,myNFAconstructor.node_set, myNFAconstructor.begin_state, myNFAconstructor.end_state);
    myDFAconstructor.construction();
    myDFAconstructor.output();
    return 0;
}
