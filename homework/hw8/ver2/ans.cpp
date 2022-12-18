/*
Write your Rope implementation in this file. 
You do not have to keep any of the code that is already in this file.
Functions that are required that you have not implemented have an assert 0
meaning they will always crash. This should help you make sure you implement
everything.
*/

#include <cassert>
#include "ans.h"

//Should advance to the next Node using in-order traversal
//It can point at any Node, not just leaves
rope_iterator& rope_iterator::operator++(){
    if (ptr_ == NULL) {
        return *this;
    }
    else if (ptr_ -> right == NULL && ptr_ -> parent == NULL) {
        ptr_ = NULL;
    }
    else if (ptr_ -> left != NULL) {
        if (ptr_ -> right == NULL) {
            ptr_ = NULL;
            return *this;
        }
        ptr_ = ptr_ -> right;
        while (!is_leaf(ptr_)) {
            ptr_ = ptr_ -> left;
        }
    }
    else if (ptr_ -> parent -> left == ptr_ && is_leaf(ptr_)) {
        ptr_ = ptr_ -> parent;
    }
    else if (is_leaf(ptr_)) {
        while (ptr_ -> parent -> right == ptr_) {
            ptr_ = ptr_ -> parent;
            if (ptr_ -> parent == NULL) {
                ptr_ = NULL;
                return *this;
            }
        }
        ptr_ = ptr_ -> parent;
    }
    if (ptr_ != NULL) {
        //std::cout << ptr_ -> weight;
    }
    return *this;
}

//Point to the first Node for in-order traversal
rope_iterator Rope::begin() const{
    Node* x = root;
    while (!is_leaf(x)) {
        x = x -> left;
    }
    return rope_iterator(x);
}

Rope::Rope(){
    size_ = 0;
    root = NULL;
}

//Should make the root = p and adjust any member variables
//This should not make a copy of the rope with root at p,
//it should just "steal" the Node*
Rope::Rope(Node* p){
    root = p;
    size_ = 0;
    for (rope_iterator it = this -> begin(); it != this -> end(); it++) {
        if (is_leaf(it.ptr_)) {
            size_ += it.weight();
        }
    }
}

Rope::~Rope(){
    deleterope(root);
    root = NULL;
}

// recursive function to delete the whole rope
void Rope::deleterope(Node* root) {
    if (root == NULL) {
        return;
    }

    deleterope(root -> right);
    deleterope(root -> left);
    delete root;
} 

Node* copy(Node* root) {
    if (root == NULL) {
        return NULL;
    }
    Node* newRoot = new Node;
    newRoot -> weight = root -> weight;
    newRoot -> value = root -> value;
    newRoot -> parent = root;
    newRoot -> right = copy(root -> right);
    newRoot -> left = copy(root -> left);
    return newRoot;
}

Rope::Rope(const Rope& r){
    size_ = r.size();
    root = copy(r.expose_root());
}

Rope& Rope::operator= (const Rope& r){
    size_ = r.size_;
    root = copy(r.expose_root());
    return *this;
}

//MUST BE ITERATIVE
//Get a single character at index i
bool Rope::index(int i, char& c) const{
    if (root == NULL) {
        return false;
    }
    Node* tmp = root;
    while(!is_leaf(tmp)){
        if ((tmp -> weight) <= i) {
            i -= tmp -> weight;
            tmp = tmp -> right;
        }
        else if ((tmp -> weight) > i) {
            tmp = tmp -> left;
        }
    }
    c = (tmp -> value)[i];
    return true;
}

//Add the other rope (r)'s string to the end of my string
void Rope::concat(const Rope& r){
    if (this -> size_ == 0) {
        root = copy(r.expose_root());
    }
    Node* NewRoot = new Node;
    root -> parent = NewRoot;
    NewRoot -> weight = size_;
    NewRoot -> left = root;
    NewRoot -> right = copy(r.expose_root());
    NewRoot -> right -> parent = NewRoot;
    root = NewRoot;
    size_ += r.size();
}

Node* concat_no_copy(Node* X1, Node* X2) {
    Node* NewRoot = new Node;
    X1 -> parent = NewRoot;
    NewRoot -> weight = X1 -> weight;
    NewRoot -> left = X1;
    NewRoot -> right = X2;
    NewRoot -> right -> parent = NewRoot;
    return NewRoot;
}

//Get a substring from index i to index j.
//Includes both the characters at index i and at index j.
//String can be one character if i and j match
//Returns true if a string was returned, and false otherwise
//Function should be written with efficient running time.
bool Rope::report(int i, int j, std::string& s) const{
    s.clear();
    char c; 
    if (i > j) {
        std::cerr << "WRONG INDEXING, j LESS THAN i." << std::endl;
        return false;
    }
    else if (i == j) {
        this -> index(i,c);
        s.push_back(c);
        return true;
    }
    else {
        for (int z = i; z <= j; z++) {
            this -> index(z,c);
            s.push_back(c);
        }
        return true;
    }
}

//The first i characters should stay in the current rope, while a new
//Rope (rhs) should contain the remaining size_-i characters.
//A valid split should always result in two ropes of non-zero length.
//If the split would not be valid, this rope should not be changed,
//and the rhs rope should be an empty rope.
//The return value should be this rope (the "left") part of the string
//This function should move the nodes to the rhs instead of making new copies.
Rope& Rope::split(int i, Rope& rhs){
    int j = i;
    int x;
    Node* tmp = root;
    Node* X1;
    Node* X2 = NULL;
    while(!is_leaf(tmp)){
        if ((tmp -> weight) < j) {
            j -= tmp -> weight;
            tmp = tmp -> right;
        }
        else if ((tmp -> weight) >= j) {
            if (X2 != NULL && tmp -> right != NULL) {
                X1 = tmp -> right;
            }
            else if (tmp -> right != NULL) {
                X2 = tmp -> right;
            }
            tmp -> right = NULL;
            tmp = tmp -> left;
        }
        x = tmp -> weight;
    }
    if (x == j) {
        Node* tmp_ = concat_no_copy(X1,X2);
        rhs.set_root(tmp_);
        rhs.update(rhs.expose_root2());
    } 
    
    for (rope_iterator it = rhs.begin(); it != rhs.end(); it++) {
        if (is_leaf(it.ptr_)) {
            rhs.addsize(it.weight());
        }
    }
    this -> update(root);
    size_ = 0;
    for (rope_iterator it = this -> begin(); it != this -> end(); it++) {
        if (is_leaf(it.ptr_)) {
            size_ += it.weight();
        }
    }
    return *this;
}

void Rope::set_root(Node* n) {
    root = n;
}

void Rope::update(Node* top) {
    if (top == NULL) {
        return;
    }
    if (!is_leaf(top)) {
        leaf_weight(top);
        if (top -> right != NULL) {
            update(top -> right);
        }
        else if (top -> left != NULL) {
            update(top -> left);
        }
    }
}

void Rope::leaf_weight(Node* top) {
    Node* tmp = top;
    Node* tmp2 = top;
    while (!is_leaf(tmp)) {
        tmp = tmp -> left;
    }
    
    tmp2 = tmp2 -> left;
    while (!is_leaf(tmp2)) {
        if (tmp2 -> right == NULL) {
            tmp2 = tmp2 -> left;
        }
        else {
            tmp2 = tmp2 -> right;
        }
    }
    top -> weight = 0;
    for (rope_iterator it = rope_iterator(tmp); it != rope_iterator(tmp2); it++) {
        if (is_leaf(it.ptr_)) {
            top -> weight += it.weight();
        }
    }
    top -> weight += tmp2 -> weight;
}

Node* Rope::expose_root2() {
    return root;
}
