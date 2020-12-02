/*
Name: Raj Phuyal 
Compiler Used: Visual Studio
Program Description: In this project we develop an emergency room simulator by using heaps and priority queuing.
*/

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <vector>

#include "BST.h"

using namespace std;

int ticket_no;
bool admit_flag;

BST *queue;

char *ltrim(char *s) {
    while(isspace(*s)) s++;
    return s;
}
char *rtrim(char *s) {
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}
char *trim(char *s) {
    return rtrim(ltrim(s)); 
}

void trim(string &str) {
	str = trim((char*)str.c_str());
}

void printInputDescription() {
	cout << ">>...please input command" << endl;
}

int getTicketNo() {
	return ++ticket_no;
}

void handleCommand(stringstream &ss, string cmd) {
	if (cmd == "exit") {
		//exit program
		exit(0);
	} else if (cmd == "load") {
		string file;
		getline(ss, file, ' ');
		trim(file);
		ifstream fin(file);
		while (true) {				
			string str;
			getline(fin, str);
			if (str == "") break;
			stringstream fs(str);
			getline(fs, cmd, ' ');
			trim(cmd);
			/* Call handleCommand function recursively so that
			commands in file including "load" will be executed properly */
			if (cmd == "admit") {
				string first_name, last_name, buf;
		
				int ticket_no = getTicketNo();
				
				getline(fs, last_name, ' ');
				trim(last_name);
				getline(fs, buf, ' ');
				getline(fs, first_name, ' ');
				trim(first_name);
				 
			if (last_name == "   " || first_name == "   ") {
					cout << "...Please input name correctly!" << endl;
					return;
				}
				
				Node node;
				node.ticket_no = ticket_no;
				node.last_name = last_name;
				node.first_name = first_name;
				node.priority = "ambulatory";
				
//			cout << "Creating a patient record for " << last_name << ", " << first_name << endl;
//				cout << "Priority: ambulatory" << endl;
//				cout << "Ticket: " << node.ticket_no << endl;
				
				admit_flag = true;
				
				while(true) {
					string _str, _cmd, _type, _detail;
					string _tmp;
					
					getline(fin, _str);
					trim(_str);
					stringstream _fs(_str);
					getline(_fs, _cmd,' ');
			
					if (_cmd == "timda") {
						admit_flag = false;
						
						// add new node to priority queue.
						queue->push(node);
						break;
					} else if (_cmd == "set") {
						
						getline(_fs, _type,' ');
						trim(_type);
						if (_type == "complaint") {
							getline(_fs, _detail,' ');
							trim(_detail);
							node.complaint = _detail;
						} else if (_type == "priority") {
							getline(_fs, _detail, ' ');
							trim(_detail);
							node.priority = _detail;
						} else {
							cout << "...invalid SET command" << endl;
						}
						
					} else if (_cmd == "add") {
						getline(_fs, _type, ' ');
						trim(_type);
						
						if (_type == "symptom") {
							getline(_fs, _detail, ' ');
							trim(_detail);
							node.symtom.push_back(_detail);
						} else {
							cout << "...invalid ADD command" << endl;
						}
					} else {
						cout << "Sorry, unable execute other command until close the current patient record" << endl;
					}
				}
			}
			else {
				handleCommand(fs, cmd);
			}
		}
	} else if (cmd == "display") {
		// display top node's record 
		if (queue->empty()) {
			cout << "No patient!" << endl;
		} else {
			Node node = queue->top();
			node.display();		
		}
	} else if (cmd == "next") {
		// popup top node in priority queue
		queue->popup();	
	} else if (cmd == "admit") {
		string first_name, last_name, buf;
		
		int ticket_no = getTicketNo();
		
		getline(ss, last_name,' ');
		trim(last_name);
		getline(ss, first_name,' ');
		getline(ss, buf, ' ');
		trim(first_name);
		
		if (last_name == "  " || first_name == "  ") {
			cout << "...Please input name correctly!" << endl;
			return;
		}
		
		Node node;
		node.ticket_no = ticket_no;
		node.last_name = last_name;
		node.first_name = first_name;
		node.priority = "ambulatory";
		
		cout << "Creating a patient record for " << last_name << "," << first_name << endl;
		cout << "Priority: ambulatory" << endl;
		cout << "Ticket: " << node.ticket_no << endl;
		
		admit_flag = true;
		
		while(true) {
			string _str, _cmd, _type, _detail;
			string _tmp;
			
			getline(cin, _str);
			trim(_str);
			stringstream _ss(_str);
			getline(_ss, _cmd, ' ');
	
			if (_cmd == "timda") {
				admit_flag = false;
				
				// add new node to priority queue.
				queue->push(node);
				break;
			} else if (_cmd == "set") {
				
				getline(_ss, _type, ' ');
			
				trim(_type);
				if (_type == "complaint") {
					getline(_ss, _detail,' ');
					trim(_detail);
					node.complaint = _detail;
					cout << "Compliant Added!" << endl;
				}
				else if (_type == "priority") {
					getline(_ss, _detail,' ');
					trim(_detail);
					node.priority = _detail;
					cout <<  "Priority Added!" << endl;
				} else {
					cout << "...invalid SET command" << endl;
				}
				
			} else if (_cmd == "add") {
				getline(_ss, _type, ' ');
				trim(_type);
				
				if (_type == "symptom") {
					getline(_ss, _detail, ' ');
					trim(_detail);
					node.symtom.push_back(_detail);
					cout << "Symptom Recorded!" << endl;
				} else {
					cout << "...Invalid ADD command" << endl;
				}
			} else {
				cout << "Sorry, unable to execute other command until you close the current patient record" << endl;
			}			
		}
		
	} else if (cmd == "set" || cmd == "add" || cmd == "timda") {
		cout << "...sorry, only works after admit command" << endl;
	} else {
		cout << "Unknown Command" << endl;
	}
}

int main(int argc, char** argv) {
	
	queue = new BST(100);	
	string str, cmd;
	
	// Main iteration of command input until exit command
	while (true) {
		// Print Input description
		printInputDescription();
		// Input command line
		getline(cin, str);
		stringstream ss(str);
		//Get command token
		getline(ss, cmd, ' ' );
		// Remove unnecessary whitespace
		trim(cmd);
		// Do actions accorging to command category
		handleCommand(ss, cmd);
	}
	
	return 0;
}
