/*
Write your Rope implementation in this file. 
You do not have to keep any of the code that is already in this file.
Functions that are required that you have not implemented have an assert 0
meaning they will always crash. This should help you make sure you implement
everything.
*/

#include <cassert>
#include "Rope.h"

//Should advance to the next Node using in-order traversal
//It can point at any Node, not just leaves
rope_iterator& rope_iterator::operator++(){
	//if right is null
	if (ptr_->right == NULL) { 
		//while they have a parent, and the parent only has right
		 while (ptr_->parent != NULL && ptr_->parent->right == ptr_) {
			 //set the pointer to be the parent
			ptr_ = ptr_->parent; 
		}
		//after looping through set the pointer to the parent
      ptr_ = ptr_->parent;
    }else{
		//else if there is something in right
		//set the pointer to right
		ptr_ = ptr_->right;
		//while the pointer's left has something
      while (ptr_->left != NULL){
		  //set it to pointer to the left
		   ptr_ = ptr_->left; 
		}
    }
	//then returns the object
    return *this;
}

//Point to the first Node for in-order traversal
rope_iterator Rope::begin() const{
	//if the root doesn't exist
	if(!root){
		//return null
		return rope_iterator(NULL);
	//if it does exist
	}else{
		//create a new node
		Node* r = root;
		//while it is a valid leaf
		while (!is_leaf(r)) {
			//set it to the left
			r = r -> left;
		}
		//then return the rope
		return rope_iterator(r);
	}
}
//constuctor
Rope::Rope(){
	//sets default values
	//size to 0
	size_ = 0;
	//and root to be null
	root = NULL;
}

//Should make the root = p and adjust any member variables
//This should not make a copy of the rope with root at p,
//it should just "steal" the Node*
Rope::Rope(Node* p){
	root = p;
	size_ = 0;
	//creates a rope iterator
	rope_iterator iter = this -> begin();
	//while you don't reach the end of the rope
	while (iter != this -> end()) {
		//if the pointer is valid
		if (is_leaf(iter.ptr_)) {
			//add its weight to the size
			size_ += iter.weight();
			//increment the iterator
			iter++;
		//else
		}else{
			//increment the iterator
			iter++;
		}
	}
}
//functon that deletes the rope recursively
void Rope::delete_rope(Node* root) {
	//if there is something in the root
	if(root != NULL){
		//deletes the left
		delete_rope(root -> left);
		//deletes the right
		delete_rope(root -> right);
		//then deletes entire root
		delete root;
	}
} 
//deconstructor
Rope::~Rope(){
	//uses function to delete root
	delete_rope(root);
	//resets to default values
	size_ = 0;
	root = NULL;
}
//get function that returns the root
Node* Rope::get_root() {
	return root;
}

//copies root
Node* copy(Node* root) {
	//if the root has values
	if (root != NULL) {
		//creates a new node
		Node* new_ = new Node;
		//sets value, weight, parent, left, and right
		// to the new node
		new_ -> value = root -> value;
		new_ -> weight = root -> weight;
		new_ -> parent = root;
		new_ -> left = copy(root -> left);
		new_ -> right = copy(root -> right);
		//return the new node
		return new_;
	//else if it has nothing
	}else{
		//return null, since root would be null
		return NULL;
	}
}
//another constructor if rope is inputted
Rope::Rope(const Rope& r){
	//sets the size to the rope's size
	size_ = r.size();
	//sets the root and makes a copy of it for use
	root = copy(r.expose_root());
}
//= operator
Rope& Rope::operator= (const Rope& r){
	//sets the size to the size
	size_ = r.size_;
	//sets root to root by making a copy of it
	root = copy(r.expose_root());
	//returns the rope object
	return *this;
}

//MUST BE ITERATIVE
//Get a single character at index i
bool Rope::index(int i, char& c) const{
	//if the root had values
	if (root != NULL) {
		//creates new node
		Node* n = root;
		//while the node is a valid leaf
		while(!is_leaf(n)){
			//if the weight is creater than the index
			if ((n -> weight) > i){
				//set the node to the left
				n = n-> left;
			}else{
				//reduce the index by the weight
				i -= n -> weight;
				//set the node to the right
				n = n-> right;
			}
		}
		//set the character to the nodes
		//value at that index
		c = (n -> value)[i];
		//return true, because you found an index at that point
		return true;
	//else
	}else{
		//return false
		return false;
	}
}

//Add the other rope (r)'s string to the end of my string
void Rope::concat(const Rope& r){
	//if the size is 0
	if (this -> size_ == 0) {
		//set the root to make a copy of it
		//since there is only the root
		root = copy(r.expose_root());
	//else
	}else{
		//make a new node
		Node* new_ = new Node;
		//set the root's parent to new
		root -> parent = new_;
		//set's the weight to the size
		new_-> weight = size_;
		//set's the left to the root
		new_ -> left = root;
		//set's the right to the copy 
		new_ -> right = copy(r.expose_root());
		//sets the right's parent to the new
		new_ -> right -> parent = new_;
		//sets the root to new
		root = new_;
		//adds the size of the root to the size
		size_ += r.size();	
	}
}
//special case where you concantate two nodes of left and right
Node* concat_two(Node* n1, Node* n2) {
	//creates new node
	Node* new_ = new Node;
	//sets the first parent to new
	n1 -> parent = new_;
	//sets the weight to the first weight
	new_ -> weight = n1 -> weight;
	//sets the left to the first
	new_ -> left = n1;
	//sets the right to the second
	new_ -> right = n2;
	//sets the right parent to new
	new_ -> right -> parent = new_;
	//returns new
	return new_;
}

//Get a substring from index i to index j.
//Includes both the characters at index i and at index j.
//String can be one character if i and j match
//Returns true if a string was returned, and false otherwise
//Function should be written with efficient running time.
bool Rope::report(int i, int j, std::string& s) const{
	//creates character variable
	char c; 
	//clears the string
	s.clear();
	//if the index of i > j
	if (i > j) {
		//can't index because i has to be lower in order to index 
		// from i to j
		std::cerr << "ERROR: UNABLE TO INDEX" << std::endl;
		//return false cause you can't report
		return false;
	}
	//if i isn't equal to j, and is valid
	// after checking that i and j are a valid range
	// from above if statement
	if (i != j) {
		//while i is less than or equal to j
		while(i <= j) {
			//set this to the index of i and the
			// character
			this -> index(i,c);
			//push back the character into the string
			s.push_back(c);
			//increment through the range
			i++;
		}
		//return true
		return true;
		//then check next index
		this -> index(i,c);
		//push back into string again
		s.push_back(c);
		//and return true
		return true;
	//else
	}else {
		//find the index
		this -> index(i,c);
		//push back the string
		s.push_back(c);
		//return true
		return true;
	}
}
//sets the rope objects root to whatever root is sent in
void Rope::set_root(Node* n) {
	root = n;
}
//updates the rope
void Rope::update(Node* n){
	//while the root isn't empty
	if (n != NULL) {
		//if the root is valid
		if (!is_leaf(n)) {
			//get the leaf's weight
			leaf_weight(n);
		//if the right isn't null
		if (n -> right != NULL) {
			//update the right
			update(n -> right);
		}
		//else if the left isn't null
		else if (n -> left != NULL) {
			//update the left
			update(n -> left);
			}
		}
	}
}

//function that gets the weight at that specific leaf
void Rope::leaf_weight(Node* n) {
	//creates two variables
	Node* n1 = n;
	Node* n2 = n;
	//while the first if valid
	while (!is_leaf(n1)) {
		//set the first to the left
		n1 = n1 -> left;
	}
	//set the second to the left
	n2 = n2 -> left;
	//while the second is valid
	while (!is_leaf(n2)) {
		//if the second's right isn't null
		if (n2 -> right != NULL) {
			//set the second to the right
			n2 = n2 -> right;
		//else
		}else{
			//set the second to the left
			n2 = n2 -> left;
		}
	}
	//sets the weight to 0
	n -> weight = 0;
	//creates a rope iterator with the first
	rope_iterator iter = rope_iterator(n1);
	//while it's not eual to the iterator of the second
	while (iter != rope_iterator(n2)) {
		//if the pointer is valid
		if (is_leaf(iter.ptr_)) {
			//add the weight to the current weight
			n -> weight += iter.weight();
			//increment the iterator
			iter++;
		}else{
			//increment the iterator
			iter++;
		}
	}
	//adds the second's weight to the inital weight
	n -> weight += n2 -> weight;
}

//The first i characters should stay in the current rope, while a new
//Rope (rhs) should contain the remaining size_-i characters.
//A valid split should always result in two ropes of non-zero length.
//If the split would not be valid, this rope should not be changed,
//and the rhs rope should be an empty rope.
//The return value should be this rope (the "left") part of the string
//This function should move the nodes to the rhs instead of making new copies.
Rope& Rope::split(int i, Rope& rhs){
	//sets a variable to the first i characters
	int x = i;
	//variable to check new weight
	int w;
	//sets a node to the root
	Node* n = root;
	//creates new nodes
	Node* n1;
	//sets the second node to a null value
	Node* n2 = NULL;
	//while the node is valid
	while(!is_leaf(n)){
		//if the weight is less than the first x(i) characters
		if ((n -> weight) < x) {
			//decrement the number of characters
			x -= n -> weight;
			//set the node to the right
			n = n -> right;
		//else
		}else{
			//if the 2nd node and the nodes right isn't null
			if (n2 != NULL && n -> right != NULL) {
				//sets the empty node to the right node
				n1 = n -> right;
			}
			//else if the right node is not null
			else if (n -> right != NULL) {
				//set the null node ot the right node
				n2 = n -> right;
			}
			//if none of these conditions occur
			//set the node's right to null
			// and set the node to the left
			n -> right = NULL;
			n = n -> left;
		}
		//set the weight to the node's updated weight
		w = n -> weight;
	}
	//if the weight is equal to number of characters
	if (w == x) {
		//creates a new root and calls the concat_tow function
		Node* concat_root = concat_two(n1,n2);
		//sets the right side to the concated root
		rhs.set_root(concat_root);
		//update the right side to it's root 
		// aka the concated root
		rhs.update(rhs.get_root());
	} 
	//creates a rope iterator of the rhs
	rope_iterator iter = rhs.begin();
	//while you're not at the end
	while(iter != rhs.end()){
		//and the pointer is valid
		if (is_leaf(iter.ptr_)) {
			//add the weight to the size of the rhs
			rhs.add_to_size(iter.weight());
			//increment the iterator
			iter++;
		//else
		}else{
			//increment the iterator
			iter++;
		}
	}
	//then update the rope
	this -> update(root);
	//reset the size
	size_ = 0;
	//set the interator to the beginning of the rope
	iter = this->begin();
	//while you aren't at the end
	while (iter != this -> end()){
		//if the pointer is valid
		if (is_leaf(iter.ptr_)) {
			//add the weight to the size
			size_ += iter.weight();
			//increment the iterator
			iter++;
		}else{
			//increment the iterator
			iter++;
		}
	}
	//return the split rope
	return *this;
}


