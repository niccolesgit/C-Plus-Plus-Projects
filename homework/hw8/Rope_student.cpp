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
	assert(0 && "rope_iterator operator++ not implemented!");
}

//Point to the first Node for in-order traversal
rope_iterator Rope::begin() const{
	assert(0 && "rope_iterator begin() not implemented!");
}

Rope::Rope(){
	assert(0 && "Rope default constructor not implemented!");
}

//Should make the root = p and adjust any member variables
//This should not make a copy of the rope with root at p,
//it should just "steal" the Node*
Rope::Rope(Node* p){
	assert(0 && "Rope constructor from Node not implemented!");
}

Rope::~Rope(){
	assert(0 && "Rope destructor not implemented!");
}

Rope::Rope(const Rope& r){
	assert(0 && "Rope copy constructor not implemented!");
}

Rope& Rope::operator= (const Rope& r){
	assert(0 && "Rope assignment not implemented!");
}

//MUST BE ITERATIVE
//Get a single character at index i
bool Rope::index(int i, char& c) const{
	assert(0 && "Rope index() not implemented!");
}

//Add the other rope (r)'s string to the end of my string
void Rope::concat(const Rope& r){
	assert(0 && "Rope concat() not implemented!");
}

//Get a substring from index i to index j.
//Includes both the characters at index i and at index j.
//String can be one character if i and j match
//Returns true if a string was returned, and false otherwise
//Function should be written with efficient running time.
bool Rope::report(int i, int j, std::string& s) const{
	assert(0 && "Rope report() not implemented!");
}

//The first i characters should stay in the current rope, while a new
//Rope (rhs) should contain the remaining size_-i characters.
//A valid split should always result in two ropes of non-zero length.
//If the split would not be valid, this rope should not be changed,
//and the rhs rope should be an empty rope.
//The return value should be this rope (the "left") part of the string
//This function should move the nodes to the rhs instead of making new copies.
Rope& Rope::split(int i, Rope& rhs){
	assert(0 && "Rope split() not implemented!");
}
