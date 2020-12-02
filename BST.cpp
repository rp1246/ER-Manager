/*
Name: Raj Phuyal
Compiler Used: Visual Studio
Program Description: In this project we develop an emergency room simulator by using heaps and priority queuing.
*/

#include "BST.h"
#include <cmath>

bool operator<(Node &a, Node &b) {
	int pa = a.get_prio(a.priority);
	int pb = b.get_prio(b.priority);
	if (pa != pb) return pa > pb;
	return a.ticket_no > b.ticket_no;
}
bool operator>(Node &a, Node &b) {
	int pa = a.get_prio(a.priority);                      
	int pb = b.get_prio(b.priority);          
	if (pa != pb) return pa < pb;
	return a.ticket_no < b.ticket_no;
}

BST::BST(unsigned int capacity) {
	capacity_ = capacity;
	size_ = 0;
	heap_ = new Node[capacity_+1];	
}

BST::~BST() {
	delete [] heap_;
}

unsigned int BST::size() const {
	return size_;
}

bool BST::empty() const {
	return !size_;
}

bool BST::full() const {
	return (size_ == capacity_);
}

int log2(int val) {
	return log(val) / log(2);
}

Node BST::top() const {
	return heap_[1];
}

bool BST::push(Node val) {
	if(full()) return false;
	heap_[++size_] = val;
	int index = size_;
	while(heap_[index] > heap_[index/2] && index/2 != 0) {
		Node temp = heap_[index]; 
		heap_[index] = heap_[index/2];
		heap_[index/2] = temp;
		index = index/2;
	}
	return true;
}

bool BST::popup() {
	if(empty()) return false; 
	else {
		heap_[1] = heap_[size_];
		size_--;
		int index = 1;
		int larger_child;
		
		while ((2*index <= size_ && heap_[index] < heap_[2*index]) || (2 * index + 1 <= size_ && heap_[index] < heap_[2*index + 1])) {
			if (2 * index + 1 <= size_) {
				if (heap_[2*index] > heap_[2*index+1]) larger_child = 2*index; 
				else larger_child = 2*index+1;
			}
			else larger_child = 2 * index;
			Node temp = heap_[index]; 
			heap_[index] = heap_[larger_child];
			heap_[larger_child] = temp;
			index = larger_child;
		}
		return true;
	}	 
}

