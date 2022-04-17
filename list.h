//
// Created by Mauricio on 15/04/2022.
//

#ifndef EVALUATEEXPRESION_OWO_LIST_H
#define EVALUATEEXPRESION_OWO_LIST_H

#include <string>
using namespace std;


template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev;

    Node(){
        Node(0);
    }

    Node(T value) : next(nullptr), prev(nullptr), data(value) {}

    ~Node() = default;

    void killSelf() {
        if(next != nullptr)
            next->killSelf();
        delete this;
    }
};


template <typename T>
class ForwardList{
private:
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    int nodes;

public:
    ForwardList() {
        head = tail = nullptr;
        nodes = 0;
    }

    ~ForwardList() {
        if(head)
            head->killSelf();
        head = nullptr;
        tail = nullptr;
        nodes = 0;
    }

    T& front() {
        if(is_empty())
            throw std::invalid_argument("It's empty");

        return head->data;
    }

    T back() {
        if(is_empty())
            throw std::invalid_argument("It's empty");

        return tail->data;
    }

    void push_front(T data) {
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

    void push_back(T data) {
        Node<T>* node = new Node<T>(data);

        if(is_empty()) {
            push_front(data);
        } else {
            tail->next = node;
            tail = node;
        }

        nodes++;
    }

    T pop_front() {
        if(is_empty())
            throw std::invalid_argument("It's empty");

        T data = head->data;

        if(size() == 1) {
            delete head;
            head = tail = nullptr;
            nodes--;
            return data;
        }

        Node<T> *tmp = head;
        head = head->next;
        delete tmp;
        nodes--;
        return data;
    }

    T pop_back() {
        if(is_empty())
            throw std::invalid_argument("It's empty");

        int data = tail->data;

        if(size() == 1) {
            delete head;
            head = tail = nullptr;
            nodes--;
            return data;
        }

        Node<T> *tmp = head;
        while(tmp->next != tail)
            tmp = tmp->next;
        delete tmp->next;
        tail = tmp;
        tail->next = nullptr;
        nodes--;
        return data;
    }

    T insert(T data, int pos) {
        if(pos < 0 || pos > size()-1)
            throw std::invalid_argument("Invalid position");

        if(pos == 0)
            push_front(data);
        else if(pos == size()-1)
            push_back(data);
        else {
            Node<T> *node = new Node<T>(data);
            Node<T> *tmp = head;

            for(size_t i=0; i<pos-1; ++i)
                tmp = tmp->next;
            node->next = tmp->next;
            tmp->next = node;
            nodes++;
        }

        return data;
    }

    bool remove(int pos) {
        if(pos < 0 || pos > size()-1) {
            return false;
            throw std::invalid_argument("Invalid position");
        }

        if(pos == 0)
            pop_front();
        else if(pos == size() - 1)
            pop_back();
        else {
            Node<T> *tmp = head;

            for(size_t i=0; i<pos-1; ++i)
                tmp = tmp->next;

            Node<T> *node = tmp->next;
            tmp->next = node->next;
            delete node;
            nodes--;
        }

        return true;
    }

    T& operator[](int pos) {
        if (pos < 0 || pos > size() - 1)
            throw std::invalid_argument("Invalid position");

        Node<T> *tmp = head;
        for (int i=0; i<pos; i++)
            tmp = tmp->next;
        return tmp->data;
    }

    bool is_empty() {
        return head == nullptr && tail == nullptr;
    }

    int size() {
        return nodes;
    }

    void clear() {
        if(head) {
            head->killSelf();
            head = nullptr;
            tail = nullptr;
            nodes = 0;
        }
    }

    void sort() {
        if(is_empty()) return;

        for (int i = 0; i < nodes - 1; i++) { // bubble sort
            Node<T>* temp = head;

            for (int j = 0; j < nodes - i - 1; j++) {
                if (temp->data > temp->next->data) {
                    T temp_data = temp->data;
                    temp->data = temp->next->data;
                    temp->next->data = temp_data;
                }
                temp = temp->next;
            }
        }
    }

    bool is_sorted() {
        if(is_empty()) return true;

        Node<T>* tmp = head;
        for(int i = 0; i < nodes - 1; i++) {
            if(tmp->data > tmp->next->data)
                return false;
            tmp = tmp->next;
        }
        return true;
    }

    void reverse() {
        Node<T>* tmp = head;
        tail = head;
        Node<T>* tmphead = new Node<T>();

        for(int i = 0; i < nodes; i++){
            head = tmp->next;
            tmp->next = tmphead->next;
            tmphead->next = tmp;
            tmp = head;
        }
        tail->next = nullptr;
        head = tmphead->next;

        delete tmphead;
    }

    std::string name() {
        if(typeid(T).name() == typeid('T').name()){
            Node<T>* tmp = head;
            std::string result;
            for(int i = 0; i < nodes; i++) {
                string s(1, tmp->data);
                result += s + " ";
                tmp = tmp->next;
            }
            return result;
        }


        Node<T>* tmp = head;
        std::string result;
        for(int i = 0; i < nodes; i++) {
            if(tmp->data < 0){
                if(tmp->data == -1){
                    result += "* ";
                }else if(tmp->data == -1.1){
                    result += "/ ";
                }else if(tmp->data == -2){
                    result += "+ ";
                }else if(tmp->data == -2.1){
                    result += "- ";
                }else{
                    result += "% ";
                }
            }else
                result += std::to_string(tmp->data) + " ";
            tmp = tmp->next;
        }
        return result;
    }

};

#endif //EVALUATEEXPRESION_OWO_LIST_H
