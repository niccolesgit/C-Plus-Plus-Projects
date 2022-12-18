/*
You may add things to this .h file as needed. 
However keep in mind that Rope_provided.cpp will always be compiled in Submitty tests.
So you should not delete or change any methods that are implemented in Rope_provided.cpp
All your implementation should go in Rope_student.cpp
*/

#ifndef _ROPE_H
#define _ROPE_H

#include <string>
#include <vector>
#include <iostream>

class Node{
public:
	Node() : left(NULL), right(NULL), parent(NULL), weight(0) {}
	Node* left;
	Node* right;
	Node* parent;
	int weight;
	std::string value;
};

class Rope;

class rope_iterator{
public:
	rope_iterator();
	rope_iterator(Node* p);
	rope_iterator& operator++();
	rope_iterator operator++(int);
	int weight() const;
	const std::string& value() const;
	friend class Rope;
	bool operator!=(const rope_iterator& it2) const;
private:
	Node* ptr_;
};

class Rope{
public:
	Rope();
	~Rope();
	Rope(Node* p);
	Rope(const Rope& r);
	Rope& operator= (const Rope& r);

	bool index(int i, char& c) const; //Get a single character
	void concat(const Rope& r); //Add the other string to me by copy
	bool report(int i, int j, std::string& s) const; //Substring
	Rope& split(int i, Rope& rhs); //Split the string at index i into this (LHS) and a new Rope rhs
	

	//acessors
	int size() const; //gets size 
	Node* expose_root() const; //from Rope_provided
	Node* get_root(); //gets the root
	//modifiers
	void delete_rope(Node* root); //deletes the rope
	void set_root(Node* n); //sers root to the node
	void update(Node* n); //updates the node
	void leaf_weight(Node* n); //calculates the leaf's weight
	void add_to_size(int x) {size_ += x;} //adds an int to the size
	void print(std::ostream& out) const; //prints the rope
	void print_strings(std::ostream& out) const; //prints the strings
	//rope iterators
	rope_iterator begin() const;
	rope_iterator end() const;


private:
	void print(std::ostream& out, Node* head, int depth) const;
private:
	int size_;
	Node* root;
};
bool is_leaf(Node* p); 
Node* copy(Node* root); //copies root
Node* concat_no_copy(Node* n1, Node* n2); //adds string without copying
#endif
