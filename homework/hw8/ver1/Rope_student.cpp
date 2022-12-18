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
	 if (ptr_->right == NULL) { 
		 while (ptr_->parent != NULL && ptr_->parent->right == ptr_) {
			ptr_ = ptr_->parent; 
		}
      ptr_ = ptr_->parent;
    }else{
		ptr_ = ptr_->right;
      while (ptr_->left != NULL){
		   ptr_ = ptr_->left; 
		}
    }
    return *this;
}

//Point to the first Node for in-order traversal
rope_iterator Rope::begin() const{
	//if the root doesn't exist that return null
	if(!root){
		return rope_iterator(NULL);
	}
	Node* p = root;
	//if it is not a leaf change the pointer
	while(p->value.length() == 0){
		p = p->left;
	}
	//return the iterator at the leaf at the beginning
	return rope_iterator(p);
}

Rope::Rope(){
	size_ = 0;
	root = NULL;
}

//Should make the root = p and adjust any member variables
//This should not make a copy of the rope with root at p,
//it should just "steal" the Node*
Rope::Rope(Node* p){
	//reassign the root and the weight 
	root = p;
	size_ = p->weight;
	//adds the weight of the right side
	while(p->right){
		p = p->right;
		size_ += p->weight;
	}
}
void deleteRope(Node* root)
{
	if(root != NULL){
		//delete each node
		deleteRope(root->right);
		deleteRope(root->left);
		root->weight = 0;
		delete root;
	}
}

Rope::~Rope(){
	//calls the helper function
	deleteRope(root);
	//set the size to zerp and the root to NULL
	size_ = 0;
	root = NULL;
}
Node* Rope::copy(Node* old_, Node* parent_){
	if (old_ != NULL){
      //the new node that is created to hold old values 	
	   Node* new_ = new Node();
	   //copies weight and string and parent
	   new_->value = old_->value;
	   new_->weight = old_->weight;
	   new_->parent = parent_;
	   //calls the function again for each left and right tree
	   new_->left = copy(old_->left, new_);
	   new_->right = copy(old_->right, new_);
	   return new_;
  	}else{
	   return NULL;
   }
}
Rope::Rope(const Rope& r){
	//calls helper function and adjusts size
	root = this->copy(r.root, NULL);
	size_ = r.size_;

}

Rope& Rope::operator= (const Rope& r){
		if(&r != this){
		//calls the destructor on this rope
		deleteRope(root);
		//copies the rope passed in
		root = this->copy(r.root, NULL);
		//copies the size
		size_ = r.size_;
	}
	return *this;
}

//MUST BE ITERATIVE
//Get a single character at index i
bool Rope::index(int i, char& c) const{
	//creates a copy of root
	if(i >= 0 || i <= size_){
		Node* croot = root;
		while (!is_leaf(croot)){
		//loops through the left part of the rope
		//right side
			if(i >= croot->weight){
				//have to subtract the weight
				i -= croot->weight;
				if(!croot->right){
					return false;
				}else{
					//index is not in the rope
					croot = croot->right;
				}

			}else {
				//keep going left
				if(!croot->left){
					return false;
				}else{
					//index is not in the rope
					croot = croot->left;
				}
			}
		}
		//if the node is actually a lead and the index 
		if( croot->value.length() > 0 && i < (int)(croot->value.length())){
			c = croot->value[i];
			return true;
		}
		return false;
	}else{
		return false;
	}
}

//Add the other rope (r)'s string to the end of my string
void Rope::concat(const Rope& r){
	//keeps track of the right hand side
	int right_size = r.size_;
	//keeps track of the side of the left hand side
	int left_size = size_;
	//create the new root that would join the two
	Node* new_ = new Node();
	Node* croot = root;
	int nweight = root->weight;
	while(!is_leaf(croot)){
		croot = croot->right;
		nweight += croot->weight;
	}
	new_->weight = nweight;
	new_->left = root;
	root->parent = new_;
	//copy the right side
	new_->right = this->copy(r.root, NULL);
	root = new_;
	size_ = right_size + left_size;
}

//Get a substring from index i to index j.
//Includes both the characters at index i and at index j.
//String can be one character if i and j match
//Returns true if a string was returned, and false otherwise
//Function should be written with efficient running time.
bool Rope::report(int i, int j, std::string& s) const{
	//bool that keeps track of if its valid
	if( i > j || i < 0 || j <0 || i > size_ || j >size_){
		return false;
	}
	bool breakpoint = false;
	char c;
	for(int x = i; x <= j; x++){
		breakpoint = index(x,c);
		if(breakpoint == false){
			break;
		}
		s += c;
	}
	if(breakpoint == false){
		return false;
	}
	return true;
}

//The first i characters should stay in the current rope, while a new
//Rope (rhs) should contain the remaining size_-i characters.
//A valid split should always result in two ropes of non-zero length.
//If the split would not be valid, this rope should not be changed,
//and the rhs rope should be an empty rope.
//The return value should be this rope (the "left") part of the string
//This function should move the nodes to the rhs instead of making new copies.
Rope& Rope::split(int i, Rope& rhs){
	if( i < 0 || i > size_){
		return *this;
	}
	Node* current = root;
	char c;
	while (!is_leaf(current)){
		if(i < current->weight){
			current = current->left;
		}
		else {
			i = i - current->weight;
			current = current->right;
		}
	}
	if(current->value.length() > 0){
		c = current->value[i-1];
	}
	if(i != 0){
		if(i-1 == 0){
			std::string letter(1,c);
			std::string s = "";
			bool t = report(i,current->value.length(),s);
			if(t == false){
				return *this;
			}
			else{
				Node* new_left = new Node();
				Node* new_right = new Node();
				current->left = new_left;
				new_left->parent = current;
				new_left->value = letter;
				new_left->weight = 1;
				current->weight = 1;
				current->right = new_right;
				new_right->parent = current;
				new_right->value = s;
				new_right->weight = new_right->value.length();
			}
		}
	}
	Node* p = current->parent;
	int new_weight = p->weight;
	p->parent->weight = new_weight;
	Rope x1 = Rope(current);
	p->right = NULL;
	
	while(p!= root){
		if(p->weight == new_weight && p->right){
			Node* p2 = p;
			p = p->right;
			Rope x2 = Rope(p);
			p2->right = NULL;
			x1.concat(x2);
		}
	}
	rhs = x1;
	return *this;
}
