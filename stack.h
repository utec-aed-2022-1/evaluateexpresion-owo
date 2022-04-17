//
// Created by Mauricio on 15/04/2022.
//
#include "list.h"
#ifndef EVALUATEEXPRESION_OWO_STACK_H
#define EVALUATEEXPRESION_OWO_STACK_H

template <typename T>
class Stack : public ForwardList<T>{
public:
    Stack():ForwardList<T>(){};

    void push(T data){
        ForwardList<T>::push_front(data);
    }

    T pop(){
        return ForwardList<T>::pop_front();
    }
};

#endif //EVALUATEEXPRESION_OWO_STACK_H
