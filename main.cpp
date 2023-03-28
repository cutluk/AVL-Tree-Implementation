//
//  main.cpp
//  Gator AVL Project
//
//  Created by Luke Cutting on 2/15/23.
//

#include <iostream>
#include <string>
#include <sstream>
#include "AVL_Tree.h"
#include <cstdlib>
#include <ctime>
using namespace std;

int main(int argc, const char * argv[]) {
    
    
    // Create Tree object
    AVL_Tree Tree = AVL_Tree();
    
    int commandSize;
    string command;
    string name;
    string ufid;
    
    cin >> commandSize;
    
    for(int i=0; i < commandSize; i++){
        
        cin >> command;
        
        if (command == "insert"){
            string space;
            getline(cin, space, '\"');
            getline(cin, name, '\"');
            cin >> ufid;
            
            Tree.insert(name, ufid);
        }
        else if(command == "remove"){
            cin >> ufid;
            Tree.removeID(ufid);
        }
        else if (command == "search") {
            string line;
            getline(cin, line); // read the whole line
            
            size_t start_pos = line.find("\"");
            size_t end_pos = line.rfind("\"");
            
            if (start_pos != string::npos && end_pos != string::npos && start_pos != end_pos) {
                // the line contains a quoted string, extract it and search by name
                string name = line.substr(start_pos + 1, end_pos - start_pos - 1);
                Tree.searchName(name);
            } else {
                // the line does not contain a quoted string, try to parse it as a string ID and search by ID
                string id = line.substr(line.find_first_not_of(" "), 8); // extract the first 8 non-space characters as the ID string
                if (id.find_first_not_of("0123456789") == string::npos) {
                    string name = Tree.searchID(id);
                    cout << name << endl;
                }
                else {
                    cout << "unsuccessful" << endl;
                }
            }
        }

        else if(command == "printInorder"){
            Tree.printInOrder();
        }
        else if(command == "printPreorder"){
            Tree.printPreorder();
        }
        else if(command == "printPostorder"){
            Tree.printPostorder();
        }
        else if(command == "printLevelCount"){
            Tree.printLevelCount();
        }
        else if(command == "removeInorder"){
            string val;
            getline(cin, val);
            int n = stoi(val);
            Tree.removeInorder(n);
        }
        else {
            cout << "unsuccessful" << endl;
        }
        
    }
    
    
}


