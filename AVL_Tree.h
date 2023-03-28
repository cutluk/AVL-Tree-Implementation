//
//  AVL_TREE.h
//  Gator AVL Project
//
//  Created by Luke Cutting on 2/15/23.
//

#ifndef Header_h
#define Header_h

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <stack>
using namespace std;

struct Node{
    string ufid;
    string name;
    Node* left = nullptr;
    Node* right = nullptr;
    int level = 1;
    
    
    // node constructor
    Node(string nameIn, string ufidIn){
        name = nameIn;
        ufid = ufidIn;
    }
};

class AVL_Tree{
    private:
        Node* root = nullptr;
    
    public:
        
        // Max Node calculation
        Node* maxNode(Node* root) {
            Node* temp = root;

            while(temp->right != nullptr) {
                temp = temp->right;
            }
            return temp;
        }
    
        // height calculation
        int height(Node* root){
            if(root == nullptr){
                return 0;
            }else{
                return max(height(root->left), height(root->right))+1;
            }
        }

            
        // Perform right rotation
        Node* right(Node* root) {
            Node* leftChild = root->left;
            root->left = leftChild->right;
            leftChild->right = root;

            root->level = height(root);
            leftChild->level = height(leftChild);
            
            return leftChild;
        }
    

        // Perform a left rotation
        Node* left(Node* root){
            Node* rightChild = root->right;
            root->right = rightChild->left;
            rightChild->left = root;
            
            root->level = height(root);
            rightChild->level = height(rightChild);
            
            return rightChild;
        }
    
    
// Insert the name and ID
    
    void insert(string name, string ufid){
        
        // check if name is valid and id is valid
        regex validChar = regex("^[a-zA-Z\\s]*$");
        regex validDigit = regex("^[0-9]*$");
        bool check = regex_search(name, validChar);
        bool checkDigit = regex_search(ufid, validDigit);
        
        // check if ufid is a valid length
        if(ufid.length() != 8){
            checkDigit = false;
        }
        
        // check if id is unique
        if(checkDigit){
            if(searchID(ufid) != "unsuccessful"){
                checkDigit = false;
            }
        }
        if(check && checkDigit){
            root = insertNode(root, name, ufid);
            root->level = height(root);
            cout << "successful" << endl;
        }else{
            cout << "unsuccessful" << endl;
        }
    } 

    Node* insertNode(Node* root, string name, string ufid){
        if(root == nullptr){
            return new Node(name, ufid);
        }
        
        if(stoi(ufid) < stoi(root->ufid)){
            root->left = insertNode(root->left, name, ufid);
        }else{
            root->right = insertNode(root->right, name, ufid);
        }
        
        int balance = height(root->left) - height(root->right);
        
        // perform rotations as necessary to maintain the AVL tree property
        if(balance > 1 && stoi(ufid) < stoi(root->left->ufid)){
            return right(root);
        }
        
        if(balance < -1 && stoi(ufid) > stoi(root->right->ufid)){
            return left(root);
        }
        
        if(balance > 1 && stoi(ufid) > stoi(root->left->ufid)){
            root->left = left(root->left);
            return right(root);
        }
        
        if(balance < -1 && stoi(ufid) < stoi(root->right->ufid)){
            root->right = right(root->right);
            return left(root);
        }
        
        return root;
    }


    
    
// Remove the ID
    
    void deleteID(Node*& root, string ufid){
        if(root == nullptr){
            cout << "unsuccessful" << endl;
        }
        if(stoi(root->ufid) > stoi(ufid)){
            deleteID(root->left, ufid);
        }else if(stoi(root->ufid) < stoi(ufid)){
            deleteID(root->right, ufid);
        }else{
            // no children
            if(root->right == nullptr && root->left == nullptr){
                delete root;
                root = nullptr;
                cout << "successful" << endl;
            }

            // one right child node
            else if(root->right != nullptr && root->left == nullptr) {
                Node* temp = root;
                root = root->right;
                delete temp;
                cout << "successful" << endl;
            }
            
            // one left child node
            else if(root->left != nullptr && root->right == nullptr){
                Node* temp = root;
                root = root->left;
                delete temp;
                cout << "successful" << endl;
            }
            
            // two children nodes
            else{
                Node *temp = maxNode(root->left);
                root->name = temp->name;
                root->ufid = temp->ufid;
                deleteID(root->left, temp->ufid);
            }

        }
    }
    
    void removeID(string ufid){
        if(searchIDhelper(this->root, ufid) != "unsuccessful"){
            deleteID(this->root, ufid);
        }
        else{
            cout << "unsuccessful" << endl;
        }
    }
    
    
    
// Search ID
    
    string searchIDhelper(Node* root, string id){
        if(root == nullptr){
            return "unsuccessful";
        }
        else{
            if(stoi(root->ufid) == stoi(id)){
                return root->name;
            }
            else if(stoi(root->ufid) > stoi(id)){
                return searchIDhelper(root->left, id);
            }
            else if(stoi(root->ufid) < stoi(id)){
                return searchIDhelper(root->right, id);
            }
        }
        return "unsuccessful";
    }
    
    string searchID(string id){
        return searchIDhelper(this->root, id);
    }
    
    
    
// Search for Name
    string searchNameHelper(Node* root, string name, string& result) {
        if (root == nullptr) {
            return "";
        }
        
        if (root->name == name) {
            result += root->ufid + "\n";
        }
        
        searchNameHelper(root->left, name, result);
        searchNameHelper(root->right, name, result);
        return result;
    }

    void searchName(string name) {
        string result = "";
        searchNameHelper(this->root, name, result);
        if (result == "") {
            cout << "unsuccessful" << endl;
        } else {
            cout << result;
        }
    }

    
    
// In Order Traversal Function
    
    void inOrderTraversal(Node* root, vector<string>& printVector){
        if(root == nullptr){
            return;
        }
        // L,N,R
        inOrderTraversal(root->left, printVector);
        printVector.push_back(root->name);
        inOrderTraversal(root->right, printVector);
    }
    
    void printInOrder(){
        vector<string> printVector;
        
        inOrderTraversal(this->root, printVector);
        
        if(printVector.size()==0){
            cout << "unsuccessful" << endl;
        }else{
            for(int i=0; i<printVector.size()-1; i++){
                cout << printVector[i] << ", ";
            }
            cout << printVector[printVector.size()-1] << endl;
        }
    }
    
    
    
// Pre Order Traversal Function
    
    void preOrderTraversal(Node* root, vector<string>& printVector){
        if(root == nullptr){
            return;
        }
        // N,L,R
        printVector.push_back(root->name);
        preOrderTraversal(root->left, printVector);
        preOrderTraversal(root->right, printVector);
    }
    
    void printPreorder(){
        vector<string> printVector;
        
        preOrderTraversal(this->root, printVector);
        
        if(printVector.size()==0){
            cout << "unsuccessful" << endl;
        }else{
            for(int i=0; i<printVector.size()-1; i++){
                cout << printVector[i] << ", ";
            }
            cout << printVector[printVector.size()-1] << endl;
        }
    }
    
    
    
// Post Order Traversal Function
    
    void postOrderTraversal(Node* root, vector<string>& printVector){
        if(root == nullptr){
            return;
        }
        // L,R,N
        postOrderTraversal(root->left, printVector);
        postOrderTraversal(root->right, printVector);
        printVector.push_back(root->name);
    }
    
    void printPostorder(){
        vector<string> printVector;
        
        postOrderTraversal(this->root, printVector);
        
        if(printVector.size()==0){
            cout << "unsuccessful" << endl;
        }else{
            for(int i=0; i<printVector.size()-1; i++){
                cout << printVector[i] << ", ";
            }
            cout << printVector[printVector.size()-1] << endl;
        }
    }
    
  
    
    
// Level Counter Function
    
    void levelCountHelper(Node* root){
        if(root == nullptr){
            cout << "0" << endl;
        }else{
            cout << root->level << endl;
        }
    }
    
    void printLevelCount(){
        levelCountHelper(this->root);
    }
    
    
    
    
// Remove Nodes using In order
    void removeInOrderTraversal(Node* root, int n, int count, string& result) {
        stack<Node*> s;
        Node* curr = root;

        while (curr != nullptr || !s.empty()) {
            while (curr != nullptr) {
                s.push(curr);
                curr = curr->left;
            }

            curr = s.top();
            s.pop();
            
            if (count == n) {
                result = curr->ufid;
                return;
            }
            count++;
            curr = curr->right;
        }
    }
    
    void removeInorder(int n){
        removeInOrderMain(this->root, n);
    }

    void removeInOrderMain(Node* root, int n)
    {
        int count = 0;
        string result = "";
       removeInOrderTraversal(this->root, n, count, result);

        if(result==""){
            cout << "unsuccessful" << endl;
        }else{
            deleteID(this->root, result);
        }
    }
        
    
};

#endif /* Header_h */
