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
//    cout<<"原始正则表达式:"<<a<<endl;
//    NFAConstrctor myNFAconstructor;
//    myNFAconstructor.read(a);
//    myNFAconstructor.transformToSuffix();
//    cout<<"后缀正则表达式:";
//    myNFAconstructor.output();
//    myNFAconstructor.createNFA();
//    cout<<"NFA"<<endl;
//    myNFAconstructor.output_NFA();

//    string a = "a*-b-c";
//    string a = "a*-b*-c*";
    string a = "(a|b*)-c*";
    cout<<"原始正则表达式:"<<a<<endl;
    NFAConstrctor myNFAconstructor;
    myNFAconstructor.read(a);
    myNFAconstructor.transformToSuffix();
    cout<<"后缀正则表达式:";
    myNFAconstructor.output();
    myNFAconstructor.createNFA();
    myNFAconstructor.output_NFA();
    
    
    
    cout<<"DFA:"<<endl;
    DFAConstructor myDFAconstructor(myNFAconstructor.terminal_symbol,myNFAconstructor.node_set);
    myDFAconstructor.construction();
    myDFAconstructor.output();
    return 0;
}
