//
// Created by Mauricio on 16/04/2022.
//
#include "stack.h"
#ifndef EVALUATEEXPRESION_OWO_FUNCTIONS_H
#define EVALUATEEXPRESION_OWO_FUNCTIONS_H

bool issymbol(char a){
    if(
            a == '(' ||
            a == ')' ||
            a == '+' ||
            a == '-' ||
            a == '*' ||
            a == '/'
    ) {
        return true;
    }
    return false;
}

double tn(char a){ //tn = tonumber
    if(a == '0')
        return 0;
    else if( a == '1')
        return 1;
    else if( a == '2')
        return 2;
    else if( a == '3')
        return 3;
    else if( a == '4')
        return 4;
    else if( a == '5')
        return 5;
    else if( a == '6')
        return 6;
    else if( a == '7')
        return 7;
    else if( a == '8')
        return 8;
    else if( a == '9')
        return 9;
    else if( a == '*')
        return -1;
    else if( a == '/')
        return -1.1;
    else if( a == '+')
        return -2;
    else if( a == '-')
        return -2.1;
    else if( a == '(')
        return -3;
    else if( a == ')')
        return -4;
}

template<typename  T, typename  U>
bool decompose(Stack<T>& num, Stack<U>& sym, string input){
    char prev;
    for(int i = 0; i < input.size(); i++){
        if(i > 0)
            prev = input[(i - 1)];

        if(input[i] != ' '){
            if(issymbol(input[i])){
                //sym.push(input[i]);
                if(input[i] == ')' || input[i] == '('){
                    if(input[i] == '(')
                        sym.push(input[i]);
                    else{ //input[i] == ')'
                        while(!sym.is_empty() && sym.front() != '(')
                            num.push( tn(sym.pop()) );
                        if(sym.is_empty()) {
                            sym.push('%');
                            return false;
                        }
                        else
                            sym.pop();
                    }
                }
                else{
                    if( int( tn(sym.front()) ) >= int( tn(input[i]) ) ) {
                        while( int( tn(sym.front()) ) >= int( tn(input[i]) ) )
                            num.push( tn(sym.pop()) );
                        sym.push(input[i]);
                    }else{
                        sym.push(input[i]);
                    }
                }

            } else{
                if(i > 0 && !issymbol(prev) && prev != ' '){
                    num.front() = (num.front() * 10) +   tn(input[i]);
                }else {
                    num.push(tn(input[i]));
                }
            }
        }
    }

    cout<<num.name()<<endl;
    cout<<sym.name()<<endl;

    return false;
}

#endif //EVALUATEEXPRESION_OWO_FUNCTIONS_H
