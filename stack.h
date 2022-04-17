#ifndef STACK_H
#define STACK_H

#include <iostream>
#include "forward.h"

using namespace std;

template<typename T>
struct StackList : public ForwardList<T> {
  StackList() : ForwardList<T>() {}
  ~StackList() {}

  void push(T);
  T pop();
  T top();
  void display();
};

template<typename T>
void StackList<T>::push(T data) {
  ForwardList<T>::push_back(data);
}


template<typename T>
T StackList<T>::pop() {
  return ForwardList<T>::pop_back(); 
}


template<typename T>
T StackList<T>::top() {
  return ForwardList<T>::front();
}


template<typename T>
void StackList<T>::display() {
  ForwardList<T>::display();
}
#endif