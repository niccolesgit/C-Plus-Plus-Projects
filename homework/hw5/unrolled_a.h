//
// Borrowed from UnrolledLL, the DSLIST_handout.h as the HW handout said we could
//

#ifndef HW5_UNROLLED_H
#define HW5_UNROLLED_H
#include <iostream>
#include <cassert>
#include <string>
const int NUM_ELEMENTS_PER_NODE = 6;
using namespace std;

// -----------------------------------------------------------------
// NODE CLASS
template <class T>
class Node {
public:
    Node(): num_elements(0), next_(nullptr) , prev_(nullptr) {    }

    // REPRESENTATION
    unsigned int num_elements;
    T elements[NUM_ELEMENTS_PER_NODE];
    Node<T>* next_;
    Node<T>* prev_;
};

// A "forward declaration" of this class is needed
template <class T> class UnrolledLL;

// -----------------------------------------------------------------
// UNROLLED LIST ITERATOR
template <class T>
class list_iterator {
public:
    // default constructor, copy constructor, assignment operator, & destructor
    list_iterator() : ptr_(nullptr), offset(0){}
    list_iterator(Node<T>* p, unsigned int enter_offset) : ptr_(p), offset(enter_offset) {}
    list_iterator(const list_iterator<T>& old) : ptr_(old.ptr_), offset(old.offset) {}
    list_iterator<T>& operator=(const list_iterator<T>& old) {
        ptr_ = old.ptr_;
        offset = old.offset;
        return *this;
    }

    ~list_iterator() {} //not used, but implemented for full completion

    // dereferencing operator, gives access to the value at the pointer
    T& operator*()  { return ptr_->elements[offset];  }   //POINTS TO SPECIFIC VALUE

    // increment & decrement operators
    list_iterator<T>& operator++() { // pre-increment, e.g., ++iter

        if (offset == ptr_ -> num_elements - 1){
            ptr_ = ptr_->next_;
            offset = 0;
        }
        else{
            offset++;
        }

        return *this;
    }

    list_iterator<T> operator++(int) { // post-increment, e.g., iter++
        list_iterator<T> temp(*this);

        if (offset == ptr_ -> num_elements - 1){
            ptr_ = ptr_-> next_;
            offset = 0;
        }
        else{
            offset++;
        }

        return temp;
    }
    list_iterator<T>& operator--() { // pre-decrement, e.g., --iter

        if (offset == 0){
            ptr_ = ptr_->prev_;
            offset = ptr_ -> num_elements -1;
        }
        else{
            offset--;
        }

        return *this;
    }
    list_iterator<T> operator--(int) { // post-decrement, e.g., iter--
        list_iterator<T> temp(*this);
        if (offset == 0){
            ptr_ = ptr_->prev_;
            offset = ptr_ -> num_elements -1;
        }
        else{
            offset--;
        }
        return temp;
    }
    // the UnrolledLL class needs access to the private ptr_ member variable-- not inheritance
    friend class UnrolledLL<T>;

    // Comparison operators
    bool operator==(const list_iterator<T>& r) const {
        return (ptr_ == r.ptr_) && (offset == r.offset);
    }

    bool operator!=(const list_iterator<T>& r) const {
        return (ptr_ != r.ptr_) || (offset != r.offset);
    }

private:
    // REPRESENTATION
    Node<T>* ptr_;    // ptr to node in the list
    unsigned int offset; // like an index for the array within the node

};

// -----------------------------------------------------------------
// UNROLLED LIST CLASS DECLARATION
// Note that it explicitly maintains the size of the list.
template <class T>
class UnrolledLL {
public:
    // default constructor, copy constructor, assignment operator, & destructor
    UnrolledLL() : head_(nullptr), tail_(nullptr), size_(0) {}
    UnrolledLL( UnrolledLL<T>& old) { this->copy_list(old); }
    UnrolledLL& operator= (const UnrolledLL<T>& old);
    ~UnrolledLL() { this->destroy_list(); }
 
    // simple accessors & modifiers
    unsigned int size() const { return size_; }
    bool empty() const { return head_ == nullptr; }
    void clear() { this->destroy_list(); }

    // read/write access to contents
    const T& front() const { return head_ -> elements [0];  }
    T& front() { return head_-> elements [0]; }
    const T& back() const { return tail_-> elements[tail_-> num_elements-1]; }
    T& back() { return tail_-> elements[tail_-> num_elements-1]; }

    // modify the linked list structure
    void push_front(const T& v);
    void pop_front();
    void push_back(const T& v);
    void pop_back();

    void print(ostream &cout) const;

    typedef list_iterator<T> iterator; // THE BEGIN SHOULD POINT TO FRONT
    iterator erase(iterator itr);
    iterator insert(iterator itr, const T& v);
    iterator begin() { return iterator(head_, 0); }
    iterator end() { return iterator(); }

private:
    // private helper functions
    void copy_list( UnrolledLL<T>& old);
    void destroy_list();

    //REPRESENTATION
    Node<T>* head_;
    Node<T>* tail_;
    unsigned int size_;
};

// -----------------------------------------------------------------
// UNROLLED LIST CLASS IMPLEMENTATION
template <class T> UnrolledLL<T>& UnrolledLL<T>::operator= (const UnrolledLL<T>& old) {
    // check for self-assignment
    if (&old != this) {
        this->destroy_list();
        this->copy_list(old);
    }
    return *this;
}


// Function: push_front(const T& v) -> parameter: object of type T that is to be inserted as the first
//                                                element of the UnrolledLL.
// Return type: void
/* Purpose: to add an element to the front of the unrolled list aka the head. If the UnrolledLL is empty
 *          it creates a new node, points the head and tail to this new pointer and adds the element.
 *          If it is not empty but there are spaces available in the node it reallocates the elements in
 *          the node one over to the right and then places the first element of the node to v. Else, if
 *          the node is full it creates a new node, makes it the new head and puts v as the first value. */

template <class T> void UnrolledLL<T>::push_front(const T& v) {
    ++size_;
    if (empty()) {
        Node<T>* node = new Node<T>;
        head_ = node;
        tail_ = node;
        node -> elements[0] = v;
        node -> num_elements++;
    }
    else if (head_-> num_elements < NUM_ELEMENTS_PER_NODE){

        for (unsigned int i = head_ -> num_elements ; i > 0; i--){ //start at last element
            head_ -> elements[i] = head_ -> elements[i-1];
        }
        head_->elements[1] = head_->elements[0];
        head_ -> elements[0] = v;
        head_ -> num_elements++;
    }
    else{
        Node<T>* node = new Node<T>;
        head_ -> prev_ = node;
        node -> next_ = head_;
        head_ = node;
        node -> elements[0] = v;
        node -> num_elements++;
    }
}


// Function: pop_front()
// Return type: void
/* Purpose: to add an element to the back of the unrolled list aka the tail. If there is only one element
 *          in the node, it checks whether there is also only one node or not. If there is only one node
 *          it uses the destroy_list() function to get rid of the whole node because there cannot be any
 *          empty nodes if there are no elements to be stored. If there are more nodes, the head pointer is
 *          pointed to the next node, the now previous node is deleted and the prev pointer of this new
 *          head is set to nullptr.                                                                             */

template <class T> void UnrolledLL<T>::pop_front() {
    --size_;

    if (head_-> num_elements == 1) {
        if (head_ == tail_){ //one node
            destroy_list(); //destroys all nodes
        }
        else{
            head_ = head_ -> next_;
            delete head_ -> prev_;
            head_ -> prev_ = nullptr;
        }
    } 
    else {
        for (unsigned int i = 0; i < head_->num_elements - 1; i++) { //start at last element
            head_->elements[i] = head_->elements[i + 1];
        }
        head_->num_elements--;
    }
}


// Function: push_back(const T& v) -> parameter: object of type T that is to be inserted as the last
//                                               element of the UnrolledLL.
// Return type: void
/* Purpose: to add an element to the back of the unrolled list aka the tail. If the list is empty it creates
 *          a new node and initializes it. If there are spaces available in the node it just adds v to the last
 *          index of the elements array of the node. Lastly, if there are no more spaces in the node, it creates
 *          a new node, changes the tail pointer so that its next now points to this new node created, points
 *          the prev of this new node to the tail, and finally points the tail to this new pointer and it adds v
 *          as the first element of this new node.
 *
 * */

template <class T> void UnrolledLL<T>::push_back(const T& v) {
    ++size_;

    if (empty()) {
        Node<T>* node = new Node<T>;
        head_ = node;
        tail_ = node;
        node -> elements[0]=v;
        node -> num_elements++;
    }
    else if (tail_-> num_elements < NUM_ELEMENTS_PER_NODE){
        tail_ -> elements[tail_ -> num_elements] = v;
        tail_ -> num_elements++;
    }
    else{
        Node<T>* node = new Node<T>;
        tail_ -> next_ = node;
        node -> prev_ = tail_;
        tail_ = node;
        node -> elements[tail_ -> num_elements] = v;
        node -> num_elements++;
    }
}


// Function: pop_back()
// Return type: void
/* Purpose: to delete the last element of the unrolled list (the last element of the last node aka tail). If there
 *          is more than one element in the tail, the number of elements of tail is decreased by 1 (so that the last
 *          element is basically out of bounds and cannot be accessed, in a sense erasing it). If there is only 1
 *          element in the last node aka tail, it creates an iterator that points to the last element of tail (the
 *          only element) and it uses the erase function to delete it and properly dereference pointers.             */

template <class T> void UnrolledLL<T>::pop_back() {
    if (tail_-> num_elements > 1){
        tail_ -> num_elements--;
        --size_;
    }
    else{
        list_iterator<T>itr(tail_, tail_-> num_elements-1);
        erase(itr);
    }
}


// Function: print(ostream& cout) -> parameter: ostream object to be able to output the content of the nodes
//                                              to the screen.
// Return type: void
/* Purpose: to provide a visual representation of the inside of the unrolled list. Prints the total size of
            the UnrolledLL as well as the size and contents of each node. It does this by creating a temporary
            node pointer that goes through every single node and printing the elements on the elements array
            inside each node.                                                                                   */

template <class T> void UnrolledLL<T>::print(ostream& cout) const{
    cout << "UnrolledLL, size: " + to_string(size_) << endl;
    Node<T>* temp = head_;

    while(temp != nullptr){
        cout<< "node:["<< temp ->num_elements <<"]";
        for (unsigned int i = 0; i < temp->num_elements ; i++) {
            cout << " " << temp->elements[i];
        }
        cout<<endl;
        temp = temp->next_;
    }

}

// Function: erase(iterator itr) -> parameter: itr that points to a specific node and the index the
//                                             object to be erased.
// Return type: iterator to a node, which node it points to depends on the conditions of the initial itr (usually the
//              next element within the same node or the first element of the next node)
/* Purpose: erases a values at a specific location within a node. This location and node are defined by the itr
            parameter. If there is only one element in one node, it destroys the node using destroy_list() and returns
            the end() iterator. If there is only one element in the node, but there are more nodes before or after it
            updates the pointers to the head, tail, next, and prev, accordingly as to not leave any nodes "in the air",
            creates a new iterator that points to the next node and deletes the current iterator which held the one single
            object. In the case that there is more than one element in the node it reallocates all elements within the node
            from index offset onward one spot to the left, ultimately overwriting the value to be erased, finally updating
            the number of elements of said node.                                                                                */

template <class T> typename UnrolledLL<T>::iterator UnrolledLL<T>::erase(iterator itr) {
    --size_;

    if (itr.ptr_-> num_elements == 1) { // exactly one element in the node
        if (head_ == tail_){ // if there is only one node
            destroy_list();
            return end();
        }
        else { // >1 node
            if(itr.ptr_ != head_ ){
                itr.ptr_ -> prev_ -> next_ = itr.ptr_ -> next_;
            }
            else{
                head_ = itr.ptr_ -> next_;
            }
            if(itr.ptr_ != tail_){
                itr.ptr_ -> next_ -> prev_ = itr.ptr_ -> prev_ ;
            }
            else{
                tail_ = itr.ptr_-> prev_;
            }

            list_iterator<T> newItr(itr.ptr_ -> next_, 0);
            delete itr.ptr_;
            return newItr;
        }
    }
    else { // more than 1 element in the node
        for (unsigned int i = itr.offset; i < itr.ptr_-> num_elements-1; i++) {
            itr.ptr_->elements[i] = itr.ptr_->elements[i + 1];
        }

        itr.ptr_ -> num_elements--;

        if (itr.offset == itr.ptr_->num_elements){
            itr.ptr_ = itr.ptr_ -> next_;
            itr.offset = 0;
        }

        return itr;
    }
}


// Function: insert(iterator itr, const T& v) -> parameters: iterator itr points to a specific node and
//                                                           index where an object v is inserted. v is the
//                                                           object to be inserted.
// Return type: typename, which is an iterator to the node where you are trying to insert an object
/* Purpose: adds an object of type T, v, into a certain space specified by the itr entered, which contains
            a pointer to the node necessary and a value of where in the node elements array to put it.
            If there is space available in the node, it reallocates all the elements from that space onward
            one space to the right and then inserts v into index offset. Else, if there are no more spaces in
            the node the itr is pointing to, a new node is created, the necessary pointers are updated, the
            elements starting at offset (where v is to be inserted) are reallocated to the new node, and v
            is inserted as the last value (which is now index offset) of the original node.                     */

template <class T> typename UnrolledLL<T>::iterator UnrolledLL<T>::insert(iterator itr, const T& v) {
    ++size_;
    if (itr.ptr_ -> num_elements < NUM_ELEMENTS_PER_NODE){ // if there are available spaces in the node
        for (unsigned int i= itr.ptr_ -> num_elements; i > itr.offset; i--){
            itr.ptr_ -> elements[i] = itr.ptr_ -> elements[i-1];
        }
        itr.ptr_ -> elements[itr.offset] = v;
        itr.ptr_ -> num_elements++;
        return itr;
    }

    else{ // no more spaces in the node
        Node<T>* node2 = new Node<T>;
        node2 -> next_ = itr.ptr_ -> next_;
        itr.ptr_ -> next_ = node2;
        node2 -> prev_ = itr.ptr_;
        if (node2 -> next_ != nullptr){
            node2 -> next_ -> prev_ = node2;
        }
        else{
            tail_ = node2;
        }

        for (unsigned int i = itr.offset; i < itr.ptr_->num_elements ; i++){
            node2 -> elements[i-itr.offset] = itr.ptr_->elements[i];
            node2 -> num_elements++;
        }
        itr.ptr_ -> elements[itr.offset] = v;
        itr.ptr_-> num_elements = itr.offset + 1;
        return itr;
    }
}


// Function: copy_list( UnrolledLL<T>& old) -> parameter: unrolled list to be copied
// Return type: void
/* Purpose: copies the "old" list to the list that is calling this function. It uses
            the push_back function in a loop to copy every single value in the old list
            to this list, thus ALL of the values are copied in the same order, but not
            in the same permutation, meaning that if there were any empty spaces within
            a node in the old unrolled list, those spaces will not be empty in this one.
            Example: (In this case the max number of elements per node is 3)
                "old" aka list I'm trying to copy:
                node 1 | size = 2: 1, 2
                node 2 | size = 2: 3, , 5
                node 3 | size = 2: 6, 7

                copy:
                node 1 | size = 3: 1, 2, 3
                node 2 | size = 3: 5, 6, 7                                                     */

template <class T> void UnrolledLL<T>::copy_list( UnrolledLL<T>& old) {
    size_ = 0;
    head_= nullptr;
    tail_= nullptr;
    for (UnrolledLL<int>::iterator itr = old.begin(); itr != old.end(); itr++){
        push_back(*itr);
    }
}

// Function: destroy_list()
// Return type: void
// Purpose: 'destroys' all nodes. When called deletes the memory allocated for all existing nodes, sets
//          the head and tail to nullptr and size to 0. Uses the pointers of the UnrolledLL as well as
//          the next and prev pointers within the nodes to make sure to delete every single one of them.

template <class T> void UnrolledLL<T>::destroy_list() {
    while (head_ != tail_){
        head_ = head_ -> next_;
        delete(head_ -> prev_);
    }
    delete(head_);
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
}


template <class T> bool operator== (UnrolledLL<T>& left, UnrolledLL<T>& right) {
    if (left.size() != right.size()) return false;
    typename UnrolledLL<T>::iterator left_itr = left.begin();
    typename UnrolledLL<T>::iterator right_itr = right.begin();
    // walk over both lists, looking for a mismatched value
    while (left_itr != left.end()) {
        if (*left_itr != *right_itr) return false;
        left_itr++; right_itr++;
    }
    return true;
}


template <class T> bool operator!= (UnrolledLL<T>& left, UnrolledLL<T>& right){
    return !(left==right);
}


#endif //HW5_UNROLLED_H
