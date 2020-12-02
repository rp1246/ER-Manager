/*
Student Name: Raj Phuyal
Compiler Used: Visual Studio
Program Description: In this project we develop an emergency room simulator by using heaps and priority queuing.
*/

#ifndef BST_H
#define BST_H

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

static string P[5] = {"code", "critical", "urgent", "non-urgent disabled", "ambulatory"};

struct _Node {
	int ticket_no;
	string last_name, first_name;
	string priority;
	string complaint;
	vector <string> symtom;
	_Node() {
		ticket_no = 0;
		symtom.clear();
		complaint.clear();
		first_name.clear(); last_name.clear();
		priority = "ambulatory";
	}
	int get_prio(string str) {
		transform(str.begin(), str.end(), str.begin(), ::tolower);
		for (int i = 0; i < 5; i++) {
			if (P[i] == str) return  i;
		}
		return 4;
	}
	void display() {
		cout << "Patient Record for " << last_name << ", " << first_name << endl;
		cout << "Ticket No: " << ticket_no << endl;
		cout << "Priority: " << priority << endl;
		cout << "Symtom: ";
		for (int i = 0; i < symtom.size(); i++) cout << " " << symtom[i];
		cout << endl;
		cout << "Complaint: " << complaint << endl;
	}
};

typedef _Node Node;


class BST
{
	public:
		// Construtor
		BST(unsigned int capacity);
		// Destructor
		~BST();
		// Returns the number of elements in the priority queue.
		unsigned int size() const;
		// Returns true if the priority queue is empty, and false otherwise.
		bool empty() const;
		// Returns true if the priority queue is full, and false otherwise.
		bool full() const;
		
		// Returns the max element of the priority queue, but does not remove it.
		Node top() const;
		// Inserts node into the priority queue. Returns true if successful, and 
		// false otherwise.
		bool push(Node val);
		// Removes the top element with the maximum value (priority) and rearranges 
		// the resulting heap. Returns true if successful, and false otherwise.
		bool popup();
	
	private:
		
	 	Node* heap_;
	 	
		// Total number of elements that the priority queue can store.
		unsigned int capacity_;
		
		// Current number of elements in the priority queue.
  		unsigned int size_;
};

#endif
