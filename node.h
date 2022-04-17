#ifndef NODE_H
#define NODE_H

template <typename T>
struct Node {
	T data;
	Node<T>* next;
	Node<T>* prev;

	Node(){
		Node(0);
	}

	Node(T value) : next(nullptr), prev(nullptr), data(value) {}

	~Node() {
		if(next)
			delete next;
	}

	void killSelf() {
		if(next != nullptr)
			next->killSelf();
		delete this;
	}
};

#endif