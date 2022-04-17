#ifndef FORWARD_H
#define FORWARD_H
#include <iostream>
#include <stdexcept>
#include "list.h"

using namespace std;

template <typename T>
struct ForwardList : public List<T> {
  Node<T>* head;
  Node<T>* tail;
  int nodes;

  ForwardList() : List<T>() {
    head = tail = nullptr;
    nodes = 0;
  }
  
  ~ForwardList() {
    if (head)
      head->killSelf();
    head = nullptr;
    tail = nullptr;
    nodes = 0;
  }

  T& front();
  T& back();
  void push_front(T);
  void push_back(T);
  T pop_front();
  T pop_back();
  T insert(T, int);
  bool remove(int);
  T& operator[](int);
  bool is_empty();
  int size();
  void clear();
  void sort();
  bool is_sorted();
  void reverse();
  std::string name();
  void display();
};

template <typename T>
T& ForwardList<T>::front() {
  if(is_empty()) throw std::invalid_argument("It's empty");

  return head->data;
}


template <typename T>
T& ForwardList<T>::back() {
  if(is_empty()) throw std::invalid_argument("It's empty");

  return tail->data;
}


template <typename T>
void ForwardList<T>::push_front(T data) {
  Node<T>* node = new Node<T>(data);

  if(is_empty()) { 
    head = node;
    tail = node;
  } else {
    node->next = head;
    head = node;
  }
  nodes++;
}


template <typename T>
void ForwardList<T>::push_back(T data) {
  Node<T>* node = new Node<T>(data);

  if(is_empty()) {
    push_front(data);
  } else {
    tail->next = node;
    tail = node;
    nodes++;
  }
}


template <typename T>
T ForwardList<T>::pop_front() {
  if(is_empty())
    throw std::invalid_argument("It's empty");

  T data = head->data;

  if(size() == 1) {
    delete head;
    head = tail = nullptr;
    nodes--;
    return data;
  }

  Node<T>* tmp = head;
  head = head->next;
  delete tmp;
  nodes--;
  return data;
}


template <typename T>
T ForwardList<T>::pop_back() {
  if(is_empty()) 
    throw std::invalid_argument("It's empty");

  T data = tail->data;

  if(size() == 1) { 
    delete head;
    head = tail = nullptr;
    nodes--;
    return data;
  } 

  Node<T>* tmp = head;
  while(tmp->next != tail)
    tmp = tmp->next;
  delete tmp->next;
  tail = tmp;
  tail->next = nullptr;
  nodes--;

  return data;
}


template <typename T>
T ForwardList<T>::insert(T data, int pos) {
  if(pos < 0 || pos > size()-1)
    throw std::invalid_argument("Invalid position");

  if(pos == 0)
    push_front(data);
  else if(pos == size()-1)
    push_back(data);
  else {
    Node<T>* node = new Node<T>(data);
    Node<T>* tmp = head;

    for(int i = 0; i < pos - 1; i++)
      tmp = tmp->next;

    node->next = tmp->next;
    tmp->next = node;
    nodes++;
  }
  return data;
}


template <typename T>
bool ForwardList<T>::remove(int pos) {
  if(pos < 0 || pos > size()-1)
    throw std::invalid_argument("Out of range");

  if(pos == 0)
    pop_front();
  else if(pos == size()-1)
    pop_back();
  else {
    Node<T>* tmp = head;

    for(int i = 0; i < pos - 1; i++)
      tmp = tmp->next;

    Node<T>* node = tmp->next;
    tmp->next = node->next;
    delete node;
    nodes--;
  }
  return true;
}

template <typename T>
T& ForwardList<T>::operator[](int pos) {
  if(pos < 0 || pos > size()-1)
    throw std::invalid_argument("Out of range");

  Node<T>* tmp = head;
  for(int i = 0; i < pos; i++)
    tmp = tmp->next;
  return tmp->data;
}


template <typename T>
bool ForwardList<T>::is_empty() {
  return size() == 0;
}


template <typename T>
int ForwardList<T>::size() {
  return nodes;
}


template <typename T>
void ForwardList<T>::clear() {
  if(head) {
    head->killSelf();
    head = tail = nullptr;
    nodes = 0;
  }
}


template <typename T>
void ForwardList<T>::sort() { 
  if(is_empty()) return;

  for (int i = 0; i < nodes - 1; i++){
    Node<T>* temp = head;
    for (int j = 0; j < nodes - i - 1; j++){
      if (temp->data > temp->next->data){
        T temp_data = temp->data;
        temp->data = temp->next->data;
        temp->next->data = temp_data;
      }
      temp = temp->next;
    }
  }
}


template <typename T>
bool ForwardList<T>::is_sorted() {
  if(is_empty()) return true;

  Node<T>* tmp = head;
  for(int i = 0; i < nodes - 1; i++) {
    if(tmp->data > tmp->next->data)
      return false;
    tmp = tmp->next;
  }
  return true;
}


template <typename T>
void ForwardList<T>::reverse() {
  if(size() > 1) {
    Node<T>* tmp = head->next;
    Node<T>* prev = head;
    head->next = nullptr;

    while(tmp != nullptr) {
      head = tmp;
      tmp = tmp->next;
      head->next = prev;
      prev = head;
    }
  }
}


template <typename T>
std::string ForwardList<T>::name() {
  return "ForwardList";
}


template <typename T>
void ForwardList<T>::display() {
  if(is_empty()) return;

  for(Node<T>* tmp = head; tmp != nullptr; tmp = tmp->next)
    cout << tmp->data << " ";
  cout << endl;
}

#endif